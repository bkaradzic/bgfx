/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef BGFX_C99_H_HEADER_GUARD
#define BGFX_C99_H_HEADER_GUARD

#include <stdbool.h> // bool
#include <stdint.h>  // uint32_t
#include <stdlib.h>  // size_t

#include "bgfxdefines.h"

enum bgfx_renderer_type
{
	BGFX_RENDERER_TYPE_NULL,
	BGFX_RENDERER_TYPE_DIRECT3D9,
	BGFX_RENDERER_TYPE_DIRECT3D11,
	BGFX_RENDERER_TYPE_OPENGLES,
	BGFX_RENDERER_TYPE_OPENGL,

	BGFX_RENDERER_TYPE_COUNT
};

typedef enum bgfx_renderer_type bgfx_renderer_type_t;

enum bgfx_attrib
{
	BGFX_ATTRIB_POSITION,
	BGFX_ATTRIB_NORMAL,
	BGFX_ATTRIB_TANGENT,
	BGFX_ATTRIB_COLOR0,
	BGFX_ATTRIB_COLOR1,
	BGFX_ATTRIB_INDICES,
	BGFX_ATTRIB_WEIGHT,
	BGFX_ATTRIB_TEXCOORD0,
	BGFX_ATTRIB_TEXCOORD1,
	BGFX_ATTRIB_TEXCOORD2,
	BGFX_ATTRIB_TEXCOORD3,
	BGFX_ATTRIB_TEXCOORD4,
	BGFX_ATTRIB_TEXCOORD5,
	BGFX_ATTRIB_TEXCOORD6,
	BGFX_ATTRIB_TEXCOORD7,

	BGFX_ATTRIB_COUNT
};

typedef enum bgfx_attrib bgfx_attrib_t;

enum bgfx_attrib_type
{
	BGFX_ATTRIB_TYPE_UINT8,
	BGFX_ATTRIB_TYPE_INT16,
	BGFX_ATTRIB_TYPE_HALF,
	BGFX_ATTRIB_TYPE_FLOAT,

	BGFX_ATTRIB_TYPE_COUNT
};

typedef enum bgfx_attrib_type bgfx_attrib_type_t;

enum bgfx_texture_format
{
	BGFX_TEXTURE_FORMAT_BC1,
	BGFX_TEXTURE_FORMAT_BC2,
	BGFX_TEXTURE_FORMAT_BC3,
	BGFX_TEXTURE_FORMAT_BC4,
	BGFX_TEXTURE_FORMAT_BC5,
	BGFX_TEXTURE_FORMAT_ETC1,
	BGFX_TEXTURE_FORMAT_ETC2,
	BGFX_TEXTURE_FORMAT_ETC2A,
	BGFX_TEXTURE_FORMAT_ETC2A1,
	BGFX_TEXTURE_FORMAT_PTC12,
	BGFX_TEXTURE_FORMAT_PTC14,
	BGFX_TEXTURE_FORMAT_PTC12A,
	BGFX_TEXTURE_FORMAT_PTC14A,
	BGFX_TEXTURE_FORMAT_PTC22,
	BGFX_TEXTURE_FORMAT_PTC24,

	BGFX_TEXTURE_FORMAT_UNKNOWN,

	BGFX_TEXTURE_FORMAT_R8,
	BGFX_TEXTURE_FORMAT_R16,
	BGFX_TEXTURE_FORMAT_R16F,
	BGFX_TEXTURE_FORMAT_BGRA8,
	BGFX_TEXTURE_FORMAT_RGBA16,
	BGFX_TEXTURE_FORMAT_RGBA16F,
	BGFX_TEXTURE_FORMAT_R5G6B5,
	BGFX_TEXTURE_FORMAT_RGBA4,
	BGFX_TEXTURE_FORMAT_RGB5A1,
	BGFX_TEXTURE_FORMAT_RGB10A2,

	BGFX_TEXTURE_FORMAT_UNKNOWN_DEPTH,

	BGFX_TEXTURE_FORMAT_D16,
	BGFX_TEXTURE_FORMAT_D24,
	BGFX_TEXTURE_FORMAT_D24S8,
	BGFX_TEXTURE_FORMAT_D32,
	BGFX_TEXTURE_FORMAT_D16F,
	BGFX_TEXTURE_FORMAT_D24F,
	BGFX_TEXTURE_FORMAT_D32F,
	BGFX_TEXTURE_FORMAT_D0S8,

	BGFX_TEXTURE_FORMAT_COUNT
};

typedef enum bgfx_texture_format bgfx_texture_format_t;

enum bgfx_uniform_type
{
	BGFX_UNIFORM_TYPE_UNIFORM1I,
	BGFX_UNIFORM_TYPE_UNIFORM1F,
	BGFX_UNIFORM_TYPE_END,

	BGFX_UNIFORM_TYPE_UNIFORM1IV,
	BGFX_UNIFORM_TYPE_UNIFORM1FV,
	BGFX_UNIFORM_TYPE_UNIFORM2FV,
	BGFX_UNIFORM_TYPE_UNIFORM3FV,
	BGFX_UNIFORM_TYPE_UNIFORM4FV,
	BGFX_UNIFORM_TYPE_UNIFORM3X3FV,
	BGFX_UNIFORM_TYPE_UNIFORM4X4FV,

	BGFX_UNIFORM_TYPE_COUNT
};

typedef enum bgfx_uniform_type bgfx_uniform_type_t;

#define BGFX_HANDLE_T(_name) \
	struct _name { uint16_t idx; }; \
	typedef struct _name _name##_t

BGFX_HANDLE_T(bgfx_dynamic_index_buffer_handle);
BGFX_HANDLE_T(bgfx_dynamic_vertex_buffer_handle);
BGFX_HANDLE_T(bgfx_frame_buffer_handle);
BGFX_HANDLE_T(bgfx_index_buffer_handle);
BGFX_HANDLE_T(bgfx_program_handle);
BGFX_HANDLE_T(bgfx_shader_handle);
BGFX_HANDLE_T(bgfx_texture_handle);
BGFX_HANDLE_T(bgfx_uniform_handle);
BGFX_HANDLE_T(bgfx_vertex_buffer_handle);
BGFX_HANDLE_T(bgfx_vertex_decl_handle);

#undef BGFX_HANDLE_T

struct bgfx_memory
{
	uint8_t* data;
	uint32_t size;
};

typedef struct bgfx_memory bgfx_memory_t;

struct bgfx_vertex_decl
{
	uint32_t hash;
	uint16_t stride;
	uint16_t offset[BGFX_ATTRIB_COUNT];
	uint8_t  attributes[BGFX_ATTRIB_COUNT];
};

typedef struct bgfx_vertex_decl bgfx_vertex_decl_t;

struct bgfx_transient_index_buffer
{
	uint8_t* data;
	uint32_t size;
	bgfx_index_buffer_handle_t handle;
	uint32_t startIndex;
};

typedef struct bgfx_transient_index_buffer bgfx_transient_index_buffer_t;

struct bgfx_transient_vertex_buffer
{
	uint8_t* data;
	uint32_t size;
	uint32_t startVertex;
	uint16_t stride;
	bgfx_vertex_buffer_handle_t handle;
	bgfx_vertex_decl_handle_t decl;
};

typedef struct bgfx_transient_vertex_buffer bgfx_transient_vertex_buffer_t;

struct bgfx_instance_data_buffer
{
	uint8_t* data;
	uint32_t size;
	uint32_t offset;
	uint16_t stride;
	uint16_t num;
	bgfx_vertex_buffer_handle_t handle;
};

typedef struct bgfx_instance_data_buffer bgfx_instance_data_buffer_t;

struct bgfx_texture_info
{
	bgfx_texture_format_t format;
	uint32_t storageSize;
	uint16_t width;
	uint16_t height;
	uint16_t depth;
	uint8_t numMips;
	uint8_t bitsPerPixel;
};

typedef struct bgfx_texture_info bgfx_texture_info_t;

#if defined(__cplusplus)
#	define BGFX_C_API extern "C"
#else
#	define BGFX_C_API
#endif // defined(__cplusplus)

///
BGFX_C_API void bgfx_vertex_decl_begin(bgfx_vertex_decl_t* _decl, bgfx_renderer_type_t _renderer);

///
BGFX_C_API void bgfx_vertex_decl_add(bgfx_vertex_decl_t* _decl, bgfx_attrib_t _attrib, uint8_t _num, bgfx_attrib_type_t _type, bool _normalized, bool _asInt);

///
BGFX_C_API void bgfx_vertex_decl_skip(bgfx_vertex_decl_t* _decl, uint8_t _num);

///
BGFX_C_API void bgfx_vertex_decl_end(bgfx_vertex_decl_t* _decl);

///
BGFX_C_API void bgfx_init();

///
BGFX_C_API void bgfx_shutdown();

///
BGFX_C_API void bgfx_reset(uint32_t _width, uint32_t _height, uint32_t _flags);

///
BGFX_C_API uint32_t bgfx_frame();

///
BGFX_C_API bgfx_renderer_type_t bgfx_get_renderer_type();

///
BGFX_C_API const bgfx_memory_t* bgfx_alloc(uint32_t _size);

///
BGFX_C_API const bgfx_memory_t* bgfx_copy(const void* _data, uint32_t _size);

///
BGFX_C_API const bgfx_memory_t* bgfx_make_ref(const void* _data, uint32_t _size);

///
BGFX_C_API void bgfx_set_debug(uint32_t _debug);

///
BGFX_C_API void bgfx_dbg_text_clear(uint8_t _attr, bool _small);

///
BGFX_C_API void bgfx_dbg_text_printf(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, ...);

///
BGFX_C_API bgfx_index_buffer_handle_t bgfx_create_index_buffer(const bgfx_memory_t* _mem);

///
BGFX_C_API void bgfx_destroy_index_buffer(bgfx_index_buffer_handle_t _handle);

///
BGFX_C_API bgfx_vertex_buffer_handle_t bgfx_create_vertex_buffer(const bgfx_memory_t* _mem, const bgfx_vertex_decl_t* _decl);

///
BGFX_C_API void bgfx_destroy_vertex_buffer(bgfx_vertex_buffer_handle_t _handle);

///
BGFX_C_API bgfx_dynamic_index_buffer_handle_t bgfx_create_dynamic_index_buffer(uint32_t _num);

///
BGFX_C_API bgfx_dynamic_index_buffer_handle_t bgfx_create_dynamic_index_buffer_mem(const bgfx_memory_t* _mem);

///
BGFX_C_API void bgfx_update_dynamic_index_buffer(bgfx_dynamic_index_buffer_handle_t _handle, const bgfx_memory_t* _mem);

///
BGFX_C_API void bgfx_destroy_dynamic_index_buffer(bgfx_dynamic_index_buffer_handle_t _handle);

///
BGFX_C_API bgfx_dynamic_vertex_buffer_handle_t bgfx_create_dynamic_vertex_buffer(uint16_t _num, const bgfx_vertex_decl_t* _decl);

///
BGFX_C_API bgfx_dynamic_vertex_buffer_handle_t bgfx_create_dynamic_vertex_buffer_mem(const bgfx_memory_t* _mem, const bgfx_vertex_decl_t* _decl);

///
BGFX_C_API void bgfx_update_dynamic_vertex_buffer(bgfx_dynamic_vertex_buffer_handle_t _handle, const bgfx_memory_t* _mem);

///
BGFX_C_API void bgfx_destroy_dynamic_vertex_buffer(bgfx_dynamic_vertex_buffer_handle_t _handle);

///
BGFX_C_API bool bgfx_check_avail_transient_index_buffer(uint32_t _num);

///
BGFX_C_API bool bgfx_check_avail_transient_vertex_buffer(uint32_t _num, const bgfx_vertex_decl_t* _decl);

///
BGFX_C_API bool bgfx_check_avail_instance_data_buffer(uint32_t _num, uint16_t _stride);

///
BGFX_C_API bool bgfx_check_avail_transient_buffers(uint32_t _numVertices, const bgfx_vertex_decl_t* _decl, uint32_t _numIndices);

///
BGFX_C_API void bgfx_alloc_transient_index_buffer(bgfx_transient_index_buffer_t* _tib, uint32_t _num);

///
BGFX_C_API void bgfx_alloc_transient_vertex_buffer(bgfx_transient_vertex_buffer_t* _tvb, uint32_t _num, const bgfx_vertex_decl_t* _decl);

///
BGFX_C_API bool bgfx_alloc_transient_buffers(bgfx_transient_vertex_buffer_t* _tvb, const bgfx_vertex_decl_t* _decl, uint16_t _numVertices, bgfx_transient_index_buffer_t* _tib, uint16_t _numIndices);

///
BGFX_C_API const bgfx_instance_data_buffer_t* bgfx_alloc_instance_data_buffer(uint32_t _num, uint16_t _stride);

///
BGFX_C_API bgfx_shader_handle_t bgfx_create_shader(const bgfx_memory_t* _mem);

///
BGFX_C_API uint16_t bgfx_get_shader_uniforms(bgfx_shader_handle_t _handle, bgfx_uniform_handle_t* _uniforms, uint16_t _max);

///
BGFX_C_API void bgfx_destroy_shader(bgfx_shader_handle_t _handle);

///
BGFX_C_API bgfx_program_handle_t bgfx_create_program(bgfx_shader_handle_t _vsh, bgfx_shader_handle_t _fsh, bool _destroyShaders);

///
BGFX_C_API void bgfx_destroy_program(bgfx_program_handle_t _handle);

///
BGFX_C_API void bgfx_calc_texture_size(bgfx_texture_info_t* _info, uint16_t _width, uint16_t _height, uint16_t _depth, uint8_t _numMips, bgfx_texture_format_t _format);

///
BGFX_C_API bgfx_texture_handle_t bgfx_create_texture(const bgfx_memory_t* _mem, uint32_t _flags, uint8_t _skip, bgfx_texture_info_t* _info);

///
BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_2d(uint16_t _width, uint16_t _height, uint8_t _numMips, bgfx_texture_format_t _format, uint32_t _flags, const bgfx_memory_t* _mem);

///
BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_3d(uint16_t _width, uint16_t _height, uint16_t _depth, uint8_t _numMips, bgfx_texture_format_t _format, uint32_t _flags, const bgfx_memory_t* _mem);

///
BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_cube(uint16_t _size, uint8_t _numMips, bgfx_texture_format_t _format, uint32_t _flags, const bgfx_memory_t* _mem);

///
BGFX_C_API void bgfx_update_texture_2d(bgfx_texture_handle_t _handle, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const bgfx_memory_t* _mem, uint16_t _pitch);

///
BGFX_C_API void bgfx_update_texture_3d(bgfx_texture_handle_t _handle, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _z, uint16_t _width, uint16_t _height, uint16_t _depth, const bgfx_memory_t* _mem);

///
BGFX_C_API void bgfx_update_texture_cube(bgfx_texture_handle_t _handle, uint8_t _side, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const bgfx_memory_t* _mem, uint16_t _pitch);

///
BGFX_C_API void bgfx_destroy_texture(bgfx_texture_handle_t _handle);

///
BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer(uint16_t _width, uint16_t _height, bgfx_texture_format_t _format, uint32_t _textureFlags);

///
BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_from_handles(uint8_t _num, bgfx_texture_handle_t* _handles, bool _destroyTextures);

///
BGFX_C_API void bgfx_destroy_frame_buffer(bgfx_frame_buffer_handle_t _handle);

///
BGFX_C_API bgfx_uniform_handle_t bgfx_create_uniform(const char* _name, bgfx_uniform_type_t _type, uint16_t _num);

///
BGFX_C_API void bgfx_destroy_uniform(bgfx_uniform_handle_t _handle);

///
BGFX_C_API void bgfx_set_view_name(uint8_t _id, const char* _name);

///
BGFX_C_API void bgfx_set_view_rect(uint8_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

///
BGFX_C_API void bgfx_set_view_rect_mask(uint32_t _viewMask, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

///
BGFX_C_API void bgfx_set_view_scissor(uint8_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

///
BGFX_C_API void bgfx_set_view_scissor_mask(uint32_t _viewMask, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

///
BGFX_C_API void bgfx_set_view_clear(uint8_t _id, uint8_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil);

///
BGFX_C_API void bgfx_set_view_clear_mask(uint32_t _viewMask, uint8_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil);

///
BGFX_C_API void bgfx_set_view_seq(uint8_t _id, bool _enabled);

///
BGFX_C_API void bgfx_set_view_seq_mask(uint32_t _viewMask, bool _enabled);

///
BGFX_C_API void bgfx_set_view_frame_buffer(uint8_t _id, bgfx_frame_buffer_handle_t _handle);

///
BGFX_C_API void bgfx_set_view_frame_buffer_mask(uint32_t _viewMask, bgfx_frame_buffer_handle_t _handle);

///
BGFX_C_API void bgfx_set_view_transform(uint8_t _id, const void* _view, const void* _proj);

///
BGFX_C_API void bgfx_set_view_transform_mask(uint32_t _viewMask, const void* _view, const void* _proj);

///
BGFX_C_API void bgfx_set_marker(const char* _marker);

///
BGFX_C_API void bgfx_set_state(uint64_t _state, uint32_t _rgba);

///
BGFX_C_API void bgfx_set_stencil(uint32_t _fstencil, uint32_t _bstencil);

///
BGFX_C_API uint16_t bgfx_set_scissor(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

///
BGFX_C_API void bgfx_set_scissor_cached(uint16_t _cache);

///
BGFX_C_API uint32_t bgfx_set_transform(const void* _mtx, uint16_t _num);

///
BGFX_C_API void bgfx_set_transform_cached(uint32_t _cache, uint16_t _num);

///
BGFX_C_API void bgfx_set_uniform(bgfx_uniform_handle_t _handle, const void* _value, uint16_t _num);

///
BGFX_C_API void bgfx_set_index_buffer(bgfx_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices);

///
BGFX_C_API void bgfx_set_dynamic_index_buffer(bgfx_dynamic_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices);

///
BGFX_C_API void bgfx_set_transient_index_buffer(const bgfx_transient_index_buffer_t* _tib, uint32_t _firstIndex, uint32_t _numIndices);

///
BGFX_C_API void bgfx_set_vertex_buffer(bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices);

///
BGFX_C_API void bgfx_set_dynamic_vertex_buffer(bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _numVertices);

///
BGFX_C_API void bgfx_set_transient_vertex_buffer(const bgfx_transient_vertex_buffer_t* _tvb, uint32_t _startVertex, uint32_t _numVertices);

///
BGFX_C_API void bgfx_set_instance_data_buffer(const bgfx_instance_data_buffer_t* _idb, uint16_t _num);

///
BGFX_C_API void bgfx_set_program(bgfx_program_handle_t _handle);

///
BGFX_C_API void bgfx_set_texture(uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint32_t _flags);

///
BGFX_C_API void bgfx_set_texture_from_frame_buffer(uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_frame_buffer_handle_t _handle, uint8_t _attachment, uint32_t _flags);

///
BGFX_C_API uint32_t bgfx_submit(uint8_t _id, int32_t _depth);

///
BGFX_C_API uint32_t bgfx_submit_mask(uint32_t _viewMask, int32_t _depth);

///
BGFX_C_API void bgfx_discard();

///
BGFX_C_API void bgfx_save_screen_shot(const char* _filePath);

#undef BGFX_C_API

#endif // BGFX_C99_H_HEADER_GUARD
