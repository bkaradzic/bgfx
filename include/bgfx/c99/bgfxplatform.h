/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 *
 * vim: set tabstop=4 expandtab:
 */

#ifndef BGFX_PLATFORM_C99_H_HEADER_GUARD
#define BGFX_PLATFORM_C99_H_HEADER_GUARD

// NOTICE:
// This header file contains platform specific interfaces. It is only
// necessary to use this header in conjunction with creating windows.

#include <bx/platform.h>
#include <bgfx/c99/bgfxplatform.h>

typedef enum bgfx_render_frame
{
    BGFX_RENDER_FRAME_NO_CONTEXT,
    BGFX_RENDER_FRAME_RENDER,
    BGFX_RENDER_FRAME_EXITING,

    BGFX_RENDER_FRAME_COUNT

} bgfx_render_frame_t;

/**
 * WARNING: This call should be only used on platforms that don't
 * allow creating separate rendering thread. If it is called before
 * to bgfx_init, render thread won't be created by bgfx_init call.
 */
BGFX_C_API bgfx_render_frame_t bgfx_render_frame();

typedef struct bgfx_platform_data
{
    void* ndt;
    void* nwh;
    void* context;
    void* backBuffer;
    void* backBufferDS;

} bgfx_platform_data_t;

/**/
BGFX_C_API void bgfx_set_platform_data(const bgfx_platform_data_t* _data);

typedef struct bgfx_internal_data
{
    const struct bgfx_caps* caps;
    void* context;

} bgfx_internal_data_t;

/**/
BGFX_C_API const bgfx_internal_data_t* bgfx_get_internal_data();

/**/
BGFX_C_API uintptr_t bgfx_override_internal_texture_ptr(bgfx_texture_handle_t _handle, uintptr_t _ptr);

/**/
BGFX_C_API uintptr_t bgfx_override_internal_texture(bgfx_texture_handle_t _handle, uint16_t _width, uint16_t _height, uint8_t _numMips, bgfx_texture_format_t _format, uint32_t _flags);

/**/
typedef struct bgfx_interface_vtbl
{
    bgfx_render_frame_t (*render_frame)();
    void (*set_platform_data)(const bgfx_platform_data_t* _data);
    const bgfx_internal_data_t* (*get_internal_data)();
    uintptr_t (*override_internal_texture_ptr)(bgfx_texture_handle_t _handle, uintptr_t _ptr);
    uintptr_t (*override_internal_texture)(bgfx_texture_handle_t _handle, uint16_t _width, uint16_t _height, uint8_t _numMips, bgfx_texture_format_t _format, uint32_t _flags);
    void (*vertex_decl_begin)(bgfx_vertex_decl_t* _decl, bgfx_renderer_type_t _renderer);
    void (*vertex_decl_add)(bgfx_vertex_decl_t* _decl, bgfx_attrib_t _attrib, uint8_t _num, bgfx_attrib_type_t _type, bool _normalized, bool _asInt);
    void (*vertex_decl_skip)(bgfx_vertex_decl_t* _decl, uint8_t _num);
    void (*vertex_decl_end)(bgfx_vertex_decl_t* _decl);
    void (*vertex_pack)(const float _input[4], bool _inputNormalized, bgfx_attrib_t _attr, const bgfx_vertex_decl_t* _decl, void* _data, uint32_t _index);
    void (*vertex_unpack)(float _output[4], bgfx_attrib_t _attr, const bgfx_vertex_decl_t* _decl, const void* _data, uint32_t _index);
    void (*vertex_convert)(const bgfx_vertex_decl_t* _destDecl, void* _destData, const bgfx_vertex_decl_t* _srcDecl, const void* _srcData, uint32_t _num);
    uint16_t (*weld_vertices)(uint16_t* _output, const bgfx_vertex_decl_t* _decl, const void* _data, uint16_t _num, float _epsilon);
    void (*image_swizzle_bgra8)(uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _src, void* _dst);
    void (*image_rgba8_downsample_2x2)(uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _src, void* _dst);
    uint8_t (*get_supported_renderers)(bgfx_renderer_type_t _enum[BGFX_RENDERER_TYPE_COUNT]);
    const char* (*get_renderer_name)(bgfx_renderer_type_t _type);
    bool (*init)(bgfx_renderer_type_t _type, uint16_t _vendorId, uint16_t _deviceId, bgfx_callback_interface_t* _callback, bgfx_allocator_interface_t* _allocator);
    void (*shutdown)();
    void (*reset)(uint32_t _width, uint32_t _height, uint32_t _flags);
    uint32_t (*frame)();
    bgfx_renderer_type_t (*get_renderer_type)();
    const bgfx_caps_t* (*get_caps)();
    const bgfx_hmd_t* (*get_hmd)();
    const bgfx_stats_t* (*get_stats)();
    const bgfx_memory_t* (*alloc)(uint32_t _size);
    const bgfx_memory_t* (*copy)(const void* _data, uint32_t _size);
    const bgfx_memory_t* (*make_ref)(const void* _data, uint32_t _size);
    const bgfx_memory_t* (*make_ref_release)(const void* _data, uint32_t _size, bgfx_release_fn_t _releaseFn, void* _userData);
    void (*set_debug)(uint32_t _debug);
    void (*dbg_text_clear)(uint8_t _attr, bool _small);
    void (*dbg_text_printf)(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, ...);
    void (*dbg_text_image)(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const void* _data, uint16_t _pitch);
    bgfx_index_buffer_handle_t (*create_index_buffer)(const bgfx_memory_t* _mem, uint16_t _flags);
    void (*destroy_index_buffer)(bgfx_index_buffer_handle_t _handle);
    bgfx_vertex_buffer_handle_t (*create_vertex_buffer)(const bgfx_memory_t* _mem, const bgfx_vertex_decl_t* _decl, uint16_t _flags);
    void (*destroy_vertex_buffer)(bgfx_vertex_buffer_handle_t _handle);
    bgfx_dynamic_index_buffer_handle_t (*create_dynamic_index_buffer)(uint32_t _num, uint16_t _flags);
    bgfx_dynamic_index_buffer_handle_t (*create_dynamic_index_buffer_mem)(const bgfx_memory_t* _mem, uint16_t _flags);
    void (*update_dynamic_index_buffer)(bgfx_dynamic_index_buffer_handle_t _handle, uint32_t _startIndex, const bgfx_memory_t* _mem);
    void (*destroy_dynamic_index_buffer)(bgfx_dynamic_index_buffer_handle_t _handle);
    bgfx_dynamic_vertex_buffer_handle_t (*create_dynamic_vertex_buffer)(uint32_t _num, const bgfx_vertex_decl_t* _decl, uint16_t _flags);
    bgfx_dynamic_vertex_buffer_handle_t (*create_dynamic_vertex_buffer_mem)(const bgfx_memory_t* _mem, const bgfx_vertex_decl_t* _decl, uint16_t _flags);
    void (*update_dynamic_vertex_buffer)(bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, const bgfx_memory_t* _mem);
    void (*destroy_dynamic_vertex_buffer)(bgfx_dynamic_vertex_buffer_handle_t _handle);
    bool (*check_avail_transient_index_buffer)(uint32_t _num);
    bool (*check_avail_transient_vertex_buffer)(uint32_t _num, const bgfx_vertex_decl_t* _decl);
    bool (*check_avail_instance_data_buffer)(uint32_t _num, uint16_t _stride);
    bool (*check_avail_transient_buffers)(uint32_t _numVertices, const bgfx_vertex_decl_t* _decl, uint32_t _numIndices);
    void (*alloc_transient_index_buffer)(bgfx_transient_index_buffer_t* _tib, uint32_t _num);
    void (*alloc_transient_vertex_buffer)(bgfx_transient_vertex_buffer_t* _tvb, uint32_t _num, const bgfx_vertex_decl_t* _decl);
    bool (*alloc_transient_buffers)(bgfx_transient_vertex_buffer_t* _tvb, const bgfx_vertex_decl_t* _decl, uint32_t _numVertices, bgfx_transient_index_buffer_t* _tib, uint32_t _numIndices);
    const bgfx_instance_data_buffer_t* (*alloc_instance_data_buffer)(uint32_t _num, uint16_t _stride);
    bgfx_indirect_buffer_handle_t (*create_indirect_buffer)(uint32_t _num);
    void (*destroy_indirect_buffer)(bgfx_indirect_buffer_handle_t _handle);
    bgfx_shader_handle_t (*create_shader)(const bgfx_memory_t* _mem);
    uint16_t (*get_shader_uniforms)(bgfx_shader_handle_t _handle, bgfx_uniform_handle_t* _uniforms, uint16_t _max);
    void (*destroy_shader)(bgfx_shader_handle_t _handle);
    bgfx_program_handle_t (*create_program)(bgfx_shader_handle_t _vsh, bgfx_shader_handle_t _fsh, bool _destroyShaders);
    bgfx_program_handle_t (*create_compute_program)(bgfx_shader_handle_t _csh, bool _destroyShaders);
    void (*destroy_program)(bgfx_program_handle_t _handle);
    void (*calc_texture_size)(bgfx_texture_info_t* _info, uint16_t _width, uint16_t _height, uint16_t _depth, bool _cubeMap, uint8_t _numMips, bgfx_texture_format_t _format);
    bgfx_texture_handle_t (*create_texture)(const bgfx_memory_t* _mem, uint32_t _flags, uint8_t _skip, bgfx_texture_info_t* _info);
    bgfx_texture_handle_t (*create_texture_2d)(uint16_t _width, uint16_t _height, uint8_t _numMips, bgfx_texture_format_t _format, uint32_t _flags, const bgfx_memory_t* _mem);
    bgfx_texture_handle_t (*create_texture_2d_scaled)(bgfx_backbuffer_ratio_t _ratio, uint8_t _numMips, bgfx_texture_format_t _format, uint32_t _flags);
    bgfx_texture_handle_t (*create_texture_3d)(uint16_t _width, uint16_t _height, uint16_t _depth, uint8_t _numMips, bgfx_texture_format_t _format, uint32_t _flags, const bgfx_memory_t* _mem);
    bgfx_texture_handle_t (*create_texture_cube)(uint16_t _size, uint8_t _numMips, bgfx_texture_format_t _format, uint32_t _flags, const bgfx_memory_t* _mem);
    void (*update_texture_2d)(bgfx_texture_handle_t _handle, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const bgfx_memory_t* _mem, uint16_t _pitch);
    void (*update_texture_3d)(bgfx_texture_handle_t _handle, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _z, uint16_t _width, uint16_t _height, uint16_t _depth, const bgfx_memory_t* _mem);
    void (*update_texture_cube)(bgfx_texture_handle_t _handle, uint8_t _side, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const bgfx_memory_t* _mem, uint16_t _pitch);
    void (*destroy_texture)(bgfx_texture_handle_t _handle);
    bgfx_frame_buffer_handle_t (*create_frame_buffer)(uint16_t _width, uint16_t _height, bgfx_texture_format_t _format, uint32_t _textureFlags);
    bgfx_frame_buffer_handle_t (*create_frame_buffer_scaled)(bgfx_backbuffer_ratio_t _ratio, bgfx_texture_format_t _format, uint32_t _textureFlags);
    bgfx_frame_buffer_handle_t (*create_frame_buffer_from_handles)(uint8_t _num, const bgfx_texture_handle_t* _handles, bool _destroyTextures);
    bgfx_frame_buffer_handle_t (*create_frame_buffer_from_nwh)(void* _nwh, uint16_t _width, uint16_t _height, bgfx_texture_format_t _depthFormat);
    void (*destroy_frame_buffer)(bgfx_frame_buffer_handle_t _handle);
    bgfx_uniform_handle_t (*create_uniform)(const char* _name, bgfx_uniform_type_t _type, uint16_t _num);
    void (*destroy_uniform)(bgfx_uniform_handle_t _handle);
    bgfx_occlusion_query_handle_t (*create_occlusion_query)();
    bgfx_occlusion_query_result_t (*get_result)(bgfx_occlusion_query_handle_t _handle);
    void (*destroy_occlusion_query)(bgfx_occlusion_query_handle_t _handle);
    void (*set_palette_color)(uint8_t _index, const float _rgba[4]);
    void (*set_view_name)(uint8_t _id, const char* _name);
    void (*set_view_rect)(uint8_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);
    void (*set_view_scissor)(uint8_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);
    void (*set_view_clear)(uint8_t _id, uint16_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil);
    void (*set_view_clear_mrt)(uint8_t _id, uint16_t _flags, float _depth, uint8_t _stencil, uint8_t _0, uint8_t _1, uint8_t _2, uint8_t _3, uint8_t _4, uint8_t _5, uint8_t _6, uint8_t _7);
    void (*set_view_seq)(uint8_t _id, bool _enabled);
    void (*set_view_frame_buffer)(uint8_t _id, bgfx_frame_buffer_handle_t _handle);
    void (*set_view_transform)(uint8_t _id, const void* _view, const void* _proj);
    void (*set_view_transform_stereo)(uint8_t _id, const void* _view, const void* _projL, uint8_t _flags, const void* _projR);
    void (*set_view_remap)(uint8_t _id, uint8_t _num, const void* _remap);
    void (*set_marker)(const char* _marker);
    void (*set_state)(uint64_t _state, uint32_t _rgba);
    void (*set_condition)(bgfx_occlusion_query_handle_t _handle, bool _visible);
    void (*set_stencil)(uint32_t _fstencil, uint32_t _bstencil);
    uint16_t (*set_scissor)(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);
    void (*set_scissor_cached)(uint16_t _cache);
    uint32_t (*set_transform)(const void* _mtx, uint16_t _num);
    uint32_t (*alloc_transform)(bgfx_transform_t* _transform, uint16_t _num);
    void (*set_transform_cached)(uint32_t _cache, uint16_t _num);
    void (*set_uniform)(bgfx_uniform_handle_t _handle, const void* _value, uint16_t _num);
    void (*set_index_buffer)(bgfx_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices);
    void (*set_dynamic_index_buffer)(bgfx_dynamic_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices);
    void (*set_transient_index_buffer)(const bgfx_transient_index_buffer_t* _tib, uint32_t _firstIndex, uint32_t _numIndices);
    void (*set_vertex_buffer)(bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices);
    void (*set_dynamic_vertex_buffer)(bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _numVertices);
    void (*set_transient_vertex_buffer)(const bgfx_transient_vertex_buffer_t* _tvb, uint32_t _startVertex, uint32_t _numVertices);
    void (*set_instance_data_buffer)(const bgfx_instance_data_buffer_t* _idb, uint32_t _num);
    void (*set_instance_data_from_vertex_buffer)(bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num);
    void (*set_instance_data_from_dynamic_vertex_buffer)(bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num);
    void (*set_texture)(uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint32_t _flags);
    void (*set_texture_from_frame_buffer)(uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_frame_buffer_handle_t _handle, uint8_t _attachment, uint32_t _flags);
    uint32_t (*touch)(uint8_t _id);
    uint32_t (*submit)(uint8_t _id, bgfx_program_handle_t _handle, int32_t _depth);
    uint32_t (*submit_occlusion_query)(uint8_t _id, bgfx_program_handle_t _program, bgfx_occlusion_query_handle_t _occlusionQuery, int32_t _depth);
    uint32_t (*submit_indirect)(uint8_t _id, bgfx_program_handle_t _handle, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, int32_t _depth);
    void (*set_image)(uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint8_t _mip, bgfx_access_t _access, bgfx_texture_format_t _format);
    void (*set_image_from_frame_buffer)(uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_frame_buffer_handle_t _handle, uint8_t _attachment, bgfx_access_t _access, bgfx_texture_format_t _format);
    void (*set_compute_index_buffer)(uint8_t _stage, bgfx_index_buffer_handle_t _handle, bgfx_access_t _access);
    void (*set_compute_vertex_buffer)(uint8_t _stage, bgfx_vertex_buffer_handle_t _handle, bgfx_access_t _access);
    void (*set_compute_dynamic_index_buffer)(uint8_t _stage, bgfx_dynamic_index_buffer_handle_t _handle, bgfx_access_t _access);
    void (*set_compute_dynamic_vertex_buffer)(uint8_t _stage, bgfx_dynamic_vertex_buffer_handle_t _handle, bgfx_access_t _access);
    void (*set_compute_indirect_buffer)(uint8_t _stage, bgfx_indirect_buffer_handle_t _handle, bgfx_access_t _access);
    uint32_t (*dispatch)(uint8_t _id, bgfx_program_handle_t _handle, uint16_t _numX, uint16_t _numY, uint16_t _numZ, uint8_t _flags);
    uint32_t (*dispatch_indirect)(uint8_t _id, bgfx_program_handle_t _handle, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, uint8_t _flags);
    void (*discard)();
    void (*blit)(uint8_t _id, bgfx_texture_handle_t _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, bgfx_texture_handle_t _src, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth);
    void (*save_screen_shot)(const char* _filePath);

} bgfx_interface_vtbl_t;

typedef bgfx_interface_vtbl_t* (*PFN_BGFX_GET_INTERFACE)(uint32_t _version);

#endif // BGFX_PLATFORM_C99_H_HEADER_GUARD
