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

import static io.github.bkaradzic.bgfx.BgfxUtil.*;


/**
 * Java FFM bindings for the bgfx C99 API.
 */
@NullUnmarked
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
		"bgfx_set_view_rect", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_FLOAT, ValueLayout.JAVA_FLOAT));
	static final MethodHandle MH_SET_VIEW_RECT_RATIO = downcall(
		"bgfx_set_view_rect_ratio", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_VIEW_SCISSOR = downcall(
		"bgfx_set_view_scissor", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_SET_VIEW_DEPTH_BIAS = downcall(
		"bgfx_set_view_depth_bias", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ValueLayout.JAVA_INT, ValueLayout.JAVA_FLOAT, ValueLayout.JAVA_FLOAT));
	static final MethodHandle MH_SET_VIEW_SAMPLE_MASK = downcall(
		"bgfx_set_view_sample_mask", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ValueLayout.JAVA_INT));
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
	static final MethodHandle MH_ENCODER_SET_SAMPLE_MASK = downcall(
		"bgfx_encoder_set_sample_mask", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_SET_SCISSOR = downcall(
		"bgfx_encoder_set_scissor", FunctionDescriptor.of(ValueLayout.JAVA_SHORT, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_ENCODER_SET_SCISSOR_CACHED = downcall(
		"bgfx_encoder_set_scissor_cached", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_ENCODER_SET_DEPTH_CONTROL = downcall(
		"bgfx_encoder_set_depth_control", FunctionDescriptor.of(ValueLayout.JAVA_SHORT, ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.JAVA_FLOAT, ValueLayout.JAVA_FLOAT, ValueLayout.JAVA_BOOLEAN));
	static final MethodHandle MH_ENCODER_SET_DEPTH_CONTROL_CACHED = downcall(
		"bgfx_encoder_set_depth_control_cached", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_ENCODER_SET_TRANSFORM = downcall(
		"bgfx_encoder_set_transform", FunctionDescriptor.of(ValueLayout.JAVA_INT, ValueLayout.ADDRESS, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_ENCODER_SET_TRANSFORM_CACHED = downcall(
		"bgfx_encoder_set_transform_cached", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_ENCODER_ALLOC_TRANSFORM = downcall(
		"bgfx_encoder_alloc_transform", FunctionDescriptor.of(ValueLayout.JAVA_INT, ValueLayout.ADDRESS, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_ENCODER_SET_UNIFORM = downcall(
		"bgfx_encoder_set_uniform", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, UniformHandle.LAYOUT, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_ENCODER_SET_UNIFORM_REF = downcall(
		"bgfx_encoder_set_uniform_ref", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, UniformHandle.LAYOUT, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
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
		"bgfx_encoder_set_texture_view", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_BYTE, UniformHandle.LAYOUT, TextureHandle.LAYOUT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_INT, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_BYTE));
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
		"bgfx_encoder_set_compute_index_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_BYTE, IndexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_SET_COMPUTE_VERTEX_BUFFER = downcall(
		"bgfx_encoder_set_compute_vertex_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_BYTE, VertexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_SET_COMPUTE_DYNAMIC_INDEX_BUFFER = downcall(
		"bgfx_encoder_set_compute_dynamic_index_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_BYTE, DynamicIndexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_SET_COMPUTE_DYNAMIC_VERTEX_BUFFER = downcall(
		"bgfx_encoder_set_compute_dynamic_vertex_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_BYTE, DynamicVertexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
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
	static final MethodHandle MH_SET_SAMPLE_MASK = downcall(
		"bgfx_set_sample_mask", FunctionDescriptor.ofVoid(ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_SCISSOR = downcall(
		"bgfx_set_scissor", FunctionDescriptor.of(ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_SET_SCISSOR_CACHED = downcall(
		"bgfx_set_scissor_cached", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_SET_DEPTH_CONTROL = downcall(
		"bgfx_set_depth_control", FunctionDescriptor.of(ValueLayout.JAVA_SHORT, ValueLayout.JAVA_INT, ValueLayout.JAVA_FLOAT, ValueLayout.JAVA_FLOAT, ValueLayout.JAVA_BOOLEAN));
	static final MethodHandle MH_SET_DEPTH_CONTROL_CACHED = downcall(
		"bgfx_set_depth_control_cached", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_SET_TRANSFORM = downcall(
		"bgfx_set_transform", FunctionDescriptor.of(ValueLayout.JAVA_INT, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_SET_TRANSFORM_CACHED = downcall(
		"bgfx_set_transform_cached", FunctionDescriptor.ofVoid(ValueLayout.JAVA_INT, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_ALLOC_TRANSFORM = downcall(
		"bgfx_alloc_transform", FunctionDescriptor.of(ValueLayout.JAVA_INT, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_SET_UNIFORM = downcall(
		"bgfx_set_uniform", FunctionDescriptor.ofVoid(UniformHandle.LAYOUT, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_SET_UNIFORM_REF = downcall(
		"bgfx_set_uniform_ref", FunctionDescriptor.ofVoid(UniformHandle.LAYOUT, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
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
		"bgfx_set_texture_view", FunctionDescriptor.ofVoid(ValueLayout.JAVA_BYTE, UniformHandle.LAYOUT, TextureHandle.LAYOUT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_INT, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_BYTE));
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
		"bgfx_set_compute_index_buffer", FunctionDescriptor.ofVoid(ValueLayout.JAVA_BYTE, IndexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_COMPUTE_VERTEX_BUFFER = downcall(
		"bgfx_set_compute_vertex_buffer", FunctionDescriptor.ofVoid(ValueLayout.JAVA_BYTE, VertexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_COMPUTE_DYNAMIC_INDEX_BUFFER = downcall(
		"bgfx_set_compute_dynamic_index_buffer", FunctionDescriptor.ofVoid(ValueLayout.JAVA_BYTE, DynamicIndexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_COMPUTE_DYNAMIC_VERTEX_BUFFER = downcall(
		"bgfx_set_compute_dynamic_vertex_buffer", FunctionDescriptor.ofVoid(ValueLayout.JAVA_BYTE, DynamicVertexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
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
	 * @return Frame number when the result will be available. See: {@code frame}. If the device is lost before then, {@code CallbackI.fatal} reports {@code Fatal.DEVICE_LOST} in that frame, and {@code _data} is left untouched.
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
	 * @param _hasMips Indicates that texture contains full mip-map chain. Ignored when {@code BGFX_TEXTURE_MIP_COUNT} is set in _flags.
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
	 * @param _hasMips Indicates that texture contains full mip-map chain. Ignored when {@code BGFX_TEXTURE_MIP_COUNT} is set in _flags.
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
	 * @param _hasMips Indicates that texture contains full mip-map chain. Ignored when {@code BGFX_TEXTURE_MIP_COUNT} is set in _flags.
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
	 * @param _hasMips Indicates that texture contains full mip-map chain. Ignored when {@code BGFX_TEXTURE_MIP_COUNT} is set in _flags.
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
	 * @return Frame number when the result will be available. See: {@code frame}. If the device is lost before then, {@code CallbackI.fatal} reports {@code Fatal.DEVICE_LOST} in that frame, and {@code _data} is left untouched.
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
	 *       "nnnnc &lt;view name&gt;"
	 *        ^   ^ ^
	 *        |   +--- compute (C)
	 *        +------- view id
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
	 * @param _minDepth Viewport minimum depth (maps clip-space z=0).
	 * @param _maxDepth Viewport maximum depth (maps clip-space z=1).
	 */
	public static void setViewRect(short _id, short _x, short _y, @Unsigned short _width, @Unsigned short _height, float _minDepth, float _maxDepth) {
		try {
			MH_SET_VIEW_RECT.invokeExact(_id, _x, _y, _width, _height, _minDepth, _maxDepth);
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
	 * Set view depth bias. Applies to all draws in the view unless overridden per-draw
	 * with {@code setDepthControl}.
	 * @param _id View id.
	 * @param _constant Constant depth bias.
	 * @param _slopeScale Slope-scaled depth bias.
	 * @param _clamp Depth bias clamp.
	 */
	public static void setViewDepthBias(short _id, int _constant, float _slopeScale, float _clamp) {
		try {
			MH_SET_VIEW_DEPTH_BIAS.invokeExact(_id, _constant, _slopeScale, _clamp);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set view multisample coverage mask. Combined with the per-draw mask set by
	 * {@code setSampleMask}, so a draw can narrow the view's mask but not widen it.
	 * @param _id View id.
	 * @param _mask Sample coverage mask.
	 */
	public static void setViewSampleMask(short _id, @Unsigned int _mask) {
		try {
			MH_SET_VIEW_SAMPLE_MASK.invokeExact(_id, _mask);
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
	 * clear color palette. Frame buffer attachment with palette index set to
	 * {@code UINT8_MAX} is not cleared.
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
	 * Post submit view reordering. A view in {@code _order} that currently renders
	 * outside the remapped range swaps places with the view it displaces, so the
	 * order stays a permutation of all view ids.
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
	 * Reset all view settings to default, including the view name.
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
	 * @param _filePath Will be passed to {@code CallbackI.screenShot} callback. If the device is lost before the screenshot is taken, {@code CallbackI.fatal} reports {@code Fatal.DEVICE_LOST} in that frame and {@code screenShot} is not called for this request.
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
	 * Set multisample coverage mask for draw primitive. Samples whose bit is clear
	 * in the mask are never written, regardless of the coverage the rasterizer
	 * computes. Only has an effect when rendering to a multisampled target.
	 * @param _mask Sample coverage mask.
	 */
	public static void setSampleMask(@Unsigned int _mask) {
		try {
			MH_SET_SAMPLE_MASK.invokeExact(_mask);
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
	 * Set depth control (depth bias and depth clip) for draw primitive. Overrides the
	 * view depth bias for this draw.
	 * @param _constant Constant depth bias.
	 * @param _slopeScale Slope-scaled depth bias.
	 * @param _clamp Depth bias clamp.
	 * @param _depthClamp Disable depth clipping and clamp NDC depth to the [0,1] range instead.
	 * @return Depth control cache index.
	 */
	public static @Unsigned short setDepthControl(int _constant, float _slopeScale, float _clamp, boolean _depthClamp) {
		try {
			return (@Unsigned short) MH_SET_DEPTH_CONTROL.invokeExact(_constant, _slopeScale, _clamp, _depthClamp);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set depth control from depth-control cache for draw primitive.
	 * @param _cache Index in depth control cache.
	 */
	public static void setDepthControlCached(@Unsigned short _cache) {
		try {
			MH_SET_DEPTH_CONTROL_CACHED.invokeExact(_cache);
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
	 * Set shader uniform parameter by reference. Unlike {@code setUniform}, the data
	 * is not copied immediately; the renderer reads it from {@code _value} at frame render
	 * time. The pointer must remain valid and unchanged until the frame is rendered
	 * (up to two {@code frame} calls with multithreaded submission).
	 * @param _handle Uniform.
	 * @param _value Pointer to uniform data. Must stay valid until the frame is rendered.
	 * @param _num Number of elements. Passing {@code UINT16_MAX} will use the _num passed on uniform creation.
	 */
	public static void setUniformRef(UniformHandle _handle, MemorySegment _value, @Unsigned short _num) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_UNIFORM_REF.invokeExact(_handle.allocate(arena), address(_value), _num);
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
	 * @param _lodMin Lowest (most detailed) level of detail the sampler may use, in quarter-mip steps, relative to {@code _firstMip}.
	 * @param _lodMax Highest (least detailed) level of detail the sampler may use, in quarter-mip steps, relative to {@code _firstMip}. {@code UINT8_MAX} leaves it unclamped.
	 */
	public static void setTextureView(@Unsigned byte _stage, UniformHandle _sampler, TextureHandle _handle, @Unsigned short _firstLayer, @Unsigned short _numLayers, @Unsigned byte _firstMip, @Unsigned byte _numMips, @Unsigned int _flags, @Unsigned byte _lodMin, @Unsigned byte _lodMax) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_TEXTURE_VIEW.invokeExact(_stage, _sampler.allocate(arena), _handle.allocate(arena), _firstLayer, _numLayers, _firstMip, _numMips, _flags, _lodMin, _lodMax);
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
	public static void submit(short _id, ProgramHandle _program, @Unsigned int _depth, @Unsigned int _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SUBMIT.invokeExact(_id, _program.allocate(arena), _depth, NativeObject.toUnsignedByte(_flags));
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
	public static void submitOcclusionQuery(short _id, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, @Unsigned int _depth, @Unsigned int _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SUBMIT_OCCLUSION_QUERY.invokeExact(_id, _program.allocate(arena), _occlusionQuery.allocate(arena), _depth, NativeObject.toUnsignedByte(_flags));
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
	public static void submitIndirect(short _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, @Unsigned int _start, @Unsigned int _num, @Unsigned int _depth, @Unsigned int _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SUBMIT_INDIRECT.invokeExact(_id, _program.allocate(arena), _indirectHandle.allocate(arena), _start, _num, _depth, NativeObject.toUnsignedByte(_flags));
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
	public static void submitIndirectCount(short _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, @Unsigned int _start, IndexBufferHandle _numHandle, @Unsigned int _numIndex, @Unsigned int _numMax, @Unsigned int _depth, @Unsigned int _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SUBMIT_INDIRECT_COUNT.invokeExact(_id, _program.allocate(arena), _indirectHandle.allocate(arena), _start, _numHandle.allocate(arena), _numIndex, _numMax, _depth, NativeObject.toUnsignedByte(_flags));
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
	 * @param _offset Byte offset the shader's view of the buffer starts at. Must be a multiple of 256 bytes.
	 * @param _size Bytes bound from the offset, {@code UINT32_MAX} for the rest of the buffer.
	 */
	public static void setComputeIndexBuffer(@Unsigned byte _stage, IndexBufferHandle _handle, Access _access, @Unsigned int _offset, @Unsigned int _size) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_COMPUTE_INDEX_BUFFER.invokeExact(_stage, _handle.allocate(arena), _access.ordinal(), _offset, _size);
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
	 * @param _offset Byte offset the shader's view of the buffer starts at. Must be a multiple of 256 bytes.
	 * @param _size Bytes bound from the offset, {@code UINT32_MAX} for the rest of the buffer.
	 */
	public static void setComputeVertexBuffer(@Unsigned byte _stage, VertexBufferHandle _handle, Access _access, @Unsigned int _offset, @Unsigned int _size) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_COMPUTE_VERTEX_BUFFER.invokeExact(_stage, _handle.allocate(arena), _access.ordinal(), _offset, _size);
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
	 * @param _offset Byte offset the shader's view of the buffer starts at. Must be a multiple of 256 bytes.
	 * @param _size Bytes bound from the offset, {@code UINT32_MAX} for the rest of the buffer.
	 */
	public static void setComputeDynamicIndexBuffer(@Unsigned byte _stage, DynamicIndexBufferHandle _handle, Access _access, @Unsigned int _offset, @Unsigned int _size) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_COMPUTE_DYNAMIC_INDEX_BUFFER.invokeExact(_stage, _handle.allocate(arena), _access.ordinal(), _offset, _size);
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
	 * @param _offset Byte offset the shader's view of the buffer starts at. Must be a multiple of 256 bytes.
	 * @param _size Bytes bound from the offset, {@code UINT32_MAX} for the rest of the buffer.
	 */
	public static void setComputeDynamicVertexBuffer(@Unsigned byte _stage, DynamicVertexBufferHandle _handle, Access _access, @Unsigned int _offset, @Unsigned int _size) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_COMPUTE_DYNAMIC_VERTEX_BUFFER.invokeExact(_stage, _handle.allocate(arena), _access.ordinal(), _offset, _size);
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
	public static void dispatch(short _id, ProgramHandle _program, @Unsigned int _numX, @Unsigned int _numY, @Unsigned int _numZ, @Unsigned int _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_DISPATCH.invokeExact(_id, _program.allocate(arena), _numX, _numY, _numZ, NativeObject.toUnsignedByte(_flags));
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
	public static void dispatchIndirect(short _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, @Unsigned int _start, @Unsigned int _num, @Unsigned int _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_DISPATCH_INDIRECT.invokeExact(_id, _program.allocate(arena), _indirectHandle.allocate(arena), _start, _num, NativeObject.toUnsignedByte(_flags));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Discard previously set state for draw or compute call.
	 * @param _flags Draw/compute states to discard.
	 */
	public static void discard(@Unsigned int _flags) {
		try {
			MH_DISCARD.invokeExact(NativeObject.toUnsignedByte(_flags));
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


	/**
	 * Memory release callback.
	 */
	@NullMarked
	@FunctionalInterface
	@SuppressWarnings("restricted")
	public interface ReleaseFn {
		/**
		 * Native callback function descriptor.
		 */
		FunctionDescriptor DESCRIPTOR = FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.ADDRESS);
		/**
		 * Bound callback target used to create upcall stubs.
		 */
		MethodHandle TARGET = upcallTarget(
			ReleaseFn.class, "invoke", MethodType.methodType(
				void.class, MemorySegment.class, MemorySegment.class));

		/**
		 * Invoked by native bgfx code. Implementations must not throw.
		 * @param _ptr Pointer to allocated data.
		 * @param _userData User defined data if needed.
		 */
		void invoke(MemorySegment _ptr, MemorySegment _userData);

		/**
		 * Creates an upcall stub for this callback.
		 * The arena must remain alive until bgfx can no longer invoke the callback.
		 * @param arena a caller-owned, long-lived arena
		 * @return the native function pointer
		 */
		default MemorySegment upcall(Arena arena) {
			Objects.requireNonNull(arena, "arena");
			return LINKER.upcallStub(TARGET.bindTo(this), DESCRIPTOR, arena);
		}
	}

	/**
	 * Constants for State flags.
	 */
	@NullMarked
	public static final class StateFlags {
		private StateFlags() {
		}
		/**
		 * Enable R write.
		 */
		public static final long WriteR = 0x0000000000000001L;

		/**
		 * Enable G write.
		 */
		public static final long WriteG = 0x0000000000000002L;

		/**
		 * Enable B write.
		 */
		public static final long WriteB = 0x0000000000000004L;

		/**
		 * Enable alpha write.
		 */
		public static final long WriteA = 0x0000000000000008L;

		/**
		 * Enable depth write.
		 */
		public static final long WriteZ = 0x0000004000000000L;

		/**
		 * Enable RGB write.
		 */
		public static final long WriteRgb = 0x0000000000000007L;

		/**
		 * Write all channels mask.
		 */
		public static final long WriteMask = 0x000000400000000fL;

		/**
		 * Enable depth test, less.
		 */
		public static final long DepthTestLess = 0x0000000000000010L;

		/**
		 * Enable depth test, less or equal.
		 */
		public static final long DepthTestLequal = 0x0000000000000020L;

		/**
		 * Enable depth test, equal.
		 */
		public static final long DepthTestEqual = 0x0000000000000030L;

		/**
		 * Enable depth test, greater or equal.
		 */
		public static final long DepthTestGequal = 0x0000000000000040L;

		/**
		 * Enable depth test, greater.
		 */
		public static final long DepthTestGreater = 0x0000000000000050L;

		/**
		 * Enable depth test, not equal.
		 */
		public static final long DepthTestNotequal = 0x0000000000000060L;

		/**
		 * Enable depth test, never.
		 */
		public static final long DepthTestNever = 0x0000000000000070L;

		/**
		 * Enable depth test, always.
		 */
		public static final long DepthTestAlways = 0x0000000000000080L;

		/**
		 * State flag value {@code DepthTestShift}.
		 */
		public static final long DepthTestShift = 4;

		/**
		 * State flag value {@code DepthTestMask}.
		 */
		public static final long DepthTestMask = 0x00000000000000f0L;

		/**
		 * 0, 0, 0, 0
		 */
		public static final long BlendZero = 0x0000000000001000L;

		/**
		 * 1, 1, 1, 1
		 */
		public static final long BlendOne = 0x0000000000002000L;

		/**
		 * Rs, Gs, Bs, As
		 */
		public static final long BlendSrcColor = 0x0000000000003000L;

		/**
		 * 1-Rs, 1-Gs, 1-Bs, 1-As
		 */
		public static final long BlendInvSrcColor = 0x0000000000004000L;

		/**
		 * As, As, As, As
		 */
		public static final long BlendSrcAlpha = 0x0000000000005000L;

		/**
		 * 1-As, 1-As, 1-As, 1-As
		 */
		public static final long BlendInvSrcAlpha = 0x0000000000006000L;

		/**
		 * Ad, Ad, Ad, Ad
		 */
		public static final long BlendDstAlpha = 0x0000000000007000L;

		/**
		 * 1-Ad, 1-Ad, 1-Ad ,1-Ad
		 */
		public static final long BlendInvDstAlpha = 0x0000000000008000L;

		/**
		 * Rd, Gd, Bd, Ad
		 */
		public static final long BlendDstColor = 0x0000000000009000L;

		/**
		 * 1-Rd, 1-Gd, 1-Bd, 1-Ad
		 */
		public static final long BlendInvDstColor = 0x000000000000a000L;

		/**
		 * f, f, f, 1; f = min(As, 1-Ad)
		 */
		public static final long BlendSrcAlphaSat = 0x000000000000b000L;

		/**
		 * Blend factor
		 */
		public static final long BlendFactor = 0x000000000000c000L;

		/**
		 * 1-Blend factor
		 */
		public static final long BlendInvFactor = 0x000000000000d000L;

		/**
		 * State flag value {@code BlendShift}.
		 */
		public static final long BlendShift = 12;

		/**
		 * State flag value {@code BlendMask}.
		 */
		public static final long BlendMask = 0x000000000ffff000L;

		/**
		 * Blend add: src + dst.
		 */
		public static final long BlendEquationAdd = 0x0000000000000000L;

		/**
		 * Blend subtract: src - dst.
		 */
		public static final long BlendEquationSub = 0x0000000010000000L;

		/**
		 * Blend reverse subtract: dst - src.
		 */
		public static final long BlendEquationRevsub = 0x0000000020000000L;

		/**
		 * Blend min: min(src, dst).
		 */
		public static final long BlendEquationMin = 0x0000000030000000L;

		/**
		 * Blend max: max(src, dst).
		 */
		public static final long BlendEquationMax = 0x0000000040000000L;

		/**
		 * State flag value {@code BlendEquationShift}.
		 */
		public static final long BlendEquationShift = 28;

		/**
		 * State flag value {@code BlendEquationMask}.
		 */
		public static final long BlendEquationMask = 0x00000003f0000000L;

		/**
		 * Cull clockwise triangles.
		 */
		public static final long CullCw = 0x0000001000000000L;

		/**
		 * Cull counter-clockwise triangles.
		 */
		public static final long CullCcw = 0x0000002000000000L;

		/**
		 * State flag value {@code CullShift}.
		 */
		public static final long CullShift = 36;

		/**
		 * State flag value {@code CullMask}.
		 */
		public static final long CullMask = 0x0000003000000000L;

		/**
		 * State flag value {@code AlphaRefShift}.
		 */
		public static final long AlphaRefShift = 40;

		/**
		 * State flag value {@code AlphaRefMask}.
		 */
		public static final long AlphaRefMask = 0x0000ff0000000000L;

		/**
		 * Tristrip.
		 */
		public static final long PtTristrip = 0x0001000000000000L;

		/**
		 * Lines.
		 */
		public static final long PtLines = 0x0002000000000000L;

		/**
		 * Line strip.
		 */
		public static final long PtLinestrip = 0x0003000000000000L;

		/**
		 * Points.
		 */
		public static final long PtPoints = 0x0004000000000000L;

		/**
		 * State flag value {@code PtShift}.
		 */
		public static final long PtShift = 48;

		/**
		 * State flag value {@code PtMask}.
		 */
		public static final long PtMask = 0x0007000000000000L;

		/**
		 * State flag value {@code PointSizeShift}.
		 */
		public static final long PointSizeShift = 52;

		/**
		 * State flag value {@code PointSizeMask}.
		 */
		public static final long PointSizeMask = 0x00f0000000000000L;

		/**
		 * Enable MSAA rasterization.
		 */
		public static final long Msaa = 0x0100000000000000L;

		/**
		 * Enable line AA rasterization.
		 */
		public static final long Lineaa = 0x0200000000000000L;

		/**
		 * Enable conservative rasterization.
		 */
		public static final long ConservativeRaster = 0x0400000000000000L;

		/**
		 * No state.
		 */
		public static final long None = 0x0000000000000000L;

		/**
		 * Front counter-clockwise (default is clockwise).
		 */
		public static final long FrontCcw = 0x0000008000000000L;

		/**
		 * Enable blend independent.
		 */
		public static final long BlendIndependent = 0x0000000400000000L;

		/**
		 * Enable alpha to coverage.
		 */
		public static final long BlendAlphaToCoverage = 0x0000000800000000L;

		/**
		 * Default state is write to RGB, alpha, and depth with depth test less enabled, with clockwise
		 * culling and MSAA (when writing into MSAA frame buffer, otherwise this flag is ignored).
		 */
		public static final long Default = 0x010000500000001fL;

		/**
		 * State flag value {@code Mask}.
		 */
		public static final long Mask = 0xffffffffffffffffL;

		/**
		 * State flag value {@code ReservedShift}.
		 */
		public static final long ReservedShift = 61;

		/**
		 * State flag value {@code ReservedMask}.
		 */
		public static final long ReservedMask = 0xe000000000000000L;
	}

	/**
	 * Constants for Stencil flags.
	 */
	@NullMarked
	public static final class StencilFlags {
		private StencilFlags() {
		}

		/**
		 * Stencil flag value {@code FuncRefShift}.
		 */
		public static final int FuncRefShift = 0;

		/**
		 * Stencil flag value {@code FuncRefMask}.
		 */
		public static final int FuncRefMask = 0x000000ff;

		/**
		 * Stencil flag value {@code FuncRmaskShift}.
		 */
		public static final int FuncRmaskShift = 8;

		/**
		 * Stencil flag value {@code FuncRmaskMask}.
		 */
		public static final int FuncRmaskMask = 0x0000ff00;

		/**
		 * No stencil test.
		 */
		public static final int None = 0x0000ff00;

		/**
		 * Stencil front or back mask.
		 */
		public static final int Mask = 0xffffffff;

		/**
		 * Enable stencil test, less.
		 */
		public static final int TestLess = 0x00010000;

		/**
		 * Enable stencil test, less or equal.
		 */
		public static final int TestLequal = 0x00020000;

		/**
		 * Enable stencil test, equal.
		 */
		public static final int TestEqual = 0x00030000;

		/**
		 * Enable stencil test, greater or equal.
		 */
		public static final int TestGequal = 0x00040000;

		/**
		 * Enable stencil test, greater.
		 */
		public static final int TestGreater = 0x00050000;

		/**
		 * Enable stencil test, not equal.
		 */
		public static final int TestNotequal = 0x00060000;

		/**
		 * Enable stencil test, never.
		 */
		public static final int TestNever = 0x00070000;

		/**
		 * Enable stencil test, always.
		 */
		public static final int TestAlways = 0x00080000;

		/**
		 * Stencil flag value {@code TestShift}.
		 */
		public static final int TestShift = 16;

		/**
		 * Stencil flag value {@code TestMask}.
		 */
		public static final int TestMask = 0x000f0000;

		/**
		 * Zero.
		 */
		public static final int OpFailSZero = 0x00000000;

		/**
		 * Keep.
		 */
		public static final int OpFailSKeep = 0x00100000;

		/**
		 * Replace.
		 */
		public static final int OpFailSReplace = 0x00200000;

		/**
		 * Increment and wrap.
		 */
		public static final int OpFailSIncr = 0x00300000;

		/**
		 * Increment and clamp.
		 */
		public static final int OpFailSIncrsat = 0x00400000;

		/**
		 * Decrement and wrap.
		 */
		public static final int OpFailSDecr = 0x00500000;

		/**
		 * Decrement and clamp.
		 */
		public static final int OpFailSDecrsat = 0x00600000;

		/**
		 * Invert.
		 */
		public static final int OpFailSInvert = 0x00700000;

		/**
		 * Stencil flag value {@code OpFailSShift}.
		 */
		public static final int OpFailSShift = 20;

		/**
		 * Stencil flag value {@code OpFailSMask}.
		 */
		public static final int OpFailSMask = 0x00f00000;

		/**
		 * Zero.
		 */
		public static final int OpFailZZero = 0x00000000;

		/**
		 * Keep.
		 */
		public static final int OpFailZKeep = 0x01000000;

		/**
		 * Replace.
		 */
		public static final int OpFailZReplace = 0x02000000;

		/**
		 * Increment and wrap.
		 */
		public static final int OpFailZIncr = 0x03000000;

		/**
		 * Increment and clamp.
		 */
		public static final int OpFailZIncrsat = 0x04000000;

		/**
		 * Decrement and wrap.
		 */
		public static final int OpFailZDecr = 0x05000000;

		/**
		 * Decrement and clamp.
		 */
		public static final int OpFailZDecrsat = 0x06000000;

		/**
		 * Invert.
		 */
		public static final int OpFailZInvert = 0x07000000;

		/**
		 * Stencil flag value {@code OpFailZShift}.
		 */
		public static final int OpFailZShift = 24;

		/**
		 * Stencil flag value {@code OpFailZMask}.
		 */
		public static final int OpFailZMask = 0x0f000000;

		/**
		 * Zero.
		 */
		public static final int OpPassZZero = 0x00000000;

		/**
		 * Keep.
		 */
		public static final int OpPassZKeep = 0x10000000;

		/**
		 * Replace.
		 */
		public static final int OpPassZReplace = 0x20000000;

		/**
		 * Increment and wrap.
		 */
		public static final int OpPassZIncr = 0x30000000;

		/**
		 * Increment and clamp.
		 */
		public static final int OpPassZIncrsat = 0x40000000;

		/**
		 * Decrement and wrap.
		 */
		public static final int OpPassZDecr = 0x50000000;

		/**
		 * Decrement and clamp.
		 */
		public static final int OpPassZDecrsat = 0x60000000;

		/**
		 * Invert.
		 */
		public static final int OpPassZInvert = 0x70000000;

		/**
		 * Stencil flag value {@code OpPassZShift}.
		 */
		public static final int OpPassZShift = 28;

		/**
		 * Stencil flag value {@code OpPassZMask}.
		 */
		public static final int OpPassZMask = 0xf0000000;
	}

	/**
	 * Constants for Clear flags.
	 */
	@NullMarked
	public static final class ClearFlags {
		private ClearFlags() {
		}
		/**
		 * No clear flags.
		 */
		public static final short None = (short) 0x0000;

		/**
		 * Clear color.
		 */
		public static final short Color = (short) 0x0001;

		/**
		 * Clear depth.
		 */
		public static final short Depth = (short) 0x0002;

		/**
		 * Clear stencil.
		 */
		public static final short Stencil = (short) 0x0004;

		/**
		 * Discard frame buffer attachment 0.
		 */
		public static final short DiscardColor0 = (short) 0x0008;

		/**
		 * Discard frame buffer attachment 1.
		 */
		public static final short DiscardColor1 = (short) 0x0010;

		/**
		 * Discard frame buffer attachment 2.
		 */
		public static final short DiscardColor2 = (short) 0x0020;

		/**
		 * Discard frame buffer attachment 3.
		 */
		public static final short DiscardColor3 = (short) 0x0040;

		/**
		 * Discard frame buffer attachment 4.
		 */
		public static final short DiscardColor4 = (short) 0x0080;

		/**
		 * Discard frame buffer attachment 5.
		 */
		public static final short DiscardColor5 = (short) 0x0100;

		/**
		 * Discard frame buffer attachment 6.
		 */
		public static final short DiscardColor6 = (short) 0x0200;

		/**
		 * Discard frame buffer attachment 7.
		 */
		public static final short DiscardColor7 = (short) 0x0400;

		/**
		 * Discard frame buffer depth attachment.
		 */
		public static final short DiscardDepth = (short) 0x0800;

		/**
		 * Discard frame buffer stencil attachment.
		 */
		public static final short DiscardStencil = (short) 0x1000;

		/**
		 * Clear flag value {@code DiscardColorMask}.
		 */
		public static final short DiscardColorMask = (short) 0x07f8;

		/**
		 * Clear flag value {@code DiscardMask}.
		 */
		public static final short DiscardMask = (short) 0x1ff8;
	}

	/**
	 * Rendering state discard. When state is preserved in submit, rendering states can be discarded
	 * on a finer grain.
	 */
	@NullMarked
	public static final class DiscardFlags {
		private DiscardFlags() {
		}
		/**
		 * Preserve everything.
		 */
		public static final int None = 0x00000000;

		/**
		 * Discard texture sampler and buffer bindings.
		 */
		public static final int Bindings = 0x00000001;

		/**
		 * Discard index buffer.
		 */
		public static final int IndexBuffer = 0x00000002;

		/**
		 * Discard instance data.
		 */
		public static final int InstanceData = 0x00000004;

		/**
		 * Discard state and uniform bindings.
		 */
		public static final int State = 0x00000008;

		/**
		 * Discard transform.
		 */
		public static final int Transform = 0x00000010;

		/**
		 * Discard vertex streams.
		 */
		public static final int VertexStreams = 0x00000020;

		/**
		 * Discard all states.
		 */
		public static final int All = 0x000000ff;
	}

	/**
	 * Constants for Debug flags.
	 */
	@NullMarked
	public static final class DebugFlags {
		private DebugFlags() {
		}
		/**
		 * No debug.
		 */
		public static final int None = 0x00000000;

		/**
		 * Enable wireframe for all primitives.
		 */
		public static final int Wireframe = 0x00000001;

		/**
		 * Enable infinitely fast hardware test. No draw calls will be submitted to driver.
		 * It's useful when profiling to quickly assess bottleneck between CPU and GPU.
		 */
		public static final int Ifh = 0x00000002;

		/**
		 * Enable statistics display.
		 */
		public static final int Stats = 0x00000004;

		/**
		 * Enable debug text display.
		 */
		public static final int Text = 0x00000008;

		/**
		 * Enable profiler. This causes per-view statistics to be collected, available through {@code Stats.ViewStats}. This is unrelated to the profiler functions in {@code CallbackI}.
		 */
		public static final int Profiler = 0x00000010;
	}

	/**
	 * Constants for Buffer flags.
	 */
	@NullMarked
	public static final class BufferFlags {
		private BufferFlags() {
		}

		/**
		 * Buffer flag value {@code None}.
		 */
		public static final short None = (short) 0x0000;

		/**
		 * Buffer will be read by shader.
		 */
		public static final short ComputeRead = (short) 0x0100;

		/**
		 * Buffer will be used for writing.
		 */
		public static final short ComputeWrite = (short) 0x0200;

		/**
		 * Buffer will be used for storing draw indirect commands.
		 */
		public static final short DrawIndirect = (short) 0x0400;

		/**
		 * Allow dynamic index/vertex buffer resize during update.
		 */
		public static final short AllowResize = (short) 0x0800;

		/**
		 * Index buffer contains 32-bit indices.
		 */
		public static final short Index32 = (short) 0x1000;

		/**
		 * Buffer flag value {@code ComputeReadWrite}.
		 */
		public static final short ComputeReadWrite = (short) 0x0300;
	}

	/**
	 * Constants for Texture flags.
	 */
	@NullMarked
	public static final class TextureFlags {
		private TextureFlags() {
		}

		/**
		 * Texture flag value {@code None}.
		 */
		public static final long None = 0x0000000000000000L;

		/**
		 * Texture will be used for MSAA sampling.
		 */
		public static final long MsaaSample = 0x0000000800000000L;

		/**
		 * Render target no MSAA.
		 */
		public static final long Rt = 0x0000001000000000L;

		/**
		 * Texture will be used for compute write.
		 */
		public static final long ComputeWrite = 0x0000100000000000L;

		/**
		 * Sample texture as sRGB.
		 */
		public static final long Srgb = 0x0000200000000000L;

		/**
		 * Texture will be used as blit destination.
		 */
		public static final long BlitDst = 0x0000400000000000L;

		/**
		 * Texture will be used for read back from GPU.
		 */
		public static final long ReadBack = 0x0000800000000000L;

		/**
		 * Texture is shared with other device or other process.
		 */
		public static final long ExternalShared = 0x0001000000000000L;

		/**
		 * Texture may be sampled and rendered with either sRGB-ness,
		 * not just the one implied by its format. Every bind and
		 * attachment must then state the encoding it wants (see
		 * {@code BGFX_SAMPLER_SRGB}, {@code BGFX_ATTACHMENT_SRGB}). Costs nothing
		 * until used, but may disable texture compression on some
		 * hardware.
		 */
		public static final long SrgbMutable = 0x0040000000000000L;

		/**
		 * Texture flag value {@code ReservedShift}.
		 */
		public static final long ReservedShift = 60;

		/**
		 * Texture flag value {@code ReservedMask}.
		 */
		public static final long ReservedMask = 0xf000000000000000L;

		/**
		 * Render target MSAAx2 mode.
		 */
		public static final long RtMsaaX2 = 0x0000002000000000L;

		/**
		 * Render target MSAAx4 mode.
		 */
		public static final long RtMsaaX4 = 0x0000003000000000L;

		/**
		 * Render target MSAAx8 mode.
		 */
		public static final long RtMsaaX8 = 0x0000004000000000L;

		/**
		 * Render target MSAAx16 mode.
		 */
		public static final long RtMsaaX16 = 0x0000005000000000L;

		/**
		 * Texture flag value {@code RtMsaaShift}.
		 */
		public static final long RtMsaaShift = 36;

		/**
		 * Texture flag value {@code RtMsaaMask}.
		 */
		public static final long RtMsaaMask = 0x0000007000000000L;

		/**
		 * Render target will be used for writing
		 */
		public static final long RtWriteOnly = 0x0000008000000000L;

		/**
		 * Texture flag value {@code RtShift}.
		 */
		public static final long RtShift = 36;

		/**
		 * Texture flag value {@code RtMask}.
		 */
		public static final long RtMask = 0x000000f000000000L;

		/**
		 * Texture flag value {@code MipCountShift}.
		 */
		public static final long MipCountShift = 49;

		/**
		 * Texture flag value {@code MipCountMask}.
		 */
		public static final long MipCountMask = 0x003e000000000000L;
	}

	/**
	 * Constants for Sampler flags.
	 */
	@NullMarked
	public static final class SamplerFlags {
		private SamplerFlags() {
		}
		/**
		 * Wrap U mode: Mirror
		 */
		public static final int UMirror = 0x00000001;

		/**
		 * Wrap U mode: Clamp
		 */
		public static final int UClamp = 0x00000002;

		/**
		 * Wrap U mode: Border
		 */
		public static final int UBorder = 0x00000003;

		/**
		 * Sampler flag value {@code UShift}.
		 */
		public static final int UShift = 0;

		/**
		 * Sampler flag value {@code UMask}.
		 */
		public static final int UMask = 0x00000003;

		/**
		 * Wrap V mode: Mirror
		 */
		public static final int VMirror = 0x00000004;

		/**
		 * Wrap V mode: Clamp
		 */
		public static final int VClamp = 0x00000008;

		/**
		 * Wrap V mode: Border
		 */
		public static final int VBorder = 0x0000000c;

		/**
		 * Sampler flag value {@code VShift}.
		 */
		public static final int VShift = 2;

		/**
		 * Sampler flag value {@code VMask}.
		 */
		public static final int VMask = 0x0000000c;

		/**
		 * Wrap W mode: Mirror
		 */
		public static final int WMirror = 0x00000010;

		/**
		 * Wrap W mode: Clamp
		 */
		public static final int WClamp = 0x00000020;

		/**
		 * Wrap W mode: Border
		 */
		public static final int WBorder = 0x00000030;

		/**
		 * Sampler flag value {@code WShift}.
		 */
		public static final int WShift = 4;

		/**
		 * Sampler flag value {@code WMask}.
		 */
		public static final int WMask = 0x00000030;

		/**
		 * Min sampling mode: Point
		 */
		public static final int MinPoint = 0x00000040;

		/**
		 * Min sampling mode: Anisotropic
		 */
		public static final int MinAnisotropic = 0x00000080;

		/**
		 * Sampler flag value {@code MinShift}.
		 */
		public static final int MinShift = 6;

		/**
		 * Sampler flag value {@code MinMask}.
		 */
		public static final int MinMask = 0x000000c0;

		/**
		 * Mag sampling mode: Point
		 */
		public static final int MagPoint = 0x00000100;

		/**
		 * Mag sampling mode: Anisotropic
		 */
		public static final int MagAnisotropic = 0x00000200;

		/**
		 * Sampler flag value {@code MagShift}.
		 */
		public static final int MagShift = 8;

		/**
		 * Sampler flag value {@code MagMask}.
		 */
		public static final int MagMask = 0x00000300;

		/**
		 * Mip sampling mode: Point
		 */
		public static final int MipPoint = 0x00000400;

		/**
		 * Sampler flag value {@code MipShift}.
		 */
		public static final int MipShift = 10;

		/**
		 * Sampler flag value {@code MipMask}.
		 */
		public static final int MipMask = 0x00000400;

		/**
		 * Compare when sampling depth texture: less.
		 */
		public static final int CompareLess = 0x00010000;

		/**
		 * Compare when sampling depth texture: less or equal.
		 */
		public static final int CompareLequal = 0x00020000;

		/**
		 * Compare when sampling depth texture: equal.
		 */
		public static final int CompareEqual = 0x00030000;

		/**
		 * Compare when sampling depth texture: greater or equal.
		 */
		public static final int CompareGequal = 0x00040000;

		/**
		 * Compare when sampling depth texture: greater.
		 */
		public static final int CompareGreater = 0x00050000;

		/**
		 * Compare when sampling depth texture: not equal.
		 */
		public static final int CompareNotequal = 0x00060000;

		/**
		 * Compare when sampling depth texture: never.
		 */
		public static final int CompareNever = 0x00070000;

		/**
		 * Compare when sampling depth texture: always.
		 */
		public static final int CompareAlways = 0x00080000;

		/**
		 * Sampler flag value {@code CompareShift}.
		 */
		public static final int CompareShift = 16;

		/**
		 * Sampler flag value {@code CompareMask}.
		 */
		public static final int CompareMask = 0x000f0000;

		/**
		 * Sampler flag value {@code BorderColorShift}.
		 */
		public static final int BorderColorShift = 24;

		/**
		 * Sampler flag value {@code BorderColorMask}.
		 */
		public static final int BorderColorMask = 0x0f000000;

		/**
		 * Sampler flag value {@code ReservedShift}.
		 */
		public static final int ReservedShift = 28;

		/**
		 * Sampler flag value {@code ReservedMask}.
		 */
		public static final int ReservedMask = 0xf0000000;

		/**
		 * Sampler flag value {@code None}.
		 */
		public static final int None = 0x00000000;

		/**
		 * Sample stencil instead of depth.
		 */
		public static final int SampleStencil = 0x00100000;

		/**
		 * Sample with sRGB conversion; absence of this flag samples
		 * without it. Only affects textures created
		 * {@code BGFX_TEXTURE_SRGB_MUTABLE}, which must state the encoding
		 * explicitly on every bind; ignored for any other texture.
		 */
		public static final int Srgb = 0x00200000;

		/**
		 * Sampler flag value {@code Point}.
		 */
		public static final int Point = 0x00000540;

		/**
		 * Sampler flag value {@code UvwMirror}.
		 */
		public static final int UvwMirror = 0x00000015;

		/**
		 * Sampler flag value {@code UvwClamp}.
		 */
		public static final int UvwClamp = 0x0000002a;

		/**
		 * Sampler flag value {@code UvwBorder}.
		 */
		public static final int UvwBorder = 0x0000003f;

		/**
		 * Sampler flag value {@code BitsMask}.
		 */
		public static final int BitsMask = 0x000f07ff;
	}

	/**
	 * Constants for Reset flags.
	 */
	@NullMarked
	public static final class ResetFlags {
		private ResetFlags() {
		}
		/**
		 * Enable 2x MSAA.
		 */
		public static final int MsaaX2 = 0x00000010;

		/**
		 * Enable 4x MSAA.
		 */
		public static final int MsaaX4 = 0x00000020;

		/**
		 * Enable 8x MSAA.
		 */
		public static final int MsaaX8 = 0x00000030;

		/**
		 * Enable 16x MSAA.
		 */
		public static final int MsaaX16 = 0x00000040;

		/**
		 * Reset flag value {@code MsaaShift}.
		 */
		public static final int MsaaShift = 4;

		/**
		 * Reset flag value {@code MsaaMask}.
		 */
		public static final int MsaaMask = 0x00000070;

		/**
		 * No reset flags.
		 */
		public static final int None = 0x00000000;

		/**
		 * Not supported yet.
		 */
		public static final int Fullscreen = 0x00000001;

		/**
		 * Enable V-Sync.
		 */
		public static final int Vsync = 0x00000080;

		/**
		 * Turn on/off max anisotropy.
		 */
		public static final int Maxanisotropy = 0x00000100;

		/**
		 * Begin screen capture.
		 */
		public static final int Capture = 0x00000200;

		/**
		 * Flush rendering after submitting to GPU.
		 */
		public static final int FlushAfterRender = 0x00002000;

		/**
		 * This flag specifies where flip occurs. Default behaviour is that flip occurs
		 * before rendering new frame. This flag only has effect when {@code BGFX_CONFIG_MULTITHREADED=0}.
		 */
		public static final int FlipAfterRender = 0x00004000;

		/**
		 * Enable sRGB backbuffer.
		 */
		public static final int SrgbBackbuffer = 0x00008000;

		/**
		 * Enable HDR10 rendering.
		 */
		public static final int Hdr10 = 0x00010000;

		/**
		 * Enable HiDPI rendering.
		 */
		public static final int Hidpi = 0x00020000;

		/**
		 * Suspend rendering.
		 */
		public static final int Suspend = 0x00080000;

		/**
		 * Transparent backbuffer. Availability depends on: {@code BGFX_CAPS_TRANSPARENT_BACKBUFFER}.
		 */
		public static final int TransparentBackbuffer = 0x00100000;

		/**
		 * Reset flag value {@code FullscreenShift}.
		 */
		public static final int FullscreenShift = 0;

		/**
		 * Reset flag value {@code FullscreenMask}.
		 */
		public static final int FullscreenMask = 0x00000001;

		/**
		 * Reset flag value {@code ReservedShift}.
		 */
		public static final int ReservedShift = 31;

		/**
		 * Reset flag value {@code ReservedMask}.
		 */
		public static final int ReservedMask = 0x80000000;
	}

	/**
	 * Constants for SwapChainMsaa flags.
	 */
	@NullMarked
	public static final class SwapChainMsaaFlags {
		private SwapChainMsaaFlags() {
		}
		/**
		 * Enable 2x MSAA.
		 */
		public static final int X2 = 0x00000010;

		/**
		 * Enable 4x MSAA.
		 */
		public static final int X4 = 0x00000020;

		/**
		 * Enable 8x MSAA.
		 */
		public static final int X8 = 0x00000030;

		/**
		 * Enable 16x MSAA.
		 */
		public static final int X16 = 0x00000040;
		/**
		 * Bit shift for this flag group.
		 */
		public static final int Shift = 4;
		/**
		 * Bit mask for this flag group.
		 */
		public static final int Mask = 0x00000070;
	}

	/**
	 * Constants for SwapChain flags.
	 */
	@NullMarked
	public static final class SwapChainFlags {
		private SwapChainFlags() {
		}
		/**
		 * No swap chain flags.
		 */
		public static final int None = 0x00000000;

		/**
		 * Not supported yet.
		 */
		public static final int Fullscreen = 0x00000001;

		/**
		 * Enable sRGB backbuffer.
		 */
		public static final int SrgbBackbuffer = 0x00008000;

		/**
		 * Enable HDR10 rendering.
		 */
		public static final int Hdr10 = 0x00010000;

		/**
		 * Enable HiDPI rendering.
		 */
		public static final int Hidpi = 0x00020000;

		/**
		 * Transparent backbuffer. Availability depends on: {@code BGFX_CAPS_TRANSPARENT_BACKBUFFER}.
		 */
		public static final int TransparentBackbuffer = 0x00100000;
	}

	/**
	 * Constants for SwapChainFullscreen flags.
	 */
	@NullMarked
	public static final class SwapChainFullscreenFlags {
		private SwapChainFullscreenFlags() {
		}
		/**
		 * Bit shift for this flag group.
		 */
		public static final int Shift = 0;
		/**
		 * Bit mask for this flag group.
		 */
		public static final int Mask = 0x00000001;
	}

	/**
	 * Constants for Caps flags.
	 */
	@NullMarked
	public static final class CapsFlags {
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
		 * 16-bit floats are supported in shaders.
		 */
		public static final long ShaderF16 = 0x0000000000001000L;

		/**
		 * Multiple windows are supported.
		 */
		public static final long SwapChain = 0x0000000000002000L;

		/**
		 * Cubemap texture array is supported.
		 */
		public static final long TextureCubeArray = 0x0000000000004000L;

		/**
		 * CPU direct access to GPU texture memory.
		 */
		public static final long TextureDirectAccess = 0x0000000000008000L;

		/**
		 * External texture is supported.
		 */
		public static final long TextureExternal = 0x0000000000010000L;

		/**
		 * External shared texture is supported.
		 */
		public static final long TextureExternalShared = 0x0000000000020000L;

		/**
		 * Transparent back buffer supported.
		 */
		public static final long TransparentBackbuffer = 0x0000000000040000L;

		/**
		 * Variable Rate Shading
		 */
		public static final long VariableRateShading = 0x0000000000080000L;

		/**
		 * Vertex attribute 10_10_10_2 is supported.
		 */
		public static final long VertexAttribUint10 = 0x0000000000100000L;

		/**
		 * Hardware video decode is supported.
		 */
		public static final long VideoDecode = 0x0000000000200000L;

		/**
		 * Viewport layer is available in vertex shader.
		 */
		public static final long ViewportLayerArray = 0x0000000000400000L;
	}

	/**
	 * Constants for CapsFormat flags.
	 */
	@NullMarked
	public static final class CapsFormatFlags {
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

	/**
	 * Constants for CapsVideoCodec flags.
	 */
	@NullMarked
	public static final class CapsVideoCodecFlags {
		private CapsVideoCodecFlags() {
		}
		/**
		 * Video codec is not supported.
		 */
		public static final int None = 0x00000000;

		/**
		 * 8-bit sample depth is supported.
		 */
		public static final int Bit8 = 0x00000001;

		/**
		 * 10-bit sample depth is supported.
		 */
		public static final int Bit10 = 0x00000002;

		/**
		 * 12-bit sample depth is supported.
		 */
		public static final int Bit12 = 0x00000004;

		/**
		 * 4:2:0 chroma subsampling is supported.
		 */
		public static final int Chroma420 = 0x00000008;

		/**
		 * 4:2:2 chroma subsampling is supported.
		 */
		public static final int Chroma422 = 0x00000010;

		/**
		 * 4:4:4 chroma subsampling is supported.
		 */
		public static final int Chroma444 = 0x00000020;
	}

	/**
	 * Video decoder lifetime flags (per {@code VideoDecoderInit.flags}).
	 */
	@NullMarked
	public static final class VideoDecoderInitFlags {
		private VideoDecoderInitFlags() {
		}
		/**
		 * No flags.
		 */
		public static final int None = 0x00000000;

		/**
		 * Cache submitted access units in driver-managed memory keyed by {@code ptsUs} so the
		 * presentation clock can revisit / loop without re-streaming. The cache is
		 * unbounded: the app picks the total cache size implicitly by choosing how
		 * many access units to submit. Without this flag access units are decoded once
		 * and dropped (streaming default).
		 */
		public static final int Retain = 0x00000001;
	}

	/**
	 * Video decoder per-frame submission flags (per {@code VideoDecoderFrame.flags}).
	 */
	@NullMarked
	public static final class VideoDecodeFrameFlags {
		private VideoDecodeFrameFlags() {
		}
		/**
		 * No flags.
		 */
		public static final int None = 0x00000000;

		/**
		 * First batch after a position change. The first access unit must be a clean IDR.
		 * Driver flushes its DPB, queued access units, and reorder pool before decoding;
		 * subsequent {@code presentationTimeUs} values may land anywhere (monotonicity is only
		 * required between non-{@code Set} ticks).
		 */
		public static final int Set = 0x00000001;

		/**
		 * Skip the picker dispatch for this call. Useful while bulk-loading access units
		 * so the displayed picture isn't churned mid-load.
		 */
		public static final int NoBlit = 0x00000002;

		/**
		 * Marks the last access unit of the clip; permits eager pre-decode in idle time
		 * and lets the picker emit the final frame without lookahead stalling.
		 */
		public static final int Final = 0x00000004;

		/**
		 * When {@code presentationTimeUs} runs past the highest cached {@code ptsUs}, the picker
		 * wraps modulo the cached pts range. Without this flag the picker freezes on
		 * the last displayable picture.
		 */
		public static final int Loop = 0x00000008;
	}

	/**
	 * Constants for Attachment flags.
	 */
	@NullMarked
	public static final class AttachmentFlags {
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

	/**
	 * Constants for PciId flags.
	 */
	@NullMarked
	public static final class PciIdFlags {
		private PciIdFlags() {
		}
		/**
		 * Autoselect adapter.
		 */
		public static final short None = (short) 0x0000;

		/**
		 * Software rasterizer.
		 */
		public static final short SoftwareRasterizer = (short) 0x0001;

		/**
		 * AMD adapter.
		 */
		public static final short Amd = (short) 0x1002;

		/**
		 * Apple adapter.
		 */
		public static final short Apple = (short) 0x106b;

		/**
		 * Intel adapter.
		 */
		public static final short Intel = (short) 0x8086;

		/**
		 * NVIDIA adapter.
		 */
		public static final short Nvidia = (short) 0x10de;

		/**
		 * Microsoft adapter.
		 */
		public static final short Microsoft = (short) 0x1414;

		/**
		 * ARM adapter.
		 */
		public static final short Arm = (short) 0x13b5;
	}

	/**
	 * Constants for CubeMap flags.
	 */
	@NullMarked
	public static final class CubeMapFlags {
		private CubeMapFlags() {
		}
		/**
		 * Cubemap +x.
		 */
		public static final int PositiveX = 0x00000000;

		/**
		 * Cubemap -x.
		 */
		public static final int NegativeX = 0x00000001;

		/**
		 * Cubemap +y.
		 */
		public static final int PositiveY = 0x00000002;

		/**
		 * Cubemap -y.
		 */
		public static final int NegativeY = 0x00000003;

		/**
		 * Cubemap +z.
		 */
		public static final int PositiveZ = 0x00000004;

		/**
		 * Cubemap -z.
		 */
		public static final int NegativeZ = 0x00000005;
	}

	/**
	 * Constants for Frame flags.
	 */
	@NullMarked
	public static final class FrameFlags {
		private FrameFlags() {
		}
		/**
		 * No frame flags.
		 */
		public static final int None = 0x00000000;

		/**
		 * Capture frame with graphics debugger.
		 */
		public static final int DebugCapture = 0x00000001;

		/**
		 * Discard all draw calls.
		 */
		public static final int Discard = 0x00000002;

		/**
		 * Execute all rendering commands without presenting the backbuffer.
		 */
		public static final int Flush = 0x00000004;
	}

	/**
	 * Fatal error enum.
	 */
	@NullMarked
	public enum Fatal {
		/**
		 * Fatal value {@code DEBUG_CHECK}.
		 */
		DEBUG_CHECK,
		/**
		 * Fatal value {@code INVALID_SHADER}.
		 */
		INVALID_SHADER,
		/**
		 * Fatal value {@code UNABLE_TO_INITIALIZE}.
		 */
		UNABLE_TO_INITIALIZE,
		/**
		 * Fatal value {@code UNABLE_TO_CREATE_TEXTURE}.
		 */
		UNABLE_TO_CREATE_TEXTURE,
		/**
		 * Fatal value {@code DEVICE_LOST}.
		 */
		DEVICE_LOST,

		/**
		 * Number of native enum values.
		 */
		COUNT;

		/**
		 * Native C enum layout.
		 */
		public static final ValueLayout.OfInt LAYOUT = ValueLayout.JAVA_INT;
		private static final Fatal[] VALUES = values();

		/**
		 * Returns the enum constant for a native C enum value.
		 * @param value the native enum value
		 * @return the matching enum constant
		 */
		public static Fatal fromValue(int value) {
			if (value >= 0 && value < VALUES.length) {
				return VALUES[value];
			}
			throw new IllegalArgumentException("Unknown Fatal value: " + value);
		}
	}

	/**
	 * Renderer backend type enum.
	 */
	@NullMarked
	public enum RendererType {
		/**
		 * No rendering.
		 */
		NOOP,
		/**
		 * AGC
		 */
		AGC,
		/**
		 * Direct3D 11.0
		 */
		DIRECT3D11,
		/**
		 * Direct3D 12.0
		 */
		DIRECT3D12,
		/**
		 * GNM
		 */
		GNM,
		/**
		 * Metal
		 */
		METAL,
		/**
		 * NVN
		 */
		NVN,
		/**
		 * OpenGL ES 3.0+
		 */
		OPENGLES,
		/**
		 * OpenGL 4.3+
		 */
		OPENGL,
		/**
		 * Vulkan
		 */
		VULKAN,
		/**
		 * WebGPU
		 */
		WEBGPU,

		/**
		 * Number of native enum values.
		 */
		COUNT;

		/**
		 * Native C enum layout.
		 */
		public static final ValueLayout.OfInt LAYOUT = ValueLayout.JAVA_INT;
		private static final RendererType[] VALUES = values();

		/**
		 * Returns the enum constant for a native C enum value.
		 * @param value the native enum value
		 * @return the matching enum constant
		 */
		public static RendererType fromValue(int value) {
			if (value >= 0 && value < VALUES.length) {
				return VALUES[value];
			}
			throw new IllegalArgumentException("Unknown RendererType value: " + value);
		}
	}

	/**
	 * Access mode enum.
	 */
	@NullMarked
	public enum Access {
		/**
		 * Read.
		 */
		READ,
		/**
		 * Write.
		 */
		WRITE,
		/**
		 * Read and write.
		 */
		READWRITE,

		/**
		 * Number of native enum values.
		 */
		COUNT;

		/**
		 * Native C enum layout.
		 */
		public static final ValueLayout.OfInt LAYOUT = ValueLayout.JAVA_INT;
		private static final Access[] VALUES = values();

		/**
		 * Returns the enum constant for a native C enum value.
		 * @param value the native enum value
		 * @return the matching enum constant
		 */
		public static Access fromValue(int value) {
			if (value >= 0 && value < VALUES.length) {
				return VALUES[value];
			}
			throw new IllegalArgumentException("Unknown Access value: " + value);
		}
	}

	/**
	 * Vertex attribute enum.
	 */
	@NullMarked
	public enum Attrib {
		/**
		 * a_position
		 */
		POSITION,
		/**
		 * a_normal
		 */
		NORMAL,
		/**
		 * a_tangent
		 */
		TANGENT,
		/**
		 * a_bitangent
		 */
		BITANGENT,
		/**
		 * a_color0
		 */
		COLOR0,
		/**
		 * a_color1
		 */
		COLOR1,
		/**
		 * a_color2
		 */
		COLOR2,
		/**
		 * a_color3
		 */
		COLOR3,
		/**
		 * a_indices
		 */
		INDICES,
		/**
		 * a_weight
		 */
		WEIGHT,
		/**
		 * a_texcoord0
		 */
		TEXCOORD0,
		/**
		 * a_texcoord1
		 */
		TEXCOORD1,
		/**
		 * a_texcoord2
		 */
		TEXCOORD2,
		/**
		 * a_texcoord3
		 */
		TEXCOORD3,
		/**
		 * a_texcoord4
		 */
		TEXCOORD4,
		/**
		 * a_texcoord5
		 */
		TEXCOORD5,
		/**
		 * a_texcoord6
		 */
		TEXCOORD6,
		/**
		 * a_texcoord7
		 */
		TEXCOORD7,
		/**
		 * a_texcoord8
		 */
		TEXCOORD8,
		/**
		 * a_texcoord9
		 */
		TEXCOORD9,
		/**
		 * a_texcoord10
		 */
		TEXCOORD10,
		/**
		 * a_texcoord11
		 */
		TEXCOORD11,
		/**
		 * a_texcoord12
		 */
		TEXCOORD12,
		/**
		 * a_texcoord13
		 */
		TEXCOORD13,
		/**
		 * a_texcoord14
		 */
		TEXCOORD14,
		/**
		 * a_texcoord15
		 */
		TEXCOORD15,

		/**
		 * Number of native enum values.
		 */
		COUNT;

		/**
		 * Native C enum layout.
		 */
		public static final ValueLayout.OfInt LAYOUT = ValueLayout.JAVA_INT;
		private static final Attrib[] VALUES = values();

		/**
		 * Returns the enum constant for a native C enum value.
		 * @param value the native enum value
		 * @return the matching enum constant
		 */
		public static Attrib fromValue(int value) {
			if (value >= 0 && value < VALUES.length) {
				return VALUES[value];
			}
			throw new IllegalArgumentException("Unknown Attrib value: " + value);
		}
	}

	/**
	 * Vertex attribute type enum.
	 */
	@NullMarked
	public enum AttribType {
		/**
		 * Int8
		 */
		INT8,
		/**
		 * Uint8
		 */
		UINT8,
		/**
		 * Uint10, availability depends on: {@code BGFX_CAPS_VERTEX_ATTRIB_UINT10}.
		 */
		UINT10,
		/**
		 * Int16
		 */
		INT16,
		/**
		 * Uint16
		 */
		UINT16,
		/**
		 * Half.
		 */
		HALF,
		/**
		 * Float
		 */
		FLOAT,
		/**
		 * Int32
		 */
		INT32,
		/**
		 * Uint32
		 */
		UINT32,

		/**
		 * Number of native enum values.
		 */
		COUNT;

		/**
		 * Native C enum layout.
		 */
		public static final ValueLayout.OfInt LAYOUT = ValueLayout.JAVA_INT;
		private static final AttribType[] VALUES = values();

		/**
		 * Returns the enum constant for a native C enum value.
		 * @param value the native enum value
		 * @return the matching enum constant
		 */
		public static AttribType fromValue(int value) {
			if (value >= 0 && value < VALUES.length) {
				return VALUES[value];
			}
			throw new IllegalArgumentException("Unknown AttribType value: " + value);
		}
	}

	/**
	 * Texture format enum.
	 * <p>
	 * Notation:
	 * <p>
	 *       RGBA16S
	 *       ^   ^ ^
	 *       |   | +-- [ ]Unorm
	 *       |   |     [F]loat
	 *       |   |     [S]norm
	 *       |   |     [I]nt
	 *       |   |     [U]int
	 *       |   +---- Number of bits per component
	 *       +-------- Components
	 * <p>
	 * <strong>Attention:</strong> Availability depends on Caps (see: formats).
	 */
	@NullMarked
	public enum TextureFormat {
		/**
		 * Block Compression 1. 5-bit R, 6-bit G, 5-bit B, 1-bit A. 4 BPP.
		 */
		BC1,
		/**
		 * Block Compression 2. 5-bit R, 6-bit G, 5-bit B, 4-bit explicit A. 8 BPP.
		 */
		BC2,
		/**
		 * Block Compression 3. 5-bit R, 6-bit G, 5-bit B, 8-bit interpolated A. 8 BPP.
		 */
		BC3,
		/**
		 * Block Compression 4. Single 8-bit red channel, unsigned normalized. 4 BPP.
		 */
		BC4,
		/**
		 * Block Compression 4. Single 8-bit red channel, signed normalized. 4 BPP.
		 */
		BC4S,
		/**
		 * Block Compression 5. Two 8-bit channels (RG), unsigned normalized. 8 BPP.
		 */
		BC5,
		/**
		 * Block Compression 5. Two 8-bit channels (RG), signed normalized. 8 BPP.
		 */
		BC5S,
		/**
		 * Block Compression 6H. Three 16-bit floating-point channels (RGB), HDR. 8 BPP.
		 */
		BC6H,
		/**
		 * Block Compression 6H. Three 16-bit unsigned floating-point channels (RGB), HDR. 8 BPP.
		 */
		BC6HU,
		/**
		 * RGB 4-7 bits per color channel, 0-8 bits alpha. Block Compression 7. High-quality RGBA, 4-7 bits per color, 0-8 bits alpha. 8 BPP.
		 */
		BC7,
		/**
		 * Ericsson Texture Compression 1. 8-bit per channel RGB. 4 BPP.
		 */
		ETC1,
		/**
		 * Ericsson Texture Compression 2. 8-bit per channel RGB. 4 BPP.
		 */
		ETC2,
		/**
		 * Ericsson Texture Compression 2 with full alpha. 8-bit per channel RGBA. 8 BPP.
		 */
		ETC2A,
		/**
		 * Ericsson Texture Compression 2 with 1-bit punch-through alpha. 4 BPP.
		 */
		ETC2A1,
		/**
		 * ETC2 Alpha Compression, single 11-bit red channel, unsigned normalized. 4 BPP.
		 */
		EACR11,
		/**
		 * ETC2 Alpha Compression, single 11-bit red channel, signed normalized. 4 BPP.
		 */
		EACR11S,
		/**
		 * ETC2 Alpha Compression, two 11-bit channels (RG), unsigned normalized. 8 BPP.
		 */
		EACRG11,
		/**
		 * ETC2 Alpha Compression, two 11-bit channels (RG), signed normalized. 8 BPP.
		 */
		EACRG11S,
		/**
		 * PowerVR Texture Compression v1. 3-channel RGB. 2 BPP.
		 */
		PTC12,
		/**
		 * PowerVR Texture Compression v1. 3-channel RGB. 4 BPP.
		 */
		PTC14,
		/**
		 * PowerVR Texture Compression v1. 4-channel RGBA. 2 BPP.
		 */
		PTC12A,
		/**
		 * PowerVR Texture Compression v1. 4-channel RGBA. 4 BPP.
		 */
		PTC14A,
		/**
		 * PowerVR Texture Compression v2. 4-channel RGBA. 2 BPP.
		 */
		PTC22,
		/**
		 * PowerVR Texture Compression v2. 4-channel RGBA. 4 BPP.
		 */
		PTC24,
		/**
		 * AMD Texture Compression. 3-channel RGB. 4 BPP.
		 */
		ATC,
		/**
		 * AMD Texture Compression with explicit alpha. 4-channel RGBA. 8 BPP.
		 */
		ATCE,
		/**
		 * AMD Texture Compression with interpolated alpha. 4-channel RGBA. 8 BPP.
		 */
		ATCI,
		/**
		 * Adaptive Scalable Texture Compression, 4x4 block, RGBA. 8.00 BPP.
		 */
		ASTC4X4,
		/**
		 * Adaptive Scalable Texture Compression, 5x4 block, RGBA. 6.40 BPP.
		 */
		ASTC5X4,
		/**
		 * Adaptive Scalable Texture Compression, 5x5 block, RGBA. 5.12 BPP.
		 */
		ASTC5X5,
		/**
		 * Adaptive Scalable Texture Compression, 6x5 block, RGBA. 4.27 BPP.
		 */
		ASTC6X5,
		/**
		 * Adaptive Scalable Texture Compression, 6x6 block, RGBA. 3.56 BPP.
		 */
		ASTC6X6,
		/**
		 * Adaptive Scalable Texture Compression, 8x5 block, RGBA. 3.20 BPP.
		 */
		ASTC8X5,
		/**
		 * Adaptive Scalable Texture Compression, 8x6 block, RGBA. 2.67 BPP.
		 */
		ASTC8X6,
		/**
		 * Adaptive Scalable Texture Compression, 8x8 block, RGBA. 2.00 BPP.
		 */
		ASTC8X8,
		/**
		 * Adaptive Scalable Texture Compression, 10x5 block, RGBA. 2.56 BPP.
		 */
		ASTC10X5,
		/**
		 * Adaptive Scalable Texture Compression, 10x6 block, RGBA. 2.13 BPP.
		 */
		ASTC10X6,
		/**
		 * Adaptive Scalable Texture Compression, 10x8 block, RGBA. 1.60 BPP.
		 */
		ASTC10X8,
		/**
		 * Adaptive Scalable Texture Compression, 10x10 block, RGBA. 1.28 BPP.
		 */
		ASTC10X10,
		/**
		 * Adaptive Scalable Texture Compression, 12x10 block, RGBA. 1.07 BPP.
		 */
		ASTC12X10,
		/**
		 * Adaptive Scalable Texture Compression, 12x12 block, RGBA. 0.89 BPP.
		 */
		ASTC12X12,
		/**
		 * Compressed formats above.
		 */
		UNKNOWN,
		/**
		 * 1-bit single-channel red. Monochrome, 1-bit per pixel. 1 BPP.
		 */
		R1,
		/**
		 * 8-bit single-channel alpha, unsigned normalized. 8 BPP.
		 */
		A8,
		/**
		 * 8-bit single-channel red, unsigned normalized. 8 BPP.
		 */
		R8,
		/**
		 * 8-bit single-channel red, signed integer. 8 BPP.
		 */
		R8I,
		/**
		 * 8-bit single-channel red, unsigned integer. 8 BPP.
		 */
		R8U,
		/**
		 * 8-bit single-channel red, signed normalized. 8 BPP.
		 */
		R8S,
		/**
		 * 16-bit single-channel red, unsigned normalized. 16 BPP.
		 */
		R16,
		/**
		 * 16-bit single-channel red, signed integer. 16 BPP.
		 */
		R16I,
		/**
		 * 16-bit single-channel red, unsigned integer. 16 BPP.
		 */
		R16U,
		/**
		 * 16-bit single-channel red, half-precision floating point. 16 BPP.
		 */
		R16F,
		/**
		 * 16-bit single-channel red, signed normalized. 16 BPP.
		 */
		R16S,
		/**
		 * 32-bit single-channel red, signed integer. 32 BPP.
		 */
		R32I,
		/**
		 * 32-bit single-channel red, unsigned integer. 32 BPP.
		 */
		R32U,
		/**
		 * 32-bit single-channel red, full-precision floating point. 32 BPP.
		 */
		R32F,
		/**
		 * Two 8-bit channels (red, green), unsigned normalized. 16 BPP.
		 */
		RG8,
		/**
		 * Two 8-bit channels (red, green), signed integer. 16 BPP.
		 */
		RG8I,
		/**
		 * Two 8-bit channels (red, green), unsigned integer. 16 BPP.
		 */
		RG8U,
		/**
		 * Two 8-bit channels (red, green), signed normalized. 16 BPP.
		 */
		RG8S,
		/**
		 * Two 16-bit channels (red, green), unsigned normalized. 32 BPP.
		 */
		RG16,
		/**
		 * Two 16-bit channels (red, green), signed integer. 32 BPP.
		 */
		RG16I,
		/**
		 * Two 16-bit channels (red, green), unsigned integer. 32 BPP.
		 */
		RG16U,
		/**
		 * Two 16-bit channels (red, green), half-precision floating point. 32 BPP.
		 */
		RG16F,
		/**
		 * Two 16-bit channels (red, green), signed normalized. 32 BPP.
		 */
		RG16S,
		/**
		 * Two 32-bit channels (red, green), signed integer. 64 BPP.
		 */
		RG32I,
		/**
		 * Two 32-bit channels (red, green), unsigned integer. 64 BPP.
		 */
		RG32U,
		/**
		 * Two 32-bit channels (red, green), full-precision floating point. 64 BPP.
		 */
		RG32F,
		/**
		 * Three 8-bit channels (red, green, blue), unsigned normalized. 24 BPP.
		 */
		RGB8,
		/**
		 * Three 8-bit channels (red, green, blue), signed integer. 24 BPP.
		 */
		RGB8I,
		/**
		 * Three 8-bit channels (red, green, blue), unsigned integer. 24 BPP.
		 */
		RGB8U,
		/**
		 * Three 8-bit channels (red, green, blue), signed normalized. 24 BPP.
		 */
		RGB8S,
		/**
		 * Shared-exponent RGB. 9 bits per RGB channel with a shared 5-bit exponent, floating point. 32 BPP.
		 */
		RGB9E5F,
		/**
		 * Four 8-bit channels (blue, green, red, alpha), unsigned normalized. BGRA byte order. 32 BPP.
		 */
		BGRA8,
		/**
		 * Four 8-bit channels (red, green, blue, alpha), unsigned normalized. 32 BPP.
		 */
		RGBA8,
		/**
		 * Four 8-bit channels (red, green, blue, alpha), signed integer. 32 BPP.
		 */
		RGBA8I,
		/**
		 * Four 8-bit channels (red, green, blue, alpha), unsigned integer. 32 BPP.
		 */
		RGBA8U,
		/**
		 * Four 8-bit channels (red, green, blue, alpha), signed normalized. 32 BPP.
		 */
		RGBA8S,
		/**
		 * Four 16-bit channels (red, green, blue, alpha), unsigned normalized. 64 BPP.
		 */
		RGBA16,
		/**
		 * Four 16-bit channels (red, green, blue, alpha), signed integer. 64 BPP.
		 */
		RGBA16I,
		/**
		 * Four 16-bit channels (red, green, blue, alpha), unsigned integer. 64 BPP.
		 */
		RGBA16U,
		/**
		 * Four 16-bit channels (red, green, blue, alpha), half-precision floating point. 64 BPP.
		 */
		RGBA16F,
		/**
		 * Four 16-bit channels (red, green, blue, alpha), signed normalized. 64 BPP.
		 */
		RGBA16S,
		/**
		 * Four 32-bit channels (red, green, blue, alpha), signed integer. 128 BPP.
		 */
		RGBA32I,
		/**
		 * Four 32-bit channels (red, green, blue, alpha), unsigned integer. 128 BPP.
		 */
		RGBA32U,
		/**
		 * Four 32-bit channels (red, green, blue, alpha), full-precision floating point. 128 BPP.
		 */
		RGBA32F,
		/**
		 * Packed 16-bit, 5-bit blue, 6-bit green, 5-bit red. BGR byte order, unsigned normalized. 16 BPP.
		 */
		B5G6R5,
		/**
		 * Packed 16-bit, 5-bit red, 6-bit green, 5-bit blue. RGB byte order, unsigned normalized. 16 BPP.
		 */
		R5G6B5,
		/**
		 * Packed 16-bit, 4-bit per channel (blue, green, red, alpha). BGRA byte order, unsigned normalized. 16 BPP.
		 */
		BGRA4,
		/**
		 * Packed 16-bit, 4-bit per channel (red, green, blue, alpha), unsigned normalized. 16 BPP.
		 */
		RGBA4,
		/**
		 * Packed 16-bit, 5-bit blue, 5-bit green, 5-bit red, 1-bit alpha. BGRA byte order, unsigned normalized. 16 BPP.
		 */
		BGR5A1,
		/**
		 * Packed 16-bit, 5-bit red, 5-bit green, 5-bit blue, 1-bit alpha, unsigned normalized. 16 BPP.
		 */
		RGB5A1,
		/**
		 * Packed 32-bit, 10-bit red, 10-bit green, 10-bit blue, 2-bit alpha, unsigned normalized. 32 BPP.
		 */
		RGB10A2,
		/**
		 * Packed 32-bit, 10-bit red, 10-bit green, 10-bit blue, 2-bit alpha, unsigned integer. 32 BPP.
		 */
		RGB10A2U,
		/**
		 * Packed 32-bit, 11-bit red, 11-bit green, 10-bit blue, unsigned floating point. No alpha. 32 BPP.
		 */
		RG11B10F,
		/**
		 * Depth formats below.
		 */
		UNKNOWNDEPTH,
		/**
		 * 16-bit depth, unsigned normalized. 16 BPP.
		 */
		D16,
		/**
		 * 24-bit depth, unsigned normalized (stored as 32-bit with 8 bits unused). 32 BPP.
		 */
		D24,
		/**
		 * 24-bit depth, unsigned normalized, with 8-bit stencil. 32 BPP.
		 */
		D24S8,
		/**
		 * 32-bit depth, unsigned normalized. 32 BPP.
		 */
		D32,
		/**
		 * 16-bit depth, floating point. 16 BPP.
		 */
		D16F,
		/**
		 * 24-bit depth, floating point (stored as 32-bit). 32 BPP.
		 */
		D24F,
		/**
		 * 32-bit depth, floating point. 32 BPP.
		 */
		D32F,
		/**
		 * 32-bit depth, floating point, with 8-bit stencil (stored as 64-bit). 64 BPP.
		 */
		D32FS8,
		/**
		 * 8-bit stencil only, no depth. 8 BPP.
		 */
		D0S8,

		/**
		 * Number of native enum values.
		 */
		COUNT;

		/**
		 * Native C enum layout.
		 */
		public static final ValueLayout.OfInt LAYOUT = ValueLayout.JAVA_INT;
		private static final TextureFormat[] VALUES = values();

		/**
		 * Returns the enum constant for a native C enum value.
		 * @param value the native enum value
		 * @return the matching enum constant
		 */
		public static TextureFormat fromValue(int value) {
			if (value >= 0 && value < VALUES.length) {
				return VALUES[value];
			}
			throw new IllegalArgumentException("Unknown TextureFormat value: " + value);
		}
	}

	/**
	 * Uniform type enum.
	 */
	@NullMarked
	public enum UniformType {
		/**
		 * Sampler.
		 */
		SAMPLER,
		/**
		 * Reserved, do not use.
		 */
		END,
		/**
		 * 4 floats vector.
		 */
		VEC4,
		/**
		 * 3x3 matrix.
		 */
		MAT3,
		/**
		 * 4x4 matrix.
		 */
		MAT4,

		/**
		 * Number of native enum values.
		 */
		COUNT;

		/**
		 * Native C enum layout.
		 */
		public static final ValueLayout.OfInt LAYOUT = ValueLayout.JAVA_INT;
		private static final UniformType[] VALUES = values();

		/**
		 * Returns the enum constant for a native C enum value.
		 * @param value the native enum value
		 * @return the matching enum constant
		 */
		public static UniformType fromValue(int value) {
			if (value >= 0 && value < VALUES.length) {
				return VALUES[value];
			}
			throw new IllegalArgumentException("Unknown UniformType value: " + value);
		}
	}

	/**
	 * Uniform frequency enum.
	 */
	@NullMarked
	public enum UniformFreq {
		/**
		 * Changing per draw call.
		 */
		DRAW,
		/**
		 * Changing per view.
		 */
		VIEW,
		/**
		 * Changing per frame.
		 */
		FRAME,

		/**
		 * Number of native enum values.
		 */
		COUNT;

		/**
		 * Native C enum layout.
		 */
		public static final ValueLayout.OfInt LAYOUT = ValueLayout.JAVA_INT;
		private static final UniformFreq[] VALUES = values();

		/**
		 * Returns the enum constant for a native C enum value.
		 * @param value the native enum value
		 * @return the matching enum constant
		 */
		public static UniformFreq fromValue(int value) {
			if (value >= 0 && value < VALUES.length) {
				return VALUES[value];
			}
			throw new IllegalArgumentException("Unknown UniformFreq value: " + value);
		}
	}

	/**
	 * Backbuffer ratio enum.
	 * <p>
	 * The ratio is always relative to the window bgfx was initialized with, and is
	 * re-resolved by {@code reset}. It is not relative to whichever window a texture
	 * happens to be rendered to, so on a second window a ratio texture is not
	 * meaningfully sized. For that reason a ratio texture cannot be used as
	 * {@code SwapChain.depth}.
	 */
	@NullMarked
	public enum BackbufferRatio {
		/**
		 * Equal to the main window's backbuffer.
		 */
		EQUAL,
		/**
		 * One half size of the main window's backbuffer.
		 */
		HALF,
		/**
		 * One quarter size of the main window's backbuffer.
		 */
		QUARTER,
		/**
		 * One eighth size of the main window's backbuffer.
		 */
		EIGHTH,
		/**
		 * One sixteenth size of the main window's backbuffer.
		 */
		SIXTEENTH,
		/**
		 * Double size of the main window's backbuffer.
		 */
		DOUBLE,

		/**
		 * Number of native enum values.
		 */
		COUNT;

		/**
		 * Native C enum layout.
		 */
		public static final ValueLayout.OfInt LAYOUT = ValueLayout.JAVA_INT;
		private static final BackbufferRatio[] VALUES = values();

		/**
		 * Returns the enum constant for a native C enum value.
		 * @param value the native enum value
		 * @return the matching enum constant
		 */
		public static BackbufferRatio fromValue(int value) {
			if (value >= 0 && value < VALUES.length) {
				return VALUES[value];
			}
			throw new IllegalArgumentException("Unknown BackbufferRatio value: " + value);
		}
	}

	/**
	 * Occlusion query result.
	 */
	@NullMarked
	public enum OcclusionQueryResult {
		/**
		 * Query failed test.
		 */
		INVISIBLE,
		/**
		 * Query passed test.
		 */
		VISIBLE,
		/**
		 * Query result is not available yet.
		 */
		NORESULT,

		/**
		 * Number of native enum values.
		 */
		COUNT;

		/**
		 * Native C enum layout.
		 */
		public static final ValueLayout.OfInt LAYOUT = ValueLayout.JAVA_INT;
		private static final OcclusionQueryResult[] VALUES = values();

		/**
		 * Returns the enum constant for a native C enum value.
		 * @param value the native enum value
		 * @return the matching enum constant
		 */
		public static OcclusionQueryResult fromValue(int value) {
			if (value >= 0 && value < VALUES.length) {
				return VALUES[value];
			}
			throw new IllegalArgumentException("Unknown OcclusionQueryResult value: " + value);
		}
	}

	/**
	 * Video codec enum.
	 */
	@NullMarked
	public enum VideoCodec {
		/**
		 * H.264 / AVC.
		 */
		H264,
		/**
		 * H.265 / HEVC.
		 */
		H265,
		/**
		 * AV1.
		 */
		AV1,

		/**
		 * Number of native enum values.
		 */
		COUNT;

		/**
		 * Native C enum layout.
		 */
		public static final ValueLayout.OfInt LAYOUT = ValueLayout.JAVA_INT;
		private static final VideoCodec[] VALUES = values();

		/**
		 * Returns the enum constant for a native C enum value.
		 * @param value the native enum value
		 * @return the matching enum constant
		 */
		public static VideoCodec fromValue(int value) {
			if (value >= 0 && value < VALUES.length) {
				return VALUES[value];
			}
			throw new IllegalArgumentException("Unknown VideoCodec value: " + value);
		}
	}

	/**
	 * Primitive topology.
	 */
	@NullMarked
	public enum Topology {
		/**
		 * Triangle list.
		 */
		TRI_LIST,
		/**
		 * Triangle strip.
		 */
		TRI_STRIP,
		/**
		 * Line list.
		 */
		LINE_LIST,
		/**
		 * Line strip.
		 */
		LINE_STRIP,
		/**
		 * Point list.
		 */
		POINT_LIST,

		/**
		 * Number of native enum values.
		 */
		COUNT;

		/**
		 * Native C enum layout.
		 */
		public static final ValueLayout.OfInt LAYOUT = ValueLayout.JAVA_INT;
		private static final Topology[] VALUES = values();

		/**
		 * Returns the enum constant for a native C enum value.
		 * @param value the native enum value
		 * @return the matching enum constant
		 */
		public static Topology fromValue(int value) {
			if (value >= 0 && value < VALUES.length) {
				return VALUES[value];
			}
			throw new IllegalArgumentException("Unknown Topology value: " + value);
		}
	}

	/**
	 * Topology conversion function.
	 */
	@NullMarked
	public enum TopologyConvert {
		/**
		 * Flip winding order of triangle list.
		 */
		TRI_LIST_FLIP_WINDING,
		/**
		 * Flip winding order of triangle strip.
		 */
		TRI_STRIP_FLIP_WINDING,
		/**
		 * Convert triangle list to line list.
		 */
		TRI_LIST_TO_LINE_LIST,
		/**
		 * Convert triangle strip to triangle list.
		 */
		TRI_STRIP_TO_TRI_LIST,
		/**
		 * Convert line strip to line list.
		 */
		LINE_STRIP_TO_LINE_LIST,

		/**
		 * Number of native enum values.
		 */
		COUNT;

		/**
		 * Native C enum layout.
		 */
		public static final ValueLayout.OfInt LAYOUT = ValueLayout.JAVA_INT;
		private static final TopologyConvert[] VALUES = values();

		/**
		 * Returns the enum constant for a native C enum value.
		 * @param value the native enum value
		 * @return the matching enum constant
		 */
		public static TopologyConvert fromValue(int value) {
			if (value >= 0 && value < VALUES.length) {
				return VALUES[value];
			}
			throw new IllegalArgumentException("Unknown TopologyConvert value: " + value);
		}
	}

	/**
	 * Topology sort order.
	 */
	@NullMarked
	public enum TopologySort {
		/**
		 * TopologySort value {@code DIRECTION_FRONT_TO_BACK_MIN}.
		 */
		DIRECTION_FRONT_TO_BACK_MIN,
		/**
		 * TopologySort value {@code DIRECTION_FRONT_TO_BACK_AVG}.
		 */
		DIRECTION_FRONT_TO_BACK_AVG,
		/**
		 * TopologySort value {@code DIRECTION_FRONT_TO_BACK_MAX}.
		 */
		DIRECTION_FRONT_TO_BACK_MAX,
		/**
		 * TopologySort value {@code DIRECTION_BACK_TO_FRONT_MIN}.
		 */
		DIRECTION_BACK_TO_FRONT_MIN,
		/**
		 * TopologySort value {@code DIRECTION_BACK_TO_FRONT_AVG}.
		 */
		DIRECTION_BACK_TO_FRONT_AVG,
		/**
		 * TopologySort value {@code DIRECTION_BACK_TO_FRONT_MAX}.
		 */
		DIRECTION_BACK_TO_FRONT_MAX,
		/**
		 * TopologySort value {@code DISTANCE_FRONT_TO_BACK_MIN}.
		 */
		DISTANCE_FRONT_TO_BACK_MIN,
		/**
		 * TopologySort value {@code DISTANCE_FRONT_TO_BACK_AVG}.
		 */
		DISTANCE_FRONT_TO_BACK_AVG,
		/**
		 * TopologySort value {@code DISTANCE_FRONT_TO_BACK_MAX}.
		 */
		DISTANCE_FRONT_TO_BACK_MAX,
		/**
		 * TopologySort value {@code DISTANCE_BACK_TO_FRONT_MIN}.
		 */
		DISTANCE_BACK_TO_FRONT_MIN,
		/**
		 * TopologySort value {@code DISTANCE_BACK_TO_FRONT_AVG}.
		 */
		DISTANCE_BACK_TO_FRONT_AVG,
		/**
		 * TopologySort value {@code DISTANCE_BACK_TO_FRONT_MAX}.
		 */
		DISTANCE_BACK_TO_FRONT_MAX,

		/**
		 * Number of native enum values.
		 */
		COUNT;

		/**
		 * Native C enum layout.
		 */
		public static final ValueLayout.OfInt LAYOUT = ValueLayout.JAVA_INT;
		private static final TopologySort[] VALUES = values();

		/**
		 * Returns the enum constant for a native C enum value.
		 * @param value the native enum value
		 * @return the matching enum constant
		 */
		public static TopologySort fromValue(int value) {
			if (value >= 0 && value < VALUES.length) {
				return VALUES[value];
			}
			throw new IllegalArgumentException("Unknown TopologySort value: " + value);
		}
	}

	/**
	 * View mode sets draw call sort order.
	 */
	@NullMarked
	public enum ViewMode {
		/**
		 * Default sort order.
		 */
		DEFAULT,
		/**
		 * Sort in the same order in which submit calls were called.
		 */
		SEQUENTIAL,
		/**
		 * Sort draw call depth in ascending order.
		 */
		DEPTH_ASCENDING,
		/**
		 * Sort draw call depth in descending order.
		 */
		DEPTH_DESCENDING,

		/**
		 * Number of native enum values.
		 */
		COUNT;

		/**
		 * Native C enum layout.
		 */
		public static final ValueLayout.OfInt LAYOUT = ValueLayout.JAVA_INT;
		private static final ViewMode[] VALUES = values();

		/**
		 * Returns the enum constant for a native C enum value.
		 * @param value the native enum value
		 * @return the matching enum constant
		 */
		public static ViewMode fromValue(int value) {
			if (value >= 0 && value < VALUES.length) {
				return VALUES[value];
			}
			throw new IllegalArgumentException("Unknown ViewMode value: " + value);
		}
	}

	/**
	 * Shading Rate.
	 */
	@NullMarked
	public enum ShadingRate {
		/**
		 * 1x1
		 */
		RATE_1X_1,
		/**
		 * 1x2
		 */
		RATE_1X_2,
		/**
		 * 2x1
		 */
		RATE_2X_1,
		/**
		 * 2x2
		 */
		RATE_2X_2,
		/**
		 * 2x4
		 */
		RATE_2X_4,
		/**
		 * 4x2
		 */
		RATE_4X_2,
		/**
		 * 4x4
		 */
		RATE_4X_4,

		/**
		 * Number of native enum values.
		 */
		COUNT;

		/**
		 * Native C enum layout.
		 */
		public static final ValueLayout.OfInt LAYOUT = ValueLayout.JAVA_INT;
		private static final ShadingRate[] VALUES = values();

		/**
		 * Returns the enum constant for a native C enum value.
		 * @param value the native enum value
		 * @return the matching enum constant
		 */
		public static ShadingRate fromValue(int value) {
			if (value >= 0 && value < VALUES.length) {
				return VALUES[value];
			}
			throw new IllegalArgumentException("Unknown ShadingRate value: " + value);
		}
	}

	/**
	 * Native window handle type.
	 */
	@NullMarked
	public enum NativeWindowHandleType {
		/**
		 * Platform default handle type (X11 on Linux).
		 */
		DEFAULT,
		/**
		 * Wayland.
		 */
		WAYLAND,

		/**
		 * Number of native enum values.
		 */
		COUNT;

		/**
		 * Native C enum layout.
		 */
		public static final ValueLayout.OfInt LAYOUT = ValueLayout.JAVA_INT;
		private static final NativeWindowHandleType[] VALUES = values();

		/**
		 * Returns the enum constant for a native C enum value.
		 * @param value the native enum value
		 * @return the matching enum constant
		 */
		public static NativeWindowHandleType fromValue(int value) {
			if (value >= 0 && value < VALUES.length) {
				return VALUES[value];
			}
			throw new IllegalArgumentException("Unknown NativeWindowHandleType value: " + value);
		}
	}

	/**
	 * Render frame enum.
	 */
	@NullMarked
	public enum RenderFrame {
		/**
		 * Renderer context is not created yet.
		 */
		NO_CONTEXT,
		/**
		 * Renderer context is created and rendering.
		 */
		RENDER,
		/**
		 * Renderer context wait for main thread signal timed out without rendering.
		 */
		TIMEOUT,
		/**
		 * Renderer context is getting destroyed.
		 */
		EXITING,

		/**
		 * Number of native enum values.
		 */
		COUNT;

		/**
		 * Native C enum layout.
		 */
		public static final ValueLayout.OfInt LAYOUT = ValueLayout.JAVA_INT;
		private static final RenderFrame[] VALUES = values();

		/**
		 * Returns the enum constant for a native C enum value.
		 * @param value the native enum value
		 * @return the matching enum constant
		 */
		public static RenderFrame fromValue(int value) {
			if (value >= 0 && value < VALUES.length) {
				return VALUES[value];
			}
			throw new IllegalArgumentException("Unknown RenderFrame value: " + value);
		}
	}

	/**
	 * Renderer capabilities.
	 */
	@NullMarked
	public static final class Caps extends NativeObject {
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
			MemoryLayout.sequenceLayout(4, Bgfx.Caps.GPU.LAYOUT).withName("gpu"),
			Bgfx.Caps.Limits.LAYOUT.withName("limits"),
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
		public Bgfx.Caps.Limits limits() {
			return new Bgfx.Caps.Limits(slice(MH_LIMITS, segment()));
		}

		/**
		 * Sets the native {@code limits} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Caps limits(Bgfx.Caps.Limits value) {
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


		/**
		 * GPU info.
		 */
		@NullMarked
		public static final class GPU extends NativeObject {
			/**
			 * Native C structure layout.
			 */
			public static final StructLayout LAYOUT = cStruct("bgfx_caps_gpu_t",
				ValueLayout.JAVA_SHORT.withName("vendorId"),
				ValueLayout.JAVA_SHORT.withName("deviceId"));
			private static final VarHandle VH_VENDORID = LAYOUT.varHandle(
				MemoryLayout.PathElement.groupElement("vendorId"));
			private static final VarHandle VH_DEVICEID = LAYOUT.varHandle(
				MemoryLayout.PathElement.groupElement("deviceId"));
			/**
			 * Wraps an existing native structure.
			 * @param segment native memory segment
			 */
			public GPU(MemorySegment segment) {
				super(segment, LAYOUT);
			}

			/**
			 * Allocates a native structure.
			 * @param allocator destination allocator
			 */
			public GPU(SegmentAllocator allocator) {
				super(allocator, LAYOUT);
			}

			/**
			 * Vendor PCI id. See {@code BGFX_PCI_ID_*}.
			 * @return the field value
			 */
			public @Unsigned short vendorId() {
				return (@Unsigned short) VH_VENDORID.get(segment(), 0L);
			}

			/**
			 * Sets the native {@code vendorId} field and returns {@code this}.
			 * @param value the new field value
			 */
			public GPU vendorId(@Unsigned short value) {
				VH_VENDORID.set(segment(), 0L, value);
				return this;
			}

			/**
			 * Sets the native {@code vendorId} field and returns {@code this}.
			 * @param value the new field value
			 */
			public GPU vendorId(int value) {
				return vendorId(NativeObject.toUnsignedShort(value));
			}

			/**
			 * Device id.
			 * @return the field value
			 */
			public @Unsigned short deviceId() {
				return (@Unsigned short) VH_DEVICEID.get(segment(), 0L);
			}

			/**
			 * Sets the native {@code deviceId} field and returns {@code this}.
			 * @param value the new field value
			 */
			public GPU deviceId(@Unsigned short value) {
				VH_DEVICEID.set(segment(), 0L, value);
				return this;
			}

			/**
			 * Sets the native {@code deviceId} field and returns {@code this}.
			 * @param value the new field value
			 */
			public GPU deviceId(int value) {
				return deviceId(NativeObject.toUnsignedShort(value));
			}
		}

		/**
		 * Renderer runtime limits.
		 */
		@NullMarked
		public static final class Limits extends NativeObject {
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
	}

	/**
	 * Internal data.
	 */
	@NullMarked
	public static final class InternalData extends NativeObject {
		/**
		 * Native C structure layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_internal_data_t",
			ValueLayout.ADDRESS.withName("caps"),
			ValueLayout.ADDRESS.withName("context"));
		private static final VarHandle VH_CAPS = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("caps"));
		private static final VarHandle VH_CONTEXT = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("context"));
		/**
		 * Wraps an existing native structure.
		 * @param segment native memory segment
		 */
		public InternalData(MemorySegment segment) {
			super(segment, LAYOUT);
		}

		/**
		 * Allocates a native structure.
		 * @param allocator destination allocator
		 */
		public InternalData(SegmentAllocator allocator) {
			super(allocator, LAYOUT);
		}

		/**
		 * Renderer capabilities.
		 * @return the field value
		 */
		public Caps caps() {
			return new Caps((MemorySegment) VH_CAPS.get(segment(), 0L));
		}

		/**
		 * Sets the native {@code caps} field and returns {@code this}.
		 * @param value the new field value
		 */
		public InternalData caps(Caps value) {
			VH_CAPS.set(segment(), 0L, address(value));
			return this;
		}

		/**
		 * GL context, or D3D device.
		 * @return the field value
		 */
		public MemorySegment context() {
			return address((MemorySegment) VH_CONTEXT.get(segment(), 0L));
		}

		/**
		 * Sets the native {@code context} field and returns {@code this}.
		 * @param value the new field value
		 */
		public InternalData context(MemorySegment value) {
			VH_CONTEXT.set(segment(), 0L, address(value));
			return this;
		}
	}

	/**
	 * Platform data.
	 */
	@NullMarked
	public static final class PlatformData extends NativeObject {
		/**
		 * Native C structure layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_platform_data_t",
			ValueLayout.ADDRESS.withName("context"),
			ValueLayout.ADDRESS.withName("queue"),
			ValueLayout.JAVA_INT.withName("type"));
		private static final VarHandle VH_CONTEXT = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("context"));
		private static final VarHandle VH_QUEUE = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("queue"));
		private static final VarHandle VH_TYPE = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("type"));
		/**
		 * Wraps an existing native structure.
		 * @param segment native memory segment
		 */
		public PlatformData(MemorySegment segment) {
			super(segment, LAYOUT);
		}

		/**
		 * Allocates a native structure.
		 * @param allocator destination allocator
		 */
		public PlatformData(SegmentAllocator allocator) {
			super(allocator, LAYOUT);
		}

		/**
		 * GL context, D3D device, or Vulkan device. If {@code NULL}, bgfx
		 * will create context/device.
		 * @return the field value
		 */
		public MemorySegment context() {
			return address((MemorySegment) VH_CONTEXT.get(segment(), 0L));
		}

		/**
		 * Sets the native {@code context} field and returns {@code this}.
		 * @param value the new field value
		 */
		public PlatformData context(MemorySegment value) {
			VH_CONTEXT.set(segment(), 0L, address(value));
			return this;
		}

		/**
		 * D3D12 Queue. If {@code NULL} bgfx will create queue.
		 * @return the field value
		 */
		public MemorySegment queue() {
			return address((MemorySegment) VH_QUEUE.get(segment(), 0L));
		}

		/**
		 * Sets the native {@code queue} field and returns {@code this}.
		 * @param value the new field value
		 */
		public PlatformData queue(MemorySegment value) {
			VH_QUEUE.set(segment(), 0L, address(value));
			return this;
		}

		/**
		 * Handle type. Needed for platforms having more than one option.
		 * @return the field value
		 */
		public NativeWindowHandleType type() {
			return NativeWindowHandleType.fromValue((int) VH_TYPE.get(segment(), 0L));
		}

		/**
		 * Sets the native {@code type} field and returns {@code this}.
		 * @param value the new field value
		 */
		public PlatformData type(NativeWindowHandleType value) {
			VH_TYPE.set(segment(), 0L, value.ordinal());
			return this;
		}
	}

	/**
	 * Swap chain description.
	 */
	@NullMarked
	public static final class SwapChain extends NativeObject {
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

	/**
	 * Initialization parameters used by {@code init}.
	 */
	@NullMarked
	public static final class Init extends NativeObject {
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
			Bgfx.Init.Limits.LAYOUT.withName("limits"),
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
		public Bgfx.Init.Limits limits() {
			return new Bgfx.Init.Limits(slice(MH_LIMITS, segment()));
		}

		/**
		 * Sets the native {@code limits} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Init limits(Bgfx.Init.Limits value) {
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


		/**
		 * Configurable runtime limits parameters.
		 */
		@NullMarked
		public static final class Limits extends NativeObject {
			/**
			 * Native C structure layout.
			 */
			public static final StructLayout LAYOUT = cStruct("bgfx_init_limits_t",
				ValueLayout.JAVA_SHORT.withName("maxEncoders"),
				ValueLayout.JAVA_INT.withName("numDrawCalls"),
				ValueLayout.JAVA_INT.withName("numDrawCallPeakFrames"),
				ValueLayout.JAVA_INT.withName("minViews"),
				ValueLayout.JAVA_INT.withName("minResourceCbSize"),
				ValueLayout.JAVA_INT.withName("maxTransientVbSize"),
				ValueLayout.JAVA_INT.withName("maxTransientIbSize"),
				ValueLayout.JAVA_INT.withName("minUniformBufferSize"));
			private static final VarHandle VH_MAXENCODERS = LAYOUT.varHandle(
				MemoryLayout.PathElement.groupElement("maxEncoders"));
			private static final VarHandle VH_NUMDRAWCALLS = LAYOUT.varHandle(
				MemoryLayout.PathElement.groupElement("numDrawCalls"));
			private static final VarHandle VH_NUMDRAWCALLPEAKFRAMES = LAYOUT.varHandle(
				MemoryLayout.PathElement.groupElement("numDrawCallPeakFrames"));
			private static final VarHandle VH_MINVIEWS = LAYOUT.varHandle(
				MemoryLayout.PathElement.groupElement("minViews"));
			private static final VarHandle VH_MINRESOURCECBSIZE = LAYOUT.varHandle(
				MemoryLayout.PathElement.groupElement("minResourceCbSize"));
			private static final VarHandle VH_MAXTRANSIENTVBSIZE = LAYOUT.varHandle(
				MemoryLayout.PathElement.groupElement("maxTransientVbSize"));
			private static final VarHandle VH_MAXTRANSIENTIBSIZE = LAYOUT.varHandle(
				MemoryLayout.PathElement.groupElement("maxTransientIbSize"));
			private static final VarHandle VH_MINUNIFORMBUFFERSIZE = LAYOUT.varHandle(
				MemoryLayout.PathElement.groupElement("minUniformBufferSize"));
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
			 * Maximum number of encoder threads.
			 * @return the field value
			 */
			public @Unsigned short maxEncoders() {
				return (@Unsigned short) VH_MAXENCODERS.get(segment(), 0L);
			}

			/**
			 * Sets the native {@code maxEncoders} field and returns {@code this}.
			 * @param value the new field value
			 */
			public Limits maxEncoders(@Unsigned short value) {
				VH_MAXENCODERS.set(segment(), 0L, value);
				return this;
			}

			/**
			 * Sets the native {@code maxEncoders} field and returns {@code this}.
			 * @param value the new field value
			 */
			public Limits maxEncoders(int value) {
				return maxEncoders(NativeObject.toUnsignedShort(value));
			}

			/**
			 * Number of draw calls per frame to reserve storage for. Rounded
			 * up to a multiple of {@code BGFX_CONFIG_DRAW_CALL_BLOCK}, which is also
			 * the minimum. This is a reservation, not a limit: submitting more
			 * than this grows the storage during the frame, up to
			 * {@code BGFX_CONFIG_MAX_DRAW_CALLS}. With
			 * {@code BGFX_CONFIG_DYNAMIC_FRAME_STORAGE} disabled nothing grows, and
			 * this is a hard limit that {@code Caps.Limits.maxDrawCalls} reports
			 * back; submissions past it are dropped. See
			 * {@code Stats.numDrawCallsPeak} to size it.
			 * @return the field value
			 */
			public @Unsigned int numDrawCalls() {
				return (@Unsigned int) VH_NUMDRAWCALLS.get(segment(), 0L);
			}

			/**
			 * Sets the native {@code numDrawCalls} field and returns {@code this}.
			 * @param value the new field value
			 */
			public Limits numDrawCalls(@Unsigned int value) {
				VH_NUMDRAWCALLS.set(segment(), 0L, value);
				return this;
			}

			/**
			 * Number of frames the draw-call peak (high-water mark) is observed
			 * before unused storage is released. Also used for view storage,
			 * resource command buffers and uniform buffers. Set to 0 to keep
			 * whatever has been allocated for the lifetime of the context. With
			 * {@code BGFX_CONFIG_DYNAMIC_FRAME_STORAGE} disabled draw/blit/rect storage
			 * is not resized; unused uniform and resource command buffer space
			 * is still released.
			 * @return the field value
			 */
			public @Unsigned int numDrawCallPeakFrames() {
				return (@Unsigned int) VH_NUMDRAWCALLPEAKFRAMES.get(segment(), 0L);
			}

			/**
			 * Sets the native {@code numDrawCallPeakFrames} field and returns {@code this}.
			 * @param value the new field value
			 */
			public Limits numDrawCallPeakFrames(@Unsigned int value) {
				VH_NUMDRAWCALLPEAKFRAMES.set(segment(), 0L, value);
				return this;
			}

			/**
			 * Minimum number of views to keep state for. Rounded up to a
			 * multiple of 64. This is a reservation, not a limit: a view past it
			 * gets storage when it is first set, up to
			 * {@code Caps.Limits.maxViews}, and that storage is released again once
			 * the views sharing it are all reset. Per-frame view data is sized
			 * by the views used in a frame, see {@code numDrawCallPeakFrames}. With
			 * {@code BGFX_CONFIG_DYNAMIC_FRAME_STORAGE} disabled storage for all views
			 * is allocated up front.
			 * @return the field value
			 */
			public @Unsigned int minViews() {
				return (@Unsigned int) VH_MINVIEWS.get(segment(), 0L);
			}

			/**
			 * Sets the native {@code minViews} field and returns {@code this}.
			 * @param value the new field value
			 */
			public Limits minViews(@Unsigned int value) {
				VH_MINVIEWS.set(segment(), 0L, value);
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
		}
	}

	/**
	 * Memory must be obtained by calling {@code alloc}, {@code copy}, or {@code makeRef}.
	 * <p>
	 * <strong>Attention:</strong> It is illegal to create this structure on stack and pass it to any bgfx API.
	 */
	@NullMarked
	public static final class Memory extends NativeObject {
		/**
		 * Native C structure layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_memory_t",
			ValueLayout.ADDRESS.withName("data"),
			ValueLayout.JAVA_INT.withName("size"));
		private static final VarHandle VH_DATA = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("data"));
		private static final VarHandle VH_SIZE = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("size"));
		/**
		 * Wraps an existing native structure.
		 * @param segment native memory segment
		 */
		public Memory(MemorySegment segment) {
			super(segment, LAYOUT);
		}

		/**
		 * Allocates a native structure.
		 * @param allocator destination allocator
		 */
		public Memory(SegmentAllocator allocator) {
			super(allocator, LAYOUT);
		}

		/**
		 * Pointer to data.
		 * @return the field value
		 */
		public MemorySegment data() {
			return address((MemorySegment) VH_DATA.get(segment(), 0L));
		}

		/**
		 * Sets the native {@code data} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Memory data(MemorySegment value) {
			VH_DATA.set(segment(), 0L, address(value));
			return this;
		}

		/**
		 * Data size.
		 * @return the field value
		 */
		public @Unsigned int size() {
			return (@Unsigned int) VH_SIZE.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code size} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Memory size(@Unsigned int value) {
			VH_SIZE.set(segment(), 0L, value);
			return this;
		}
	}

	/**
	 * Transient index buffer.
	 */
	@NullMarked
	public static final class TransientIndexBuffer extends NativeObject {
		/**
		 * Native C structure layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_transient_index_buffer_t",
			ValueLayout.ADDRESS.withName("data"),
			ValueLayout.JAVA_INT.withName("size"),
			ValueLayout.JAVA_INT.withName("startIndex"),
			IndexBufferHandle.LAYOUT.withName("handle"),
			ValueLayout.JAVA_BOOLEAN.withName("isIndex16"));
		private static final VarHandle VH_DATA = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("data"));
		private static final VarHandle VH_SIZE = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("size"));
		private static final VarHandle VH_STARTINDEX = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("startIndex"));
		private static final MethodHandle MH_HANDLE = LAYOUT.sliceHandle(
			MemoryLayout.PathElement.groupElement("handle"));
		private static final VarHandle VH_ISINDEX16 = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("isIndex16"));
		/**
		 * Wraps an existing native structure.
		 * @param segment native memory segment
		 */
		public TransientIndexBuffer(MemorySegment segment) {
			super(segment, LAYOUT);
		}

		/**
		 * Allocates a native structure.
		 * @param allocator destination allocator
		 */
		public TransientIndexBuffer(SegmentAllocator allocator) {
			super(allocator, LAYOUT);
		}

		/**
		 * Pointer to data.
		 * @return the field value
		 */
		public MemorySegment data() {
			return address((MemorySegment) VH_DATA.get(segment(), 0L));
		}

		/**
		 * Sets the native {@code data} field and returns {@code this}.
		 * @param value the new field value
		 */
		public TransientIndexBuffer data(MemorySegment value) {
			VH_DATA.set(segment(), 0L, address(value));
			return this;
		}

		/**
		 * Data size.
		 * @return the field value
		 */
		public @Unsigned int size() {
			return (@Unsigned int) VH_SIZE.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code size} field and returns {@code this}.
		 * @param value the new field value
		 */
		public TransientIndexBuffer size(@Unsigned int value) {
			VH_SIZE.set(segment(), 0L, value);
			return this;
		}

		/**
		 * First index.
		 * @return the field value
		 */
		public @Unsigned int startIndex() {
			return (@Unsigned int) VH_STARTINDEX.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code startIndex} field and returns {@code this}.
		 * @param value the new field value
		 */
		public TransientIndexBuffer startIndex(@Unsigned int value) {
			VH_STARTINDEX.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Index buffer handle.
		 * @return the field value
		 */
		public IndexBufferHandle handle() {
			return IndexBufferHandle.read(slice(MH_HANDLE, segment()));
		}

		/**
		 * Sets the native {@code handle} field and returns {@code this}.
		 * @param value the new field value
		 */
		public TransientIndexBuffer handle(IndexBufferHandle value) {
			value.write(slice(MH_HANDLE, segment()));
			return this;
		}

		/**
		 * Index buffer format is 16-bits if true, otherwise it is 32-bit.
		 * @return the field value
		 */
		public boolean isIndex16() {
			return (boolean) VH_ISINDEX16.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code isIndex16} field and returns {@code this}.
		 * @param value the new field value
		 */
		public TransientIndexBuffer isIndex16(boolean value) {
			VH_ISINDEX16.set(segment(), 0L, value);
			return this;
		}
	}

	/**
	 * Transient vertex buffer.
	 */
	@NullMarked
	public static final class TransientVertexBuffer extends NativeObject {
		/**
		 * Native C structure layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_transient_vertex_buffer_t",
			ValueLayout.ADDRESS.withName("data"),
			ValueLayout.JAVA_INT.withName("size"),
			ValueLayout.JAVA_INT.withName("startVertex"),
			ValueLayout.JAVA_SHORT.withName("stride"),
			VertexBufferHandle.LAYOUT.withName("handle"),
			VertexLayoutHandle.LAYOUT.withName("layoutHandle"));
		private static final VarHandle VH_DATA = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("data"));
		private static final VarHandle VH_SIZE = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("size"));
		private static final VarHandle VH_STARTVERTEX = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("startVertex"));
		private static final VarHandle VH_STRIDE = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("stride"));
		private static final MethodHandle MH_HANDLE = LAYOUT.sliceHandle(
			MemoryLayout.PathElement.groupElement("handle"));
		private static final MethodHandle MH_LAYOUTHANDLE = LAYOUT.sliceHandle(
			MemoryLayout.PathElement.groupElement("layoutHandle"));
		/**
		 * Wraps an existing native structure.
		 * @param segment native memory segment
		 */
		public TransientVertexBuffer(MemorySegment segment) {
			super(segment, LAYOUT);
		}

		/**
		 * Allocates a native structure.
		 * @param allocator destination allocator
		 */
		public TransientVertexBuffer(SegmentAllocator allocator) {
			super(allocator, LAYOUT);
		}

		/**
		 * Pointer to data.
		 * @return the field value
		 */
		public MemorySegment data() {
			return address((MemorySegment) VH_DATA.get(segment(), 0L));
		}

		/**
		 * Sets the native {@code data} field and returns {@code this}.
		 * @param value the new field value
		 */
		public TransientVertexBuffer data(MemorySegment value) {
			VH_DATA.set(segment(), 0L, address(value));
			return this;
		}

		/**
		 * Data size.
		 * @return the field value
		 */
		public @Unsigned int size() {
			return (@Unsigned int) VH_SIZE.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code size} field and returns {@code this}.
		 * @param value the new field value
		 */
		public TransientVertexBuffer size(@Unsigned int value) {
			VH_SIZE.set(segment(), 0L, value);
			return this;
		}

		/**
		 * First vertex.
		 * @return the field value
		 */
		public @Unsigned int startVertex() {
			return (@Unsigned int) VH_STARTVERTEX.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code startVertex} field and returns {@code this}.
		 * @param value the new field value
		 */
		public TransientVertexBuffer startVertex(@Unsigned int value) {
			VH_STARTVERTEX.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Vertex stride.
		 * @return the field value
		 */
		public @Unsigned short stride() {
			return (@Unsigned short) VH_STRIDE.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code stride} field and returns {@code this}.
		 * @param value the new field value
		 */
		public TransientVertexBuffer stride(@Unsigned short value) {
			VH_STRIDE.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code stride} field and returns {@code this}.
		 * @param value the new field value
		 */
		public TransientVertexBuffer stride(int value) {
			return stride(NativeObject.toUnsignedShort(value));
		}

		/**
		 * Vertex buffer handle.
		 * @return the field value
		 */
		public VertexBufferHandle handle() {
			return VertexBufferHandle.read(slice(MH_HANDLE, segment()));
		}

		/**
		 * Sets the native {@code handle} field and returns {@code this}.
		 * @param value the new field value
		 */
		public TransientVertexBuffer handle(VertexBufferHandle value) {
			value.write(slice(MH_HANDLE, segment()));
			return this;
		}

		/**
		 * Vertex layout handle.
		 * @return the field value
		 */
		public VertexLayoutHandle layoutHandle() {
			return VertexLayoutHandle.read(slice(MH_LAYOUTHANDLE, segment()));
		}

		/**
		 * Sets the native {@code layoutHandle} field and returns {@code this}.
		 * @param value the new field value
		 */
		public TransientVertexBuffer layoutHandle(VertexLayoutHandle value) {
			value.write(slice(MH_LAYOUTHANDLE, segment()));
			return this;
		}
	}

	/**
	 * Instance data buffer info.
	 */
	@NullMarked
	public static final class InstanceDataBuffer extends NativeObject {
		/**
		 * Native C structure layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_instance_data_buffer_t",
			ValueLayout.ADDRESS.withName("data"),
			ValueLayout.JAVA_INT.withName("size"),
			ValueLayout.JAVA_INT.withName("offset"),
			ValueLayout.JAVA_INT.withName("num"),
			ValueLayout.JAVA_SHORT.withName("stride"),
			VertexBufferHandle.LAYOUT.withName("handle"));
		private static final VarHandle VH_DATA = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("data"));
		private static final VarHandle VH_SIZE = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("size"));
		private static final VarHandle VH_OFFSET = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("offset"));
		private static final VarHandle VH_NUM = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("num"));
		private static final VarHandle VH_STRIDE = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("stride"));
		private static final MethodHandle MH_HANDLE = LAYOUT.sliceHandle(
			MemoryLayout.PathElement.groupElement("handle"));
		/**
		 * Wraps an existing native structure.
		 * @param segment native memory segment
		 */
		public InstanceDataBuffer(MemorySegment segment) {
			super(segment, LAYOUT);
		}

		/**
		 * Allocates a native structure.
		 * @param allocator destination allocator
		 */
		public InstanceDataBuffer(SegmentAllocator allocator) {
			super(allocator, LAYOUT);
		}

		/**
		 * Pointer to data.
		 * @return the field value
		 */
		public MemorySegment data() {
			return address((MemorySegment) VH_DATA.get(segment(), 0L));
		}

		/**
		 * Sets the native {@code data} field and returns {@code this}.
		 * @param value the new field value
		 */
		public InstanceDataBuffer data(MemorySegment value) {
			VH_DATA.set(segment(), 0L, address(value));
			return this;
		}

		/**
		 * Data size.
		 * @return the field value
		 */
		public @Unsigned int size() {
			return (@Unsigned int) VH_SIZE.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code size} field and returns {@code this}.
		 * @param value the new field value
		 */
		public InstanceDataBuffer size(@Unsigned int value) {
			VH_SIZE.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Offset in vertex buffer.
		 * @return the field value
		 */
		public @Unsigned int offset() {
			return (@Unsigned int) VH_OFFSET.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code offset} field and returns {@code this}.
		 * @param value the new field value
		 */
		public InstanceDataBuffer offset(@Unsigned int value) {
			VH_OFFSET.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Number of instances.
		 * @return the field value
		 */
		public @Unsigned int num() {
			return (@Unsigned int) VH_NUM.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code num} field and returns {@code this}.
		 * @param value the new field value
		 */
		public InstanceDataBuffer num(@Unsigned int value) {
			VH_NUM.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Vertex buffer stride.
		 * @return the field value
		 */
		public @Unsigned short stride() {
			return (@Unsigned short) VH_STRIDE.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code stride} field and returns {@code this}.
		 * @param value the new field value
		 */
		public InstanceDataBuffer stride(@Unsigned short value) {
			VH_STRIDE.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code stride} field and returns {@code this}.
		 * @param value the new field value
		 */
		public InstanceDataBuffer stride(int value) {
			return stride(NativeObject.toUnsignedShort(value));
		}

		/**
		 * Vertex buffer object handle.
		 * @return the field value
		 */
		public VertexBufferHandle handle() {
			return VertexBufferHandle.read(slice(MH_HANDLE, segment()));
		}

		/**
		 * Sets the native {@code handle} field and returns {@code this}.
		 * @param value the new field value
		 */
		public InstanceDataBuffer handle(VertexBufferHandle value) {
			value.write(slice(MH_HANDLE, segment()));
			return this;
		}
	}

	/**
	 * Region of a texture, used as the source or destination of a blit, or as
	 * the region handed to {@code read}.
	 * <p>
	 * Every field defaults to zero, and zero always means "the natural whole".
	 * {@code { .handle = tex }} therefore addresses all of mip 0.
	 */
	@NullMarked
	public static final class TextureRegion extends NativeObject {
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

	/**
	 * Region of a buffer, used as the source or destination of a blit, or as the
	 * region handed to {@code read}.
	 * <p>
	 * {@code rowPitch} and {@code slicePitch} describe how texture data is laid out in the
	 * buffer, and are ignored when the other end of the blit is also a buffer.
	 * Both are in bytes, and 0 selects the tightly packed layout: a row pitch of
	 * the region width in blocks multiplied by the block size, and a slice pitch
	 * of that row pitch multiplied by the region height in blocks.
	 * <p>
	 * A pitch the backend cannot copy natively is repacked by bgfx, which costs
	 * an extra pass over the data. {@code Caps.Limits.blitRowPitchAlign} and
	 * {@code blitOffsetAlign} report what the backend copies directly, and
	 * {@code BufferRegion.init} fills in a layout that matches them.
	 */
	@NullMarked
	public static final class BufferRegion extends NativeObject {
		/**
		 * Native C structure layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_buffer_region_t",
			BufferHandle.LAYOUT.withName("handle"),
			ValueLayout.JAVA_INT.withName("offset"),
			ValueLayout.JAVA_INT.withName("size"),
			ValueLayout.JAVA_INT.withName("rowPitch"),
			ValueLayout.JAVA_INT.withName("slicePitch"));
		private static final MethodHandle MH_HANDLE = LAYOUT.sliceHandle(
			MemoryLayout.PathElement.groupElement("handle"));
		private static final VarHandle VH_OFFSET = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("offset"));
		private static final VarHandle VH_SIZE = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("size"));
		private static final VarHandle VH_ROWPITCH = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("rowPitch"));
		private static final VarHandle VH_SLICEPITCH = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("slicePitch"));
		/**
		 * Wraps an existing native structure.
		 * @param segment native memory segment
		 */
		public BufferRegion(MemorySegment segment) {
			super(segment, LAYOUT);
		}

		/**
		 * Allocates a native structure.
		 * @param allocator destination allocator
		 */
		public BufferRegion(SegmentAllocator allocator) {
			super(allocator, LAYOUT);
		}

		/**
		 * Buffer handle.
		 * @return the field value
		 */
		public BufferHandle handle() {
			return BufferHandle.read(slice(MH_HANDLE, segment()));
		}

		/**
		 * Sets the native {@code handle} field and returns {@code this}.
		 * @param value the new field value
		 */
		public BufferRegion handle(BufferHandle value) {
			value.writeTagged(slice(MH_HANDLE, segment()));
			return this;
		}

		/**
		 * Byte offset into the buffer.
		 * @return the field value
		 */
		public @Unsigned int offset() {
			return (@Unsigned int) VH_OFFSET.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code offset} field and returns {@code this}.
		 * @param value the new field value
		 */
		public BufferRegion offset(@Unsigned int value) {
			VH_OFFSET.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Number of bytes. Only used when both ends of a blit are
		 * buffers, or by {@code read}. 0 uses the rest of the buffer.
		 * @return the field value
		 */
		public @Unsigned int size() {
			return (@Unsigned int) VH_SIZE.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code size} field and returns {@code this}.
		 * @param value the new field value
		 */
		public BufferRegion size(@Unsigned int value) {
			VH_SIZE.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Distance in bytes between the start of two consecutive rows
		 * of blocks. 0 is tightly packed.
		 * @return the field value
		 */
		public @Unsigned int rowPitch() {
			return (@Unsigned int) VH_ROWPITCH.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code rowPitch} field and returns {@code this}.
		 * @param value the new field value
		 */
		public BufferRegion rowPitch(@Unsigned int value) {
			VH_ROWPITCH.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Distance in bytes between the start of two consecutive
		 * slices, layers or cube faces. 0 is tightly packed.
		 * @return the field value
		 */
		public @Unsigned int slicePitch() {
			return (@Unsigned int) VH_SLICEPITCH.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code slicePitch} field and returns {@code this}.
		 * @param value the new field value
		 */
		public BufferRegion slicePitch(@Unsigned int value) {
			VH_SLICEPITCH.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Fill {@code rowPitch}, {@code slicePitch} and {@code size} with the layout the backend copies
		 * fastest for {@code _texture}, and round {@code offset} up to {@code Caps.Limits.blitOffsetAlign}.
		 * {@code handle} is left untouched, so {@code size} can be used to create the buffer the
		 * region will point at.
		 * @param _texture Texture region the buffer is copied to or from.
		 */
		public final void initTexture(TextureRegion _texture) {
			try {
				MH_BUFFER_REGION_INIT_TEXTURE.invokeExact(segment(), address(_texture));
			} catch (Throwable ex) {
				throw invocationFailure(ex);
			}
		}

		/**
		 * Fill in the region a blit between two buffers copies. {@code rowPitch} and
		 * {@code slicePitch} are left at zero, since neither end of such a blit is a
		 * texture.
		 * @param _handle Buffer handle.
		 * @param _offset Byte offset into the buffer.
		 * @param _size Number of bytes. 0 uses the rest of the buffer.
		 */
		public final void initBuffer(BufferHandle _handle, @Unsigned int _offset, @Unsigned int _size) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_BUFFER_REGION_INIT_BUFFER.invokeExact(segment(), _handle.allocateTagged(arena), _offset, _size);
				}
			} catch (Throwable ex) {
				throw invocationFailure(ex);
			}
		}
	}

	/**
	 * Texture info.
	 */
	@NullMarked
	public static final class TextureInfo extends NativeObject {
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

	/**
	 * Video decoder initialization. Serialized into the Memory passed to
	 * {@code createTexture2D}. When the memory blob begins with {@code magic}, bgfx
	 * infers the texture is a video decode destination (the caller need not set
	 * any extra texture flag). Everything else the renderer needs about the
	 * stream (chroma format, bit depth, profile, level, coded dimensions, DPB
	 * layout, color metadata) is parsed out of the codec parameter sets at
	 * create time.
	 */
	@NullMarked
	public static final class VideoDecoderInit extends NativeObject {
		/**
		 * Native C structure layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_video_decoder_init_t",
			ValueLayout.JAVA_INT.withName("magic"),
			ValueLayout.JAVA_INT.withName("codec"),
			ValueLayout.ADDRESS.withName("parameterSets"),
			ValueLayout.JAVA_INT.withName("parameterSetsSize"),
			ValueLayout.JAVA_INT.withName("cachedAuBytes"),
			ValueLayout.JAVA_BYTE.withName("flags"));
		private static final VarHandle VH_MAGIC = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("magic"));
		private static final VarHandle VH_CODEC = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("codec"));
		private static final VarHandle VH_PARAMETERSETS = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("parameterSets"));
		private static final VarHandle VH_PARAMETERSETSSIZE = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("parameterSetsSize"));
		private static final VarHandle VH_CACHEDAUBYTES = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("cachedAuBytes"));
		private static final VarHandle VH_FLAGS = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("flags"));
		/**
		 * Wraps an existing native structure.
		 * @param segment native memory segment
		 */
		public VideoDecoderInit(MemorySegment segment) {
			super(segment, LAYOUT);
		}

		/**
		 * Allocates a native structure.
		 * @param allocator destination allocator
		 */
		public VideoDecoderInit(SegmentAllocator allocator) {
			super(allocator, LAYOUT);
		}

		/**
		 * Structure magic. Must be {@code BX_MAKEFOURCC('V', 'D', 'I', 0x0)}.
		 * @return the field value
		 */
		public @Unsigned int magic() {
			return (@Unsigned int) VH_MAGIC.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code magic} field and returns {@code this}.
		 * @param value the new field value
		 */
		public VideoDecoderInit magic(@Unsigned int value) {
			VH_MAGIC.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Video codec. See: {@code VideoCodec}.
		 * @return the field value
		 */
		public VideoCodec codec() {
			return VideoCodec.fromValue((int) VH_CODEC.get(segment(), 0L));
		}

		/**
		 * Sets the native {@code codec} field and returns {@code this}.
		 * @param value the new field value
		 */
		public VideoDecoderInit codec(VideoCodec value) {
			VH_CODEC.set(segment(), 0L, value.ordinal());
			return this;
		}

		/**
		 * Codec parameter sets (Annex B for H.264/H.265, OBUs for AV1).
		 * @return the field value
		 */
		public MemorySegment parameterSets() {
			return address((MemorySegment) VH_PARAMETERSETS.get(segment(), 0L));
		}

		/**
		 * Sets the native {@code parameterSets} field and returns {@code this}.
		 * @param value the new field value
		 */
		public VideoDecoderInit parameterSets(MemorySegment value) {
			VH_PARAMETERSETS.set(segment(), 0L, address(value));
			return this;
		}

		/**
		 * Parameter sets size in bytes.
		 * @return the field value
		 */
		public @Unsigned int parameterSetsSize() {
			return (@Unsigned int) VH_PARAMETERSETSSIZE.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code parameterSetsSize} field and returns {@code this}.
		 * @param value the new field value
		 */
		public VideoDecoderInit parameterSetsSize(@Unsigned int value) {
			VH_PARAMETERSETSSIZE.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Soft cap (in bytes) on the streaming access-unit FIFO (when
		 * {@code BGFX_VIDEO_DECODER_INIT_RETAIN} is NOT set). 0 selects the
		 * default. Ignored in RETAIN mode (the retain cache is unbounded).
		 * @return the field value
		 */
		public @Unsigned int cachedAuBytes() {
			return (@Unsigned int) VH_CACHEDAUBYTES.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code cachedAuBytes} field and returns {@code this}.
		 * @param value the new field value
		 */
		public VideoDecoderInit cachedAuBytes(@Unsigned int value) {
			VH_CACHEDAUBYTES.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Decoder lifetime flags. See: {@code BGFX_VIDEO_DECODER_INIT_*}.
		 * @return the field value
		 */
		public @Unsigned byte flags() {
			return (@Unsigned byte) VH_FLAGS.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code flags} field and returns {@code this}.
		 * @param value the new field value
		 */
		public VideoDecoderInit flags(@Unsigned byte value) {
			VH_FLAGS.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code flags} field and returns {@code this}.
		 * @param value the new field value
		 */
		public VideoDecoderInit flags(int value) {
			return flags(NativeObject.toUnsignedByte(value));
		}
	}

	/**
	 * One access unit entry inside a {@code VideoDecoderFrame} batch. The bitstream
	 * for the AU lives at offset {@code Σ aus[0..ii].size} inside the frame's
	 * {@code bitstream} buffer (access units are stored back-to-back in decode /
	 * submission order).
	 */
	@NullMarked
	public static final class VideoDecoderAu extends NativeObject {
		/**
		 * Native C structure layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_video_decoder_au_t",
			ValueLayout.JAVA_INT.withName("size"),
			ValueLayout.JAVA_LONG.withName("ptsUs"));
		private static final VarHandle VH_SIZE = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("size"));
		private static final VarHandle VH_PTSUS = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("ptsUs"));
		/**
		 * Wraps an existing native structure.
		 * @param segment native memory segment
		 */
		public VideoDecoderAu(MemorySegment segment) {
			super(segment, LAYOUT);
		}

		/**
		 * Allocates a native structure.
		 * @param allocator destination allocator
		 */
		public VideoDecoderAu(SegmentAllocator allocator) {
			super(allocator, LAYOUT);
		}

		/**
		 * Access unit size in bytes.
		 * @return the field value
		 */
		public @Unsigned int size() {
			return (@Unsigned int) VH_SIZE.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code size} field and returns {@code this}.
		 * @param value the new field value
		 */
		public VideoDecoderAu size(@Unsigned int value) {
			VH_SIZE.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Presentation timestamp in microseconds for this access unit (container-provided).
		 * @return the field value
		 */
		public long ptsUs() {
			return (long) VH_PTSUS.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code ptsUs} field and returns {@code this}.
		 * @param value the new field value
		 */
		public VideoDecoderAu ptsUs(long value) {
			VH_PTSUS.set(segment(), 0L, value);
			return this;
		}
	}

	/**
	 * Video decoder per-frame submission. Serialized into the Memory passed
	 * to {@code updateTexture2D} for a video decode destination texture. The
	 * renderer parses the slice / tile-group header out of the bitstream and
	 * translates it to the backend-specific decoder arguments.
	 * <p>
	 * A single call may submit a batch of access units: {@code bitstream} is the
	 * back-to-back concatenation of {@code numAus} access units, and {@code aus[ii]}
	 * holds the size and PTS of each. AUs are enqueued in array order
	 * (which is the codec's decode order). Set {@code numAus == 0} (and
	 * {@code bitstream == NULL}) for a presentation-only tick that only advances
	 * the playback clock.
	 * <p>
	 * The {@code bitstream} and {@code aus} pointers must remain valid until bgfx has
	 * consumed the submission ({@code copy} only deep-copies the
	 * {@code VideoDecoderFrame} struct itself, not the buffers it references).
	 */
	@NullMarked
	public static final class VideoDecoderFrame extends NativeObject {
		/**
		 * Native C structure layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_video_decoder_frame_t",
			ValueLayout.JAVA_INT.withName("magic"),
			ValueLayout.ADDRESS.withName("bitstream"),
			ValueLayout.ADDRESS.withName("aus"),
			ValueLayout.JAVA_INT.withName("numAus"),
			ValueLayout.JAVA_LONG.withName("presentationTimeUs"),
			ValueLayout.JAVA_BYTE.withName("flags"));
		private static final VarHandle VH_MAGIC = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("magic"));
		private static final VarHandle VH_BITSTREAM = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("bitstream"));
		private static final VarHandle VH_AUS = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("aus"));
		private static final VarHandle VH_NUMAUS = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("numAus"));
		private static final VarHandle VH_PRESENTATIONTIMEUS = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("presentationTimeUs"));
		private static final VarHandle VH_FLAGS = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("flags"));
		/**
		 * Wraps an existing native structure.
		 * @param segment native memory segment
		 */
		public VideoDecoderFrame(MemorySegment segment) {
			super(segment, LAYOUT);
		}

		/**
		 * Allocates a native structure.
		 * @param allocator destination allocator
		 */
		public VideoDecoderFrame(SegmentAllocator allocator) {
			super(allocator, LAYOUT);
		}

		/**
		 * Structure magic. Must be {@code BX_MAKEFOURCC('V', 'D', 'F', 0x0)}.
		 * @return the field value
		 */
		public @Unsigned int magic() {
			return (@Unsigned int) VH_MAGIC.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code magic} field and returns {@code this}.
		 * @param value the new field value
		 */
		public VideoDecoderFrame magic(@Unsigned int value) {
			VH_MAGIC.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Concatenated access-unit bitstream (decode order). NULL for presentation-only ticks.
		 * @return the field value
		 */
		public MemorySegment bitstream() {
			return address((MemorySegment) VH_BITSTREAM.get(segment(), 0L));
		}

		/**
		 * Sets the native {@code bitstream} field and returns {@code this}.
		 * @param value the new field value
		 */
		public VideoDecoderFrame bitstream(MemorySegment value) {
			VH_BITSTREAM.set(segment(), 0L, address(value));
			return this;
		}

		/**
		 * Per-AU size and PTS array. NULL when {@code numAus == 0}.
		 * @return the field value
		 */
		public VideoDecoderAu aus() {
			return new VideoDecoderAu((MemorySegment) VH_AUS.get(segment(), 0L));
		}

		/**
		 * Sets the native {@code aus} field and returns {@code this}.
		 * @param value the new field value
		 */
		public VideoDecoderFrame aus(VideoDecoderAu value) {
			VH_AUS.set(segment(), 0L, address(value));
			return this;
		}

		/**
		 * Number of access units in this batch. 0 for presentation-only ticks.
		 * @return the field value
		 */
		public @Unsigned int numAus() {
			return (@Unsigned int) VH_NUMAUS.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code numAus} field and returns {@code this}.
		 * @param value the new field value
		 */
		public VideoDecoderFrame numAus(@Unsigned int value) {
			VH_NUMAUS.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Current playback wall-clock time. Driver dispatches the picture whose {@code ptsUs}
		 * best matches. Must be monotonically non-decreasing between non-{@code SET} calls.
		 * @return the field value
		 */
		public long presentationTimeUs() {
			return (long) VH_PRESENTATIONTIMEUS.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code presentationTimeUs} field and returns {@code this}.
		 * @param value the new field value
		 */
		public VideoDecoderFrame presentationTimeUs(long value) {
			VH_PRESENTATIONTIMEUS.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Per-frame submission flags. See: {@code BGFX_VIDEO_DECODE_FRAME_*}.
		 * @return the field value
		 */
		public @Unsigned byte flags() {
			return (@Unsigned byte) VH_FLAGS.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code flags} field and returns {@code this}.
		 * @param value the new field value
		 */
		public VideoDecoderFrame flags(@Unsigned byte value) {
			VH_FLAGS.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code flags} field and returns {@code this}.
		 * @param value the new field value
		 */
		public VideoDecoderFrame flags(int value) {
			return flags(NativeObject.toUnsignedByte(value));
		}
	}

	/**
	 * Uniform info.
	 */
	@NullMarked
	public static final class UniformInfo extends NativeObject {
		/**
		 * Native C structure layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_uniform_info_t",
			MemoryLayout.sequenceLayout(256, ValueLayout.JAVA_BYTE).withName("name"),
			ValueLayout.JAVA_INT.withName("type"),
			ValueLayout.JAVA_SHORT.withName("num"));
		private static final MethodHandle MH_NAME = LAYOUT.sliceHandle(
			MemoryLayout.PathElement.groupElement("name"));
		private static final VarHandle VH_TYPE = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("type"));
		private static final VarHandle VH_NUM = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("num"));
		/**
		 * Wraps an existing native structure.
		 * @param segment native memory segment
		 */
		public UniformInfo(MemorySegment segment) {
			super(segment, LAYOUT);
		}

		/**
		 * Allocates a native structure.
		 * @param allocator destination allocator
		 */
		public UniformInfo(SegmentAllocator allocator) {
			super(allocator, LAYOUT);
		}

		/**
		 * Uniform name.
		 * @return a segment view of the inline array
		 */
		public MemorySegment name() {
			return slice(MH_NAME, segment());
		}

		/**
		 * Uniform type.
		 * @return the field value
		 */
		public UniformType type() {
			return UniformType.fromValue((int) VH_TYPE.get(segment(), 0L));
		}

		/**
		 * Sets the native {@code type} field and returns {@code this}.
		 * @param value the new field value
		 */
		public UniformInfo type(UniformType value) {
			VH_TYPE.set(segment(), 0L, value.ordinal());
			return this;
		}

		/**
		 * Number of elements in array.
		 * @return the field value
		 */
		public @Unsigned short num() {
			return (@Unsigned short) VH_NUM.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code num} field and returns {@code this}.
		 * @param value the new field value
		 */
		public UniformInfo num(@Unsigned short value) {
			VH_NUM.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code num} field and returns {@code this}.
		 * @param value the new field value
		 */
		public UniformInfo num(int value) {
			return num(NativeObject.toUnsignedShort(value));
		}
	}

	/**
	 * Frame buffer texture attachment info.
	 */
	@NullMarked
	public static final class Attachment extends NativeObject {
		/**
		 * Native C structure layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_attachment_t",
			ValueLayout.JAVA_INT.withName("access"),
			TextureHandle.LAYOUT.withName("handle"),
			ValueLayout.JAVA_SHORT.withName("mip"),
			ValueLayout.JAVA_SHORT.withName("layer"),
			ValueLayout.JAVA_SHORT.withName("numLayers"),
			ValueLayout.JAVA_BYTE.withName("flags"));
		private static final VarHandle VH_ACCESS = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("access"));
		private static final MethodHandle MH_HANDLE = LAYOUT.sliceHandle(
			MemoryLayout.PathElement.groupElement("handle"));
		private static final VarHandle VH_MIP = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("mip"));
		private static final VarHandle VH_LAYER = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("layer"));
		private static final VarHandle VH_NUMLAYERS = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("numLayers"));
		private static final VarHandle VH_FLAGS = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("flags"));
		/**
		 * Wraps an existing native structure.
		 * @param segment native memory segment
		 */
		public Attachment(MemorySegment segment) {
			super(segment, LAYOUT);
		}

		/**
		 * Allocates a native structure.
		 * @param allocator destination allocator
		 */
		public Attachment(SegmentAllocator allocator) {
			super(allocator, LAYOUT);
		}

		/**
		 * Attachment access. See {@code Access}.
		 * @return the field value
		 */
		public Access access() {
			return Access.fromValue((int) VH_ACCESS.get(segment(), 0L));
		}

		/**
		 * Sets the native {@code access} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Attachment access(Access value) {
			VH_ACCESS.set(segment(), 0L, value.ordinal());
			return this;
		}

		/**
		 * Render target texture handle.
		 * @return the field value
		 */
		public TextureHandle handle() {
			return TextureHandle.read(slice(MH_HANDLE, segment()));
		}

		/**
		 * Sets the native {@code handle} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Attachment handle(TextureHandle value) {
			value.write(slice(MH_HANDLE, segment()));
			return this;
		}

		/**
		 * Mip level.
		 * @return the field value
		 */
		public @Unsigned short mip() {
			return (@Unsigned short) VH_MIP.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code mip} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Attachment mip(@Unsigned short value) {
			VH_MIP.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code mip} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Attachment mip(int value) {
			return mip(NativeObject.toUnsignedShort(value));
		}

		/**
		 * Cubemap side or depth layer/slice to use.
		 * @return the field value
		 */
		public @Unsigned short layer() {
			return (@Unsigned short) VH_LAYER.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code layer} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Attachment layer(@Unsigned short value) {
			VH_LAYER.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code layer} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Attachment layer(int value) {
			return layer(NativeObject.toUnsignedShort(value));
		}

		/**
		 * Number of texture layer/slice(s) in array to use.
		 * @return the field value
		 */
		public @Unsigned short numLayers() {
			return (@Unsigned short) VH_NUMLAYERS.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code numLayers} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Attachment numLayers(@Unsigned short value) {
			VH_NUMLAYERS.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code numLayers} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Attachment numLayers(int value) {
			return numLayers(NativeObject.toUnsignedShort(value));
		}

		/**
		 * Attachment flags. See: {@code BGFX_ATTACHMENT_*}
		 * @return the field value
		 */
		public @Unsigned byte flags() {
			return (@Unsigned byte) VH_FLAGS.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code flags} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Attachment flags(@Unsigned byte value) {
			VH_FLAGS.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code flags} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Attachment flags(int value) {
			return flags(NativeObject.toUnsignedByte(value));
		}

		/**
		 * Init attachment.
		 * @param _handle Render target texture handle.
		 * @param _access Access. See {@code Access}.
		 * @param _layer Cubemap side or depth layer/slice to use.
		 * @param _numLayers Number of texture layer/slice(s) in array to use.
		 * @param _mip Mip level.
		 * @param _flags Attachment flags. See: {@code BGFX_ATTACHMENT_*}
		 */
		public final void init(TextureHandle _handle, Access _access, @Unsigned short _layer, @Unsigned short _numLayers, @Unsigned short _mip, @Unsigned byte _flags) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ATTACHMENT_INIT.invokeExact(segment(), _handle.allocate(arena), _access.ordinal(), _layer, _numLayers, _mip, _flags);
				}
			} catch (Throwable ex) {
				throw invocationFailure(ex);
			}
		}
	}

	/**
	 * Transform data.
	 */
	@NullMarked
	public static final class Transform extends NativeObject {
		/**
		 * Native C structure layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_transform_t",
			ValueLayout.ADDRESS.withName("data"),
			ValueLayout.JAVA_SHORT.withName("num"));
		private static final VarHandle VH_DATA = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("data"));
		private static final VarHandle VH_NUM = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("num"));
		/**
		 * Wraps an existing native structure.
		 * @param segment native memory segment
		 */
		public Transform(MemorySegment segment) {
			super(segment, LAYOUT);
		}

		/**
		 * Allocates a native structure.
		 * @param allocator destination allocator
		 */
		public Transform(SegmentAllocator allocator) {
			super(allocator, LAYOUT);
		}

		/**
		 * Pointer to first 4x4 matrix.
		 * @return the field value
		 */
		public MemorySegment data() {
			return address((MemorySegment) VH_DATA.get(segment(), 0L));
		}

		/**
		 * Sets the native {@code data} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Transform data(MemorySegment value) {
			VH_DATA.set(segment(), 0L, address(value));
			return this;
		}

		/**
		 * Number of matrices.
		 * @return the field value
		 */
		public @Unsigned short num() {
			return (@Unsigned short) VH_NUM.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code num} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Transform num(@Unsigned short value) {
			VH_NUM.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code num} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Transform num(int value) {
			return num(NativeObject.toUnsignedShort(value));
		}
	}

	/**
	 * View stats.
	 */
	@NullMarked
	public static final class ViewStats extends NativeObject {
		/**
		 * Native C structure layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_view_stats_t",
			MemoryLayout.sequenceLayout(256, ValueLayout.JAVA_BYTE).withName("name"),
			ValueLayout.JAVA_SHORT.withName("view"),
			ValueLayout.JAVA_LONG.withName("cpuTimeBegin"),
			ValueLayout.JAVA_LONG.withName("cpuTimeEnd"),
			ValueLayout.JAVA_LONG.withName("gpuTimeBegin"),
			ValueLayout.JAVA_LONG.withName("gpuTimeEnd"),
			ValueLayout.JAVA_INT.withName("gpuFrameNum"));
		private static final MethodHandle MH_NAME = LAYOUT.sliceHandle(
			MemoryLayout.PathElement.groupElement("name"));
		private static final VarHandle VH_VIEW = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("view"));
		private static final VarHandle VH_CPUTIMEBEGIN = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("cpuTimeBegin"));
		private static final VarHandle VH_CPUTIMEEND = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("cpuTimeEnd"));
		private static final VarHandle VH_GPUTIMEBEGIN = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("gpuTimeBegin"));
		private static final VarHandle VH_GPUTIMEEND = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("gpuTimeEnd"));
		private static final VarHandle VH_GPUFRAMENUM = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("gpuFrameNum"));
		/**
		 * Wraps an existing native structure.
		 * @param segment native memory segment
		 */
		public ViewStats(MemorySegment segment) {
			super(segment, LAYOUT);
		}

		/**
		 * Allocates a native structure.
		 * @param allocator destination allocator
		 */
		public ViewStats(SegmentAllocator allocator) {
			super(allocator, LAYOUT);
		}

		/**
		 * View name.
		 * @return a segment view of the inline array
		 */
		public MemorySegment name() {
			return slice(MH_NAME, segment());
		}

		/**
		 * View id.
		 * @return the field value
		 */
		public short view() {
			return (short) VH_VIEW.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code view} field and returns {@code this}.
		 * @param value the new field value
		 */
		public ViewStats view(short value) {
			VH_VIEW.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code view} field and returns {@code this}.
		 * @param value the new field value
		 */
		public ViewStats view(int value) {
			return view((short)value);
		}

		/**
		 * CPU (submit) begin time.
		 * @return the field value
		 */
		public long cpuTimeBegin() {
			return (long) VH_CPUTIMEBEGIN.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code cpuTimeBegin} field and returns {@code this}.
		 * @param value the new field value
		 */
		public ViewStats cpuTimeBegin(long value) {
			VH_CPUTIMEBEGIN.set(segment(), 0L, value);
			return this;
		}

		/**
		 * CPU (submit) end time.
		 * @return the field value
		 */
		public long cpuTimeEnd() {
			return (long) VH_CPUTIMEEND.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code cpuTimeEnd} field and returns {@code this}.
		 * @param value the new field value
		 */
		public ViewStats cpuTimeEnd(long value) {
			VH_CPUTIMEEND.set(segment(), 0L, value);
			return this;
		}

		/**
		 * GPU begin time.
		 * @return the field value
		 */
		public long gpuTimeBegin() {
			return (long) VH_GPUTIMEBEGIN.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code gpuTimeBegin} field and returns {@code this}.
		 * @param value the new field value
		 */
		public ViewStats gpuTimeBegin(long value) {
			VH_GPUTIMEBEGIN.set(segment(), 0L, value);
			return this;
		}

		/**
		 * GPU end time.
		 * @return the field value
		 */
		public long gpuTimeEnd() {
			return (long) VH_GPUTIMEEND.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code gpuTimeEnd} field and returns {@code this}.
		 * @param value the new field value
		 */
		public ViewStats gpuTimeEnd(long value) {
			VH_GPUTIMEEND.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Frame which generated gpuTimeBegin, gpuTimeEnd.
		 * @return the field value
		 */
		public @Unsigned int gpuFrameNum() {
			return (@Unsigned int) VH_GPUFRAMENUM.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code gpuFrameNum} field and returns {@code this}.
		 * @param value the new field value
		 */
		public ViewStats gpuFrameNum(@Unsigned int value) {
			VH_GPUFRAMENUM.set(segment(), 0L, value);
			return this;
		}
	}

	/**
	 * Encoder stats.
	 */
	@NullMarked
	public static final class EncoderStats extends NativeObject {
		/**
		 * Native C structure layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_encoder_stats_t",
			ValueLayout.JAVA_LONG.withName("cpuTimeBegin"),
			ValueLayout.JAVA_LONG.withName("cpuTimeEnd"));
		private static final VarHandle VH_CPUTIMEBEGIN = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("cpuTimeBegin"));
		private static final VarHandle VH_CPUTIMEEND = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("cpuTimeEnd"));
		/**
		 * Wraps an existing native structure.
		 * @param segment native memory segment
		 */
		public EncoderStats(MemorySegment segment) {
			super(segment, LAYOUT);
		}

		/**
		 * Allocates a native structure.
		 * @param allocator destination allocator
		 */
		public EncoderStats(SegmentAllocator allocator) {
			super(allocator, LAYOUT);
		}

		/**
		 * Encoder thread CPU submit begin time.
		 * @return the field value
		 */
		public long cpuTimeBegin() {
			return (long) VH_CPUTIMEBEGIN.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code cpuTimeBegin} field and returns {@code this}.
		 * @param value the new field value
		 */
		public EncoderStats cpuTimeBegin(long value) {
			VH_CPUTIMEBEGIN.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Encoder thread CPU submit end time.
		 * @return the field value
		 */
		public long cpuTimeEnd() {
			return (long) VH_CPUTIMEEND.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code cpuTimeEnd} field and returns {@code this}.
		 * @param value the new field value
		 */
		public EncoderStats cpuTimeEnd(long value) {
			VH_CPUTIMEEND.set(segment(), 0L, value);
			return this;
		}
	}

	/**
	 * Renderer statistics data.
	 * <p>
	 * <strong>Remarks:</strong> All time values are high-resolution timestamps, while
	 * time frequencies define timestamps-per-second for that hardware.
	 */
	@NullMarked
	public static final class Stats extends NativeObject {
		/**
		 * Native C structure layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_stats_t",
			ValueLayout.JAVA_LONG.withName("cpuTimeFrame"),
			ValueLayout.JAVA_LONG.withName("cpuTimeBegin"),
			ValueLayout.JAVA_LONG.withName("cpuTimeEnd"),
			ValueLayout.JAVA_LONG.withName("cpuTimerFreq"),
			ValueLayout.JAVA_LONG.withName("gpuTimeBegin"),
			ValueLayout.JAVA_LONG.withName("gpuTimeEnd"),
			ValueLayout.JAVA_LONG.withName("gpuTimerFreq"),
			ValueLayout.JAVA_LONG.withName("waitRender"),
			ValueLayout.JAVA_LONG.withName("waitSubmit"),
			ValueLayout.JAVA_INT.withName("numDraw"),
			ValueLayout.JAVA_INT.withName("numCompute"),
			ValueLayout.JAVA_INT.withName("numBlit"),
			ValueLayout.JAVA_INT.withName("numBlitRepack"),
			ValueLayout.JAVA_INT.withName("numDrawCallsPeak"),
			ValueLayout.JAVA_INT.withName("maxGpuLatency"),
			ValueLayout.JAVA_INT.withName("gpuFrameNum"),
			ValueLayout.JAVA_SHORT.withName("numDynamicIndexBuffers"),
			ValueLayout.JAVA_SHORT.withName("numDynamicVertexBuffers"),
			ValueLayout.JAVA_SHORT.withName("numFrameBuffers"),
			ValueLayout.JAVA_SHORT.withName("numIndexBuffers"),
			ValueLayout.JAVA_SHORT.withName("numOcclusionQueries"),
			ValueLayout.JAVA_SHORT.withName("numPrograms"),
			ValueLayout.JAVA_SHORT.withName("numShaders"),
			ValueLayout.JAVA_SHORT.withName("numTextures"),
			ValueLayout.JAVA_SHORT.withName("numUniforms"),
			ValueLayout.JAVA_SHORT.withName("numVertexBuffers"),
			ValueLayout.JAVA_SHORT.withName("numVertexLayouts"),
			ValueLayout.JAVA_LONG.withName("textureMemoryUsed"),
			ValueLayout.JAVA_LONG.withName("rtMemoryUsed"),
			ValueLayout.JAVA_INT.withName("transientVbUsed"),
			ValueLayout.JAVA_INT.withName("transientIbUsed"),
			MemoryLayout.sequenceLayout(5, ValueLayout.JAVA_INT).withName("numPrims"),
			ValueLayout.JAVA_LONG.withName("gpuMemoryMax"),
			ValueLayout.JAVA_LONG.withName("gpuMemoryUsed"),
			ValueLayout.JAVA_SHORT.withName("width"),
			ValueLayout.JAVA_SHORT.withName("height"),
			ValueLayout.JAVA_SHORT.withName("textWidth"),
			ValueLayout.JAVA_SHORT.withName("textHeight"),
			ValueLayout.JAVA_SHORT.withName("numViews"),
			ValueLayout.ADDRESS.withName("viewStats"),
			ValueLayout.JAVA_BYTE.withName("numEncoders"),
			ValueLayout.ADDRESS.withName("encoderStats"));
		private static final VarHandle VH_CPUTIMEFRAME = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("cpuTimeFrame"));
		private static final VarHandle VH_CPUTIMEBEGIN = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("cpuTimeBegin"));
		private static final VarHandle VH_CPUTIMEEND = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("cpuTimeEnd"));
		private static final VarHandle VH_CPUTIMERFREQ = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("cpuTimerFreq"));
		private static final VarHandle VH_GPUTIMEBEGIN = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("gpuTimeBegin"));
		private static final VarHandle VH_GPUTIMEEND = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("gpuTimeEnd"));
		private static final VarHandle VH_GPUTIMERFREQ = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("gpuTimerFreq"));
		private static final VarHandle VH_WAITRENDER = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("waitRender"));
		private static final VarHandle VH_WAITSUBMIT = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("waitSubmit"));
		private static final VarHandle VH_NUMDRAW = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("numDraw"));
		private static final VarHandle VH_NUMCOMPUTE = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("numCompute"));
		private static final VarHandle VH_NUMBLIT = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("numBlit"));
		private static final VarHandle VH_NUMBLITREPACK = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("numBlitRepack"));
		private static final VarHandle VH_NUMDRAWCALLSPEAK = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("numDrawCallsPeak"));
		private static final VarHandle VH_MAXGPULATENCY = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("maxGpuLatency"));
		private static final VarHandle VH_GPUFRAMENUM = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("gpuFrameNum"));
		private static final VarHandle VH_NUMDYNAMICINDEXBUFFERS = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("numDynamicIndexBuffers"));
		private static final VarHandle VH_NUMDYNAMICVERTEXBUFFERS = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("numDynamicVertexBuffers"));
		private static final VarHandle VH_NUMFRAMEBUFFERS = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("numFrameBuffers"));
		private static final VarHandle VH_NUMINDEXBUFFERS = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("numIndexBuffers"));
		private static final VarHandle VH_NUMOCCLUSIONQUERIES = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("numOcclusionQueries"));
		private static final VarHandle VH_NUMPROGRAMS = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("numPrograms"));
		private static final VarHandle VH_NUMSHADERS = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("numShaders"));
		private static final VarHandle VH_NUMTEXTURES = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("numTextures"));
		private static final VarHandle VH_NUMUNIFORMS = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("numUniforms"));
		private static final VarHandle VH_NUMVERTEXBUFFERS = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("numVertexBuffers"));
		private static final VarHandle VH_NUMVERTEXLAYOUTS = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("numVertexLayouts"));
		private static final VarHandle VH_TEXTUREMEMORYUSED = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("textureMemoryUsed"));
		private static final VarHandle VH_RTMEMORYUSED = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("rtMemoryUsed"));
		private static final VarHandle VH_TRANSIENTVBUSED = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("transientVbUsed"));
		private static final VarHandle VH_TRANSIENTIBUSED = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("transientIbUsed"));
		private static final MethodHandle MH_NUMPRIMS = LAYOUT.sliceHandle(
			MemoryLayout.PathElement.groupElement("numPrims"));
		private static final VarHandle VH_GPUMEMORYMAX = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("gpuMemoryMax"));
		private static final VarHandle VH_GPUMEMORYUSED = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("gpuMemoryUsed"));
		private static final VarHandle VH_WIDTH = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("width"));
		private static final VarHandle VH_HEIGHT = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("height"));
		private static final VarHandle VH_TEXTWIDTH = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("textWidth"));
		private static final VarHandle VH_TEXTHEIGHT = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("textHeight"));
		private static final VarHandle VH_NUMVIEWS = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("numViews"));
		private static final VarHandle VH_VIEWSTATS = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("viewStats"));
		private static final VarHandle VH_NUMENCODERS = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("numEncoders"));
		private static final VarHandle VH_ENCODERSTATS = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("encoderStats"));
		/**
		 * Wraps an existing native structure.
		 * @param segment native memory segment
		 */
		public Stats(MemorySegment segment) {
			super(segment, LAYOUT);
		}

		/**
		 * Allocates a native structure.
		 * @param allocator destination allocator
		 */
		public Stats(SegmentAllocator allocator) {
			super(allocator, LAYOUT);
		}

		/**
		 * CPU time between two {@code frame} calls.
		 * @return the field value
		 */
		public long cpuTimeFrame() {
			return (long) VH_CPUTIMEFRAME.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code cpuTimeFrame} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats cpuTimeFrame(long value) {
			VH_CPUTIMEFRAME.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Render thread CPU submit begin time.
		 * @return the field value
		 */
		public long cpuTimeBegin() {
			return (long) VH_CPUTIMEBEGIN.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code cpuTimeBegin} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats cpuTimeBegin(long value) {
			VH_CPUTIMEBEGIN.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Render thread CPU submit end time.
		 * @return the field value
		 */
		public long cpuTimeEnd() {
			return (long) VH_CPUTIMEEND.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code cpuTimeEnd} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats cpuTimeEnd(long value) {
			VH_CPUTIMEEND.set(segment(), 0L, value);
			return this;
		}

		/**
		 * CPU timer frequency. Timestamps-per-second
		 * @return the field value
		 */
		public long cpuTimerFreq() {
			return (long) VH_CPUTIMERFREQ.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code cpuTimerFreq} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats cpuTimerFreq(long value) {
			VH_CPUTIMERFREQ.set(segment(), 0L, value);
			return this;
		}

		/**
		 * GPU frame begin time.
		 * @return the field value
		 */
		public long gpuTimeBegin() {
			return (long) VH_GPUTIMEBEGIN.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code gpuTimeBegin} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats gpuTimeBegin(long value) {
			VH_GPUTIMEBEGIN.set(segment(), 0L, value);
			return this;
		}

		/**
		 * GPU frame end time.
		 * @return the field value
		 */
		public long gpuTimeEnd() {
			return (long) VH_GPUTIMEEND.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code gpuTimeEnd} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats gpuTimeEnd(long value) {
			VH_GPUTIMEEND.set(segment(), 0L, value);
			return this;
		}

		/**
		 * GPU timer frequency.
		 * @return the field value
		 */
		public long gpuTimerFreq() {
			return (long) VH_GPUTIMERFREQ.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code gpuTimerFreq} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats gpuTimerFreq(long value) {
			VH_GPUTIMERFREQ.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Time spent waiting for render backend thread to finish issuing draw commands to underlying graphics API.
		 * @return the field value
		 */
		public long waitRender() {
			return (long) VH_WAITRENDER.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code waitRender} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats waitRender(long value) {
			VH_WAITRENDER.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Time spent waiting for submit thread to advance to next frame.
		 * @return the field value
		 */
		public long waitSubmit() {
			return (long) VH_WAITSUBMIT.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code waitSubmit} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats waitSubmit(long value) {
			VH_WAITSUBMIT.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Number of draw calls submitted.
		 * @return the field value
		 */
		public @Unsigned int numDraw() {
			return (@Unsigned int) VH_NUMDRAW.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code numDraw} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numDraw(@Unsigned int value) {
			VH_NUMDRAW.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Number of compute calls submitted.
		 * @return the field value
		 */
		public @Unsigned int numCompute() {
			return (@Unsigned int) VH_NUMCOMPUTE.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code numCompute} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numCompute(@Unsigned int value) {
			VH_NUMCOMPUTE.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Number of blit calls submitted.
		 * @return the field value
		 */
		public @Unsigned int numBlit() {
			return (@Unsigned int) VH_NUMBLIT.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code numBlit} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numBlit(@Unsigned int value) {
			VH_NUMBLIT.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Number of buffer to texture blit calls that had to be repacked,
		 * because {@code BufferRegion.rowPitch} or {@code offset} didn't match
		 * {@code Caps.Limits.blitRowPitchAlign} or {@code blitOffsetAlign}.
		 * @return the field value
		 */
		public @Unsigned int numBlitRepack() {
			return (@Unsigned int) VH_NUMBLITREPACK.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code numBlitRepack} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numBlitRepack(@Unsigned int value) {
			VH_NUMBLITREPACK.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Highest number of draw+compute calls requested in a single
		 * frame so far (peak demand, before any were dropped). Useful
		 * to tune {@code Init.Limits.numDrawCalls}.
		 * @return the field value
		 */
		public @Unsigned int numDrawCallsPeak() {
			return (@Unsigned int) VH_NUMDRAWCALLSPEAK.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code numDrawCallsPeak} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numDrawCallsPeak(@Unsigned int value) {
			VH_NUMDRAWCALLSPEAK.set(segment(), 0L, value);
			return this;
		}

		/**
		 * GPU driver latency.
		 * @return the field value
		 */
		public @Unsigned int maxGpuLatency() {
			return (@Unsigned int) VH_MAXGPULATENCY.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code maxGpuLatency} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats maxGpuLatency(@Unsigned int value) {
			VH_MAXGPULATENCY.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Frame which generated gpuTimeBegin, gpuTimeEnd.
		 * @return the field value
		 */
		public @Unsigned int gpuFrameNum() {
			return (@Unsigned int) VH_GPUFRAMENUM.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code gpuFrameNum} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats gpuFrameNum(@Unsigned int value) {
			VH_GPUFRAMENUM.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Number of used dynamic index buffers.
		 * @return the field value
		 */
		public @Unsigned short numDynamicIndexBuffers() {
			return (@Unsigned short) VH_NUMDYNAMICINDEXBUFFERS.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code numDynamicIndexBuffers} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numDynamicIndexBuffers(@Unsigned short value) {
			VH_NUMDYNAMICINDEXBUFFERS.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code numDynamicIndexBuffers} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numDynamicIndexBuffers(int value) {
			return numDynamicIndexBuffers(NativeObject.toUnsignedShort(value));
		}

		/**
		 * Number of used dynamic vertex buffers.
		 * @return the field value
		 */
		public @Unsigned short numDynamicVertexBuffers() {
			return (@Unsigned short) VH_NUMDYNAMICVERTEXBUFFERS.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code numDynamicVertexBuffers} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numDynamicVertexBuffers(@Unsigned short value) {
			VH_NUMDYNAMICVERTEXBUFFERS.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code numDynamicVertexBuffers} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numDynamicVertexBuffers(int value) {
			return numDynamicVertexBuffers(NativeObject.toUnsignedShort(value));
		}

		/**
		 * Number of used frame buffers.
		 * @return the field value
		 */
		public @Unsigned short numFrameBuffers() {
			return (@Unsigned short) VH_NUMFRAMEBUFFERS.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code numFrameBuffers} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numFrameBuffers(@Unsigned short value) {
			VH_NUMFRAMEBUFFERS.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code numFrameBuffers} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numFrameBuffers(int value) {
			return numFrameBuffers(NativeObject.toUnsignedShort(value));
		}

		/**
		 * Number of used index buffers.
		 * @return the field value
		 */
		public @Unsigned short numIndexBuffers() {
			return (@Unsigned short) VH_NUMINDEXBUFFERS.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code numIndexBuffers} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numIndexBuffers(@Unsigned short value) {
			VH_NUMINDEXBUFFERS.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code numIndexBuffers} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numIndexBuffers(int value) {
			return numIndexBuffers(NativeObject.toUnsignedShort(value));
		}

		/**
		 * Number of used occlusion queries.
		 * @return the field value
		 */
		public @Unsigned short numOcclusionQueries() {
			return (@Unsigned short) VH_NUMOCCLUSIONQUERIES.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code numOcclusionQueries} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numOcclusionQueries(@Unsigned short value) {
			VH_NUMOCCLUSIONQUERIES.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code numOcclusionQueries} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numOcclusionQueries(int value) {
			return numOcclusionQueries(NativeObject.toUnsignedShort(value));
		}

		/**
		 * Number of used programs.
		 * @return the field value
		 */
		public @Unsigned short numPrograms() {
			return (@Unsigned short) VH_NUMPROGRAMS.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code numPrograms} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numPrograms(@Unsigned short value) {
			VH_NUMPROGRAMS.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code numPrograms} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numPrograms(int value) {
			return numPrograms(NativeObject.toUnsignedShort(value));
		}

		/**
		 * Number of used shaders.
		 * @return the field value
		 */
		public @Unsigned short numShaders() {
			return (@Unsigned short) VH_NUMSHADERS.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code numShaders} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numShaders(@Unsigned short value) {
			VH_NUMSHADERS.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code numShaders} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numShaders(int value) {
			return numShaders(NativeObject.toUnsignedShort(value));
		}

		/**
		 * Number of used textures.
		 * @return the field value
		 */
		public @Unsigned short numTextures() {
			return (@Unsigned short) VH_NUMTEXTURES.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code numTextures} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numTextures(@Unsigned short value) {
			VH_NUMTEXTURES.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code numTextures} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numTextures(int value) {
			return numTextures(NativeObject.toUnsignedShort(value));
		}

		/**
		 * Number of used uniforms.
		 * @return the field value
		 */
		public @Unsigned short numUniforms() {
			return (@Unsigned short) VH_NUMUNIFORMS.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code numUniforms} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numUniforms(@Unsigned short value) {
			VH_NUMUNIFORMS.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code numUniforms} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numUniforms(int value) {
			return numUniforms(NativeObject.toUnsignedShort(value));
		}

		/**
		 * Number of used vertex buffers.
		 * @return the field value
		 */
		public @Unsigned short numVertexBuffers() {
			return (@Unsigned short) VH_NUMVERTEXBUFFERS.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code numVertexBuffers} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numVertexBuffers(@Unsigned short value) {
			VH_NUMVERTEXBUFFERS.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code numVertexBuffers} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numVertexBuffers(int value) {
			return numVertexBuffers(NativeObject.toUnsignedShort(value));
		}

		/**
		 * Number of used vertex layouts.
		 * @return the field value
		 */
		public @Unsigned short numVertexLayouts() {
			return (@Unsigned short) VH_NUMVERTEXLAYOUTS.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code numVertexLayouts} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numVertexLayouts(@Unsigned short value) {
			VH_NUMVERTEXLAYOUTS.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code numVertexLayouts} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numVertexLayouts(int value) {
			return numVertexLayouts(NativeObject.toUnsignedShort(value));
		}

		/**
		 * Estimate of texture memory used.
		 * @return the field value
		 */
		public long textureMemoryUsed() {
			return (long) VH_TEXTUREMEMORYUSED.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code textureMemoryUsed} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats textureMemoryUsed(long value) {
			VH_TEXTUREMEMORYUSED.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Estimate of render target memory used.
		 * @return the field value
		 */
		public long rtMemoryUsed() {
			return (long) VH_RTMEMORYUSED.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code rtMemoryUsed} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats rtMemoryUsed(long value) {
			VH_RTMEMORYUSED.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Amount of transient vertex buffer used.
		 * @return the field value
		 */
		public int transientVbUsed() {
			return (int) VH_TRANSIENTVBUSED.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code transientVbUsed} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats transientVbUsed(int value) {
			VH_TRANSIENTVBUSED.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Amount of transient index buffer used.
		 * @return the field value
		 */
		public int transientIbUsed() {
			return (int) VH_TRANSIENTIBUSED.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code transientIbUsed} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats transientIbUsed(int value) {
			VH_TRANSIENTIBUSED.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Number of primitives rendered.
		 * @return a segment view of the inline array
		 */
		public MemorySegment numPrims() {
			return slice(MH_NUMPRIMS, segment());
		}

		/**
		 * Maximum available GPU memory for application.
		 * @return the field value
		 */
		public long gpuMemoryMax() {
			return (long) VH_GPUMEMORYMAX.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code gpuMemoryMax} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats gpuMemoryMax(long value) {
			VH_GPUMEMORYMAX.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Amount of GPU memory used by the application.
		 * @return the field value
		 */
		public long gpuMemoryUsed() {
			return (long) VH_GPUMEMORYUSED.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code gpuMemoryUsed} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats gpuMemoryUsed(long value) {
			VH_GPUMEMORYUSED.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Backbuffer width in pixels.
		 * @return the field value
		 */
		public @Unsigned short width() {
			return (@Unsigned short) VH_WIDTH.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code width} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats width(@Unsigned short value) {
			VH_WIDTH.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code width} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats width(int value) {
			return width(NativeObject.toUnsignedShort(value));
		}

		/**
		 * Backbuffer height in pixels.
		 * @return the field value
		 */
		public @Unsigned short height() {
			return (@Unsigned short) VH_HEIGHT.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code height} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats height(@Unsigned short value) {
			VH_HEIGHT.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code height} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats height(int value) {
			return height(NativeObject.toUnsignedShort(value));
		}

		/**
		 * Debug text width in characters.
		 * @return the field value
		 */
		public @Unsigned short textWidth() {
			return (@Unsigned short) VH_TEXTWIDTH.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code textWidth} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats textWidth(@Unsigned short value) {
			VH_TEXTWIDTH.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code textWidth} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats textWidth(int value) {
			return textWidth(NativeObject.toUnsignedShort(value));
		}

		/**
		 * Debug text height in characters.
		 * @return the field value
		 */
		public @Unsigned short textHeight() {
			return (@Unsigned short) VH_TEXTHEIGHT.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code textHeight} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats textHeight(@Unsigned short value) {
			VH_TEXTHEIGHT.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code textHeight} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats textHeight(int value) {
			return textHeight(NativeObject.toUnsignedShort(value));
		}

		/**
		 * Number of view stats.
		 * @return the field value
		 */
		public @Unsigned short numViews() {
			return (@Unsigned short) VH_NUMVIEWS.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code numViews} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numViews(@Unsigned short value) {
			VH_NUMVIEWS.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code numViews} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numViews(int value) {
			return numViews(NativeObject.toUnsignedShort(value));
		}

		/**
		 * Array of View stats.
		 * @return the field value
		 */
		public ViewStats viewStats() {
			return new ViewStats((MemorySegment) VH_VIEWSTATS.get(segment(), 0L));
		}

		/**
		 * Sets the native {@code viewStats} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats viewStats(ViewStats value) {
			VH_VIEWSTATS.set(segment(), 0L, address(value));
			return this;
		}

		/**
		 * Number of encoders used during frame.
		 * @return the field value
		 */
		public @Unsigned byte numEncoders() {
			return (@Unsigned byte) VH_NUMENCODERS.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code numEncoders} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numEncoders(@Unsigned byte value) {
			VH_NUMENCODERS.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code numEncoders} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats numEncoders(int value) {
			return numEncoders(NativeObject.toUnsignedByte(value));
		}

		/**
		 * Array of encoder stats.
		 * @return the field value
		 */
		public EncoderStats encoderStats() {
			return new EncoderStats((MemorySegment) VH_ENCODERSTATS.get(segment(), 0L));
		}

		/**
		 * Sets the native {@code encoderStats} field and returns {@code this}.
		 * @param value the new field value
		 */
		public Stats encoderStats(EncoderStats value) {
			VH_ENCODERSTATS.set(segment(), 0L, address(value));
			return this;
		}
	}

	/**
	 * Vertex layout.
	 */
	@NullMarked
	public static final class VertexLayout extends NativeObject {
		/**
		 * Native C structure layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_vertex_layout_t",
			ValueLayout.JAVA_INT.withName("hash"),
			ValueLayout.JAVA_SHORT.withName("stride"),
			MemoryLayout.sequenceLayout(26, ValueLayout.JAVA_SHORT).withName("offset"),
			MemoryLayout.sequenceLayout(26, ValueLayout.JAVA_SHORT).withName("attributes"));
		private static final VarHandle VH_HASH = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("hash"));
		private static final VarHandle VH_STRIDE = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("stride"));
		private static final MethodHandle MH_OFFSET = LAYOUT.sliceHandle(
			MemoryLayout.PathElement.groupElement("offset"));
		private static final MethodHandle MH_ATTRIBUTES = LAYOUT.sliceHandle(
			MemoryLayout.PathElement.groupElement("attributes"));
		/**
		 * Wraps an existing native structure.
		 * @param segment native memory segment
		 */
		public VertexLayout(MemorySegment segment) {
			super(segment, LAYOUT);
		}

		/**
		 * Allocates a native structure.
		 * @param allocator destination allocator
		 */
		public VertexLayout(SegmentAllocator allocator) {
			super(allocator, LAYOUT);
		}

		/**
		 * Hash.
		 * @return the field value
		 */
		public @Unsigned int hash() {
			return (@Unsigned int) VH_HASH.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code hash} field and returns {@code this}.
		 * @param value the new field value
		 */
		public VertexLayout hash(@Unsigned int value) {
			VH_HASH.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Stride.
		 * @return the field value
		 */
		public @Unsigned short stride() {
			return (@Unsigned short) VH_STRIDE.get(segment(), 0L);
		}

		/**
		 * Sets the native {@code stride} field and returns {@code this}.
		 * @param value the new field value
		 */
		public VertexLayout stride(@Unsigned short value) {
			VH_STRIDE.set(segment(), 0L, value);
			return this;
		}

		/**
		 * Sets the native {@code stride} field and returns {@code this}.
		 * @param value the new field value
		 */
		public VertexLayout stride(int value) {
			return stride(NativeObject.toUnsignedShort(value));
		}

		/**
		 * Attribute offsets.
		 * @return a segment view of the inline array
		 */
		public MemorySegment offset() {
			return slice(MH_OFFSET, segment());
		}

		/**
		 * Used attributes.
		 * @return a segment view of the inline array
		 */
		public MemorySegment attributes() {
			return slice(MH_ATTRIBUTES, segment());
		}

		/**
		 * Start VertexLayout.
		 * @param _rendererType Renderer backend type. See: {@code RendererType}
		 * @return Returns itself.
		 */
		public final VertexLayout begin(RendererType _rendererType) {
			try {
				return new VertexLayout((MemorySegment) MH_VERTEX_LAYOUT_BEGIN.invokeExact(segment(), _rendererType.ordinal()));
			} catch (Throwable ex) {
				throw invocationFailure(ex);
			}
		}

		/**
		 * Add attribute to VertexLayout.
		 * <p>
		 * <strong>Remarks:</strong> Must be called between begin/end.
		 * @param _attrib Attribute semantics. See: {@code Attrib}
		 * @param _num Number of elements 1, 2, 3 or 4.
		 * @param _type Element type.
		 * @param _normalized When using fixed point AttribType (f.e. Uint8) value will be normalized for vertex shader usage. When normalized is set to true, AttribType.UINT8 value in range 0-255 will be in range 0.0-1.0 in vertex shader.
		 * @param _asInt Packaging rule for vertexPack, vertexUnpack, and vertexConvert for AttribType.UINT8 and AttribType.INT16. Unpacking code must be implemented inside vertex shader.
		 * @return Returns itself.
		 */
		public final VertexLayout add(Attrib _attrib, @Unsigned byte _num, AttribType _type, boolean _normalized, boolean _asInt) {
			try {
				return new VertexLayout((MemorySegment) MH_VERTEX_LAYOUT_ADD.invokeExact(segment(), _attrib.ordinal(), _num, _type.ordinal(), _normalized, _asInt));
			} catch (Throwable ex) {
				throw invocationFailure(ex);
			}
		}

		/**
		 * Decode attribute.
		 * @param _attrib Attribute semantics. See: {@code Attrib}
		 * @param _num Number of elements.
		 * @param _type Element type.
		 * @param _normalized Attribute is normalized.
		 * @param _asInt Attribute is packed as int.
		 */
		public final void decode(Attrib _attrib, MemorySegment _num, MemorySegment _type, MemorySegment _normalized, MemorySegment _asInt) {
			try {
				MH_VERTEX_LAYOUT_DECODE.invokeExact(segment(), _attrib.ordinal(), address(_num), address(_type), address(_normalized), address(_asInt));
			} catch (Throwable ex) {
				throw invocationFailure(ex);
			}
		}

		/**
		 * Returns {@code true} if VertexLayout contains attribute.
		 * @param _attrib Attribute semantics. See: {@code Attrib}
		 * @return True if VertexLayout contains attribute.
		 */
		public final boolean has(Attrib _attrib) {
			try {
				return (boolean) MH_VERTEX_LAYOUT_HAS.invokeExact(segment(), _attrib.ordinal());
			} catch (Throwable ex) {
				throw invocationFailure(ex);
			}
		}

		/**
		 * Skip {@code _num} bytes in vertex stream.
		 * @param _num Number of bytes to skip.
		 * @return Returns itself.
		 */
		public final VertexLayout skip(@Unsigned byte _num) {
			try {
				return new VertexLayout((MemorySegment) MH_VERTEX_LAYOUT_SKIP.invokeExact(segment(), _num));
			} catch (Throwable ex) {
				throw invocationFailure(ex);
			}
		}

		/**
		 * End VertexLayout.
		 */
		public final void end() {
			try {
				MH_VERTEX_LAYOUT_END.invokeExact(segment());
			} catch (Throwable ex) {
				throw invocationFailure(ex);
			}
		}

		/**
		 * Returns relative attribute offset from the vertex.
		 * @param _attrib Attribute semantics. See: {@code Attrib}
		 * @return Relative attribute offset from the vertex.
		 */
		public final @Unsigned short getOffset(Attrib _attrib) {
			try {
				return (@Unsigned short) MH_VERTEX_LAYOUT_GET_OFFSET.invokeExact(segment(), _attrib.ordinal());
			} catch (Throwable ex) {
				throw invocationFailure(ex);
			}
		}

		/**
		 * Returns vertex stride.
		 * @return Vertex stride.
		 */
		public final @Unsigned short getStride() {
			try {
				return (@Unsigned short) MH_VERTEX_LAYOUT_GET_STRIDE.invokeExact(segment());
			} catch (Throwable ex) {
				throw invocationFailure(ex);
			}
		}

		/**
		 * Returns size of vertex buffer for number of vertices.
		 * @param _num Number of vertices.
		 * @return Size of vertex buffer for number of vertices.
		 */
		public final @Unsigned int getSize(@Unsigned int _num) {
			try {
				return (@Unsigned int) MH_VERTEX_LAYOUT_GET_SIZE.invokeExact(segment(), _num);
			} catch (Throwable ex) {
				throw invocationFailure(ex);
			}
		}
	}

	/**
	 * Encoders are used for submitting draw calls from multiple threads. Only one encoder
	 * per thread should be used. Use {@code begin()} to obtain an encoder for a thread.
	 */
	@NullMarked
	public static final class Encoder extends NativeObject {
		/**
		 * Wraps an opaque native pointer.
		 * @param segment native memory segment
		 */
		public Encoder(MemorySegment segment) {
			super(segment);
		}

		/**
		 * Sets a debug marker. This allows you to group graphics calls together for easy browsing in
		 * graphics debugging tools.
		 * @param _name Marker name.
		 * @param _len Marker name length (if length is INT32_MAX, it's expected that _name is zero terminated string.
		 */
		public final void setMarker(String _name, int _len) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_SET_MARKER.invokeExact(segment(), cString(arena, _name), _len);
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
		public final void setState(@Unsigned long _state, @Unsigned int _rgba) {
			try {
				MH_ENCODER_SET_STATE.invokeExact(segment(), _state, _rgba);
			} catch (Throwable ex) {
				throw invocationFailure(ex);
			}
		}

		/**
		 * Set condition for rendering.
		 * @param _handle Occlusion query handle.
		 * @param _visible Render if occlusion query is visible.
		 */
		public final void setCondition(OcclusionQueryHandle _handle, boolean _visible) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_SET_CONDITION.invokeExact(segment(), _handle.allocate(arena), _visible);
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
		public final void setStencil(@Unsigned int _fstencil, @Unsigned int _bstencil) {
			try {
				MH_ENCODER_SET_STENCIL.invokeExact(segment(), _fstencil, _bstencil);
			} catch (Throwable ex) {
				throw invocationFailure(ex);
			}
		}

		/**
		 * Set multisample coverage mask for draw primitive. Samples whose bit is clear
		 * in the mask are never written, regardless of the coverage the rasterizer
		 * computes. Only has an effect when rendering to a multisampled target.
		 * @param _mask Sample coverage mask.
		 */
		public final void setSampleMask(@Unsigned int _mask) {
			try {
				MH_ENCODER_SET_SAMPLE_MASK.invokeExact(segment(), _mask);
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
		public final @Unsigned short setScissor(@Unsigned short _x, @Unsigned short _y, @Unsigned short _width, @Unsigned short _height) {
			try {
				return (@Unsigned short) MH_ENCODER_SET_SCISSOR.invokeExact(segment(), _x, _y, _width, _height);
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
		public final void setScissorCached(@Unsigned short _cache) {
			try {
				MH_ENCODER_SET_SCISSOR_CACHED.invokeExact(segment(), _cache);
			} catch (Throwable ex) {
				throw invocationFailure(ex);
			}
		}

		/**
		 * Set depth control (depth bias and depth clip) for draw primitive. Overrides the
		 * view depth bias for this draw.
		 * @param _constant Constant depth bias.
		 * @param _slopeScale Slope-scaled depth bias.
		 * @param _clamp Depth bias clamp.
		 * @param _depthClamp Disable depth clipping and clamp NDC depth to the [0,1] range instead.
		 * @return Depth control cache index.
		 */
		public final @Unsigned short setDepthControl(int _constant, float _slopeScale, float _clamp, boolean _depthClamp) {
			try {
				return (@Unsigned short) MH_ENCODER_SET_DEPTH_CONTROL.invokeExact(segment(), _constant, _slopeScale, _clamp, _depthClamp);
			} catch (Throwable ex) {
				throw invocationFailure(ex);
			}
		}

		/**
		 * Set depth control from depth-control cache for draw primitive.
		 * @param _cache Index in depth control cache.
		 */
		public final void setDepthControlCached(@Unsigned short _cache) {
			try {
				MH_ENCODER_SET_DEPTH_CONTROL_CACHED.invokeExact(segment(), _cache);
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
		public final @Unsigned int setTransform(MemorySegment _mtx, @Unsigned short _num) {
			try {
				return (@Unsigned int) MH_ENCODER_SET_TRANSFORM.invokeExact(segment(), address(_mtx), _num);
			} catch (Throwable ex) {
				throw invocationFailure(ex);
			}
		}

		/**
		 *  Set model matrix from matrix cache for draw primitive.
		 * @param _cache Index in matrix cache.
		 * @param _num Number of matrices from cache.
		 */
		public final void setTransformCached(@Unsigned int _cache, @Unsigned short _num) {
			try {
				MH_ENCODER_SET_TRANSFORM_CACHED.invokeExact(segment(), _cache, _num);
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
		public final @Unsigned int allocTransform(Transform _transform, @Unsigned short _num) {
			try {
				return (@Unsigned int) MH_ENCODER_ALLOC_TRANSFORM.invokeExact(segment(), address(_transform), _num);
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
		public final void setUniform(UniformHandle _handle, MemorySegment _value, @Unsigned short _num) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_SET_UNIFORM.invokeExact(segment(), _handle.allocate(arena), address(_value), _num);
				}
			} catch (Throwable ex) {
				throw invocationFailure(ex);
			}
		}

		/**
		 * Set shader uniform parameter by reference. Unlike {@code Encoder.setUniform}, the data
		 * is not copied immediately; the renderer reads it from {@code _value} at frame render
		 * time. The pointer must remain valid and unchanged until the frame is rendered
		 * (up to two {@code frame} calls with multithreaded submission).
		 * @param _handle Uniform.
		 * @param _value Pointer to uniform data. Must stay valid until the frame is rendered.
		 * @param _num Number of elements. Passing {@code UINT16_MAX} will use the _num passed on uniform creation.
		 */
		public final void setUniformRef(UniformHandle _handle, MemorySegment _value, @Unsigned short _num) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_SET_UNIFORM_REF.invokeExact(segment(), _handle.allocate(arena), address(_value), _num);
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
		public final void setIndexBuffer(IndexBufferHandle _handle, @Unsigned int _firstIndex, @Unsigned int _numIndices) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_SET_INDEX_BUFFER.invokeExact(segment(), _handle.allocate(arena), _firstIndex, _numIndices);
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
		public final void setDynamicIndexBuffer(DynamicIndexBufferHandle _handle, @Unsigned int _firstIndex, @Unsigned int _numIndices) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_SET_DYNAMIC_INDEX_BUFFER.invokeExact(segment(), _handle.allocate(arena), _firstIndex, _numIndices);
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
		public final void setTransientIndexBuffer(TransientIndexBuffer _tib, @Unsigned int _firstIndex, @Unsigned int _numIndices) {
			try {
				MH_ENCODER_SET_TRANSIENT_INDEX_BUFFER.invokeExact(segment(), address(_tib), _firstIndex, _numIndices);
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
		public final void setVertexBuffer(@Unsigned byte _stream, VertexBufferHandle _handle, @Unsigned int _startVertex, @Unsigned int _numVertices) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_SET_VERTEX_BUFFER.invokeExact(segment(), _stream, _handle.allocate(arena), _startVertex, _numVertices);
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
		public final void setVertexBufferWithLayout(@Unsigned byte _stream, VertexBufferHandle _handle, @Unsigned int _startVertex, @Unsigned int _numVertices, VertexLayoutHandle _layoutHandle) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_SET_VERTEX_BUFFER_WITH_LAYOUT.invokeExact(segment(), _stream, _handle.allocate(arena), _startVertex, _numVertices, _layoutHandle.allocate(arena));
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
		public final void setDynamicVertexBuffer(@Unsigned byte _stream, DynamicVertexBufferHandle _handle, @Unsigned int _startVertex, @Unsigned int _numVertices) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_SET_DYNAMIC_VERTEX_BUFFER.invokeExact(segment(), _stream, _handle.allocate(arena), _startVertex, _numVertices);
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
		public final void setDynamicVertexBufferWithLayout(@Unsigned byte _stream, DynamicVertexBufferHandle _handle, @Unsigned int _startVertex, @Unsigned int _numVertices, VertexLayoutHandle _layoutHandle) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_SET_DYNAMIC_VERTEX_BUFFER_WITH_LAYOUT.invokeExact(segment(), _stream, _handle.allocate(arena), _startVertex, _numVertices, _layoutHandle.allocate(arena));
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
		public final void setTransientVertexBuffer(@Unsigned byte _stream, TransientVertexBuffer _tvb, @Unsigned int _startVertex, @Unsigned int _numVertices) {
			try {
				MH_ENCODER_SET_TRANSIENT_VERTEX_BUFFER.invokeExact(segment(), _stream, address(_tvb), _startVertex, _numVertices);
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
		public final void setTransientVertexBufferWithLayout(@Unsigned byte _stream, TransientVertexBuffer _tvb, @Unsigned int _startVertex, @Unsigned int _numVertices, VertexLayoutHandle _layoutHandle) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_SET_TRANSIENT_VERTEX_BUFFER_WITH_LAYOUT.invokeExact(segment(), _stream, address(_tvb), _startVertex, _numVertices, _layoutHandle.allocate(arena));
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
		public final void setVertexCount(@Unsigned int _numVertices) {
			try {
				MH_ENCODER_SET_VERTEX_COUNT.invokeExact(segment(), _numVertices);
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
		public final void setInstanceDataBuffer(InstanceDataBuffer _idb, @Unsigned int _start, @Unsigned int _num) {
			try {
				MH_ENCODER_SET_INSTANCE_DATA_BUFFER.invokeExact(segment(), address(_idb), _start, _num);
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
		public final void setInstanceDataFromVertexBuffer(VertexBufferHandle _handle, @Unsigned int _startVertex, @Unsigned int _num) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_SET_INSTANCE_DATA_FROM_VERTEX_BUFFER.invokeExact(segment(), _handle.allocate(arena), _startVertex, _num);
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
		public final void setInstanceDataFromDynamicVertexBuffer(DynamicVertexBufferHandle _handle, @Unsigned int _startVertex, @Unsigned int _num) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_SET_INSTANCE_DATA_FROM_DYNAMIC_VERTEX_BUFFER.invokeExact(segment(), _handle.allocate(arena), _startVertex, _num);
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
		public final void setInstanceCount(@Unsigned int _numInstances) {
			try {
				MH_ENCODER_SET_INSTANCE_COUNT.invokeExact(segment(), _numInstances);
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
		public final void setTexture(@Unsigned byte _stage, UniformHandle _sampler, TextureHandle _handle, @Unsigned int _flags) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_SET_TEXTURE.invokeExact(segment(), _stage, _sampler.allocate(arena), _handle.allocate(arena), _flags);
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
		 * @param _lodMin Lowest (most detailed) level of detail the sampler may use, in quarter-mip steps, relative to {@code _firstMip}.
		 * @param _lodMax Highest (least detailed) level of detail the sampler may use, in quarter-mip steps, relative to {@code _firstMip}. {@code UINT8_MAX} leaves it unclamped.
		 */
		public final void setTextureView(@Unsigned byte _stage, UniformHandle _sampler, TextureHandle _handle, @Unsigned short _firstLayer, @Unsigned short _numLayers, @Unsigned byte _firstMip, @Unsigned byte _numMips, @Unsigned int _flags, @Unsigned byte _lodMin, @Unsigned byte _lodMax) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_SET_TEXTURE_VIEW.invokeExact(segment(), _stage, _sampler.allocate(arena), _handle.allocate(arena), _firstLayer, _numLayers, _firstMip, _numMips, _flags, _lodMin, _lodMax);
				}
			} catch (Throwable ex) {
				throw invocationFailure(ex);
			}
		}

		/**
		 * Submit an empty primitive for rendering. Uniforms and draw state
		 * will be applied but no geometry will be submitted. Useful in cases
		 * when no other draw/compute primitive is submitted to view, but it's
		 * desired to execute clear view.
		 * <p>
		 * <strong>Remarks:</strong>
		 *   These empty draw calls will sort before ordinary draw calls.
		 * @param _id View id.
		 */
		public final void touch(short _id) {
			try {
				MH_ENCODER_TOUCH.invokeExact(segment(), _id);
			} catch (Throwable ex) {
				throw invocationFailure(ex);
			}
		}

		/**
		 * Submit primitive for rendering.
		 * @param _id View id.
		 * @param _program Program.
		 * @param _depth Depth for sorting.
		 * @param _flags Discard or preserve states. See {@code BGFX_DISCARD_*}.
		 */
		public final void submit(short _id, ProgramHandle _program, @Unsigned int _depth, @Unsigned int _flags) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_SUBMIT.invokeExact(segment(), _id, _program.allocate(arena), _depth, NativeObject.toUnsignedByte(_flags));
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
		 * @param _flags Discard or preserve states. See {@code BGFX_DISCARD_*}.
		 */
		public final void submitOcclusionQuery(short _id, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, @Unsigned int _depth, @Unsigned int _flags) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_SUBMIT_OCCLUSION_QUERY.invokeExact(segment(), _id, _program.allocate(arena), _occlusionQuery.allocate(arena), _depth, NativeObject.toUnsignedByte(_flags));
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
		 * @param _flags Discard or preserve states. See {@code BGFX_DISCARD_*}.
		 */
		public final void submitIndirect(short _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, @Unsigned int _start, @Unsigned int _num, @Unsigned int _depth, @Unsigned int _flags) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_SUBMIT_INDIRECT.invokeExact(segment(), _id, _program.allocate(arena), _indirectHandle.allocate(arena), _start, _num, _depth, NativeObject.toUnsignedByte(_flags));
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
		 * @param _flags Discard or preserve states. See {@code BGFX_DISCARD_*}.
		 */
		public final void submitIndirectCount(short _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, @Unsigned int _start, IndexBufferHandle _numHandle, @Unsigned int _numIndex, @Unsigned int _numMax, @Unsigned int _depth, @Unsigned int _flags) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_SUBMIT_INDIRECT_COUNT.invokeExact(segment(), _id, _program.allocate(arena), _indirectHandle.allocate(arena), _start, _numHandle.allocate(arena), _numIndex, _numMax, _depth, NativeObject.toUnsignedByte(_flags));
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
		 * @param _offset Byte offset the shader's view of the buffer starts at. Must be a multiple of 256 bytes.
		 * @param _size Bytes bound from the offset, {@code UINT32_MAX} for the rest of the buffer.
		 */
		public final void setComputeIndexBuffer(@Unsigned byte _stage, IndexBufferHandle _handle, Access _access, @Unsigned int _offset, @Unsigned int _size) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_SET_COMPUTE_INDEX_BUFFER.invokeExact(segment(), _stage, _handle.allocate(arena), _access.ordinal(), _offset, _size);
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
		 * @param _offset Byte offset the shader's view of the buffer starts at. Must be a multiple of 256 bytes.
		 * @param _size Bytes bound from the offset, {@code UINT32_MAX} for the rest of the buffer.
		 */
		public final void setComputeVertexBuffer(@Unsigned byte _stage, VertexBufferHandle _handle, Access _access, @Unsigned int _offset, @Unsigned int _size) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_SET_COMPUTE_VERTEX_BUFFER.invokeExact(segment(), _stage, _handle.allocate(arena), _access.ordinal(), _offset, _size);
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
		 * @param _offset Byte offset the shader's view of the buffer starts at. Must be a multiple of 256 bytes.
		 * @param _size Bytes bound from the offset, {@code UINT32_MAX} for the rest of the buffer.
		 */
		public final void setComputeDynamicIndexBuffer(@Unsigned byte _stage, DynamicIndexBufferHandle _handle, Access _access, @Unsigned int _offset, @Unsigned int _size) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_SET_COMPUTE_DYNAMIC_INDEX_BUFFER.invokeExact(segment(), _stage, _handle.allocate(arena), _access.ordinal(), _offset, _size);
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
		 * @param _offset Byte offset the shader's view of the buffer starts at. Must be a multiple of 256 bytes.
		 * @param _size Bytes bound from the offset, {@code UINT32_MAX} for the rest of the buffer.
		 */
		public final void setComputeDynamicVertexBuffer(@Unsigned byte _stage, DynamicVertexBufferHandle _handle, Access _access, @Unsigned int _offset, @Unsigned int _size) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_SET_COMPUTE_DYNAMIC_VERTEX_BUFFER.invokeExact(segment(), _stage, _handle.allocate(arena), _access.ordinal(), _offset, _size);
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
		public final void setComputeIndirectBuffer(@Unsigned byte _stage, IndirectBufferHandle _handle, Access _access) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_SET_COMPUTE_INDIRECT_BUFFER.invokeExact(segment(), _stage, _handle.allocate(arena), _access.ordinal());
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
		public final void setImage(@Unsigned byte _stage, TextureHandle _handle, @Unsigned byte _mip, Access _access, TextureFormat _format) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_SET_IMAGE.invokeExact(segment(), _stage, _handle.allocate(arena), _mip, _access.ordinal(), _format.ordinal());
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
		public final void setImageView(@Unsigned byte _stage, TextureHandle _handle, @Unsigned short _firstLayer, @Unsigned short _numLayers, @Unsigned byte _mip, Access _access, TextureFormat _format) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_SET_IMAGE_VIEW.invokeExact(segment(), _stage, _handle.allocate(arena), _firstLayer, _numLayers, _mip, _access.ordinal(), _format.ordinal());
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
		public final void dispatch(short _id, ProgramHandle _program, @Unsigned int _numX, @Unsigned int _numY, @Unsigned int _numZ, @Unsigned int _flags) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_DISPATCH.invokeExact(segment(), _id, _program.allocate(arena), _numX, _numY, _numZ, NativeObject.toUnsignedByte(_flags));
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
		public final void dispatchIndirect(short _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, @Unsigned int _start, @Unsigned int _num, @Unsigned int _flags) {
			try {
				try (Arena arena = Arena.ofConfined()) {
					MH_ENCODER_DISPATCH_INDIRECT.invokeExact(segment(), _id, _program.allocate(arena), _indirectHandle.allocate(arena), _start, _num, NativeObject.toUnsignedByte(_flags));
				}
			} catch (Throwable ex) {
				throw invocationFailure(ex);
			}
		}

		/**
		 * Discard previously set state for draw or compute call.
		 * @param _flags Discard or preserve states. See {@code BGFX_DISCARD_*}.
		 */
		public final void discard(@Unsigned int _flags) {
			try {
				MH_ENCODER_DISCARD.invokeExact(segment(), NativeObject.toUnsignedByte(_flags));
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
		public final void blit(short _id, TextureRegion _dst, TextureRegion _src) {
			try {
				MH_ENCODER_BLIT.invokeExact(segment(), _id, address(_dst), address(_src));
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
		public final void blitBuffer(short _id, BufferRegion _dst, BufferRegion _src) {
			try {
				MH_ENCODER_BLIT_BUFFER.invokeExact(segment(), _id, address(_dst), address(_src));
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
		public final void blitToBuffer(short _id, BufferRegion _dst, TextureRegion _src) {
			try {
				MH_ENCODER_BLIT_TO_BUFFER.invokeExact(segment(), _id, address(_dst), address(_src));
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
		public final void blitFromBuffer(short _id, TextureRegion _dst, BufferRegion _src) {
			try {
				MH_ENCODER_BLIT_FROM_BUFFER.invokeExact(segment(), _id, address(_dst), address(_src));
			} catch (Throwable ex) {
				throw invocationFailure(ex);
			}
		}
	}

	/**
	 * Native bgfx handle.
	 * @param idx native handle index
	 */
	@NullMarked
	public record DynamicIndexBufferHandle(short idx) implements AutoCloseable, BufferHandle {
		/**
		 * Native by-value handle layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_dynamic_index_buffer_handle_t",
			ValueLayout.JAVA_SHORT.withName("idx"));
		private static final VarHandle VH_IDX = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("idx"));
		/**
		 * Invalid handle sentinel.
		 */
		public static final DynamicIndexBufferHandle INVALID = new DynamicIndexBufferHandle((short) 0xffff);

		/**
		 * Returns this handle's native tagged-handle type.
		 * @return the native tagged-handle type
		 */
		@Override
		public short type() {
			return (short) 0;
		}

		/**
		 * Returns whether this handle is valid.
		 * @return {@code true} when the handle index is not {@code UINT16_MAX}
		 */
		public boolean isValid() {
			return idx != (short) 0xffff;
		}

		/**
		 * Allocates and writes the native by-value handle representation.
		 * @param allocator the destination allocator
		 * @return the allocated native segment
		 */
		public MemorySegment allocate(SegmentAllocator allocator) {
			MemorySegment segment = allocator.allocate(LAYOUT);
			write(segment);
			return segment;
		}

		/**
		 * Writes this handle to an existing native segment.
		 * @param segment the destination segment
		 */
		public void write(MemorySegment segment) {
			segment = view(segment, LAYOUT);
			VH_IDX.set(segment, 0L, idx);
		}

		/**
		 * Reads a by-value handle from native memory.
		 * @param segment the source segment
		 * @return the decoded handle
		 */
		public static DynamicIndexBufferHandle read(MemorySegment segment) {
			segment = view(segment, LAYOUT);
			return new DynamicIndexBufferHandle((short) VH_IDX.get(segment, 0L));
		}

		/**
		 * Destroys this native handle.
		 */
		@Override
		public void close() {
			Bgfx.destroyDynamicIndexBuffer(this);
		}
	}

	/**
	 * Native bgfx handle.
	 * @param idx native handle index
	 */
	@NullMarked
	public record DynamicVertexBufferHandle(short idx) implements AutoCloseable, BufferHandle {
		/**
		 * Native by-value handle layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_dynamic_vertex_buffer_handle_t",
			ValueLayout.JAVA_SHORT.withName("idx"));
		private static final VarHandle VH_IDX = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("idx"));
		/**
		 * Invalid handle sentinel.
		 */
		public static final DynamicVertexBufferHandle INVALID = new DynamicVertexBufferHandle((short) 0xffff);

		/**
		 * Returns this handle's native tagged-handle type.
		 * @return the native tagged-handle type
		 */
		@Override
		public short type() {
			return (short) 1;
		}

		/**
		 * Returns whether this handle is valid.
		 * @return {@code true} when the handle index is not {@code UINT16_MAX}
		 */
		public boolean isValid() {
			return idx != (short) 0xffff;
		}

		/**
		 * Allocates and writes the native by-value handle representation.
		 * @param allocator the destination allocator
		 * @return the allocated native segment
		 */
		public MemorySegment allocate(SegmentAllocator allocator) {
			MemorySegment segment = allocator.allocate(LAYOUT);
			write(segment);
			return segment;
		}

		/**
		 * Writes this handle to an existing native segment.
		 * @param segment the destination segment
		 */
		public void write(MemorySegment segment) {
			segment = view(segment, LAYOUT);
			VH_IDX.set(segment, 0L, idx);
		}

		/**
		 * Reads a by-value handle from native memory.
		 * @param segment the source segment
		 * @return the decoded handle
		 */
		public static DynamicVertexBufferHandle read(MemorySegment segment) {
			segment = view(segment, LAYOUT);
			return new DynamicVertexBufferHandle((short) VH_IDX.get(segment, 0L));
		}

		/**
		 * Destroys this native handle.
		 */
		@Override
		public void close() {
			Bgfx.destroyDynamicVertexBuffer(this);
		}
	}

	/**
	 * Native bgfx handle.
	 * @param idx native handle index
	 */
	@NullMarked
	public record FrameBufferHandle(short idx) implements AutoCloseable {
		/**
		 * Native by-value handle layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_frame_buffer_handle_t",
			ValueLayout.JAVA_SHORT.withName("idx"));
		private static final VarHandle VH_IDX = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("idx"));
		/**
		 * Invalid handle sentinel.
		 */
		public static final FrameBufferHandle INVALID = new FrameBufferHandle((short) 0xffff);

		/**
		 * Returns whether this handle is valid.
		 * @return {@code true} when the handle index is not {@code UINT16_MAX}
		 */
		public boolean isValid() {
			return idx != (short) 0xffff;
		}

		/**
		 * Allocates and writes the native by-value handle representation.
		 * @param allocator the destination allocator
		 * @return the allocated native segment
		 */
		public MemorySegment allocate(SegmentAllocator allocator) {
			MemorySegment segment = allocator.allocate(LAYOUT);
			write(segment);
			return segment;
		}

		/**
		 * Writes this handle to an existing native segment.
		 * @param segment the destination segment
		 */
		public void write(MemorySegment segment) {
			segment = view(segment, LAYOUT);
			VH_IDX.set(segment, 0L, idx);
		}

		/**
		 * Reads a by-value handle from native memory.
		 * @param segment the source segment
		 * @return the decoded handle
		 */
		public static FrameBufferHandle read(MemorySegment segment) {
			segment = view(segment, LAYOUT);
			return new FrameBufferHandle((short) VH_IDX.get(segment, 0L));
		}

		/**
		 * Destroys this native handle.
		 */
		@Override
		public void close() {
			Bgfx.destroyFrameBuffer(this);
		}
	}

	/**
	 * Native bgfx handle.
	 * @param idx native handle index
	 */
	@NullMarked
	public record IndexBufferHandle(short idx) implements AutoCloseable, BufferHandle {
		/**
		 * Native by-value handle layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_index_buffer_handle_t",
			ValueLayout.JAVA_SHORT.withName("idx"));
		private static final VarHandle VH_IDX = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("idx"));
		/**
		 * Invalid handle sentinel.
		 */
		public static final IndexBufferHandle INVALID = new IndexBufferHandle((short) 0xffff);

		/**
		 * Returns this handle's native tagged-handle type.
		 * @return the native tagged-handle type
		 */
		@Override
		public short type() {
			return (short) 2;
		}

		/**
		 * Returns whether this handle is valid.
		 * @return {@code true} when the handle index is not {@code UINT16_MAX}
		 */
		public boolean isValid() {
			return idx != (short) 0xffff;
		}

		/**
		 * Allocates and writes the native by-value handle representation.
		 * @param allocator the destination allocator
		 * @return the allocated native segment
		 */
		public MemorySegment allocate(SegmentAllocator allocator) {
			MemorySegment segment = allocator.allocate(LAYOUT);
			write(segment);
			return segment;
		}

		/**
		 * Writes this handle to an existing native segment.
		 * @param segment the destination segment
		 */
		public void write(MemorySegment segment) {
			segment = view(segment, LAYOUT);
			VH_IDX.set(segment, 0L, idx);
		}

		/**
		 * Reads a by-value handle from native memory.
		 * @param segment the source segment
		 * @return the decoded handle
		 */
		public static IndexBufferHandle read(MemorySegment segment) {
			segment = view(segment, LAYOUT);
			return new IndexBufferHandle((short) VH_IDX.get(segment, 0L));
		}

		/**
		 * Destroys this native handle.
		 */
		@Override
		public void close() {
			Bgfx.destroyIndexBuffer(this);
		}
	}

	/**
	 * Native bgfx handle.
	 * @param idx native handle index
	 */
	@NullMarked
	public record IndirectBufferHandle(short idx) implements AutoCloseable, BufferHandle {
		/**
		 * Native by-value handle layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_indirect_buffer_handle_t",
			ValueLayout.JAVA_SHORT.withName("idx"));
		private static final VarHandle VH_IDX = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("idx"));
		/**
		 * Invalid handle sentinel.
		 */
		public static final IndirectBufferHandle INVALID = new IndirectBufferHandle((short) 0xffff);

		/**
		 * Returns this handle's native tagged-handle type.
		 * @return the native tagged-handle type
		 */
		@Override
		public short type() {
			return (short) 3;
		}

		/**
		 * Returns whether this handle is valid.
		 * @return {@code true} when the handle index is not {@code UINT16_MAX}
		 */
		public boolean isValid() {
			return idx != (short) 0xffff;
		}

		/**
		 * Allocates and writes the native by-value handle representation.
		 * @param allocator the destination allocator
		 * @return the allocated native segment
		 */
		public MemorySegment allocate(SegmentAllocator allocator) {
			MemorySegment segment = allocator.allocate(LAYOUT);
			write(segment);
			return segment;
		}

		/**
		 * Writes this handle to an existing native segment.
		 * @param segment the destination segment
		 */
		public void write(MemorySegment segment) {
			segment = view(segment, LAYOUT);
			VH_IDX.set(segment, 0L, idx);
		}

		/**
		 * Reads a by-value handle from native memory.
		 * @param segment the source segment
		 * @return the decoded handle
		 */
		public static IndirectBufferHandle read(MemorySegment segment) {
			segment = view(segment, LAYOUT);
			return new IndirectBufferHandle((short) VH_IDX.get(segment, 0L));
		}

		/**
		 * Destroys this native handle.
		 */
		@Override
		public void close() {
			Bgfx.destroyIndirectBuffer(this);
		}
	}

	/**
	 * Native bgfx handle.
	 * @param idx native handle index
	 */
	@NullMarked
	public record OcclusionQueryHandle(short idx) implements AutoCloseable {
		/**
		 * Native by-value handle layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_occlusion_query_handle_t",
			ValueLayout.JAVA_SHORT.withName("idx"));
		private static final VarHandle VH_IDX = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("idx"));
		/**
		 * Invalid handle sentinel.
		 */
		public static final OcclusionQueryHandle INVALID = new OcclusionQueryHandle((short) 0xffff);

		/**
		 * Returns whether this handle is valid.
		 * @return {@code true} when the handle index is not {@code UINT16_MAX}
		 */
		public boolean isValid() {
			return idx != (short) 0xffff;
		}

		/**
		 * Allocates and writes the native by-value handle representation.
		 * @param allocator the destination allocator
		 * @return the allocated native segment
		 */
		public MemorySegment allocate(SegmentAllocator allocator) {
			MemorySegment segment = allocator.allocate(LAYOUT);
			write(segment);
			return segment;
		}

		/**
		 * Writes this handle to an existing native segment.
		 * @param segment the destination segment
		 */
		public void write(MemorySegment segment) {
			segment = view(segment, LAYOUT);
			VH_IDX.set(segment, 0L, idx);
		}

		/**
		 * Reads a by-value handle from native memory.
		 * @param segment the source segment
		 * @return the decoded handle
		 */
		public static OcclusionQueryHandle read(MemorySegment segment) {
			segment = view(segment, LAYOUT);
			return new OcclusionQueryHandle((short) VH_IDX.get(segment, 0L));
		}

		/**
		 * Destroys this native handle.
		 */
		@Override
		public void close() {
			Bgfx.destroyOcclusionQuery(this);
		}
	}

	/**
	 * Native bgfx handle.
	 * @param idx native handle index
	 */
	@NullMarked
	public record ProgramHandle(short idx) implements AutoCloseable {
		/**
		 * Native by-value handle layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_program_handle_t",
			ValueLayout.JAVA_SHORT.withName("idx"));
		private static final VarHandle VH_IDX = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("idx"));
		/**
		 * Invalid handle sentinel.
		 */
		public static final ProgramHandle INVALID = new ProgramHandle((short) 0xffff);

		/**
		 * Returns whether this handle is valid.
		 * @return {@code true} when the handle index is not {@code UINT16_MAX}
		 */
		public boolean isValid() {
			return idx != (short) 0xffff;
		}

		/**
		 * Allocates and writes the native by-value handle representation.
		 * @param allocator the destination allocator
		 * @return the allocated native segment
		 */
		public MemorySegment allocate(SegmentAllocator allocator) {
			MemorySegment segment = allocator.allocate(LAYOUT);
			write(segment);
			return segment;
		}

		/**
		 * Writes this handle to an existing native segment.
		 * @param segment the destination segment
		 */
		public void write(MemorySegment segment) {
			segment = view(segment, LAYOUT);
			VH_IDX.set(segment, 0L, idx);
		}

		/**
		 * Reads a by-value handle from native memory.
		 * @param segment the source segment
		 * @return the decoded handle
		 */
		public static ProgramHandle read(MemorySegment segment) {
			segment = view(segment, LAYOUT);
			return new ProgramHandle((short) VH_IDX.get(segment, 0L));
		}

		/**
		 * Destroys this native handle.
		 */
		@Override
		public void close() {
			Bgfx.destroyProgram(this);
		}
	}

	/**
	 * Native bgfx handle.
	 * @param idx native handle index
	 */
	@NullMarked
	public record ShaderHandle(short idx) implements AutoCloseable {
		/**
		 * Native by-value handle layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_shader_handle_t",
			ValueLayout.JAVA_SHORT.withName("idx"));
		private static final VarHandle VH_IDX = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("idx"));
		/**
		 * Invalid handle sentinel.
		 */
		public static final ShaderHandle INVALID = new ShaderHandle((short) 0xffff);

		/**
		 * Returns whether this handle is valid.
		 * @return {@code true} when the handle index is not {@code UINT16_MAX}
		 */
		public boolean isValid() {
			return idx != (short) 0xffff;
		}

		/**
		 * Allocates and writes the native by-value handle representation.
		 * @param allocator the destination allocator
		 * @return the allocated native segment
		 */
		public MemorySegment allocate(SegmentAllocator allocator) {
			MemorySegment segment = allocator.allocate(LAYOUT);
			write(segment);
			return segment;
		}

		/**
		 * Writes this handle to an existing native segment.
		 * @param segment the destination segment
		 */
		public void write(MemorySegment segment) {
			segment = view(segment, LAYOUT);
			VH_IDX.set(segment, 0L, idx);
		}

		/**
		 * Reads a by-value handle from native memory.
		 * @param segment the source segment
		 * @return the decoded handle
		 */
		public static ShaderHandle read(MemorySegment segment) {
			segment = view(segment, LAYOUT);
			return new ShaderHandle((short) VH_IDX.get(segment, 0L));
		}

		/**
		 * Destroys this native handle.
		 */
		@Override
		public void close() {
			Bgfx.destroyShader(this);
		}
	}

	/**
	 * Native bgfx handle.
	 * @param idx native handle index
	 */
	@NullMarked
	public record TextureHandle(short idx) implements AutoCloseable {
		/**
		 * Native by-value handle layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_texture_handle_t",
			ValueLayout.JAVA_SHORT.withName("idx"));
		private static final VarHandle VH_IDX = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("idx"));
		/**
		 * Invalid handle sentinel.
		 */
		public static final TextureHandle INVALID = new TextureHandle((short) 0xffff);

		/**
		 * Returns whether this handle is valid.
		 * @return {@code true} when the handle index is not {@code UINT16_MAX}
		 */
		public boolean isValid() {
			return idx != (short) 0xffff;
		}

		/**
		 * Allocates and writes the native by-value handle representation.
		 * @param allocator the destination allocator
		 * @return the allocated native segment
		 */
		public MemorySegment allocate(SegmentAllocator allocator) {
			MemorySegment segment = allocator.allocate(LAYOUT);
			write(segment);
			return segment;
		}

		/**
		 * Writes this handle to an existing native segment.
		 * @param segment the destination segment
		 */
		public void write(MemorySegment segment) {
			segment = view(segment, LAYOUT);
			VH_IDX.set(segment, 0L, idx);
		}

		/**
		 * Reads a by-value handle from native memory.
		 * @param segment the source segment
		 * @return the decoded handle
		 */
		public static TextureHandle read(MemorySegment segment) {
			segment = view(segment, LAYOUT);
			return new TextureHandle((short) VH_IDX.get(segment, 0L));
		}

		/**
		 * Destroys this native handle.
		 */
		@Override
		public void close() {
			Bgfx.destroyTexture(this);
		}
	}

	/**
	 * Native bgfx handle.
	 * @param idx native handle index
	 */
	@NullMarked
	public record UniformHandle(short idx) implements AutoCloseable {
		/**
		 * Native by-value handle layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_uniform_handle_t",
			ValueLayout.JAVA_SHORT.withName("idx"));
		private static final VarHandle VH_IDX = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("idx"));
		/**
		 * Invalid handle sentinel.
		 */
		public static final UniformHandle INVALID = new UniformHandle((short) 0xffff);

		/**
		 * Returns whether this handle is valid.
		 * @return {@code true} when the handle index is not {@code UINT16_MAX}
		 */
		public boolean isValid() {
			return idx != (short) 0xffff;
		}

		/**
		 * Allocates and writes the native by-value handle representation.
		 * @param allocator the destination allocator
		 * @return the allocated native segment
		 */
		public MemorySegment allocate(SegmentAllocator allocator) {
			MemorySegment segment = allocator.allocate(LAYOUT);
			write(segment);
			return segment;
		}

		/**
		 * Writes this handle to an existing native segment.
		 * @param segment the destination segment
		 */
		public void write(MemorySegment segment) {
			segment = view(segment, LAYOUT);
			VH_IDX.set(segment, 0L, idx);
		}

		/**
		 * Reads a by-value handle from native memory.
		 * @param segment the source segment
		 * @return the decoded handle
		 */
		public static UniformHandle read(MemorySegment segment) {
			segment = view(segment, LAYOUT);
			return new UniformHandle((short) VH_IDX.get(segment, 0L));
		}

		/**
		 * Destroys this native handle.
		 */
		@Override
		public void close() {
			Bgfx.destroyUniform(this);
		}
	}

	/**
	 * Native bgfx handle.
	 * @param idx native handle index
	 */
	@NullMarked
	public record VertexBufferHandle(short idx) implements AutoCloseable, BufferHandle {
		/**
		 * Native by-value handle layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_vertex_buffer_handle_t",
			ValueLayout.JAVA_SHORT.withName("idx"));
		private static final VarHandle VH_IDX = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("idx"));
		/**
		 * Invalid handle sentinel.
		 */
		public static final VertexBufferHandle INVALID = new VertexBufferHandle((short) 0xffff);

		/**
		 * Returns this handle's native tagged-handle type.
		 * @return the native tagged-handle type
		 */
		@Override
		public short type() {
			return (short) 4;
		}

		/**
		 * Returns whether this handle is valid.
		 * @return {@code true} when the handle index is not {@code UINT16_MAX}
		 */
		public boolean isValid() {
			return idx != (short) 0xffff;
		}

		/**
		 * Allocates and writes the native by-value handle representation.
		 * @param allocator the destination allocator
		 * @return the allocated native segment
		 */
		public MemorySegment allocate(SegmentAllocator allocator) {
			MemorySegment segment = allocator.allocate(LAYOUT);
			write(segment);
			return segment;
		}

		/**
		 * Writes this handle to an existing native segment.
		 * @param segment the destination segment
		 */
		public void write(MemorySegment segment) {
			segment = view(segment, LAYOUT);
			VH_IDX.set(segment, 0L, idx);
		}

		/**
		 * Reads a by-value handle from native memory.
		 * @param segment the source segment
		 * @return the decoded handle
		 */
		public static VertexBufferHandle read(MemorySegment segment) {
			segment = view(segment, LAYOUT);
			return new VertexBufferHandle((short) VH_IDX.get(segment, 0L));
		}

		/**
		 * Destroys this native handle.
		 */
		@Override
		public void close() {
			Bgfx.destroyVertexBuffer(this);
		}
	}

	/**
	 * Native bgfx handle.
	 * @param idx native handle index
	 */
	@NullMarked
	public record VertexLayoutHandle(short idx) implements AutoCloseable {
		/**
		 * Native by-value handle layout.
		 */
		public static final StructLayout LAYOUT = cStruct("bgfx_vertex_layout_handle_t",
			ValueLayout.JAVA_SHORT.withName("idx"));
		private static final VarHandle VH_IDX = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("idx"));
		/**
		 * Invalid handle sentinel.
		 */
		public static final VertexLayoutHandle INVALID = new VertexLayoutHandle((short) 0xffff);

		/**
		 * Returns whether this handle is valid.
		 * @return {@code true} when the handle index is not {@code UINT16_MAX}
		 */
		public boolean isValid() {
			return idx != (short) 0xffff;
		}

		/**
		 * Allocates and writes the native by-value handle representation.
		 * @param allocator the destination allocator
		 * @return the allocated native segment
		 */
		public MemorySegment allocate(SegmentAllocator allocator) {
			MemorySegment segment = allocator.allocate(LAYOUT);
			write(segment);
			return segment;
		}

		/**
		 * Writes this handle to an existing native segment.
		 * @param segment the destination segment
		 */
		public void write(MemorySegment segment) {
			segment = view(segment, LAYOUT);
			VH_IDX.set(segment, 0L, idx);
		}

		/**
		 * Reads a by-value handle from native memory.
		 * @param segment the source segment
		 * @return the decoded handle
		 */
		public static VertexLayoutHandle read(MemorySegment segment) {
			segment = view(segment, LAYOUT);
			return new VertexLayoutHandle((short) VH_IDX.get(segment, 0L));
		}

		/**
		 * Destroys this native handle.
		 */
		@Override
		public void close() {
			Bgfx.destroyVertexLayout(this);
		}
	}

	/**
	 * Tagged buffer handle. All buffer handle types implicitly convert to it, and the tag
	 * keeps track of which type the handle originally was.
	 */
	@NullMarked
	public sealed interface BufferHandle
		permits DynamicIndexBufferHandle, DynamicVertexBufferHandle, IndexBufferHandle, IndirectBufferHandle, VertexBufferHandle {
		/**
		 * Native by-value handle layout.
		 */
		StructLayout LAYOUT = cStruct("bgfx_buffer_handle_t",
			ValueLayout.JAVA_SHORT.withName("idx"),
			ValueLayout.JAVA_SHORT.withName("type"));
		/**
		 * Native handle-index field accessor.
		 */
		VarHandle VH_IDX = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("idx"));
		/**
		 * Native handle-type field accessor.
		 */
		VarHandle VH_TYPE = LAYOUT.varHandle(
			MemoryLayout.PathElement.groupElement("type"));

		/**
		 * Invalid handle sentinel.
		 */
		BufferHandle INVALID = DynamicIndexBufferHandle.INVALID;

		/**
		 * Returns the native handle index.
		 * @return the native handle index
		 */
		short idx();

		/**
		 * Returns the native handle type tag.
		 * @return the native handle type tag
		 */
		short type();

		/**
		 * Returns whether this handle is valid.
		 * @return {@code true} when the handle index is not {@code UINT16_MAX}
		 */
		default boolean isValid() {
			return idx() != (short) 0xffff;
		}

		/**
		 * Allocates and writes the native tagged handle representation.
		 * @param allocator the destination allocator
		 * @return the allocated native segment
		 */
		default MemorySegment allocateTagged(SegmentAllocator allocator) {
			MemorySegment segment = allocator.allocate(LAYOUT);
			writeTagged(segment);
			return segment;
		}

		/**
		 * Writes this handle to an existing native tagged handle segment.
		 * @param segment the destination segment
		 */
		default void writeTagged(MemorySegment segment) {
			segment = view(segment, LAYOUT);
			VH_IDX.set(segment, 0L, idx());
			VH_TYPE.set(segment, 0L, type());
		}

		/**
		 * Reads a tagged handle from native memory.
		 * @param segment the source segment
		 * @return the decoded handle
		 */
		static BufferHandle read(MemorySegment segment) {
			segment = view(segment, LAYOUT);
			short idx = (short) VH_IDX.get(segment, 0L);
			short type = (short) VH_TYPE.get(segment, 0L);
			return switch (type) {
				case 0 -> new DynamicIndexBufferHandle(idx);
				case 1 -> new DynamicVertexBufferHandle(idx);
				case 2 -> new IndexBufferHandle(idx);
				case 3 -> new IndirectBufferHandle(idx);
				case 4 -> new VertexBufferHandle(idx);
				default -> throw new IllegalArgumentException("Unknown BufferHandle type tag: " + Short.toUnsignedInt(type));
			};
		}
	}

}
