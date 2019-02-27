/*
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

/*
 *
 * AUTO GENERATED! DO NOT EDIT!
 *
 */

/**/
BGFX_C_API void bgfx_vertex_decl_begin(bgfx_vertex_decl_t* _this, bgfx_renderer_type_t _renderer);

/**/
BGFX_C_API void bgfx_vertex_decl_add(bgfx_vertex_decl_t* _this, bgfx_attrib_t _attrib, uint8_t _num, bgfx_attrib_type_t _type, bool _normalized, bool _asInt);

/**/
BGFX_C_API void bgfx_vertex_decl_decode(const bgfx_vertex_decl_t* _this, bgfx_attrib_t _attrib, uint8_t * _num, bgfx_attrib_type_t * _type, bool * _normalized, bool * _asInt);

/**/
BGFX_C_API bool bgfx_vertex_decl_has(const bgfx_vertex_decl_t* _this, bgfx_attrib_t _attrib);

/**/
BGFX_C_API void bgfx_vertex_decl_skip(bgfx_vertex_decl_t* _this, uint8_t _num);

/**/
BGFX_C_API void bgfx_vertex_decl_end(bgfx_vertex_decl_t* _this);

/**/
BGFX_C_API void bgfx_vertex_pack(const float * _input, bool _inputNormalized, bgfx_attrib_t _attr, const bgfx_vertex_decl_t * _decl, void * _data, uint32_t _index);

/**/
BGFX_C_API void bgfx_vertex_unpack(float * _output, bgfx_attrib_t _attr, const bgfx_vertex_decl_t * _decl, const void * _data, uint32_t _index);

/**/
BGFX_C_API void bgfx_vertex_convert(const bgfx_vertex_decl_t * _dstDecl, void * _dstData, const bgfx_vertex_decl_t * _srcDecl, const void * _srcData, uint32_t _num);

/**/
BGFX_C_API uint16_t bgfx_weld_vertices(uint16_t * _output, const bgfx_vertex_decl_t * _decl, const void * _data, uint16_t _num, float _epsilon);

/**/
BGFX_C_API uint32_t bgfx_topology_convert(bgfx_topology_convert_t _conversion, void * _dst, uint32_t _dstSize, const void * _indices, uint32_t _numIndices, bool _index32);

/**/
BGFX_C_API void bgfx_topology_sort_tri_list(bgfx_topology_sort_t _sort, void * _dst, uint32_t _dstSize, const float * _dir, const float * _pos, const void * _vertices, uint32_t _stride, const void * _indices, uint32_t _numIndices, bool _index32);

/**/
BGFX_C_API uint8_t bgfx_get_supported_renderers(uint8_t _max, bgfx_renderer_type_t * _enum);

/**/
BGFX_C_API const char * bgfx_get_renderer_name(bgfx_renderer_type_t _type);

/**/
BGFX_C_API void bgfx_init_ctor(bgfx_init_t * _init);

/**/
BGFX_C_API bool bgfx_init(const bgfx_init_t * _init);

/**/
BGFX_C_API void bgfx_shutdown();

/**/
BGFX_C_API void bgfx_reset(uint32_t _width, uint32_t _height, uint32_t _flags, bgfx_texture_format_t _format);

/**/
BGFX_C_API uint32_t bgfx_frame(bool _capture);

/**/
BGFX_C_API bgfx_renderer_type_t bgfx_get_renderer_type();

/**/
BGFX_C_API const bgfx_caps_t * bgfx_get_caps();

/**/
BGFX_C_API const bgfx_stats_t * bgfx_get_stats();

/**/
BGFX_C_API const bgfx_memory_t * bgfx_alloc(uint32_t _size);

/**/
BGFX_C_API const bgfx_memory_t * bgfx_copy(const void * _data, uint32_t _size);

/**/
BGFX_C_API const bgfx_memory_t * bgfx_make_ref(const void * _data, uint32_t _size);

/**/
BGFX_C_API const bgfx_memory_t * bgfx_make_ref_release(const void * _data, uint32_t _size, bgfx_release_fn_t _releaseFn, void * _userData);

/**/
BGFX_C_API void bgfx_set_debug(uint32_t _debug);

/**/
BGFX_C_API void bgfx_dbg_text_clear(uint8_t _attr, bool _small);

/**/
BGFX_C_API void bgfx_dbg_text_printf(uint16_t _x, uint16_t _y, uint8_t _attr, const char * _format, ... );

/**/
BGFX_C_API void bgfx_dbg_text_vprintf(uint16_t _x, uint16_t _y, uint8_t _attr, const char * _format, va_list _argList);

/**/
BGFX_C_API void bgfx_dbg_text_image(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const void * _data, uint16_t _pitch);

/**/
BGFX_C_API bgfx_index_buffer_handle_t bgfx_create_index_buffer(const bgfx_memory_t * _mem, uint16_t _flags);

/**/
BGFX_C_API void bgfx_set_index_buffer_name(bgfx_index_buffer_handle_t _handle, const char * _name, int32_t _len);

/**/
BGFX_C_API void bgfx_destroy_index_buffer(bgfx_index_buffer_handle_t _handle);

/**/
BGFX_C_API bgfx_vertex_buffer_handle_t bgfx_create_vertex_buffer(const bgfx_memory_t * _mem, const bgfx_vertex_decl_t * _decl, uint16_t _flags);

/**/
BGFX_C_API void bgfx_set_vertex_buffer_name(bgfx_vertex_buffer_handle_t _handle, const char * _name, int32_t _len);

/**/
BGFX_C_API void bgfx_destroy_vertex_buffer(bgfx_vertex_buffer_handle_t _handle);

/**/
BGFX_C_API bgfx_dynamic_index_buffer_handle_t bgfx_create_dynamic_index_buffer(uint32_t _num, uint16_t _flags);

/**/
BGFX_C_API bgfx_dynamic_index_buffer_handle_t bgfx_create_dynamic_index_buffer_mem(const bgfx_memory_t * _mem, uint16_t _flags);

/**/
BGFX_C_API void bgfx_update_dynamic_index_buffer(bgfx_dynamic_index_buffer_handle_t _handle, uint32_t _startIndex, const bgfx_memory_t * _mem);

/**/
BGFX_C_API void bgfx_destroy_dynamic_index_buffer(bgfx_dynamic_index_buffer_handle_t _handle);

/**/
BGFX_C_API bgfx_dynamic_vertex_buffer_handle_t bgfx_create_dynamic_vertex_buffer(uint32_t _num, const bgfx_vertex_decl_t * _decl, uint16_t _flags);

/**/
BGFX_C_API bgfx_dynamic_vertex_buffer_handle_t bgfx_create_dynamic_vertex_buffer_mem(const bgfx_memory_t * _mem, const bgfx_vertex_decl_t * _decl, uint16_t _flags);

/**/
BGFX_C_API void bgfx_update_dynamic_vertex_buffer(bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, const bgfx_memory_t * _mem);

/**/
BGFX_C_API void bgfx_destroy_dynamic_vertex_buffer(bgfx_dynamic_vertex_buffer_handle_t _handle);

/**/
BGFX_C_API uint32_t bgfx_get_avail_transient_index_buffer(uint32_t _num);

/**/
BGFX_C_API uint32_t bgfx_get_avail_transient_vertex_buffer(uint32_t _num, const bgfx_vertex_decl_t * _decl);

/**/
BGFX_C_API uint32_t bgfx_get_avail_instance_data_buffer(uint32_t _num, uint16_t _stride);

/**/
BGFX_C_API void bgfx_alloc_transient_index_buffer(bgfx_transient_index_buffer_t * _tib, uint32_t _num);

/**/
BGFX_C_API void bgfx_alloc_transient_vertex_buffer(bgfx_transient_vertex_buffer_t * _tvb, uint32_t _num, const bgfx_vertex_decl_t * _decl);

/**/
BGFX_C_API bool bgfx_alloc_transient_buffers(bgfx_transient_vertex_buffer_t * _tvb, const bgfx_vertex_decl_t * _decl, uint32_t _numVertices, bgfx_transient_index_buffer_t * _tib, uint32_t _numIndices);

/**/
BGFX_C_API void bgfx_alloc_instance_data_buffer(bgfx_instance_data_buffer_t * _idb, uint32_t _num, uint16_t _stride);

/**/
BGFX_C_API bgfx_indirect_buffer_handle_t bgfx_create_indirect_buffer(uint32_t _num);

/**/
BGFX_C_API void bgfx_destroy_indirect_buffer(bgfx_indirect_buffer_handle_t _handle);

/**/
BGFX_C_API bgfx_shader_handle_t bgfx_create_shader(const bgfx_memory_t * _mem);

/**/
BGFX_C_API uint16_t bgfx_get_shader_uniforms(bgfx_shader_handle_t _handle, bgfx_uniform_handle_t * _uniforms, uint16_t _max);

/**/
BGFX_C_API void bgfx_set_shader_name(bgfx_shader_handle_t _handle, const char * _name, int32_t _len);

/**/
BGFX_C_API void bgfx_destroy_shader(bgfx_shader_handle_t _handle);

/**/
BGFX_C_API bgfx_program_handle_t bgfx_create_program(bgfx_shader_handle_t _vsh, bgfx_shader_handle_t _fsh, bool _destroyShaders);

/**/
BGFX_C_API bgfx_program_handle_t bgfx_create_compute_program(bgfx_shader_handle_t _csh, bool _destroyShaders);

/**/
BGFX_C_API void bgfx_destroy_program(bgfx_program_handle_t _handle);

/**/
BGFX_C_API bool bgfx_is_texture_valid(uint16_t _depth, bool _cubeMap, uint16_t _numLayers, bgfx_texture_format_t _format, uint64_t _flags);

/**/
BGFX_C_API void bgfx_calc_texture_size(bgfx_texture_info_t * _info, uint16_t _width, uint16_t _height, uint16_t _depth, bool _cubeMap, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format);

/**/
BGFX_C_API bgfx_texture_handle_t bgfx_create_texture(const bgfx_memory_t * _mem, uint64_t _flags, uint8_t _skip, bgfx_texture_info_t * _info);

/**/
BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_2d(uint16_t _width, uint16_t _height, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format, uint64_t _flags, const bgfx_memory_t * _mem);

/**/
BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_2d_scaled(bgfx_backbuffer_ratio_t _ratio, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format, uint64_t _flags);

/**/
BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_3d(uint16_t _width, uint16_t _height, uint16_t _depth, bool _hasMips, bgfx_texture_format_t _format, uint64_t _flags, const bgfx_memory_t * _mem);

/**/
BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_cube(uint16_t _size, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format, uint64_t _flags, const bgfx_memory_t * _mem);

/**/
BGFX_C_API void bgfx_update_texture_2d(bgfx_texture_handle_t _handle, uint16_t _layer, uint16_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const bgfx_memory_t * _mem, uint16_t _pitch);

/**/
BGFX_C_API void bgfx_update_texture_3d(bgfx_texture_handle_t _handle, uint16_t _mip, uint16_t _x, uint16_t _y, uint16_t _z, uint16_t _width, uint16_t _height, uint16_t _depth, const bgfx_memory_t * _mem);

/**/
BGFX_C_API void bgfx_update_texture_cube(bgfx_texture_handle_t _handle, uint16_t _layer, uint8_t _side, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const bgfx_memory_t * _mem, uint16_t _pitch);

/**/
BGFX_C_API uint32_t bgfx_read_texture(bgfx_texture_handle_t _handle, void * _data, uint8_t _mip);

/**/
BGFX_C_API void bgfx_set_texture_name(bgfx_texture_handle_t _handle, const char * _name, int32_t _len);

/**/
BGFX_C_API void * bgfx_get_direct_access_ptr(bgfx_texture_handle_t _handle);

/**/
BGFX_C_API void bgfx_destroy_texture(bgfx_texture_handle_t _handle);

/**/
BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer(uint16_t _width, uint16_t _height, bgfx_texture_format_t _format, uint64_t _textureFlags);

/**/
BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_scaled(bgfx_backbuffer_ratio_t _ratio, bgfx_texture_format_t _format, uint64_t _textureFlags);

/**/
BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_from_handles(uint8_t _num, const bgfx_texture_handle_t * _handles, bool _destroyTexture);

/**/
BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_from_attachment(uint8_t _num, const bgfx_attachment_t * _handles, bool _destroyTexture);

/**/
BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_from_nwh(void * _nwh, uint16_t _width, uint16_t _height, bgfx_texture_format_t _format, bgfx_texture_format_t _depthFormat);

/**/
BGFX_C_API void bgfx_set_frame_buffer_name(bgfx_frame_buffer_handle_t _handle, const char * _name, int32_t _len);

/**/
BGFX_C_API bgfx_texture_handle_t bgfx_get_texture(bgfx_frame_buffer_handle_t _handle, uint8_t _attachment);

/**/
BGFX_C_API void bgfx_destroy_frame_buffer(bgfx_frame_buffer_handle_t _handle);

/**/
BGFX_C_API bgfx_uniform_handle_t bgfx_create_uniform(const char * _name, bgfx_uniform_type_t _type, uint16_t _num);

/**/
BGFX_C_API void bgfx_get_uniform_info(bgfx_uniform_handle_t _handle, bgfx_uniform_info_t * _info);

/**/
BGFX_C_API void bgfx_destroy_uniform(bgfx_uniform_handle_t _handle);

/**/
BGFX_C_API bgfx_occlusion_query_handle_t bgfx_create_occlusion_query();

/**/
BGFX_C_API bgfx_occlusion_query_result_t bgfx_get_result(bgfx_occlusion_query_handle_t _handle, int32_t * _result);

/**/
BGFX_C_API void bgfx_destroy_occlusion_query(bgfx_occlusion_query_handle_t _handle);

/**/
BGFX_C_API void bgfx_set_palette_color(uint8_t _index, const float * _rgba);

/**/
BGFX_C_API void bgfx_set_view_name(bgfx_view_id_t _id, const char * _name);

/**/
BGFX_C_API void bgfx_set_view_rect(bgfx_view_id_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

/**/
BGFX_C_API void bgfx_set_view_rect_ratio(bgfx_view_id_t _id, uint16_t _x, uint16_t _y, bgfx_backbuffer_ratio_t _ratio);

/**/
BGFX_C_API void bgfx_set_view_scissor(bgfx_view_id_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

/**/
BGFX_C_API void bgfx_set_view_clear(bgfx_view_id_t _id, uint16_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil);

/**/
BGFX_C_API void bgfx_set_view_clear_mrt(bgfx_view_id_t _id, uint16_t _flags, float _depth, uint8_t _stencil, uint8_t _c0, uint8_t _c1, uint8_t _c2, uint8_t _c3, uint8_t _c4, uint8_t _c5, uint8_t _c6, uint8_t _c7);

/**/
BGFX_C_API void bgfx_set_view_mode(bgfx_view_id_t _id, bgfx_view_mode_t _mode);

/**/
BGFX_C_API void bgfx_set_view_frame_buffer(bgfx_view_id_t _id, bgfx_frame_buffer_handle_t _handle);

/**/
BGFX_C_API void bgfx_set_view_transform(bgfx_view_id_t _id, const void * _view, const void * _proj);

/**/
BGFX_C_API void bgfx_set_view_order(bgfx_view_id_t _id, uint16_t _num, const bgfx_view_id_t * _order);

/**/
BGFX_C_API bgfx_encoder_t * bgfx_encoder_begin(bool _forThread);

/**/
BGFX_C_API void bgfx_encoder_end(bgfx_encoder_t * _encoder);

/**/
BGFX_C_API void bgfx_encoder_set_marker(bgfx_encoder_t* _this, const char * _marker);

/**/
BGFX_C_API void bgfx_encoder_set_state(bgfx_encoder_t* _this, uint64_t _state, uint32_t _rgba);

/**/
BGFX_C_API void bgfx_encoder_set_condition(bgfx_encoder_t* _this, bgfx_occlusion_query_handle_t _handle, bool _visible);

/**/
BGFX_C_API void bgfx_encoder_set_stencil(bgfx_encoder_t* _this, uint32_t _fstencil, uint32_t _bstencil);

/**/
BGFX_C_API uint16_t bgfx_encoder_set_scissor(bgfx_encoder_t* _this, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

/**/
BGFX_C_API void bgfx_encoder_set_scissor_cached(bgfx_encoder_t* _this, uint16_t _cache);

/**/
BGFX_C_API uint32_t bgfx_encoder_set_transform(bgfx_encoder_t* _this, const void * _mtx, uint16_t _num);

/**/
BGFX_C_API void bgfx_encoder_set_transform_cached(bgfx_encoder_t* _this, uint32_t _cache, uint16_t _num);

/**/
BGFX_C_API uint32_t bgfx_encoder_alloc_transform(bgfx_encoder_t* _this, bgfx_transform_t * _transform, uint16_t _num);

/**/
BGFX_C_API void bgfx_encoder_set_uniform(bgfx_encoder_t* _this, bgfx_uniform_handle_t _handle, const void * _value, uint16_t _num);

/**/
BGFX_C_API void bgfx_encoder_set_index_buffer(bgfx_encoder_t* _this, bgfx_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices);

/**/
BGFX_C_API void bgfx_encoder_set_dynamic_index_buffer(bgfx_encoder_t* _this, bgfx_dynamic_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices);

/**/
BGFX_C_API void bgfx_encoder_set_transient_index_buffer(bgfx_encoder_t* _this, const bgfx_transient_index_buffer_t * _tib, uint32_t _firstIndex, uint32_t _numIndices);

/**/
BGFX_C_API void bgfx_encoder_set_vertex_buffer(bgfx_encoder_t* _this, uint8_t _stream, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices);

/**/
BGFX_C_API void bgfx_encoder_set_dynamic_vertex_buffer(bgfx_encoder_t* _this, uint8_t _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices);

/**/
BGFX_C_API void bgfx_encoder_set_transient_vertex_buffer(bgfx_encoder_t* _this, uint8_t _stream, const bgfx_transient_vertex_buffer_t * _tvb, uint32_t _startVertex, uint32_t _numVertices);

/**/
BGFX_C_API void bgfx_encoder_set_vertex_count(bgfx_encoder_t* _this, uint32_t _numVertices);

/**/
BGFX_C_API void bgfx_encoder_set_instance_data_buffer(bgfx_encoder_t* _this, const bgfx_instance_data_buffer_t * _idb, uint32_t _start, uint32_t _num);

/**/
BGFX_C_API void bgfx_encoder_set_instance_data_from_vertex_buffer(bgfx_encoder_t* _this, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num);

/**/
BGFX_C_API void bgfx_encoder_set_instance_data_from_dynamic_vertex_buffer(bgfx_encoder_t* _this, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num);

/**/
BGFX_C_API void bgfx_encoder_set_instance_count(bgfx_encoder_t* _this, uint32_t _numInstances);

/**/
BGFX_C_API void bgfx_encoder_set_texture(bgfx_encoder_t* _this, uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint32_t _flags);

/**/
BGFX_C_API void bgfx_encoder_touch(bgfx_encoder_t* _this, bgfx_view_id_t _id);

/**/
BGFX_C_API void bgfx_encoder_submit(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, uint32_t _depth, bool _preserveState);

/**/
BGFX_C_API void bgfx_encoder_submit_occlusion_query(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_occlusion_query_handle_t _occlusionQuery, uint32_t _depth, bool _preserveState);

/**/
BGFX_C_API void bgfx_encoder_submit_indirect(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, uint32_t _depth, bool _preserveState);

/**/
BGFX_C_API void bgfx_encoder_set_compute_index_buffer(bgfx_encoder_t* _this, uint8_t _stage, bgfx_index_buffer_handle_t _handle, bgfx_access_t _access);

/**/
BGFX_C_API void bgfx_encoder_set_compute_vertex_buffer(bgfx_encoder_t* _this, uint8_t _stage, bgfx_vertex_buffer_handle_t _handle, bgfx_access_t _access);

/**/
BGFX_C_API void bgfx_encoder_set_compute_dynamic_index_buffer(bgfx_encoder_t* _this, uint8_t _stage, bgfx_dynamic_index_buffer_handle_t _handle, bgfx_access_t _access);

/**/
BGFX_C_API void bgfx_encoder_set_compute_dynamic_vertex_buffer(bgfx_encoder_t* _this, uint8_t _stage, bgfx_dynamic_vertex_buffer_handle_t _handle, bgfx_access_t _access);

/**/
BGFX_C_API void bgfx_encoder_set_compute_indirect_buffer(bgfx_encoder_t* _this, uint8_t _stage, bgfx_indirect_buffer_handle_t _handle, bgfx_access_t _access);

/**/
BGFX_C_API void bgfx_encoder_set_image(bgfx_encoder_t* _this, uint8_t _stage, bgfx_texture_handle_t _handle, uint8_t _mip, bgfx_access_t _access, bgfx_texture_format_t _format);

/**/
BGFX_C_API void bgfx_encoder_dispatch(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, uint32_t _numX, uint32_t _numY, uint32_t _numZ);

/**/
BGFX_C_API void bgfx_encoder_dispatch_indirect(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num);

/**/
BGFX_C_API void bgfx_encoder_discard(bgfx_encoder_t* _this);

/**/
BGFX_C_API void bgfx_encoder_blit(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_texture_handle_t _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, bgfx_texture_handle_t _src, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth);

/**/
BGFX_C_API void bgfx_request_screen_shot(bgfx_frame_buffer_handle_t _handle, const char * _filePath);

/**/
BGFX_C_API bgfx_render_frame_t bgfx_render_frame(int32_t _msecs);

/**/
BGFX_C_API void bgfx_set_platform_data(const bgfx_platform_data_t * _data);

/**/
BGFX_C_API const bgfx_internal_data_t * bgfx_get_internal_data();

/**/
BGFX_C_API uintptr_t bgfx_override_internal_texture_ptr(bgfx_texture_handle_t _handle, uintptr_t _ptr);

/**/
BGFX_C_API uintptr_t bgfx_override_internal_texture(bgfx_texture_handle_t _handle, uint16_t _width, uint16_t _height, uint8_t _numMips, bgfx_texture_format_t _format, uint32_t _flags);

/**/
BGFX_C_API void bgfx_set_marker(const char * _marker);

/**/
BGFX_C_API void bgfx_set_state(uint64_t _state, uint32_t _rgba);

/**/
BGFX_C_API void bgfx_set_condition(bgfx_occlusion_query_handle_t _handle, bool _visible);

/**/
BGFX_C_API void bgfx_set_stencil(uint32_t _fstencil, uint32_t _bstencil);

/**/
BGFX_C_API uint16_t bgfx_set_scissor(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

/**/
BGFX_C_API void bgfx_set_scissor_cached(uint16_t _cache);

/**/
BGFX_C_API uint32_t bgfx_set_transform(const void * _mtx, uint16_t _num);

/**/
BGFX_C_API void bgfx_set_transform_cached(uint32_t _cache, uint16_t _num);

/**/
BGFX_C_API uint32_t bgfx_alloc_transform(bgfx_transform_t * _transform, uint16_t _num);

/**/
BGFX_C_API void bgfx_set_uniform(bgfx_uniform_handle_t _handle, const void * _value, uint16_t _num);

/**/
BGFX_C_API void bgfx_set_index_buffer(bgfx_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices);

/**/
BGFX_C_API void bgfx_set_dynamic_index_buffer(bgfx_dynamic_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices);

/**/
BGFX_C_API void bgfx_set_transient_index_buffer(const bgfx_transient_index_buffer_t * _tib, uint32_t _firstIndex, uint32_t _numIndices);

/**/
BGFX_C_API void bgfx_set_vertex_buffer(uint8_t _stream, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices);

/**/
BGFX_C_API void bgfx_set_dynamic_vertex_buffer(uint8_t _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices);

/**/
BGFX_C_API void bgfx_set_transient_vertex_buffer(uint8_t _stream, const bgfx_transient_vertex_buffer_t * _tvb, uint32_t _startVertex, uint32_t _numVertices);

/**/
BGFX_C_API void bgfx_set_vertex_count(uint32_t _numVertices);

/**/
BGFX_C_API void bgfx_set_instance_data_buffer(const bgfx_instance_data_buffer_t * _idb, uint32_t _start, uint32_t _num);

/**/
BGFX_C_API void bgfx_set_instance_data_from_vertex_buffer(bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num);

/**/
BGFX_C_API void bgfx_set_instance_data_from_dynamic_vertex_buffer(bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num);

/**/
BGFX_C_API void bgfx_set_instance_count(uint32_t _numInstances);

/**/
BGFX_C_API void bgfx_set_texture(uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint32_t _flags);

/**/
BGFX_C_API void bgfx_touch(bgfx_view_id_t _id);

/**/
BGFX_C_API void bgfx_submit(bgfx_view_id_t _id, bgfx_program_handle_t _program, uint32_t _depth, bool _preserveState);

/**/
BGFX_C_API void bgfx_submit_occlusion_query(bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_occlusion_query_handle_t _occlusionQuery, uint32_t _depth, bool _preserveState);

/**/
BGFX_C_API void bgfx_submit_indirect(bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, uint32_t _depth, bool _preserveState);

/**/
BGFX_C_API void bgfx_set_compute_index_buffer(uint8_t _stage, bgfx_index_buffer_handle_t _handle, bgfx_access_t _access);

/**/
BGFX_C_API void bgfx_set_compute_vertex_buffer(uint8_t _stage, bgfx_vertex_buffer_handle_t _handle, bgfx_access_t _access);

/**/
BGFX_C_API void bgfx_set_compute_dynamic_index_buffer(uint8_t _stage, bgfx_dynamic_index_buffer_handle_t _handle, bgfx_access_t _access);

/**/
BGFX_C_API void bgfx_set_compute_dynamic_vertex_buffer(uint8_t _stage, bgfx_dynamic_vertex_buffer_handle_t _handle, bgfx_access_t _access);

/**/
BGFX_C_API void bgfx_set_compute_indirect_buffer(uint8_t _stage, bgfx_indirect_buffer_handle_t _handle, bgfx_access_t _access);

/**/
BGFX_C_API void bgfx_set_image(uint8_t _stage, bgfx_texture_handle_t _handle, uint8_t _mip, bgfx_access_t _access, bgfx_texture_format_t _format);

/**/
BGFX_C_API void bgfx_dispatch(bgfx_view_id_t _id, bgfx_program_handle_t _program, uint32_t _numX, uint32_t _numY, uint32_t _numZ);

/**/
BGFX_C_API void bgfx_dispatch_indirect(bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num);

/**/
BGFX_C_API void bgfx_discard();

/**/
BGFX_C_API void bgfx_blit(bgfx_view_id_t _id, bgfx_texture_handle_t _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, bgfx_texture_handle_t _src, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth);

/**/
typedef struct bgfx_interface_vtbl
{
	void (*vertex_decl_begin)(bgfx_vertex_decl_t* _this, bgfx_renderer_type_t _renderer);
	void (*vertex_decl_add)(bgfx_vertex_decl_t* _this, bgfx_attrib_t _attrib, uint8_t _num, bgfx_attrib_type_t _type, bool _normalized, bool _asInt);
	void (*vertex_decl_decode)(const bgfx_vertex_decl_t* _this, bgfx_attrib_t _attrib, uint8_t * _num, bgfx_attrib_type_t * _type, bool * _normalized, bool * _asInt);
	bool (*vertex_decl_has)(const bgfx_vertex_decl_t* _this, bgfx_attrib_t _attrib);
	void (*vertex_decl_skip)(bgfx_vertex_decl_t* _this, uint8_t _num);
	void (*vertex_decl_end)(bgfx_vertex_decl_t* _this);
	void (*vertex_pack)(const float * _input, bool _inputNormalized, bgfx_attrib_t _attr, const bgfx_vertex_decl_t * _decl, void * _data, uint32_t _index);
	void (*vertex_unpack)(float * _output, bgfx_attrib_t _attr, const bgfx_vertex_decl_t * _decl, const void * _data, uint32_t _index);
	void (*vertex_convert)(const bgfx_vertex_decl_t * _dstDecl, void * _dstData, const bgfx_vertex_decl_t * _srcDecl, const void * _srcData, uint32_t _num);
	uint16_t (*weld_vertices)(uint16_t * _output, const bgfx_vertex_decl_t * _decl, const void * _data, uint16_t _num, float _epsilon);
	uint32_t (*topology_convert)(bgfx_topology_convert_t _conversion, void * _dst, uint32_t _dstSize, const void * _indices, uint32_t _numIndices, bool _index32);
	void (*topology_sort_tri_list)(bgfx_topology_sort_t _sort, void * _dst, uint32_t _dstSize, const float * _dir, const float * _pos, const void * _vertices, uint32_t _stride, const void * _indices, uint32_t _numIndices, bool _index32);
	uint8_t (*get_supported_renderers)(uint8_t _max, bgfx_renderer_type_t * _enum);
	const char * (*get_renderer_name)(bgfx_renderer_type_t _type);
	void (*init_ctor)(bgfx_init_t * _init);
	bool (*init)(const bgfx_init_t * _init);
	void (*shutdown)();
	void (*reset)(uint32_t _width, uint32_t _height, uint32_t _flags, bgfx_texture_format_t _format);
	uint32_t (*frame)(bool _capture);
	bgfx_renderer_type_t (*get_renderer_type)();
	const bgfx_caps_t * (*get_caps)();
	const bgfx_stats_t * (*get_stats)();
	const bgfx_memory_t * (*alloc)(uint32_t _size);
	const bgfx_memory_t * (*copy)(const void * _data, uint32_t _size);
	const bgfx_memory_t * (*make_ref)(const void * _data, uint32_t _size);
	const bgfx_memory_t * (*make_ref_release)(const void * _data, uint32_t _size, bgfx_release_fn_t _releaseFn, void * _userData);
	void (*set_debug)(uint32_t _debug);
	void (*dbg_text_clear)(uint8_t _attr, bool _small);
	void (*dbg_text_printf)(uint16_t _x, uint16_t _y, uint8_t _attr, const char * _format, ... );
	void (*dbg_text_vprintf)(uint16_t _x, uint16_t _y, uint8_t _attr, const char * _format, va_list _argList);
	void (*dbg_text_image)(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const void * _data, uint16_t _pitch);
	bgfx_index_buffer_handle_t (*create_index_buffer)(const bgfx_memory_t * _mem, uint16_t _flags);
	void (*set_index_buffer_name)(bgfx_index_buffer_handle_t _handle, const char * _name, int32_t _len);
	void (*destroy_index_buffer)(bgfx_index_buffer_handle_t _handle);
	bgfx_vertex_buffer_handle_t (*create_vertex_buffer)(const bgfx_memory_t * _mem, const bgfx_vertex_decl_t * _decl, uint16_t _flags);
	void (*set_vertex_buffer_name)(bgfx_vertex_buffer_handle_t _handle, const char * _name, int32_t _len);
	void (*destroy_vertex_buffer)(bgfx_vertex_buffer_handle_t _handle);
	bgfx_dynamic_index_buffer_handle_t (*create_dynamic_index_buffer)(uint32_t _num, uint16_t _flags);
	bgfx_dynamic_index_buffer_handle_t (*create_dynamic_index_buffer_mem)(const bgfx_memory_t * _mem, uint16_t _flags);
	void (*update_dynamic_index_buffer)(bgfx_dynamic_index_buffer_handle_t _handle, uint32_t _startIndex, const bgfx_memory_t * _mem);
	void (*destroy_dynamic_index_buffer)(bgfx_dynamic_index_buffer_handle_t _handle);
	bgfx_dynamic_vertex_buffer_handle_t (*create_dynamic_vertex_buffer)(uint32_t _num, const bgfx_vertex_decl_t * _decl, uint16_t _flags);
	bgfx_dynamic_vertex_buffer_handle_t (*create_dynamic_vertex_buffer_mem)(const bgfx_memory_t * _mem, const bgfx_vertex_decl_t * _decl, uint16_t _flags);
	void (*update_dynamic_vertex_buffer)(bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, const bgfx_memory_t * _mem);
	void (*destroy_dynamic_vertex_buffer)(bgfx_dynamic_vertex_buffer_handle_t _handle);
	uint32_t (*get_avail_transient_index_buffer)(uint32_t _num);
	uint32_t (*get_avail_transient_vertex_buffer)(uint32_t _num, const bgfx_vertex_decl_t * _decl);
	uint32_t (*get_avail_instance_data_buffer)(uint32_t _num, uint16_t _stride);
	void (*alloc_transient_index_buffer)(bgfx_transient_index_buffer_t * _tib, uint32_t _num);
	void (*alloc_transient_vertex_buffer)(bgfx_transient_vertex_buffer_t * _tvb, uint32_t _num, const bgfx_vertex_decl_t * _decl);
	bool (*alloc_transient_buffers)(bgfx_transient_vertex_buffer_t * _tvb, const bgfx_vertex_decl_t * _decl, uint32_t _numVertices, bgfx_transient_index_buffer_t * _tib, uint32_t _numIndices);
	void (*alloc_instance_data_buffer)(bgfx_instance_data_buffer_t * _idb, uint32_t _num, uint16_t _stride);
	bgfx_indirect_buffer_handle_t (*create_indirect_buffer)(uint32_t _num);
	void (*destroy_indirect_buffer)(bgfx_indirect_buffer_handle_t _handle);
	bgfx_shader_handle_t (*create_shader)(const bgfx_memory_t * _mem);
	uint16_t (*get_shader_uniforms)(bgfx_shader_handle_t _handle, bgfx_uniform_handle_t * _uniforms, uint16_t _max);
	void (*set_shader_name)(bgfx_shader_handle_t _handle, const char * _name, int32_t _len);
	void (*destroy_shader)(bgfx_shader_handle_t _handle);
	bgfx_program_handle_t (*create_program)(bgfx_shader_handle_t _vsh, bgfx_shader_handle_t _fsh, bool _destroyShaders);
	bgfx_program_handle_t (*create_compute_program)(bgfx_shader_handle_t _csh, bool _destroyShaders);
	void (*destroy_program)(bgfx_program_handle_t _handle);
	bool (*is_texture_valid)(uint16_t _depth, bool _cubeMap, uint16_t _numLayers, bgfx_texture_format_t _format, uint64_t _flags);
	void (*calc_texture_size)(bgfx_texture_info_t * _info, uint16_t _width, uint16_t _height, uint16_t _depth, bool _cubeMap, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format);
	bgfx_texture_handle_t (*create_texture)(const bgfx_memory_t * _mem, uint64_t _flags, uint8_t _skip, bgfx_texture_info_t * _info);
	bgfx_texture_handle_t (*create_texture_2d)(uint16_t _width, uint16_t _height, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format, uint64_t _flags, const bgfx_memory_t * _mem);
	bgfx_texture_handle_t (*create_texture_2d_scaled)(bgfx_backbuffer_ratio_t _ratio, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format, uint64_t _flags);
	bgfx_texture_handle_t (*create_texture_3d)(uint16_t _width, uint16_t _height, uint16_t _depth, bool _hasMips, bgfx_texture_format_t _format, uint64_t _flags, const bgfx_memory_t * _mem);
	bgfx_texture_handle_t (*create_texture_cube)(uint16_t _size, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format, uint64_t _flags, const bgfx_memory_t * _mem);
	void (*update_texture_2d)(bgfx_texture_handle_t _handle, uint16_t _layer, uint16_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const bgfx_memory_t * _mem, uint16_t _pitch);
	void (*update_texture_3d)(bgfx_texture_handle_t _handle, uint16_t _mip, uint16_t _x, uint16_t _y, uint16_t _z, uint16_t _width, uint16_t _height, uint16_t _depth, const bgfx_memory_t * _mem);
	void (*update_texture_cube)(bgfx_texture_handle_t _handle, uint16_t _layer, uint8_t _side, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const bgfx_memory_t * _mem, uint16_t _pitch);
	uint32_t (*read_texture)(bgfx_texture_handle_t _handle, void * _data, uint8_t _mip);
	void (*set_texture_name)(bgfx_texture_handle_t _handle, const char * _name, int32_t _len);
	void * (*get_direct_access_ptr)(bgfx_texture_handle_t _handle);
	void (*destroy_texture)(bgfx_texture_handle_t _handle);
	bgfx_frame_buffer_handle_t (*create_frame_buffer)(uint16_t _width, uint16_t _height, bgfx_texture_format_t _format, uint64_t _textureFlags);
	bgfx_frame_buffer_handle_t (*create_frame_buffer_scaled)(bgfx_backbuffer_ratio_t _ratio, bgfx_texture_format_t _format, uint64_t _textureFlags);
	bgfx_frame_buffer_handle_t (*create_frame_buffer_from_handles)(uint8_t _num, const bgfx_texture_handle_t * _handles, bool _destroyTexture);
	bgfx_frame_buffer_handle_t (*create_frame_buffer_from_attachment)(uint8_t _num, const bgfx_attachment_t * _handles, bool _destroyTexture);
	bgfx_frame_buffer_handle_t (*create_frame_buffer_from_nwh)(void * _nwh, uint16_t _width, uint16_t _height, bgfx_texture_format_t _format, bgfx_texture_format_t _depthFormat);
	void (*set_frame_buffer_name)(bgfx_frame_buffer_handle_t _handle, const char * _name, int32_t _len);
	bgfx_texture_handle_t (*get_texture)(bgfx_frame_buffer_handle_t _handle, uint8_t _attachment);
	void (*destroy_frame_buffer)(bgfx_frame_buffer_handle_t _handle);
	bgfx_uniform_handle_t (*create_uniform)(const char * _name, bgfx_uniform_type_t _type, uint16_t _num);
	void (*get_uniform_info)(bgfx_uniform_handle_t _handle, bgfx_uniform_info_t * _info);
	void (*destroy_uniform)(bgfx_uniform_handle_t _handle);
	bgfx_occlusion_query_handle_t (*create_occlusion_query)();
	bgfx_occlusion_query_result_t (*get_result)(bgfx_occlusion_query_handle_t _handle, int32_t * _result);
	void (*destroy_occlusion_query)(bgfx_occlusion_query_handle_t _handle);
	void (*set_palette_color)(uint8_t _index, const float * _rgba);
	void (*set_view_name)(bgfx_view_id_t _id, const char * _name);
	void (*set_view_rect)(bgfx_view_id_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);
	void (*set_view_rect_ratio)(bgfx_view_id_t _id, uint16_t _x, uint16_t _y, bgfx_backbuffer_ratio_t _ratio);
	void (*set_view_scissor)(bgfx_view_id_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);
	void (*set_view_clear)(bgfx_view_id_t _id, uint16_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil);
	void (*set_view_clear_mrt)(bgfx_view_id_t _id, uint16_t _flags, float _depth, uint8_t _stencil, uint8_t _c0, uint8_t _c1, uint8_t _c2, uint8_t _c3, uint8_t _c4, uint8_t _c5, uint8_t _c6, uint8_t _c7);
	void (*set_view_mode)(bgfx_view_id_t _id, bgfx_view_mode_t _mode);
	void (*set_view_frame_buffer)(bgfx_view_id_t _id, bgfx_frame_buffer_handle_t _handle);
	void (*set_view_transform)(bgfx_view_id_t _id, const void * _view, const void * _proj);
	void (*set_view_order)(bgfx_view_id_t _id, uint16_t _num, const bgfx_view_id_t * _order);
	bgfx_encoder_t * (*encoder_begin)(bool _forThread);
	void (*encoder_end)(bgfx_encoder_t * _encoder);
	void (*encoder_set_marker)(bgfx_encoder_t* _this, const char * _marker);
	void (*encoder_set_state)(bgfx_encoder_t* _this, uint64_t _state, uint32_t _rgba);
	void (*encoder_set_condition)(bgfx_encoder_t* _this, bgfx_occlusion_query_handle_t _handle, bool _visible);
	void (*encoder_set_stencil)(bgfx_encoder_t* _this, uint32_t _fstencil, uint32_t _bstencil);
	uint16_t (*encoder_set_scissor)(bgfx_encoder_t* _this, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);
	void (*encoder_set_scissor_cached)(bgfx_encoder_t* _this, uint16_t _cache);
	uint32_t (*encoder_set_transform)(bgfx_encoder_t* _this, const void * _mtx, uint16_t _num);
	void (*encoder_set_transform_cached)(bgfx_encoder_t* _this, uint32_t _cache, uint16_t _num);
	uint32_t (*encoder_alloc_transform)(bgfx_encoder_t* _this, bgfx_transform_t * _transform, uint16_t _num);
	void (*encoder_set_uniform)(bgfx_encoder_t* _this, bgfx_uniform_handle_t _handle, const void * _value, uint16_t _num);
	void (*encoder_set_index_buffer)(bgfx_encoder_t* _this, bgfx_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices);
	void (*encoder_set_dynamic_index_buffer)(bgfx_encoder_t* _this, bgfx_dynamic_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices);
	void (*encoder_set_transient_index_buffer)(bgfx_encoder_t* _this, const bgfx_transient_index_buffer_t * _tib, uint32_t _firstIndex, uint32_t _numIndices);
	void (*encoder_set_vertex_buffer)(bgfx_encoder_t* _this, uint8_t _stream, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices);
	void (*encoder_set_dynamic_vertex_buffer)(bgfx_encoder_t* _this, uint8_t _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices);
	void (*encoder_set_transient_vertex_buffer)(bgfx_encoder_t* _this, uint8_t _stream, const bgfx_transient_vertex_buffer_t * _tvb, uint32_t _startVertex, uint32_t _numVertices);
	void (*encoder_set_vertex_count)(bgfx_encoder_t* _this, uint32_t _numVertices);
	void (*encoder_set_instance_data_buffer)(bgfx_encoder_t* _this, const bgfx_instance_data_buffer_t * _idb, uint32_t _start, uint32_t _num);
	void (*encoder_set_instance_data_from_vertex_buffer)(bgfx_encoder_t* _this, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num);
	void (*encoder_set_instance_data_from_dynamic_vertex_buffer)(bgfx_encoder_t* _this, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num);
	void (*encoder_set_instance_count)(bgfx_encoder_t* _this, uint32_t _numInstances);
	void (*encoder_set_texture)(bgfx_encoder_t* _this, uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint32_t _flags);
	void (*encoder_touch)(bgfx_encoder_t* _this, bgfx_view_id_t _id);
	void (*encoder_submit)(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, uint32_t _depth, bool _preserveState);
	void (*encoder_submit_occlusion_query)(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_occlusion_query_handle_t _occlusionQuery, uint32_t _depth, bool _preserveState);
	void (*encoder_submit_indirect)(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, uint32_t _depth, bool _preserveState);
	void (*encoder_set_compute_index_buffer)(bgfx_encoder_t* _this, uint8_t _stage, bgfx_index_buffer_handle_t _handle, bgfx_access_t _access);
	void (*encoder_set_compute_vertex_buffer)(bgfx_encoder_t* _this, uint8_t _stage, bgfx_vertex_buffer_handle_t _handle, bgfx_access_t _access);
	void (*encoder_set_compute_dynamic_index_buffer)(bgfx_encoder_t* _this, uint8_t _stage, bgfx_dynamic_index_buffer_handle_t _handle, bgfx_access_t _access);
	void (*encoder_set_compute_dynamic_vertex_buffer)(bgfx_encoder_t* _this, uint8_t _stage, bgfx_dynamic_vertex_buffer_handle_t _handle, bgfx_access_t _access);
	void (*encoder_set_compute_indirect_buffer)(bgfx_encoder_t* _this, uint8_t _stage, bgfx_indirect_buffer_handle_t _handle, bgfx_access_t _access);
	void (*encoder_set_image)(bgfx_encoder_t* _this, uint8_t _stage, bgfx_texture_handle_t _handle, uint8_t _mip, bgfx_access_t _access, bgfx_texture_format_t _format);
	void (*encoder_dispatch)(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, uint32_t _numX, uint32_t _numY, uint32_t _numZ);
	void (*encoder_dispatch_indirect)(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num);
	void (*encoder_discard)(bgfx_encoder_t* _this);
	void (*encoder_blit)(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_texture_handle_t _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, bgfx_texture_handle_t _src, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth);
	void (*request_screen_shot)(bgfx_frame_buffer_handle_t _handle, const char * _filePath);
	bgfx_render_frame_t (*render_frame)(int32_t _msecs);
	void (*set_platform_data)(const bgfx_platform_data_t * _data);
	const bgfx_internal_data_t * (*get_internal_data)();
	uintptr_t (*override_internal_texture_ptr)(bgfx_texture_handle_t _handle, uintptr_t _ptr);
	uintptr_t (*override_internal_texture)(bgfx_texture_handle_t _handle, uint16_t _width, uint16_t _height, uint8_t _numMips, bgfx_texture_format_t _format, uint32_t _flags);
	void (*set_marker)(const char * _marker);
	void (*set_state)(uint64_t _state, uint32_t _rgba);
	void (*set_condition)(bgfx_occlusion_query_handle_t _handle, bool _visible);
	void (*set_stencil)(uint32_t _fstencil, uint32_t _bstencil);
	uint16_t (*set_scissor)(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);
	void (*set_scissor_cached)(uint16_t _cache);
	uint32_t (*set_transform)(const void * _mtx, uint16_t _num);
	void (*set_transform_cached)(uint32_t _cache, uint16_t _num);
	uint32_t (*alloc_transform)(bgfx_transform_t * _transform, uint16_t _num);
	void (*set_uniform)(bgfx_uniform_handle_t _handle, const void * _value, uint16_t _num);
	void (*set_index_buffer)(bgfx_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices);
	void (*set_dynamic_index_buffer)(bgfx_dynamic_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices);
	void (*set_transient_index_buffer)(const bgfx_transient_index_buffer_t * _tib, uint32_t _firstIndex, uint32_t _numIndices);
	void (*set_vertex_buffer)(uint8_t _stream, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices);
	void (*set_dynamic_vertex_buffer)(uint8_t _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices);
	void (*set_transient_vertex_buffer)(uint8_t _stream, const bgfx_transient_vertex_buffer_t * _tvb, uint32_t _startVertex, uint32_t _numVertices);
	void (*set_vertex_count)(uint32_t _numVertices);
	void (*set_instance_data_buffer)(const bgfx_instance_data_buffer_t * _idb, uint32_t _start, uint32_t _num);
	void (*set_instance_data_from_vertex_buffer)(bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num);
	void (*set_instance_data_from_dynamic_vertex_buffer)(bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num);
	void (*set_instance_count)(uint32_t _numInstances);
	void (*set_texture)(uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint32_t _flags);
	void (*touch)(bgfx_view_id_t _id);
	void (*submit)(bgfx_view_id_t _id, bgfx_program_handle_t _program, uint32_t _depth, bool _preserveState);
	void (*submit_occlusion_query)(bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_occlusion_query_handle_t _occlusionQuery, uint32_t _depth, bool _preserveState);
	void (*submit_indirect)(bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, uint32_t _depth, bool _preserveState);
	void (*set_compute_index_buffer)(uint8_t _stage, bgfx_index_buffer_handle_t _handle, bgfx_access_t _access);
	void (*set_compute_vertex_buffer)(uint8_t _stage, bgfx_vertex_buffer_handle_t _handle, bgfx_access_t _access);
	void (*set_compute_dynamic_index_buffer)(uint8_t _stage, bgfx_dynamic_index_buffer_handle_t _handle, bgfx_access_t _access);
	void (*set_compute_dynamic_vertex_buffer)(uint8_t _stage, bgfx_dynamic_vertex_buffer_handle_t _handle, bgfx_access_t _access);
	void (*set_compute_indirect_buffer)(uint8_t _stage, bgfx_indirect_buffer_handle_t _handle, bgfx_access_t _access);
	void (*set_image)(uint8_t _stage, bgfx_texture_handle_t _handle, uint8_t _mip, bgfx_access_t _access, bgfx_texture_format_t _format);
	void (*dispatch)(bgfx_view_id_t _id, bgfx_program_handle_t _program, uint32_t _numX, uint32_t _numY, uint32_t _numZ);
	void (*dispatch_indirect)(bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num);
	void (*discard)();
	void (*blit)(bgfx_view_id_t _id, bgfx_texture_handle_t _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, bgfx_texture_handle_t _src, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth);
} bgfx_interface_vtbl_t;
