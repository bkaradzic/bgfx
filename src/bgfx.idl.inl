/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

/*
 *
 * AUTO GENERATED FROM IDL! DO NOT EDIT! (source : temp.bgfx.idl.inl)
 *
 * More info about IDL:
 * https://gist.github.com/bkaradzic/05a1c86a6dd57bf86e2d828878e88dc2#bgfx-is-switching-to-idl-to-generate-api
 *
 */

#define BGFX_C99_ENUM_CHECK(_enum, _c99enumcount) \
	BX_STATIC_ASSERT(_enum::Count == _enum::Enum(_c99enumcount) )

BGFX_C99_ENUM_CHECK(bgfx::Fatal,                BGFX_FATAL_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::RendererType,         BGFX_RENDERER_TYPE_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::Attrib,               BGFX_ATTRIB_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::AttribType,           BGFX_ATTRIB_TYPE_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::TextureFormat,        BGFX_TEXTURE_FORMAT_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::UniformType,          BGFX_UNIFORM_TYPE_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::BackbufferRatio,      BGFX_BACKBUFFER_RATIO_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::OcclusionQueryResult, BGFX_OCCLUSION_QUERY_RESULT_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::Topology,             BGFX_TOPOLOGY_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::TopologyConvert,      BGFX_TOPOLOGY_CONVERT_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::RenderFrame,          BGFX_RENDER_FRAME_COUNT);

#undef BGFX_C99_ENUM_CHECK

#define BGFX_C99_STRUCT_SIZE_CHECK(_cppstruct, _c99struct) \
	BX_STATIC_ASSERT(sizeof(_cppstruct) == sizeof(_c99struct) )

BGFX_C99_STRUCT_SIZE_CHECK(bgfx::Memory,                bgfx_memory_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::Transform,             bgfx_transform_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::Stats,                 bgfx_stats_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::VertexLayout,          bgfx_vertex_layout_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::TransientIndexBuffer,  bgfx_transient_index_buffer_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::TransientVertexBuffer, bgfx_transient_vertex_buffer_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::InstanceDataBuffer,    bgfx_instance_data_buffer_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::TextureInfo,           bgfx_texture_info_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::UniformInfo,           bgfx_uniform_info_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::Attachment,            bgfx_attachment_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::Caps::GPU,             bgfx_caps_gpu_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::Caps::Limits,          bgfx_caps_limits_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::Caps,                  bgfx_caps_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::PlatformData,          bgfx_platform_data_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::InternalData,          bgfx_internal_data_t);

#undef BGFX_C99_STRUCT_SIZE_CHECK

BGFX_C_API void bgfx_attachment_init(bgfx_attachment_t* _this, bgfx_texture_handle_t _handle, bgfx_access_t _access, uint16_t _layer, uint16_t _numLayers, uint16_t _mip, uint8_t _resolve)
{
	bgfx::Attachment* This = (bgfx::Attachment*)_this;
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	This->init(handle.cpp, (bgfx::Access::Enum)_access, _layer, _numLayers, _mip, _resolve);
}

BGFX_C_API bgfx_vertex_layout_t* bgfx_vertex_layout_begin(bgfx_vertex_layout_t* _this, bgfx_renderer_type_t _rendererType)
{
	bgfx::VertexLayout* This = (bgfx::VertexLayout*)_this;
	return (bgfx_vertex_layout_t*)&This->begin((bgfx::RendererType::Enum)_rendererType);
}

BGFX_C_API bgfx_vertex_layout_t* bgfx_vertex_layout_add(bgfx_vertex_layout_t* _this, bgfx_attrib_t _attrib, uint8_t _num, bgfx_attrib_type_t _type, bool _normalized, bool _asInt)
{
	bgfx::VertexLayout* This = (bgfx::VertexLayout*)_this;
	return (bgfx_vertex_layout_t*)&This->add((bgfx::Attrib::Enum)_attrib, _num, (bgfx::AttribType::Enum)_type, _normalized, _asInt);
}

BGFX_C_API void bgfx_vertex_layout_decode(const bgfx_vertex_layout_t* _this, bgfx_attrib_t _attrib, uint8_t * _num, bgfx_attrib_type_t * _type, bool * _normalized, bool * _asInt)
{
	const bgfx::VertexLayout* This = (const bgfx::VertexLayout*)_this;
	bgfx::AttribType::Enum type;
	This->decode((bgfx::Attrib::Enum)_attrib, *_num, type, *_normalized, *_asInt);
	*_type = (bgfx_attrib_type_t)type;
}

BGFX_C_API bool bgfx_vertex_layout_has(const bgfx_vertex_layout_t* _this, bgfx_attrib_t _attrib)
{
	const bgfx::VertexLayout* This = (const bgfx::VertexLayout*)_this;
	return This->has((bgfx::Attrib::Enum)_attrib);
}

BGFX_C_API bgfx_vertex_layout_t* bgfx_vertex_layout_skip(bgfx_vertex_layout_t* _this, uint8_t _num)
{
	bgfx::VertexLayout* This = (bgfx::VertexLayout*)_this;
	return (bgfx_vertex_layout_t*)&This->skip(_num);
}

BGFX_C_API void bgfx_vertex_layout_end(bgfx_vertex_layout_t* _this)
{
	bgfx::VertexLayout* This = (bgfx::VertexLayout*)_this;
	This->end();
}

BGFX_C_API void bgfx_vertex_pack(const float _input[4], bool _inputNormalized, bgfx_attrib_t _attr, const bgfx_vertex_layout_t * _layout, void* _data, uint32_t _index)
{
	const bgfx::VertexLayout & layout = *(const bgfx::VertexLayout *)_layout;
	bgfx::vertexPack(_input, _inputNormalized, (bgfx::Attrib::Enum)_attr, layout, _data, _index);
}

BGFX_C_API void bgfx_vertex_unpack(float _output[4], bgfx_attrib_t _attr, const bgfx_vertex_layout_t * _layout, const void* _data, uint32_t _index)
{
	const bgfx::VertexLayout & layout = *(const bgfx::VertexLayout *)_layout;
	bgfx::vertexUnpack(_output, (bgfx::Attrib::Enum)_attr, layout, _data, _index);
}

BGFX_C_API void bgfx_vertex_convert(const bgfx_vertex_layout_t * _dstLayout, void* _dstData, const bgfx_vertex_layout_t * _srcLayout, const void* _srcData, uint32_t _num)
{
	const bgfx::VertexLayout & dstLayout = *(const bgfx::VertexLayout *)_dstLayout;
	const bgfx::VertexLayout & srcLayout = *(const bgfx::VertexLayout *)_srcLayout;
	bgfx::vertexConvert(dstLayout, _dstData, srcLayout, _srcData, _num);
}

BGFX_C_API uint32_t bgfx_weld_vertices(void* _output, const bgfx_vertex_layout_t * _layout, const void* _data, uint32_t _num, bool _index32, float _epsilon)
{
	const bgfx::VertexLayout & layout = *(const bgfx::VertexLayout *)_layout;
	return bgfx::weldVertices(_output, layout, _data, _num, _index32, _epsilon);
}

BGFX_C_API uint32_t bgfx_topology_convert(bgfx_topology_convert_t _conversion, void* _dst, uint32_t _dstSize, const void* _indices, uint32_t _numIndices, bool _index32)
{
	return bgfx::topologyConvert((bgfx::TopologyConvert::Enum)_conversion, _dst, _dstSize, _indices, _numIndices, _index32);
}

BGFX_C_API void bgfx_topology_sort_tri_list(bgfx_topology_sort_t _sort, void* _dst, uint32_t _dstSize, const float _dir[3], const float _pos[3], const void* _vertices, uint32_t _stride, const void* _indices, uint32_t _numIndices, bool _index32)
{
	bgfx::topologySortTriList((bgfx::TopologySort::Enum)_sort, _dst, _dstSize, _dir, _pos, _vertices, _stride, _indices, _numIndices, _index32);
}

BGFX_C_API uint8_t bgfx_get_supported_renderers(uint8_t _max, bgfx_renderer_type_t* _enum)
{
	return bgfx::getSupportedRenderers(_max, (bgfx::RendererType::Enum*)_enum);
}

BGFX_C_API const char* bgfx_get_renderer_name(bgfx_renderer_type_t _type)
{
	return bgfx::getRendererName((bgfx::RendererType::Enum)_type);
}

/* BGFX_C_API void bgfx_init_ctor(bgfx_init_t* _init) */

/* BGFX_C_API bool bgfx_init(const bgfx_init_t * _init) */

BGFX_C_API void bgfx_shutdown(void)
{
	bgfx::shutdown();
}

BGFX_C_API void bgfx_reset(uint32_t _width, uint32_t _height, uint32_t _flags, bgfx_texture_format_t _format)
{
	bgfx::reset(_width, _height, _flags, (bgfx::TextureFormat::Enum)_format);
}

BGFX_C_API uint32_t bgfx_frame(bool _capture)
{
	return bgfx::frame(_capture);
}

BGFX_C_API bgfx_renderer_type_t bgfx_get_renderer_type(void)
{
	return (bgfx_renderer_type_t)bgfx::getRendererType();
}

BGFX_C_API const bgfx_caps_t* bgfx_get_caps(void)
{
	return (const bgfx_caps_t*)bgfx::getCaps();
}

BGFX_C_API const bgfx_stats_t* bgfx_get_stats(void)
{
	return (const bgfx_stats_t*)bgfx::getStats();
}

BGFX_C_API const bgfx_memory_t* bgfx_alloc(uint32_t _size)
{
	return (const bgfx_memory_t*)bgfx::alloc(_size);
}

BGFX_C_API const bgfx_memory_t* bgfx_copy(const void* _data, uint32_t _size)
{
	return (const bgfx_memory_t*)bgfx::copy(_data, _size);
}

BGFX_C_API const bgfx_memory_t* bgfx_make_ref(const void* _data, uint32_t _size)
{
	return (const bgfx_memory_t*)bgfx::makeRef(_data, _size);
}

BGFX_C_API const bgfx_memory_t* bgfx_make_ref_release(const void* _data, uint32_t _size, bgfx_release_fn_t _releaseFn, void* _userData)
{
	return (const bgfx_memory_t*)bgfx::makeRef(_data, _size, (bgfx::ReleaseFn)_releaseFn, _userData);
}

BGFX_C_API void bgfx_set_debug(uint32_t _debug)
{
	bgfx::setDebug(_debug);
}

BGFX_C_API void bgfx_dbg_text_clear(uint8_t _attr, bool _small)
{
	bgfx::dbgTextClear(_attr, _small);
}

BGFX_C_API void bgfx_dbg_text_printf(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, ... )
{
	va_list argList;
	va_start(argList, _format);
	bgfx::dbgTextPrintfVargs(_x, _y, _attr, _format, argList);
	va_end(argList);
}

BGFX_C_API void bgfx_dbg_text_vprintf(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, va_list _argList)
{
	bgfx::dbgTextPrintfVargs(_x, _y, _attr, _format, _argList);
}

BGFX_C_API void bgfx_dbg_text_image(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const void* _data, uint16_t _pitch)
{
	bgfx::dbgTextImage(_x, _y, _width, _height, _data, _pitch);
}

BGFX_C_API bgfx_index_buffer_handle_t bgfx_create_index_buffer(const bgfx_memory_t* _mem, uint16_t _flags)
{
	union { bgfx_index_buffer_handle_t c; bgfx::IndexBufferHandle cpp; } handle_ret;
	handle_ret.cpp = bgfx::createIndexBuffer((const bgfx::Memory*)_mem, _flags);
	return handle_ret.c;
}

BGFX_C_API void bgfx_set_index_buffer_name(bgfx_index_buffer_handle_t _handle, const char* _name, int32_t _len)
{
	union { bgfx_index_buffer_handle_t c; bgfx::IndexBufferHandle cpp; } handle = { _handle };
	bgfx::setName(handle.cpp, _name, _len);
}

BGFX_C_API void bgfx_destroy_index_buffer(bgfx_index_buffer_handle_t _handle)
{
	union { bgfx_index_buffer_handle_t c; bgfx::IndexBufferHandle cpp; } handle = { _handle };
	bgfx::destroy(handle.cpp);
}

BGFX_C_API bgfx_vertex_layout_handle_t bgfx_create_vertex_layout(const bgfx_vertex_layout_t * _layout)
{
	const bgfx::VertexLayout & layout = *(const bgfx::VertexLayout *)_layout;
	union { bgfx_vertex_layout_handle_t c; bgfx::VertexLayoutHandle cpp; } handle_ret;
	handle_ret.cpp = bgfx::createVertexLayout(layout);
	return handle_ret.c;
}

BGFX_C_API void bgfx_destroy_vertex_layout(bgfx_vertex_layout_handle_t _layoutHandle)
{
	union { bgfx_vertex_layout_handle_t c; bgfx::VertexLayoutHandle cpp; } layoutHandle = { _layoutHandle };
	bgfx::destroy(layoutHandle.cpp);
}

BGFX_C_API bgfx_vertex_buffer_handle_t bgfx_create_vertex_buffer(const bgfx_memory_t* _mem, const bgfx_vertex_layout_t * _layout, uint16_t _flags)
{
	const bgfx::VertexLayout & layout = *(const bgfx::VertexLayout *)_layout;
	union { bgfx_vertex_buffer_handle_t c; bgfx::VertexBufferHandle cpp; } handle_ret;
	handle_ret.cpp = bgfx::createVertexBuffer((const bgfx::Memory*)_mem, layout, _flags);
	return handle_ret.c;
}

BGFX_C_API void bgfx_set_vertex_buffer_name(bgfx_vertex_buffer_handle_t _handle, const char* _name, int32_t _len)
{
	union { bgfx_vertex_buffer_handle_t c; bgfx::VertexBufferHandle cpp; } handle = { _handle };
	bgfx::setName(handle.cpp, _name, _len);
}

BGFX_C_API void bgfx_destroy_vertex_buffer(bgfx_vertex_buffer_handle_t _handle)
{
	union { bgfx_vertex_buffer_handle_t c; bgfx::VertexBufferHandle cpp; } handle = { _handle };
	bgfx::destroy(handle.cpp);
}

BGFX_C_API bgfx_dynamic_index_buffer_handle_t bgfx_create_dynamic_index_buffer(uint32_t _num, uint16_t _flags)
{
	union { bgfx_dynamic_index_buffer_handle_t c; bgfx::DynamicIndexBufferHandle cpp; } handle_ret;
	handle_ret.cpp = bgfx::createDynamicIndexBuffer(_num, _flags);
	return handle_ret.c;
}

BGFX_C_API bgfx_dynamic_index_buffer_handle_t bgfx_create_dynamic_index_buffer_mem(const bgfx_memory_t* _mem, uint16_t _flags)
{
	union { bgfx_dynamic_index_buffer_handle_t c; bgfx::DynamicIndexBufferHandle cpp; } handle_ret;
	handle_ret.cpp = bgfx::createDynamicIndexBuffer((const bgfx::Memory*)_mem, _flags);
	return handle_ret.c;
}

BGFX_C_API void bgfx_update_dynamic_index_buffer(bgfx_dynamic_index_buffer_handle_t _handle, uint32_t _startIndex, const bgfx_memory_t* _mem)
{
	union { bgfx_dynamic_index_buffer_handle_t c; bgfx::DynamicIndexBufferHandle cpp; } handle = { _handle };
	bgfx::update(handle.cpp, _startIndex, (const bgfx::Memory*)_mem);
}

BGFX_C_API void bgfx_destroy_dynamic_index_buffer(bgfx_dynamic_index_buffer_handle_t _handle)
{
	union { bgfx_dynamic_index_buffer_handle_t c; bgfx::DynamicIndexBufferHandle cpp; } handle = { _handle };
	bgfx::destroy(handle.cpp);
}

BGFX_C_API bgfx_dynamic_vertex_buffer_handle_t bgfx_create_dynamic_vertex_buffer(uint32_t _num, const bgfx_vertex_layout_t* _layout, uint16_t _flags)
{
	const bgfx::VertexLayout& layout = *(const bgfx::VertexLayout*)_layout;
	union { bgfx_dynamic_vertex_buffer_handle_t c; bgfx::DynamicVertexBufferHandle cpp; } handle_ret;
	handle_ret.cpp = bgfx::createDynamicVertexBuffer(_num, layout, _flags);
	return handle_ret.c;
}

BGFX_C_API bgfx_dynamic_vertex_buffer_handle_t bgfx_create_dynamic_vertex_buffer_mem(const bgfx_memory_t* _mem, const bgfx_vertex_layout_t* _layout, uint16_t _flags)
{
	const bgfx::VertexLayout& layout = *(const bgfx::VertexLayout*)_layout;
	union { bgfx_dynamic_vertex_buffer_handle_t c; bgfx::DynamicVertexBufferHandle cpp; } handle_ret;
	handle_ret.cpp = bgfx::createDynamicVertexBuffer((const bgfx::Memory*)_mem, layout, _flags);
	return handle_ret.c;
}

BGFX_C_API void bgfx_update_dynamic_vertex_buffer(bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, const bgfx_memory_t* _mem)
{
	union { bgfx_dynamic_vertex_buffer_handle_t c; bgfx::DynamicVertexBufferHandle cpp; } handle = { _handle };
	bgfx::update(handle.cpp, _startVertex, (const bgfx::Memory*)_mem);
}

BGFX_C_API void bgfx_destroy_dynamic_vertex_buffer(bgfx_dynamic_vertex_buffer_handle_t _handle)
{
	union { bgfx_dynamic_vertex_buffer_handle_t c; bgfx::DynamicVertexBufferHandle cpp; } handle = { _handle };
	bgfx::destroy(handle.cpp);
}

BGFX_C_API uint32_t bgfx_get_avail_transient_index_buffer(uint32_t _num, bool _index32)
{
	return bgfx::getAvailTransientIndexBuffer(_num, _index32);
}

BGFX_C_API uint32_t bgfx_get_avail_transient_vertex_buffer(uint32_t _num, const bgfx_vertex_layout_t * _layout)
{
	const bgfx::VertexLayout & layout = *(const bgfx::VertexLayout *)_layout;
	return bgfx::getAvailTransientVertexBuffer(_num, layout);
}

BGFX_C_API uint32_t bgfx_get_avail_instance_data_buffer(uint32_t _num, uint16_t _stride)
{
	return bgfx::getAvailInstanceDataBuffer(_num, _stride);
}

BGFX_C_API void bgfx_alloc_transient_index_buffer(bgfx_transient_index_buffer_t* _tib, uint32_t _num, bool _index32)
{
	bgfx::allocTransientIndexBuffer((bgfx::TransientIndexBuffer*)_tib, _num, _index32);
}

BGFX_C_API void bgfx_alloc_transient_vertex_buffer(bgfx_transient_vertex_buffer_t* _tvb, uint32_t _num, const bgfx_vertex_layout_t * _layout)
{
	const bgfx::VertexLayout & layout = *(const bgfx::VertexLayout *)_layout;
	bgfx::allocTransientVertexBuffer((bgfx::TransientVertexBuffer*)_tvb, _num, layout);
}

BGFX_C_API bool bgfx_alloc_transient_buffers(bgfx_transient_vertex_buffer_t* _tvb, const bgfx_vertex_layout_t * _layout, uint32_t _numVertices, bgfx_transient_index_buffer_t* _tib, uint32_t _numIndices, bool _index32)
{
	const bgfx::VertexLayout & layout = *(const bgfx::VertexLayout *)_layout;
	return bgfx::allocTransientBuffers((bgfx::TransientVertexBuffer*)_tvb, layout, _numVertices, (bgfx::TransientIndexBuffer*)_tib, _numIndices, _index32);
}

BGFX_C_API void bgfx_alloc_instance_data_buffer(bgfx_instance_data_buffer_t* _idb, uint32_t _num, uint16_t _stride)
{
	bgfx::allocInstanceDataBuffer((bgfx::InstanceDataBuffer*)_idb, _num, _stride);
}

BGFX_C_API bgfx_indirect_buffer_handle_t bgfx_create_indirect_buffer(uint32_t _num)
{
	union { bgfx_indirect_buffer_handle_t c; bgfx::IndirectBufferHandle cpp; } handle_ret;
	handle_ret.cpp = bgfx::createIndirectBuffer(_num);
	return handle_ret.c;
}

BGFX_C_API void bgfx_destroy_indirect_buffer(bgfx_indirect_buffer_handle_t _handle)
{
	union { bgfx_indirect_buffer_handle_t c; bgfx::IndirectBufferHandle cpp; } handle = { _handle };
	bgfx::destroy(handle.cpp);
}

BGFX_C_API bgfx_shader_handle_t bgfx_create_shader(const bgfx_memory_t* _mem)
{
	union { bgfx_shader_handle_t c; bgfx::ShaderHandle cpp; } handle_ret;
	handle_ret.cpp = bgfx::createShader((const bgfx::Memory*)_mem);
	return handle_ret.c;
}

BGFX_C_API uint16_t bgfx_get_shader_uniforms(bgfx_shader_handle_t _handle, bgfx_uniform_handle_t* _uniforms, uint16_t _max)
{
	union { bgfx_shader_handle_t c; bgfx::ShaderHandle cpp; } handle = { _handle };
	return bgfx::getShaderUniforms(handle.cpp, (bgfx::UniformHandle*)_uniforms, _max);
}

BGFX_C_API void bgfx_set_shader_name(bgfx_shader_handle_t _handle, const char* _name, int32_t _len)
{
	union { bgfx_shader_handle_t c; bgfx::ShaderHandle cpp; } handle = { _handle };
	bgfx::setName(handle.cpp, _name, _len);
}

BGFX_C_API void bgfx_destroy_shader(bgfx_shader_handle_t _handle)
{
	union { bgfx_shader_handle_t c; bgfx::ShaderHandle cpp; } handle = { _handle };
	bgfx::destroy(handle.cpp);
}

BGFX_C_API bgfx_program_handle_t bgfx_create_program(bgfx_shader_handle_t _vsh, bgfx_shader_handle_t _fsh, bool _destroyShaders)
{
	union { bgfx_shader_handle_t c; bgfx::ShaderHandle cpp; } vsh = { _vsh };
	union { bgfx_shader_handle_t c; bgfx::ShaderHandle cpp; } fsh = { _fsh };
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } handle_ret;
	handle_ret.cpp = bgfx::createProgram(vsh.cpp, fsh.cpp, _destroyShaders);
	return handle_ret.c;
}

BGFX_C_API bgfx_program_handle_t bgfx_create_compute_program(bgfx_shader_handle_t _csh, bool _destroyShaders)
{
	union { bgfx_shader_handle_t c; bgfx::ShaderHandle cpp; } csh = { _csh };
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } handle_ret;
	handle_ret.cpp = bgfx::createProgram(csh.cpp, _destroyShaders);
	return handle_ret.c;
}

BGFX_C_API void bgfx_destroy_program(bgfx_program_handle_t _handle)
{
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } handle = { _handle };
	bgfx::destroy(handle.cpp);
}

BGFX_C_API bool bgfx_is_texture_valid(uint16_t _depth, bool _cubeMap, uint16_t _numLayers, bgfx_texture_format_t _format, uint64_t _flags)
{
	return bgfx::isTextureValid(_depth, _cubeMap, _numLayers, (bgfx::TextureFormat::Enum)_format, _flags);
}

BGFX_C_API bool bgfx_is_frame_buffer_valid(uint8_t _num, const bgfx_attachment_t* _attachment)
{
	return bgfx::isFrameBufferValid(_num, (const bgfx::Attachment*)_attachment);
}

BGFX_C_API void bgfx_calc_texture_size(bgfx_texture_info_t * _info, uint16_t _width, uint16_t _height, uint16_t _depth, bool _cubeMap, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format)
{
	bgfx::TextureInfo & info = *(bgfx::TextureInfo *)_info;
	bgfx::calcTextureSize(info, _width, _height, _depth, _cubeMap, _hasMips, _numLayers, (bgfx::TextureFormat::Enum)_format);
}

BGFX_C_API bgfx_texture_handle_t bgfx_create_texture(const bgfx_memory_t* _mem, uint64_t _flags, uint8_t _skip, bgfx_texture_info_t* _info)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle_ret;
	handle_ret.cpp = bgfx::createTexture((const bgfx::Memory*)_mem, _flags, _skip, (bgfx::TextureInfo*)_info);
	return handle_ret.c;
}

BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_2d(uint16_t _width, uint16_t _height, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format, uint64_t _flags, const bgfx_memory_t* _mem)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle_ret;
	handle_ret.cpp = bgfx::createTexture2D(_width, _height, _hasMips, _numLayers, (bgfx::TextureFormat::Enum)_format, _flags, (const bgfx::Memory*)_mem);
	return handle_ret.c;
}

BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_2d_scaled(bgfx_backbuffer_ratio_t _ratio, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format, uint64_t _flags)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle_ret;
	handle_ret.cpp = bgfx::createTexture2D((bgfx::BackbufferRatio::Enum)_ratio, _hasMips, _numLayers, (bgfx::TextureFormat::Enum)_format, _flags);
	return handle_ret.c;
}

BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_3d(uint16_t _width, uint16_t _height, uint16_t _depth, bool _hasMips, bgfx_texture_format_t _format, uint64_t _flags, const bgfx_memory_t* _mem)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle_ret;
	handle_ret.cpp = bgfx::createTexture3D(_width, _height, _depth, _hasMips, (bgfx::TextureFormat::Enum)_format, _flags, (const bgfx::Memory*)_mem);
	return handle_ret.c;
}

BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_cube(uint16_t _size, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format, uint64_t _flags, const bgfx_memory_t* _mem)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle_ret;
	handle_ret.cpp = bgfx::createTextureCube(_size, _hasMips, _numLayers, (bgfx::TextureFormat::Enum)_format, _flags, (const bgfx::Memory*)_mem);
	return handle_ret.c;
}

BGFX_C_API void bgfx_update_texture_2d(bgfx_texture_handle_t _handle, uint16_t _layer, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const bgfx_memory_t* _mem, uint16_t _pitch)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	bgfx::updateTexture2D(handle.cpp, _layer, _mip, _x, _y, _width, _height, (const bgfx::Memory*)_mem, _pitch);
}

BGFX_C_API void bgfx_update_texture_3d(bgfx_texture_handle_t _handle, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _z, uint16_t _width, uint16_t _height, uint16_t _depth, const bgfx_memory_t* _mem)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	bgfx::updateTexture3D(handle.cpp, _mip, _x, _y, _z, _width, _height, _depth, (const bgfx::Memory*)_mem);
}

BGFX_C_API void bgfx_update_texture_cube(bgfx_texture_handle_t _handle, uint16_t _layer, uint8_t _side, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const bgfx_memory_t* _mem, uint16_t _pitch)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	bgfx::updateTextureCube(handle.cpp, _layer, _side, _mip, _x, _y, _width, _height, (const bgfx::Memory*)_mem, _pitch);
}

BGFX_C_API uint32_t bgfx_read_texture(bgfx_texture_handle_t _handle, void* _data, uint8_t _mip)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	return bgfx::readTexture(handle.cpp, _data, _mip);
}

BGFX_C_API void bgfx_set_texture_name(bgfx_texture_handle_t _handle, const char* _name, int32_t _len)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	bgfx::setName(handle.cpp, _name, _len);
}

BGFX_C_API void* bgfx_get_direct_access_ptr(bgfx_texture_handle_t _handle)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	return bgfx::getDirectAccessPtr(handle.cpp);
}

BGFX_C_API void bgfx_destroy_texture(bgfx_texture_handle_t _handle)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	bgfx::destroy(handle.cpp);
}

BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer(uint16_t _width, uint16_t _height, bgfx_texture_format_t _format, uint64_t _textureFlags)
{
	union { bgfx_frame_buffer_handle_t c; bgfx::FrameBufferHandle cpp; } handle_ret;
	handle_ret.cpp = bgfx::createFrameBuffer(_width, _height, (bgfx::TextureFormat::Enum)_format, _textureFlags);
	return handle_ret.c;
}

BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_scaled(bgfx_backbuffer_ratio_t _ratio, bgfx_texture_format_t _format, uint64_t _textureFlags)
{
	union { bgfx_frame_buffer_handle_t c; bgfx::FrameBufferHandle cpp; } handle_ret;
	handle_ret.cpp = bgfx::createFrameBuffer((bgfx::BackbufferRatio::Enum)_ratio, (bgfx::TextureFormat::Enum)_format, _textureFlags);
	return handle_ret.c;
}

BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_from_handles(uint8_t _num, const bgfx_texture_handle_t* _handles, bool _destroyTexture)
{
	union { bgfx_frame_buffer_handle_t c; bgfx::FrameBufferHandle cpp; } handle_ret;
	handle_ret.cpp = bgfx::createFrameBuffer(_num, (const bgfx::TextureHandle*)_handles, _destroyTexture);
	return handle_ret.c;
}

BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_from_attachment(uint8_t _num, const bgfx_attachment_t* _attachment, bool _destroyTexture)
{
	union { bgfx_frame_buffer_handle_t c; bgfx::FrameBufferHandle cpp; } handle_ret;
	handle_ret.cpp = bgfx::createFrameBuffer(_num, (const bgfx::Attachment*)_attachment, _destroyTexture);
	return handle_ret.c;
}

BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_from_nwh(void* _nwh, uint16_t _width, uint16_t _height, bgfx_texture_format_t _format, bgfx_texture_format_t _depthFormat)
{
	union { bgfx_frame_buffer_handle_t c; bgfx::FrameBufferHandle cpp; } handle_ret;
	handle_ret.cpp = bgfx::createFrameBuffer(_nwh, _width, _height, (bgfx::TextureFormat::Enum)_format, (bgfx::TextureFormat::Enum)_depthFormat);
	return handle_ret.c;
}

BGFX_C_API void bgfx_set_frame_buffer_name(bgfx_frame_buffer_handle_t _handle, const char* _name, int32_t _len)
{
	union { bgfx_frame_buffer_handle_t c; bgfx::FrameBufferHandle cpp; } handle = { _handle };
	bgfx::setName(handle.cpp, _name, _len);
}

BGFX_C_API bgfx_texture_handle_t bgfx_get_texture(bgfx_frame_buffer_handle_t _handle, uint8_t _attachment)
{
	union { bgfx_frame_buffer_handle_t c; bgfx::FrameBufferHandle cpp; } handle = { _handle };
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle_ret;
	handle_ret.cpp = bgfx::getTexture(handle.cpp, _attachment);
	return handle_ret.c;
}

BGFX_C_API void bgfx_destroy_frame_buffer(bgfx_frame_buffer_handle_t _handle)
{
	union { bgfx_frame_buffer_handle_t c; bgfx::FrameBufferHandle cpp; } handle = { _handle };
	bgfx::destroy(handle.cpp);
}

BGFX_C_API bgfx_uniform_handle_t bgfx_create_uniform(const char* _name, bgfx_uniform_type_t _type, uint16_t _num)
{
	union { bgfx_uniform_handle_t c; bgfx::UniformHandle cpp; } handle_ret;
	handle_ret.cpp = bgfx::createUniform(_name, (bgfx::UniformType::Enum)_type, _num);
	return handle_ret.c;
}

BGFX_C_API void bgfx_get_uniform_info(bgfx_uniform_handle_t _handle, bgfx_uniform_info_t * _info)
{
	union { bgfx_uniform_handle_t c; bgfx::UniformHandle cpp; } handle = { _handle };
	bgfx::UniformInfo & info = *(bgfx::UniformInfo *)_info;
	bgfx::getUniformInfo(handle.cpp, info);
}

BGFX_C_API void bgfx_destroy_uniform(bgfx_uniform_handle_t _handle)
{
	union { bgfx_uniform_handle_t c; bgfx::UniformHandle cpp; } handle = { _handle };
	bgfx::destroy(handle.cpp);
}

BGFX_C_API bgfx_occlusion_query_handle_t bgfx_create_occlusion_query(void)
{
	union { bgfx_occlusion_query_handle_t c; bgfx::OcclusionQueryHandle cpp; } handle_ret;
	handle_ret.cpp = bgfx::createOcclusionQuery();
	return handle_ret.c;
}

BGFX_C_API bgfx_occlusion_query_result_t bgfx_get_result(bgfx_occlusion_query_handle_t _handle, int32_t* _result)
{
	union { bgfx_occlusion_query_handle_t c; bgfx::OcclusionQueryHandle cpp; } handle = { _handle };
	return (bgfx_occlusion_query_result_t)bgfx::getResult(handle.cpp, _result);
}

BGFX_C_API void bgfx_destroy_occlusion_query(bgfx_occlusion_query_handle_t _handle)
{
	union { bgfx_occlusion_query_handle_t c; bgfx::OcclusionQueryHandle cpp; } handle = { _handle };
	bgfx::destroy(handle.cpp);
}

BGFX_C_API void bgfx_set_palette_color(uint8_t _index, const float _rgba[4])
{
	bgfx::setPaletteColor(_index, _rgba);
}

BGFX_C_API void bgfx_set_palette_color_rgba8(uint8_t _index, uint32_t _rgba)
{
	bgfx::setPaletteColor(_index, _rgba);
}

BGFX_C_API void bgfx_set_view_name(bgfx_view_id_t _id, const char* _name)
{
	bgfx::setViewName((bgfx::ViewId)_id, _name);
}

BGFX_C_API void bgfx_set_view_rect(bgfx_view_id_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
{
	bgfx::setViewRect((bgfx::ViewId)_id, _x, _y, _width, _height);
}

BGFX_C_API void bgfx_set_view_rect_ratio(bgfx_view_id_t _id, uint16_t _x, uint16_t _y, bgfx_backbuffer_ratio_t _ratio)
{
	bgfx::setViewRect((bgfx::ViewId)_id, _x, _y, (bgfx::BackbufferRatio::Enum)_ratio);
}

BGFX_C_API void bgfx_set_view_scissor(bgfx_view_id_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
{
	bgfx::setViewScissor((bgfx::ViewId)_id, _x, _y, _width, _height);
}

BGFX_C_API void bgfx_set_view_clear(bgfx_view_id_t _id, uint16_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil)
{
	bgfx::setViewClear((bgfx::ViewId)_id, _flags, _rgba, _depth, _stencil);
}

BGFX_C_API void bgfx_set_view_clear_mrt(bgfx_view_id_t _id, uint16_t _flags, float _depth, uint8_t _stencil, uint8_t _c0, uint8_t _c1, uint8_t _c2, uint8_t _c3, uint8_t _c4, uint8_t _c5, uint8_t _c6, uint8_t _c7)
{
	bgfx::setViewClear((bgfx::ViewId)_id, _flags, _depth, _stencil, _c0, _c1, _c2, _c3, _c4, _c5, _c6, _c7);
}

BGFX_C_API void bgfx_set_view_mode(bgfx_view_id_t _id, bgfx_view_mode_t _mode)
{
	bgfx::setViewMode((bgfx::ViewId)_id, (bgfx::ViewMode::Enum)_mode);
}

BGFX_C_API void bgfx_set_view_frame_buffer(bgfx_view_id_t _id, bgfx_frame_buffer_handle_t _handle)
{
	union { bgfx_frame_buffer_handle_t c; bgfx::FrameBufferHandle cpp; } handle = { _handle };
	bgfx::setViewFrameBuffer((bgfx::ViewId)_id, handle.cpp);
}

BGFX_C_API void bgfx_set_view_transform(bgfx_view_id_t _id, const void* _view, const void* _proj)
{
	bgfx::setViewTransform((bgfx::ViewId)_id, _view, _proj);
}

BGFX_C_API void bgfx_set_view_order(bgfx_view_id_t _id, uint16_t _num, const bgfx_view_id_t* _order)
{
	bgfx::setViewOrder((bgfx::ViewId)_id, _num, (const bgfx::ViewId*)_order);
}

BGFX_C_API void bgfx_reset_view(bgfx_view_id_t _id)
{
	bgfx::resetView((bgfx::ViewId)_id);
}

BGFX_C_API bgfx_encoder_t* bgfx_encoder_begin(bool _forThread)
{
	return (bgfx_encoder_t*)bgfx::begin(_forThread);
}

BGFX_C_API void bgfx_encoder_end(bgfx_encoder_t* _encoder)
{
	bgfx::end((bgfx::Encoder*)_encoder);
}

BGFX_C_API void bgfx_encoder_set_marker(bgfx_encoder_t* _this, const char* _marker)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	This->setMarker(_marker);
}

BGFX_C_API void bgfx_encoder_set_state(bgfx_encoder_t* _this, uint64_t _state, uint32_t _rgba)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	This->setState(_state, _rgba);
}

BGFX_C_API void bgfx_encoder_set_condition(bgfx_encoder_t* _this, bgfx_occlusion_query_handle_t _handle, bool _visible)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	union { bgfx_occlusion_query_handle_t c; bgfx::OcclusionQueryHandle cpp; } handle = { _handle };
	This->setCondition(handle.cpp, _visible);
}

BGFX_C_API void bgfx_encoder_set_stencil(bgfx_encoder_t* _this, uint32_t _fstencil, uint32_t _bstencil)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	This->setStencil(_fstencil, _bstencil);
}

BGFX_C_API uint16_t bgfx_encoder_set_scissor(bgfx_encoder_t* _this, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	return This->setScissor(_x, _y, _width, _height);
}

BGFX_C_API void bgfx_encoder_set_scissor_cached(bgfx_encoder_t* _this, uint16_t _cache)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	This->setScissor(_cache);
}

BGFX_C_API uint32_t bgfx_encoder_set_transform(bgfx_encoder_t* _this, const void* _mtx, uint16_t _num)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	return This->setTransform(_mtx, _num);
}

BGFX_C_API void bgfx_encoder_set_transform_cached(bgfx_encoder_t* _this, uint32_t _cache, uint16_t _num)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	This->setTransform(_cache, _num);
}

BGFX_C_API uint32_t bgfx_encoder_alloc_transform(bgfx_encoder_t* _this, bgfx_transform_t* _transform, uint16_t _num)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	return This->allocTransform((bgfx::Transform*)_transform, _num);
}

BGFX_C_API void bgfx_encoder_set_uniform(bgfx_encoder_t* _this, bgfx_uniform_handle_t _handle, const void* _value, uint16_t _num)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	union { bgfx_uniform_handle_t c; bgfx::UniformHandle cpp; } handle = { _handle };
	This->setUniform(handle.cpp, _value, _num);
}

BGFX_C_API void bgfx_encoder_set_index_buffer(bgfx_encoder_t* _this, bgfx_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	union { bgfx_index_buffer_handle_t c; bgfx::IndexBufferHandle cpp; } handle = { _handle };
	This->setIndexBuffer(handle.cpp, _firstIndex, _numIndices);
}

BGFX_C_API void bgfx_encoder_set_dynamic_index_buffer(bgfx_encoder_t* _this, bgfx_dynamic_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	union { bgfx_dynamic_index_buffer_handle_t c; bgfx::DynamicIndexBufferHandle cpp; } handle = { _handle };
	This->setIndexBuffer(handle.cpp, _firstIndex, _numIndices);
}

BGFX_C_API void bgfx_encoder_set_transient_index_buffer(bgfx_encoder_t* _this, const bgfx_transient_index_buffer_t* _tib, uint32_t _firstIndex, uint32_t _numIndices)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	This->setIndexBuffer((const bgfx::TransientIndexBuffer*)_tib, _firstIndex, _numIndices);
}

BGFX_C_API void bgfx_encoder_set_vertex_buffer(bgfx_encoder_t* _this, uint8_t _stream, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	union { bgfx_vertex_buffer_handle_t c; bgfx::VertexBufferHandle cpp; } handle = { _handle };
	This->setVertexBuffer(_stream, handle.cpp, _startVertex, _numVertices);
}

BGFX_C_API void bgfx_encoder_set_vertex_buffer_with_layout(bgfx_encoder_t* _this, uint8_t _stream, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices, bgfx_vertex_layout_handle_t _layoutHandle)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	union { bgfx_vertex_buffer_handle_t c; bgfx::VertexBufferHandle cpp; } handle = { _handle };
	union { bgfx_vertex_layout_handle_t c; bgfx::VertexLayoutHandle cpp; } layoutHandle = { _layoutHandle };
	This->setVertexBuffer(_stream, handle.cpp, _startVertex, _numVertices, layoutHandle.cpp);
}

BGFX_C_API void bgfx_encoder_set_dynamic_vertex_buffer(bgfx_encoder_t* _this, uint8_t _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	union { bgfx_dynamic_vertex_buffer_handle_t c; bgfx::DynamicVertexBufferHandle cpp; } handle = { _handle };
	This->setVertexBuffer(_stream, handle.cpp, _startVertex, _numVertices);
}

BGFX_C_API void bgfx_encoder_set_dynamic_vertex_buffer_with_layout(bgfx_encoder_t* _this, uint8_t _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices, bgfx_vertex_layout_handle_t _layoutHandle)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	union { bgfx_dynamic_vertex_buffer_handle_t c; bgfx::DynamicVertexBufferHandle cpp; } handle = { _handle };
	union { bgfx_vertex_layout_handle_t c; bgfx::VertexLayoutHandle cpp; } layoutHandle = { _layoutHandle };
	This->setVertexBuffer(_stream, handle.cpp, _startVertex, _numVertices, layoutHandle.cpp);
}

BGFX_C_API void bgfx_encoder_set_transient_vertex_buffer(bgfx_encoder_t* _this, uint8_t _stream, const bgfx_transient_vertex_buffer_t* _tvb, uint32_t _startVertex, uint32_t _numVertices)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	This->setVertexBuffer(_stream, (const bgfx::TransientVertexBuffer*)_tvb, _startVertex, _numVertices);
}

BGFX_C_API void bgfx_encoder_set_transient_vertex_buffer_with_layout(bgfx_encoder_t* _this, uint8_t _stream, const bgfx_transient_vertex_buffer_t* _tvb, uint32_t _startVertex, uint32_t _numVertices, bgfx_vertex_layout_handle_t _layoutHandle)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	union { bgfx_vertex_layout_handle_t c; bgfx::VertexLayoutHandle cpp; } layoutHandle = { _layoutHandle };
	This->setVertexBuffer(_stream, (const bgfx::TransientVertexBuffer*)_tvb, _startVertex, _numVertices, layoutHandle.cpp);
}

BGFX_C_API void bgfx_encoder_set_vertex_count(bgfx_encoder_t* _this, uint32_t _numVertices)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	This->setVertexCount(_numVertices);
}

BGFX_C_API void bgfx_encoder_set_instance_data_buffer(bgfx_encoder_t* _this, const bgfx_instance_data_buffer_t* _idb, uint32_t _start, uint32_t _num)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	This->setInstanceDataBuffer((const bgfx::InstanceDataBuffer*)_idb, _start, _num);
}

BGFX_C_API void bgfx_encoder_set_instance_data_from_vertex_buffer(bgfx_encoder_t* _this, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	union { bgfx_vertex_buffer_handle_t c; bgfx::VertexBufferHandle cpp; } handle = { _handle };
	This->setInstanceDataBuffer(handle.cpp, _startVertex, _num);
}

BGFX_C_API void bgfx_encoder_set_instance_data_from_dynamic_vertex_buffer(bgfx_encoder_t* _this, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	union { bgfx_dynamic_vertex_buffer_handle_t c; bgfx::DynamicVertexBufferHandle cpp; } handle = { _handle };
	This->setInstanceDataBuffer(handle.cpp, _startVertex, _num);
}

BGFX_C_API void bgfx_encoder_set_instance_count(bgfx_encoder_t* _this, uint32_t _numInstances)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	This->setInstanceCount(_numInstances);
}

BGFX_C_API void bgfx_encoder_set_texture(bgfx_encoder_t* _this, uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint32_t _flags)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	union { bgfx_uniform_handle_t c; bgfx::UniformHandle cpp; } sampler = { _sampler };
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	This->setTexture(_stage, sampler.cpp, handle.cpp, _flags);
}

BGFX_C_API void bgfx_encoder_touch(bgfx_encoder_t* _this, bgfx_view_id_t _id)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	This->touch((bgfx::ViewId)_id);
}

BGFX_C_API void bgfx_encoder_submit(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, uint32_t _depth, uint8_t _flags)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } program = { _program };
	This->submit((bgfx::ViewId)_id, program.cpp, _depth, _flags);
}

BGFX_C_API void bgfx_encoder_submit_occlusion_query(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_occlusion_query_handle_t _occlusionQuery, uint32_t _depth, uint8_t _flags)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } program = { _program };
	union { bgfx_occlusion_query_handle_t c; bgfx::OcclusionQueryHandle cpp; } occlusionQuery = { _occlusionQuery };
	This->submit((bgfx::ViewId)_id, program.cpp, occlusionQuery.cpp, _depth, _flags);
}

BGFX_C_API void bgfx_encoder_submit_indirect(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, uint32_t _depth, uint8_t _flags)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } program = { _program };
	union { bgfx_indirect_buffer_handle_t c; bgfx::IndirectBufferHandle cpp; } indirectHandle = { _indirectHandle };
	This->submit((bgfx::ViewId)_id, program.cpp, indirectHandle.cpp, _start, _num, _depth, _flags);
}

BGFX_C_API void bgfx_encoder_set_compute_index_buffer(bgfx_encoder_t* _this, uint8_t _stage, bgfx_index_buffer_handle_t _handle, bgfx_access_t _access)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	union { bgfx_index_buffer_handle_t c; bgfx::IndexBufferHandle cpp; } handle = { _handle };
	This->setBuffer(_stage, handle.cpp, (bgfx::Access::Enum)_access);
}

BGFX_C_API void bgfx_encoder_set_compute_vertex_buffer(bgfx_encoder_t* _this, uint8_t _stage, bgfx_vertex_buffer_handle_t _handle, bgfx_access_t _access)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	union { bgfx_vertex_buffer_handle_t c; bgfx::VertexBufferHandle cpp; } handle = { _handle };
	This->setBuffer(_stage, handle.cpp, (bgfx::Access::Enum)_access);
}

BGFX_C_API void bgfx_encoder_set_compute_dynamic_index_buffer(bgfx_encoder_t* _this, uint8_t _stage, bgfx_dynamic_index_buffer_handle_t _handle, bgfx_access_t _access)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	union { bgfx_dynamic_index_buffer_handle_t c; bgfx::DynamicIndexBufferHandle cpp; } handle = { _handle };
	This->setBuffer(_stage, handle.cpp, (bgfx::Access::Enum)_access);
}

BGFX_C_API void bgfx_encoder_set_compute_dynamic_vertex_buffer(bgfx_encoder_t* _this, uint8_t _stage, bgfx_dynamic_vertex_buffer_handle_t _handle, bgfx_access_t _access)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	union { bgfx_dynamic_vertex_buffer_handle_t c; bgfx::DynamicVertexBufferHandle cpp; } handle = { _handle };
	This->setBuffer(_stage, handle.cpp, (bgfx::Access::Enum)_access);
}

BGFX_C_API void bgfx_encoder_set_compute_indirect_buffer(bgfx_encoder_t* _this, uint8_t _stage, bgfx_indirect_buffer_handle_t _handle, bgfx_access_t _access)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	union { bgfx_indirect_buffer_handle_t c; bgfx::IndirectBufferHandle cpp; } handle = { _handle };
	This->setBuffer(_stage, handle.cpp, (bgfx::Access::Enum)_access);
}

BGFX_C_API void bgfx_encoder_set_image(bgfx_encoder_t* _this, uint8_t _stage, bgfx_texture_handle_t _handle, uint8_t _mip, bgfx_access_t _access, bgfx_texture_format_t _format)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	This->setImage(_stage, handle.cpp, _mip, (bgfx::Access::Enum)_access, (bgfx::TextureFormat::Enum)_format);
}

BGFX_C_API void bgfx_encoder_dispatch(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, uint32_t _numX, uint32_t _numY, uint32_t _numZ, uint8_t _flags)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } program = { _program };
	This->dispatch((bgfx::ViewId)_id, program.cpp, _numX, _numY, _numZ, _flags);
}

BGFX_C_API void bgfx_encoder_dispatch_indirect(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, uint8_t _flags)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } program = { _program };
	union { bgfx_indirect_buffer_handle_t c; bgfx::IndirectBufferHandle cpp; } indirectHandle = { _indirectHandle };
	This->dispatch((bgfx::ViewId)_id, program.cpp, indirectHandle.cpp, _start, _num, _flags);
}

BGFX_C_API void bgfx_encoder_discard(bgfx_encoder_t* _this, uint8_t _flags)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	This->discard(_flags);
}

BGFX_C_API void bgfx_encoder_blit(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_texture_handle_t _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, bgfx_texture_handle_t _src, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth)
{
	bgfx::Encoder* This = (bgfx::Encoder*)_this;
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } dst = { _dst };
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } src = { _src };
	This->blit((bgfx::ViewId)_id, dst.cpp, _dstMip, _dstX, _dstY, _dstZ, src.cpp, _srcMip, _srcX, _srcY, _srcZ, _width, _height, _depth);
}

BGFX_C_API void bgfx_request_screen_shot(bgfx_frame_buffer_handle_t _handle, const char* _filePath)
{
	union { bgfx_frame_buffer_handle_t c; bgfx::FrameBufferHandle cpp; } handle = { _handle };
	bgfx::requestScreenShot(handle.cpp, _filePath);
}

BGFX_C_API bgfx_render_frame_t bgfx_render_frame(int32_t _msecs)
{
	return (bgfx_render_frame_t)bgfx::renderFrame(_msecs);
}

BGFX_C_API void bgfx_set_platform_data(const bgfx_platform_data_t * _data)
{
	const bgfx::PlatformData & data = *(const bgfx::PlatformData *)_data;
	bgfx::setPlatformData(data);
}

BGFX_C_API const bgfx_internal_data_t* bgfx_get_internal_data(void)
{
	return (const bgfx_internal_data_t*)bgfx::getInternalData();
}

BGFX_C_API uintptr_t bgfx_override_internal_texture_ptr(bgfx_texture_handle_t _handle, uintptr_t _ptr)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	return bgfx::overrideInternal(handle.cpp, _ptr);
}

BGFX_C_API uintptr_t bgfx_override_internal_texture(bgfx_texture_handle_t _handle, uint16_t _width, uint16_t _height, uint8_t _numMips, bgfx_texture_format_t _format, uint64_t _flags)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	return bgfx::overrideInternal(handle.cpp, _width, _height, _numMips, (bgfx::TextureFormat::Enum)_format, _flags);
}

BGFX_C_API void bgfx_set_marker(const char* _marker)
{
	bgfx::setMarker(_marker);
}

BGFX_C_API void bgfx_set_state(uint64_t _state, uint32_t _rgba)
{
	bgfx::setState(_state, _rgba);
}

BGFX_C_API void bgfx_set_condition(bgfx_occlusion_query_handle_t _handle, bool _visible)
{
	union { bgfx_occlusion_query_handle_t c; bgfx::OcclusionQueryHandle cpp; } handle = { _handle };
	bgfx::setCondition(handle.cpp, _visible);
}

BGFX_C_API void bgfx_set_stencil(uint32_t _fstencil, uint32_t _bstencil)
{
	bgfx::setStencil(_fstencil, _bstencil);
}

BGFX_C_API uint16_t bgfx_set_scissor(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
{
	return bgfx::setScissor(_x, _y, _width, _height);
}

BGFX_C_API void bgfx_set_scissor_cached(uint16_t _cache)
{
	bgfx::setScissor(_cache);
}

BGFX_C_API uint32_t bgfx_set_transform(const void* _mtx, uint16_t _num)
{
	return bgfx::setTransform(_mtx, _num);
}

BGFX_C_API void bgfx_set_transform_cached(uint32_t _cache, uint16_t _num)
{
	bgfx::setTransform(_cache, _num);
}

BGFX_C_API uint32_t bgfx_alloc_transform(bgfx_transform_t* _transform, uint16_t _num)
{
	return bgfx::allocTransform((bgfx::Transform*)_transform, _num);
}

BGFX_C_API void bgfx_set_uniform(bgfx_uniform_handle_t _handle, const void* _value, uint16_t _num)
{
	union { bgfx_uniform_handle_t c; bgfx::UniformHandle cpp; } handle = { _handle };
	bgfx::setUniform(handle.cpp, _value, _num);
}

BGFX_C_API void bgfx_set_index_buffer(bgfx_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices)
{
	union { bgfx_index_buffer_handle_t c; bgfx::IndexBufferHandle cpp; } handle = { _handle };
	bgfx::setIndexBuffer(handle.cpp, _firstIndex, _numIndices);
}

BGFX_C_API void bgfx_set_dynamic_index_buffer(bgfx_dynamic_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices)
{
	union { bgfx_dynamic_index_buffer_handle_t c; bgfx::DynamicIndexBufferHandle cpp; } handle = { _handle };
	bgfx::setIndexBuffer(handle.cpp, _firstIndex, _numIndices);
}

BGFX_C_API void bgfx_set_transient_index_buffer(const bgfx_transient_index_buffer_t* _tib, uint32_t _firstIndex, uint32_t _numIndices)
{
	bgfx::setIndexBuffer((const bgfx::TransientIndexBuffer*)_tib, _firstIndex, _numIndices);
}

BGFX_C_API void bgfx_set_vertex_buffer(uint8_t _stream, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices)
{
	union { bgfx_vertex_buffer_handle_t c; bgfx::VertexBufferHandle cpp; } handle = { _handle };
	bgfx::setVertexBuffer(_stream, handle.cpp, _startVertex, _numVertices);
}

BGFX_C_API void bgfx_set_vertex_buffer_with_layout(uint8_t _stream, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices, bgfx_vertex_layout_handle_t _layoutHandle)
{
	union { bgfx_vertex_buffer_handle_t c; bgfx::VertexBufferHandle cpp; } handle = { _handle };
	union { bgfx_vertex_layout_handle_t c; bgfx::VertexLayoutHandle cpp; } layoutHandle = { _layoutHandle };
	bgfx::setVertexBuffer(_stream, handle.cpp, _startVertex, _numVertices, layoutHandle.cpp);
}

BGFX_C_API void bgfx_set_dynamic_vertex_buffer(uint8_t _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices)
{
	union { bgfx_dynamic_vertex_buffer_handle_t c; bgfx::DynamicVertexBufferHandle cpp; } handle = { _handle };
	bgfx::setVertexBuffer(_stream, handle.cpp, _startVertex, _numVertices);
}

BGFX_C_API void bgfx_set_dynamic_vertex_buffer_with_layout(uint8_t _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices, bgfx_vertex_layout_handle_t _layoutHandle)
{
	union { bgfx_dynamic_vertex_buffer_handle_t c; bgfx::DynamicVertexBufferHandle cpp; } handle = { _handle };
	union { bgfx_vertex_layout_handle_t c; bgfx::VertexLayoutHandle cpp; } layoutHandle = { _layoutHandle };
	bgfx::setVertexBuffer(_stream, handle.cpp, _startVertex, _numVertices, layoutHandle.cpp);
}

BGFX_C_API void bgfx_set_transient_vertex_buffer(uint8_t _stream, const bgfx_transient_vertex_buffer_t* _tvb, uint32_t _startVertex, uint32_t _numVertices)
{
	bgfx::setVertexBuffer(_stream, (const bgfx::TransientVertexBuffer*)_tvb, _startVertex, _numVertices);
}

BGFX_C_API void bgfx_set_transient_vertex_buffer_with_layout(uint8_t _stream, const bgfx_transient_vertex_buffer_t* _tvb, uint32_t _startVertex, uint32_t _numVertices, bgfx_vertex_layout_handle_t _layoutHandle)
{
	union { bgfx_vertex_layout_handle_t c; bgfx::VertexLayoutHandle cpp; } layoutHandle = { _layoutHandle };
	bgfx::setVertexBuffer(_stream, (const bgfx::TransientVertexBuffer*)_tvb, _startVertex, _numVertices, layoutHandle.cpp);
}

BGFX_C_API void bgfx_set_vertex_count(uint32_t _numVertices)
{
	bgfx::setVertexCount(_numVertices);
}

BGFX_C_API void bgfx_set_instance_data_buffer(const bgfx_instance_data_buffer_t* _idb, uint32_t _start, uint32_t _num)
{
	bgfx::setInstanceDataBuffer((const bgfx::InstanceDataBuffer*)_idb, _start, _num);
}

BGFX_C_API void bgfx_set_instance_data_from_vertex_buffer(bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num)
{
	union { bgfx_vertex_buffer_handle_t c; bgfx::VertexBufferHandle cpp; } handle = { _handle };
	bgfx::setInstanceDataBuffer(handle.cpp, _startVertex, _num);
}

BGFX_C_API void bgfx_set_instance_data_from_dynamic_vertex_buffer(bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num)
{
	union { bgfx_dynamic_vertex_buffer_handle_t c; bgfx::DynamicVertexBufferHandle cpp; } handle = { _handle };
	bgfx::setInstanceDataBuffer(handle.cpp, _startVertex, _num);
}

BGFX_C_API void bgfx_set_instance_count(uint32_t _numInstances)
{
	bgfx::setInstanceCount(_numInstances);
}

BGFX_C_API void bgfx_set_texture(uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint32_t _flags)
{
	union { bgfx_uniform_handle_t c; bgfx::UniformHandle cpp; } sampler = { _sampler };
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	bgfx::setTexture(_stage, sampler.cpp, handle.cpp, _flags);
}

BGFX_C_API void bgfx_touch(bgfx_view_id_t _id)
{
	bgfx::touch((bgfx::ViewId)_id);
}

BGFX_C_API void bgfx_submit(bgfx_view_id_t _id, bgfx_program_handle_t _program, uint32_t _depth, uint8_t _flags)
{
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } program = { _program };
	bgfx::submit((bgfx::ViewId)_id, program.cpp, _depth, _flags);
}

BGFX_C_API void bgfx_submit_occlusion_query(bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_occlusion_query_handle_t _occlusionQuery, uint32_t _depth, uint8_t _flags)
{
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } program = { _program };
	union { bgfx_occlusion_query_handle_t c; bgfx::OcclusionQueryHandle cpp; } occlusionQuery = { _occlusionQuery };
	bgfx::submit((bgfx::ViewId)_id, program.cpp, occlusionQuery.cpp, _depth, _flags);
}

BGFX_C_API void bgfx_submit_indirect(bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, uint32_t _depth, uint8_t _flags)
{
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } program = { _program };
	union { bgfx_indirect_buffer_handle_t c; bgfx::IndirectBufferHandle cpp; } indirectHandle = { _indirectHandle };
	bgfx::submit((bgfx::ViewId)_id, program.cpp, indirectHandle.cpp, _start, _num, _depth, _flags);
}

BGFX_C_API void bgfx_set_compute_index_buffer(uint8_t _stage, bgfx_index_buffer_handle_t _handle, bgfx_access_t _access)
{
	union { bgfx_index_buffer_handle_t c; bgfx::IndexBufferHandle cpp; } handle = { _handle };
	bgfx::setBuffer(_stage, handle.cpp, (bgfx::Access::Enum)_access);
}

BGFX_C_API void bgfx_set_compute_vertex_buffer(uint8_t _stage, bgfx_vertex_buffer_handle_t _handle, bgfx_access_t _access)
{
	union { bgfx_vertex_buffer_handle_t c; bgfx::VertexBufferHandle cpp; } handle = { _handle };
	bgfx::setBuffer(_stage, handle.cpp, (bgfx::Access::Enum)_access);
}

BGFX_C_API void bgfx_set_compute_dynamic_index_buffer(uint8_t _stage, bgfx_dynamic_index_buffer_handle_t _handle, bgfx_access_t _access)
{
	union { bgfx_dynamic_index_buffer_handle_t c; bgfx::DynamicIndexBufferHandle cpp; } handle = { _handle };
	bgfx::setBuffer(_stage, handle.cpp, (bgfx::Access::Enum)_access);
}

BGFX_C_API void bgfx_set_compute_dynamic_vertex_buffer(uint8_t _stage, bgfx_dynamic_vertex_buffer_handle_t _handle, bgfx_access_t _access)
{
	union { bgfx_dynamic_vertex_buffer_handle_t c; bgfx::DynamicVertexBufferHandle cpp; } handle = { _handle };
	bgfx::setBuffer(_stage, handle.cpp, (bgfx::Access::Enum)_access);
}

BGFX_C_API void bgfx_set_compute_indirect_buffer(uint8_t _stage, bgfx_indirect_buffer_handle_t _handle, bgfx_access_t _access)
{
	union { bgfx_indirect_buffer_handle_t c; bgfx::IndirectBufferHandle cpp; } handle = { _handle };
	bgfx::setBuffer(_stage, handle.cpp, (bgfx::Access::Enum)_access);
}

BGFX_C_API void bgfx_set_image(uint8_t _stage, bgfx_texture_handle_t _handle, uint8_t _mip, bgfx_access_t _access, bgfx_texture_format_t _format)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	bgfx::setImage(_stage, handle.cpp, _mip, (bgfx::Access::Enum)_access, (bgfx::TextureFormat::Enum)_format);
}

BGFX_C_API void bgfx_dispatch(bgfx_view_id_t _id, bgfx_program_handle_t _program, uint32_t _numX, uint32_t _numY, uint32_t _numZ, uint8_t _flags)
{
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } program = { _program };
	bgfx::dispatch((bgfx::ViewId)_id, program.cpp, _numX, _numY, _numZ, _flags);
}

BGFX_C_API void bgfx_dispatch_indirect(bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, uint8_t _flags)
{
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } program = { _program };
	union { bgfx_indirect_buffer_handle_t c; bgfx::IndirectBufferHandle cpp; } indirectHandle = { _indirectHandle };
	bgfx::dispatch((bgfx::ViewId)_id, program.cpp, indirectHandle.cpp, _start, _num, _flags);
}

BGFX_C_API void bgfx_discard(uint8_t _flags)
{
	bgfx::discard(_flags);
}

BGFX_C_API void bgfx_blit(bgfx_view_id_t _id, bgfx_texture_handle_t _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, bgfx_texture_handle_t _src, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } dst = { _dst };
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } src = { _src };
	bgfx::blit((bgfx::ViewId)_id, dst.cpp, _dstMip, _dstX, _dstY, _dstZ, src.cpp, _srcMip, _srcX, _srcY, _srcZ, _width, _height, _depth);
}


/* user define functions */
BGFX_C_API void bgfx_init_ctor(bgfx_init_t* _init)
{
	BX_PLACEMENT_NEW(_init, bgfx::Init);

}

BGFX_C_API bool bgfx_init(const bgfx_init_t * _init)
{
	bgfx_init_t init =*_init;

	if (init.callback != NULL)
	{
		static bgfx::CallbackC99 s_callback;
		s_callback.m_interface = init.callback;
		init.callback = reinterpret_cast<bgfx_callback_interface_t*>(&s_callback);
	}

	if (init.allocator != NULL)
	{
		static bgfx::AllocatorC99 s_allocator;
		s_allocator.m_interface = init.allocator;
		init.allocator = reinterpret_cast<bgfx_allocator_interface_t*>(&s_allocator);
	}

	union { const bgfx_init_t* c; const bgfx::Init* cpp; } in;
	in.c = &init;

	return bgfx::init(*in.cpp);

}

/**/
BGFX_C_API bgfx_interface_vtbl_t* bgfx_get_interface(uint32_t _version)
{
	if (_version == BGFX_API_VERSION)
	{
		static bgfx_interface_vtbl_t s_bgfx_interface =
		{
			bgfx_attachment_init,
			bgfx_vertex_layout_begin,
			bgfx_vertex_layout_add,
			bgfx_vertex_layout_decode,
			bgfx_vertex_layout_has,
			bgfx_vertex_layout_skip,
			bgfx_vertex_layout_end,
			bgfx_vertex_pack,
			bgfx_vertex_unpack,
			bgfx_vertex_convert,
			bgfx_weld_vertices,
			bgfx_topology_convert,
			bgfx_topology_sort_tri_list,
			bgfx_get_supported_renderers,
			bgfx_get_renderer_name,
			bgfx_init_ctor,
			bgfx_init,
			bgfx_shutdown,
			bgfx_reset,
			bgfx_frame,
			bgfx_get_renderer_type,
			bgfx_get_caps,
			bgfx_get_stats,
			bgfx_alloc,
			bgfx_copy,
			bgfx_make_ref,
			bgfx_make_ref_release,
			bgfx_set_debug,
			bgfx_dbg_text_clear,
			bgfx_dbg_text_printf,
			bgfx_dbg_text_vprintf,
			bgfx_dbg_text_image,
			bgfx_create_index_buffer,
			bgfx_set_index_buffer_name,
			bgfx_destroy_index_buffer,
			bgfx_create_vertex_layout,
			bgfx_destroy_vertex_layout,
			bgfx_create_vertex_buffer,
			bgfx_set_vertex_buffer_name,
			bgfx_destroy_vertex_buffer,
			bgfx_create_dynamic_index_buffer,
			bgfx_create_dynamic_index_buffer_mem,
			bgfx_update_dynamic_index_buffer,
			bgfx_destroy_dynamic_index_buffer,
			bgfx_create_dynamic_vertex_buffer,
			bgfx_create_dynamic_vertex_buffer_mem,
			bgfx_update_dynamic_vertex_buffer,
			bgfx_destroy_dynamic_vertex_buffer,
			bgfx_get_avail_transient_index_buffer,
			bgfx_get_avail_transient_vertex_buffer,
			bgfx_get_avail_instance_data_buffer,
			bgfx_alloc_transient_index_buffer,
			bgfx_alloc_transient_vertex_buffer,
			bgfx_alloc_transient_buffers,
			bgfx_alloc_instance_data_buffer,
			bgfx_create_indirect_buffer,
			bgfx_destroy_indirect_buffer,
			bgfx_create_shader,
			bgfx_get_shader_uniforms,
			bgfx_set_shader_name,
			bgfx_destroy_shader,
			bgfx_create_program,
			bgfx_create_compute_program,
			bgfx_destroy_program,
			bgfx_is_texture_valid,
			bgfx_is_frame_buffer_valid,
			bgfx_calc_texture_size,
			bgfx_create_texture,
			bgfx_create_texture_2d,
			bgfx_create_texture_2d_scaled,
			bgfx_create_texture_3d,
			bgfx_create_texture_cube,
			bgfx_update_texture_2d,
			bgfx_update_texture_3d,
			bgfx_update_texture_cube,
			bgfx_read_texture,
			bgfx_set_texture_name,
			bgfx_get_direct_access_ptr,
			bgfx_destroy_texture,
			bgfx_create_frame_buffer,
			bgfx_create_frame_buffer_scaled,
			bgfx_create_frame_buffer_from_handles,
			bgfx_create_frame_buffer_from_attachment,
			bgfx_create_frame_buffer_from_nwh,
			bgfx_set_frame_buffer_name,
			bgfx_get_texture,
			bgfx_destroy_frame_buffer,
			bgfx_create_uniform,
			bgfx_get_uniform_info,
			bgfx_destroy_uniform,
			bgfx_create_occlusion_query,
			bgfx_get_result,
			bgfx_destroy_occlusion_query,
			bgfx_set_palette_color,
			bgfx_set_palette_color_rgba8,
			bgfx_set_view_name,
			bgfx_set_view_rect,
			bgfx_set_view_rect_ratio,
			bgfx_set_view_scissor,
			bgfx_set_view_clear,
			bgfx_set_view_clear_mrt,
			bgfx_set_view_mode,
			bgfx_set_view_frame_buffer,
			bgfx_set_view_transform,
			bgfx_set_view_order,
			bgfx_reset_view,
			bgfx_encoder_begin,
			bgfx_encoder_end,
			bgfx_encoder_set_marker,
			bgfx_encoder_set_state,
			bgfx_encoder_set_condition,
			bgfx_encoder_set_stencil,
			bgfx_encoder_set_scissor,
			bgfx_encoder_set_scissor_cached,
			bgfx_encoder_set_transform,
			bgfx_encoder_set_transform_cached,
			bgfx_encoder_alloc_transform,
			bgfx_encoder_set_uniform,
			bgfx_encoder_set_index_buffer,
			bgfx_encoder_set_dynamic_index_buffer,
			bgfx_encoder_set_transient_index_buffer,
			bgfx_encoder_set_vertex_buffer,
			bgfx_encoder_set_vertex_buffer_with_layout,
			bgfx_encoder_set_dynamic_vertex_buffer,
			bgfx_encoder_set_dynamic_vertex_buffer_with_layout,
			bgfx_encoder_set_transient_vertex_buffer,
			bgfx_encoder_set_transient_vertex_buffer_with_layout,
			bgfx_encoder_set_vertex_count,
			bgfx_encoder_set_instance_data_buffer,
			bgfx_encoder_set_instance_data_from_vertex_buffer,
			bgfx_encoder_set_instance_data_from_dynamic_vertex_buffer,
			bgfx_encoder_set_instance_count,
			bgfx_encoder_set_texture,
			bgfx_encoder_touch,
			bgfx_encoder_submit,
			bgfx_encoder_submit_occlusion_query,
			bgfx_encoder_submit_indirect,
			bgfx_encoder_set_compute_index_buffer,
			bgfx_encoder_set_compute_vertex_buffer,
			bgfx_encoder_set_compute_dynamic_index_buffer,
			bgfx_encoder_set_compute_dynamic_vertex_buffer,
			bgfx_encoder_set_compute_indirect_buffer,
			bgfx_encoder_set_image,
			bgfx_encoder_dispatch,
			bgfx_encoder_dispatch_indirect,
			bgfx_encoder_discard,
			bgfx_encoder_blit,
			bgfx_request_screen_shot,
			bgfx_render_frame,
			bgfx_set_platform_data,
			bgfx_get_internal_data,
			bgfx_override_internal_texture_ptr,
			bgfx_override_internal_texture,
			bgfx_set_marker,
			bgfx_set_state,
			bgfx_set_condition,
			bgfx_set_stencil,
			bgfx_set_scissor,
			bgfx_set_scissor_cached,
			bgfx_set_transform,
			bgfx_set_transform_cached,
			bgfx_alloc_transform,
			bgfx_set_uniform,
			bgfx_set_index_buffer,
			bgfx_set_dynamic_index_buffer,
			bgfx_set_transient_index_buffer,
			bgfx_set_vertex_buffer,
			bgfx_set_vertex_buffer_with_layout,
			bgfx_set_dynamic_vertex_buffer,
			bgfx_set_dynamic_vertex_buffer_with_layout,
			bgfx_set_transient_vertex_buffer,
			bgfx_set_transient_vertex_buffer_with_layout,
			bgfx_set_vertex_count,
			bgfx_set_instance_data_buffer,
			bgfx_set_instance_data_from_vertex_buffer,
			bgfx_set_instance_data_from_dynamic_vertex_buffer,
			bgfx_set_instance_count,
			bgfx_set_texture,
			bgfx_touch,
			bgfx_submit,
			bgfx_submit_occlusion_query,
			bgfx_submit_indirect,
			bgfx_set_compute_index_buffer,
			bgfx_set_compute_vertex_buffer,
			bgfx_set_compute_dynamic_index_buffer,
			bgfx_set_compute_dynamic_vertex_buffer,
			bgfx_set_compute_indirect_buffer,
			bgfx_set_image,
			bgfx_dispatch,
			bgfx_dispatch_indirect,
			bgfx_discard,
			bgfx_blit
		};

		return &s_bgfx_interface;
	}

	return NULL;
}
