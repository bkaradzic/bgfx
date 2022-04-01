/*
 *
 * AUTO GENERATED! DO NOT EDIT!
 *
 */

module bindbc.bgfx.funcs;

private import bindbc.bgfx.types;

extern(C) @nogc nothrow:

version(BindBgfx_Static)
{
	/**
	 * Init attachment.
	 * Params:
	 * _handle = Render target texture handle.
	 * _access = Access. See `Access::Enum`.
	 * _layer = Cubemap side or depth layer/slice to use.
	 * _numLayers = Number of texture layer/slice(s) in array to use.
	 * _mip = Mip level.
	 * _resolve = Resolve flags. See: `BGFX_RESOLVE_*`
	 */
	void bgfx_attachment_init(bgfx_attachment_t* _this, bgfx_texture_handle_t _handle, bgfx_access_t _access, ushort _layer, ushort _numLayers, ushort _mip, ubyte _resolve);
	
	/**
	 * Start VertexLayout.
	 * Params:
	 * _rendererType = Renderer backend type. See: `bgfx::RendererType`
	 */
	bgfx_vertex_layout_t* bgfx_vertex_layout_begin(bgfx_vertex_layout_t* _this, bgfx_renderer_type_t _rendererType);
	
	/**
	 * Add attribute to VertexLayout.
	 * Remarks: Must be called between begin/end.
	 * Params:
	 * _attrib = Attribute semantics. See: `bgfx::Attrib`
	 * _num = Number of elements 1, 2, 3 or 4.
	 * _type = Element type.
	 * _normalized = When using fixed point AttribType (f.e. Uint8)
	 * value will be normalized for vertex shader usage. When normalized
	 * is set to true, AttribType::Uint8 value in range 0-255 will be
	 * in range 0.0-1.0 in vertex shader.
	 * _asInt = Packaging rule for vertexPack, vertexUnpack, and
	 * vertexConvert for AttribType::Uint8 and AttribType::Int16.
	 * Unpacking code must be implemented inside vertex shader.
	 */
	bgfx_vertex_layout_t* bgfx_vertex_layout_add(bgfx_vertex_layout_t* _this, bgfx_attrib_t _attrib, ubyte _num, bgfx_attrib_type_t _type, bool _normalized, bool _asInt);
	
	/**
	 * Decode attribute.
	 * Params:
	 * _attrib = Attribute semantics. See: `bgfx::Attrib`
	 * _num = Number of elements.
	 * _type = Element type.
	 * _normalized = Attribute is normalized.
	 * _asInt = Attribute is packed as int.
	 */
	void bgfx_vertex_layout_decode(const(bgfx_vertex_layout_t)* _this, bgfx_attrib_t _attrib, ubyte* _num, bgfx_attrib_type_t* _type, bool* _normalized, bool* _asInt);
	
	/**
	 * Returns `true` if VertexLayout contains attribute.
	 * Params:
	 * _attrib = Attribute semantics. See: `bgfx::Attrib`
	 */
	bool bgfx_vertex_layout_has(const(bgfx_vertex_layout_t)* _this, bgfx_attrib_t _attrib);
	
	/**
	 * Skip `_num` bytes in vertex stream.
	 * Params:
	 * _num = Number of bytes to skip.
	 */
	bgfx_vertex_layout_t* bgfx_vertex_layout_skip(bgfx_vertex_layout_t* _this, ubyte _num);
	
	/**
	 * End VertexLayout.
	 */
	void bgfx_vertex_layout_end(bgfx_vertex_layout_t* _this);
	
	/**
	 * Pack vertex attribute into vertex stream format.
	 * Params:
	 * _input = Value to be packed into vertex stream.
	 * _inputNormalized = `true` if input value is already normalized.
	 * _attr = Attribute to pack.
	 * _layout = Vertex stream layout.
	 * _data = Destination vertex stream where data will be packed.
	 * _index = Vertex index that will be modified.
	 */
	void bgfx_vertex_pack(const float[4] _input, bool _inputNormalized, bgfx_attrib_t _attr, const(bgfx_vertex_layout_t)* _layout, void* _data, uint _index);
	
	/**
	 * Unpack vertex attribute from vertex stream format.
	 * Params:
	 * _output = Result of unpacking.
	 * _attr = Attribute to unpack.
	 * _layout = Vertex stream layout.
	 * _data = Source vertex stream from where data will be unpacked.
	 * _index = Vertex index that will be unpacked.
	 */
	void bgfx_vertex_unpack(float[4] _output, bgfx_attrib_t _attr, const(bgfx_vertex_layout_t)* _layout, const(void)* _data, uint _index);
	
	/**
	 * Converts vertex stream data from one vertex stream format to another.
	 * Params:
	 * _dstLayout = Destination vertex stream layout.
	 * _dstData = Destination vertex stream.
	 * _srcLayout = Source vertex stream layout.
	 * _srcData = Source vertex stream data.
	 * _num = Number of vertices to convert from source to destination.
	 */
	void bgfx_vertex_convert(const(bgfx_vertex_layout_t)* _dstLayout, void* _dstData, const(bgfx_vertex_layout_t)* _srcLayout, const(void)* _srcData, uint _num);
	
	/**
	 * Weld vertices.
	 * Params:
	 * _output = Welded vertices remapping table. The size of buffer
	 * must be the same as number of vertices.
	 * _layout = Vertex stream layout.
	 * _data = Vertex stream.
	 * _num = Number of vertices in vertex stream.
	 * _index32 = Set to `true` if input indices are 32-bit.
	 * _epsilon = Error tolerance for vertex position comparison.
	 */
	uint bgfx_weld_vertices(void* _output, const(bgfx_vertex_layout_t)* _layout, const(void)* _data, uint _num, bool _index32, float _epsilon);
	
	/**
	 * Convert index buffer for use with different primitive topologies.
	 * Params:
	 * _conversion = Conversion type, see `TopologyConvert::Enum`.
	 * _dst = Destination index buffer. If this argument is NULL
	 * function will return number of indices after conversion.
	 * _dstSize = Destination index buffer in bytes. It must be
	 * large enough to contain output indices. If destination size is
	 * insufficient index buffer will be truncated.
	 * _indices = Source indices.
	 * _numIndices = Number of input indices.
	 * _index32 = Set to `true` if input indices are 32-bit.
	 */
	uint bgfx_topology_convert(bgfx_topology_convert_t _conversion, void* _dst, uint _dstSize, const(void)* _indices, uint _numIndices, bool _index32);
	
	/**
	 * Sort indices.
	 * Params:
	 * _sort = Sort order, see `TopologySort::Enum`.
	 * _dst = Destination index buffer.
	 * _dstSize = Destination index buffer in bytes. It must be
	 * large enough to contain output indices. If destination size is
	 * insufficient index buffer will be truncated.
	 * _dir = Direction (vector must be normalized).
	 * _pos = Position.
	 * _vertices = Pointer to first vertex represented as
	 * float x, y, z. Must contain at least number of vertices
	 * referencende by index buffer.
	 * _stride = Vertex stride.
	 * _indices = Source indices.
	 * _numIndices = Number of input indices.
	 * _index32 = Set to `true` if input indices are 32-bit.
	 */
	void bgfx_topology_sort_tri_list(bgfx_topology_sort_t _sort, void* _dst, uint _dstSize, const float[3] _dir, const float[3] _pos, const(void)* _vertices, uint _stride, const(void)* _indices, uint _numIndices, bool _index32);
	
	/**
	 * Returns supported backend API renderers.
	 * Params:
	 * _max = Maximum number of elements in _enum array.
	 * _enum = Array where supported renderers will be written.
	 */
	ubyte bgfx_get_supported_renderers(ubyte _max, bgfx_renderer_type_t* _enum);
	
	/**
	 * Returns name of renderer.
	 * Params:
	 * _type = Renderer backend type. See: `bgfx::RendererType`
	 */
	const(char)* bgfx_get_renderer_name(bgfx_renderer_type_t _type);
	
	void bgfx_init_ctor(bgfx_init_t* _init);
	
	/**
	 * Initialize the bgfx library.
	 * Params:
	 * _init = Initialization parameters. See: `bgfx::Init` for more info.
	 */
	bool bgfx_init(const(bgfx_init_t)* _init);
	
	/**
	 * Shutdown bgfx library.
	 */
	void bgfx_shutdown();
	
	/**
	 * Reset graphic settings and back-buffer size.
	 * Attention: This call doesn’t change the window size, it just resizes
	 *   the back-buffer. Your windowing code controls the window size.
	 * Params:
	 * _width = Back-buffer width.
	 * _height = Back-buffer height.
	 * _flags = See: `BGFX_RESET_*` for more info.
	 *   - `BGFX_RESET_NONE` - No reset flags.
	 *   - `BGFX_RESET_FULLSCREEN` - Not supported yet.
	 *   - `BGFX_RESET_MSAA_X[2/4/8/16]` - Enable 2, 4, 8 or 16 x MSAA.
	 *   - `BGFX_RESET_VSYNC` - Enable V-Sync.
	 *   - `BGFX_RESET_MAXANISOTROPY` - Turn on/off max anisotropy.
	 *   - `BGFX_RESET_CAPTURE` - Begin screen capture.
	 *   - `BGFX_RESET_FLUSH_AFTER_RENDER` - Flush rendering after submitting to GPU.
	 *   - `BGFX_RESET_FLIP_AFTER_RENDER` - This flag  specifies where flip
	 *     occurs. Default behaviour is that flip occurs before rendering new
	 *     frame. This flag only has effect when `BGFX_CONFIG_MULTITHREADED=0`.
	 *   - `BGFX_RESET_SRGB_BACKBUFFER` - Enable sRGB back-buffer.
	 * _format = Texture format. See: `TextureFormat::Enum`.
	 */
	void bgfx_reset(uint _width, uint _height, uint _flags, bgfx_texture_format_t _format);
	
	/**
	 * Advance to next frame. When using multithreaded renderer, this call
	 * just swaps internal buffers, kicks render thread, and returns. In
	 * singlethreaded renderer this call does frame rendering.
	 * Params:
	 * _capture = Capture frame with graphics debugger.
	 */
	uint bgfx_frame(bool _capture);
	
	/**
	 * Returns current renderer backend API type.
	 * Remarks:
	 *   Library must be initialized.
	 */
	bgfx_renderer_type_t bgfx_get_renderer_type();
	
	/**
	 * Returns renderer capabilities.
	 * Remarks:
	 *   Library must be initialized.
	 */
	const(bgfx_caps_t)* bgfx_get_caps();
	
	/**
	 * Returns performance counters.
	 * Attention: Pointer returned is valid until `bgfx::frame` is called.
	 */
	const(bgfx_stats_t)* bgfx_get_stats();
	
	/**
	 * Allocate buffer to pass to bgfx calls. Data will be freed inside bgfx.
	 * Params:
	 * _size = Size to allocate.
	 */
	const(bgfx_memory_t)* bgfx_alloc(uint _size);
	
	/**
	 * Allocate buffer and copy data into it. Data will be freed inside bgfx.
	 * Params:
	 * _data = Pointer to data to be copied.
	 * _size = Size of data to be copied.
	 */
	const(bgfx_memory_t)* bgfx_copy(const(void)* _data, uint _size);
	
	/**
	 * Make reference to data to pass to bgfx. Unlike `bgfx::alloc`, this call
	 * doesn't allocate memory for data. It just copies the _data pointer. You
	 * can pass `ReleaseFn` function pointer to release this memory after it's
	 * consumed, otherwise you must make sure _data is available for at least 2
	 * `bgfx::frame` calls. `ReleaseFn` function must be able to be called
	 * from any thread.
	 * Attention: Data passed must be available for at least 2 `bgfx::frame` calls.
	 * Params:
	 * _data = Pointer to data.
	 * _size = Size of data.
	 */
	const(bgfx_memory_t)* bgfx_make_ref(const(void)* _data, uint _size);
	
	/**
	 * Make reference to data to pass to bgfx. Unlike `bgfx::alloc`, this call
	 * doesn't allocate memory for data. It just copies the _data pointer. You
	 * can pass `ReleaseFn` function pointer to release this memory after it's
	 * consumed, otherwise you must make sure _data is available for at least 2
	 * `bgfx::frame` calls. `ReleaseFn` function must be able to be called
	 * from any thread.
	 * Attention: Data passed must be available for at least 2 `bgfx::frame` calls.
	 * Params:
	 * _data = Pointer to data.
	 * _size = Size of data.
	 * _releaseFn = Callback function to release memory after use.
	 * _userData = User data to be passed to callback function.
	 */
	const(bgfx_memory_t)* bgfx_make_ref_release(const(void)* _data, uint _size, void* _releaseFn, void* _userData);
	
	/**
	 * Set debug flags.
	 * Params:
	 * _debug = Available flags:
	 *   - `BGFX_DEBUG_IFH` - Infinitely fast hardware. When this flag is set
	 *     all rendering calls will be skipped. This is useful when profiling
	 *     to quickly assess potential bottlenecks between CPU and GPU.
	 *   - `BGFX_DEBUG_PROFILER` - Enable profiler.
	 *   - `BGFX_DEBUG_STATS` - Display internal statistics.
	 *   - `BGFX_DEBUG_TEXT` - Display debug text.
	 *   - `BGFX_DEBUG_WIREFRAME` - Wireframe rendering. All rendering
	 *     primitives will be rendered as lines.
	 */
	void bgfx_set_debug(uint _debug);
	
	/**
	 * Clear internal debug text buffer.
	 * Params:
	 * _attr = Background color.
	 * _small = Default 8x16 or 8x8 font.
	 */
	void bgfx_dbg_text_clear(ubyte _attr, bool _small);
	
	/**
	 * Print formatted data to internal debug text character-buffer (VGA-compatible text mode).
	 * Params:
	 * _x = Position x from the left corner of the window.
	 * _y = Position y from the top corner of the window.
	 * _attr = Color palette. Where top 4-bits represent index of background, and bottom
	 * 4-bits represent foreground color from standard VGA text palette (ANSI escape codes).
	 * _format = `printf` style format.
	 */
	void bgfx_dbg_text_printf(ushort _x, ushort _y, ubyte _attr, const(char)* _format, ... );
	
	/**
	 * Print formatted data from variable argument list to internal debug text character-buffer (VGA-compatible text mode).
	 * Params:
	 * _x = Position x from the left corner of the window.
	 * _y = Position y from the top corner of the window.
	 * _attr = Color palette. Where top 4-bits represent index of background, and bottom
	 * 4-bits represent foreground color from standard VGA text palette (ANSI escape codes).
	 * _format = `printf` style format.
	 * _argList = Variable arguments list for format string.
	 */
	void bgfx_dbg_text_vprintf(ushort _x, ushort _y, ubyte _attr, const(char)* _format, va_list _argList);
	
	/**
	 * Draw image into internal debug text buffer.
	 * Params:
	 * _x = Position x from the left corner of the window.
	 * _y = Position y from the top corner of the window.
	 * _width = Image width.
	 * _height = Image height.
	 * _data = Raw image data (character/attribute raw encoding).
	 * _pitch = Image pitch in bytes.
	 */
	void bgfx_dbg_text_image(ushort _x, ushort _y, ushort _width, ushort _height, const(void)* _data, ushort _pitch);
	
	/**
	 * Create static index buffer.
	 * Params:
	 * _mem = Index buffer data.
	 * _flags = Buffer creation flags.
	 *   - `BGFX_BUFFER_NONE` - No flags.
	 *   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
	 *   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
	 *       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
	 *   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
	 *   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
	 *       data is passed. If this flag is not specified, and more data is passed on update, the buffer
	 *       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
	 *       buffers.
	 *   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
	 *       index buffers.
	 */
	bgfx_index_buffer_handle_t bgfx_create_index_buffer(const(bgfx_memory_t)* _mem, ushort _flags);
	
	/**
	 * Set static index buffer debug name.
	 * Params:
	 * _handle = Static index buffer handle.
	 * _name = Static index buffer name.
	 * _len = Static index buffer name length (if length is INT32_MAX, it's expected
	 * that _name is zero terminated string.
	 */
	void bgfx_set_index_buffer_name(bgfx_index_buffer_handle_t _handle, const(char)* _name, int _len);
	
	/**
	 * Destroy static index buffer.
	 * Params:
	 * _handle = Static index buffer handle.
	 */
	void bgfx_destroy_index_buffer(bgfx_index_buffer_handle_t _handle);
	
	/**
	 * Create vertex layout.
	 * Params:
	 * _layout = Vertex layout.
	 */
	bgfx_vertex_layout_handle_t bgfx_create_vertex_layout(const(bgfx_vertex_layout_t)* _layout);
	
	/**
	 * Destroy vertex layout.
	 * Params:
	 * _layoutHandle = Vertex layout handle.
	 */
	void bgfx_destroy_vertex_layout(bgfx_vertex_layout_handle_t _layoutHandle);
	
	/**
	 * Create static vertex buffer.
	 * Params:
	 * _mem = Vertex buffer data.
	 * _layout = Vertex layout.
	 * _flags = Buffer creation flags.
	 *  - `BGFX_BUFFER_NONE` - No flags.
	 *  - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
	 *  - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
	 *      is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
	 *  - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
	 *  - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
	 *      data is passed. If this flag is not specified, and more data is passed on update, the buffer
	 *      will be trimmed to fit the existing buffer size. This flag has effect only on dynamic buffers.
	 *  - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on index buffers.
	 */
	bgfx_vertex_buffer_handle_t bgfx_create_vertex_buffer(const(bgfx_memory_t)* _mem, const(bgfx_vertex_layout_t)* _layout, ushort _flags);
	
	/**
	 * Set static vertex buffer debug name.
	 * Params:
	 * _handle = Static vertex buffer handle.
	 * _name = Static vertex buffer name.
	 * _len = Static vertex buffer name length (if length is INT32_MAX, it's expected
	 * that _name is zero terminated string.
	 */
	void bgfx_set_vertex_buffer_name(bgfx_vertex_buffer_handle_t _handle, const(char)* _name, int _len);
	
	/**
	 * Destroy static vertex buffer.
	 * Params:
	 * _handle = Static vertex buffer handle.
	 */
	void bgfx_destroy_vertex_buffer(bgfx_vertex_buffer_handle_t _handle);
	
	/**
	 * Create empty dynamic index buffer.
	 * Params:
	 * _num = Number of indices.
	 * _flags = Buffer creation flags.
	 *   - `BGFX_BUFFER_NONE` - No flags.
	 *   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
	 *   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
	 *       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
	 *   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
	 *   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
	 *       data is passed. If this flag is not specified, and more data is passed on update, the buffer
	 *       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
	 *       buffers.
	 *   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
	 *       index buffers.
	 */
	bgfx_dynamic_index_buffer_handle_t bgfx_create_dynamic_index_buffer(uint _num, ushort _flags);
	
	/**
	 * Create a dynamic index buffer and initialize it.
	 * Params:
	 * _mem = Index buffer data.
	 * _flags = Buffer creation flags.
	 *   - `BGFX_BUFFER_NONE` - No flags.
	 *   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
	 *   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
	 *       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
	 *   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
	 *   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
	 *       data is passed. If this flag is not specified, and more data is passed on update, the buffer
	 *       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
	 *       buffers.
	 *   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
	 *       index buffers.
	 */
	bgfx_dynamic_index_buffer_handle_t bgfx_create_dynamic_index_buffer_mem(const(bgfx_memory_t)* _mem, ushort _flags);
	
	/**
	 * Update dynamic index buffer.
	 * Params:
	 * _handle = Dynamic index buffer handle.
	 * _startIndex = Start index.
	 * _mem = Index buffer data.
	 */
	void bgfx_update_dynamic_index_buffer(bgfx_dynamic_index_buffer_handle_t _handle, uint _startIndex, const(bgfx_memory_t)* _mem);
	
	/**
	 * Destroy dynamic index buffer.
	 * Params:
	 * _handle = Dynamic index buffer handle.
	 */
	void bgfx_destroy_dynamic_index_buffer(bgfx_dynamic_index_buffer_handle_t _handle);
	
	/**
	 * Create empty dynamic vertex buffer.
	 * Params:
	 * _num = Number of vertices.
	 * _layout = Vertex layout.
	 * _flags = Buffer creation flags.
	 *   - `BGFX_BUFFER_NONE` - No flags.
	 *   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
	 *   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
	 *       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
	 *   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
	 *   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
	 *       data is passed. If this flag is not specified, and more data is passed on update, the buffer
	 *       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
	 *       buffers.
	 *   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
	 *       index buffers.
	 */
	bgfx_dynamic_vertex_buffer_handle_t bgfx_create_dynamic_vertex_buffer(uint _num, const(bgfx_vertex_layout_t)* _layout, ushort _flags);
	
	/**
	 * Create dynamic vertex buffer and initialize it.
	 * Params:
	 * _mem = Vertex buffer data.
	 * _layout = Vertex layout.
	 * _flags = Buffer creation flags.
	 *   - `BGFX_BUFFER_NONE` - No flags.
	 *   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
	 *   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
	 *       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
	 *   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
	 *   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
	 *       data is passed. If this flag is not specified, and more data is passed on update, the buffer
	 *       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
	 *       buffers.
	 *   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
	 *       index buffers.
	 */
	bgfx_dynamic_vertex_buffer_handle_t bgfx_create_dynamic_vertex_buffer_mem(const(bgfx_memory_t)* _mem, const(bgfx_vertex_layout_t)* _layout, ushort _flags);
	
	/**
	 * Update dynamic vertex buffer.
	 * Params:
	 * _handle = Dynamic vertex buffer handle.
	 * _startVertex = Start vertex.
	 * _mem = Vertex buffer data.
	 */
	void bgfx_update_dynamic_vertex_buffer(bgfx_dynamic_vertex_buffer_handle_t _handle, uint _startVertex, const(bgfx_memory_t)* _mem);
	
	/**
	 * Destroy dynamic vertex buffer.
	 * Params:
	 * _handle = Dynamic vertex buffer handle.
	 */
	void bgfx_destroy_dynamic_vertex_buffer(bgfx_dynamic_vertex_buffer_handle_t _handle);
	
	/**
	 * Returns number of requested or maximum available indices.
	 * Params:
	 * _num = Number of required indices.
	 * _index32 = Set to `true` if input indices will be 32-bit.
	 */
	uint bgfx_get_avail_transient_index_buffer(uint _num, bool _index32);
	
	/**
	 * Returns number of requested or maximum available vertices.
	 * Params:
	 * _num = Number of required vertices.
	 * _layout = Vertex layout.
	 */
	uint bgfx_get_avail_transient_vertex_buffer(uint _num, const(bgfx_vertex_layout_t)* _layout);
	
	/**
	 * Returns number of requested or maximum available instance buffer slots.
	 * Params:
	 * _num = Number of required instances.
	 * _stride = Stride per instance.
	 */
	uint bgfx_get_avail_instance_data_buffer(uint _num, ushort _stride);
	
	/**
	 * Allocate transient index buffer.
	 * Params:
	 * _tib = TransientIndexBuffer structure is filled and is valid
	 * for the duration of frame, and it can be reused for multiple draw
	 * calls.
	 * _num = Number of indices to allocate.
	 * _index32 = Set to `true` if input indices will be 32-bit.
	 */
	void bgfx_alloc_transient_index_buffer(bgfx_transient_index_buffer_t* _tib, uint _num, bool _index32);
	
	/**
	 * Allocate transient vertex buffer.
	 * Params:
	 * _tvb = TransientVertexBuffer structure is filled and is valid
	 * for the duration of frame, and it can be reused for multiple draw
	 * calls.
	 * _num = Number of vertices to allocate.
	 * _layout = Vertex layout.
	 */
	void bgfx_alloc_transient_vertex_buffer(bgfx_transient_vertex_buffer_t* _tvb, uint _num, const(bgfx_vertex_layout_t)* _layout);
	
	/**
	 * Check for required space and allocate transient vertex and index
	 * buffers. If both space requirements are satisfied function returns
	 * true.
	 * Params:
	 * _tvb = TransientVertexBuffer structure is filled and is valid
	 * for the duration of frame, and it can be reused for multiple draw
	 * calls.
	 * _layout = Vertex layout.
	 * _numVertices = Number of vertices to allocate.
	 * _tib = TransientIndexBuffer structure is filled and is valid
	 * for the duration of frame, and it can be reused for multiple draw
	 * calls.
	 * _numIndices = Number of indices to allocate.
	 * _index32 = Set to `true` if input indices will be 32-bit.
	 */
	bool bgfx_alloc_transient_buffers(bgfx_transient_vertex_buffer_t* _tvb, const(bgfx_vertex_layout_t)* _layout, uint _numVertices, bgfx_transient_index_buffer_t* _tib, uint _numIndices, bool _index32);
	
	/**
	 * Allocate instance data buffer.
	 * Params:
	 * _idb = InstanceDataBuffer structure is filled and is valid
	 * for duration of frame, and it can be reused for multiple draw
	 * calls.
	 * _num = Number of instances.
	 * _stride = Instance stride. Must be multiple of 16.
	 */
	void bgfx_alloc_instance_data_buffer(bgfx_instance_data_buffer_t* _idb, uint _num, ushort _stride);
	
	/**
	 * Create draw indirect buffer.
	 * Params:
	 * _num = Number of indirect calls.
	 */
	bgfx_indirect_buffer_handle_t bgfx_create_indirect_buffer(uint _num);
	
	/**
	 * Destroy draw indirect buffer.
	 * Params:
	 * _handle = Indirect buffer handle.
	 */
	void bgfx_destroy_indirect_buffer(bgfx_indirect_buffer_handle_t _handle);
	
	/**
	 * Create shader from memory buffer.
	 * Params:
	 * _mem = Shader binary.
	 */
	bgfx_shader_handle_t bgfx_create_shader(const(bgfx_memory_t)* _mem);
	
	/**
	 * Returns the number of uniforms and uniform handles used inside a shader.
	 * Remarks:
	 *   Only non-predefined uniforms are returned.
	 * Params:
	 * _handle = Shader handle.
	 * _uniforms = UniformHandle array where data will be stored.
	 * _max = Maximum capacity of array.
	 */
	ushort bgfx_get_shader_uniforms(bgfx_shader_handle_t _handle, bgfx_uniform_handle_t* _uniforms, ushort _max);
	
	/**
	 * Set shader debug name.
	 * Params:
	 * _handle = Shader handle.
	 * _name = Shader name.
	 * _len = Shader name length (if length is INT32_MAX, it's expected
	 * that _name is zero terminated string).
	 */
	void bgfx_set_shader_name(bgfx_shader_handle_t _handle, const(char)* _name, int _len);
	
	/**
	 * Destroy shader.
	 * Remarks: Once a shader program is created with _handle,
	 *   it is safe to destroy that shader.
	 * Params:
	 * _handle = Shader handle.
	 */
	void bgfx_destroy_shader(bgfx_shader_handle_t _handle);
	
	/**
	 * Create program with vertex and fragment shaders.
	 * Params:
	 * _vsh = Vertex shader.
	 * _fsh = Fragment shader.
	 * _destroyShaders = If true, shaders will be destroyed when program is destroyed.
	 */
	bgfx_program_handle_t bgfx_create_program(bgfx_shader_handle_t _vsh, bgfx_shader_handle_t _fsh, bool _destroyShaders);
	
	/**
	 * Create program with compute shader.
	 * Params:
	 * _csh = Compute shader.
	 * _destroyShaders = If true, shaders will be destroyed when program is destroyed.
	 */
	bgfx_program_handle_t bgfx_create_compute_program(bgfx_shader_handle_t _csh, bool _destroyShaders);
	
	/**
	 * Destroy program.
	 * Params:
	 * _handle = Program handle.
	 */
	void bgfx_destroy_program(bgfx_program_handle_t _handle);
	
	/**
	 * Validate texture parameters.
	 * Params:
	 * _depth = Depth dimension of volume texture.
	 * _cubeMap = Indicates that texture contains cubemap.
	 * _numLayers = Number of layers in texture array.
	 * _format = Texture format. See: `TextureFormat::Enum`.
	 * _flags = Texture flags. See `BGFX_TEXTURE_*`.
	 */
	bool bgfx_is_texture_valid(ushort _depth, bool _cubeMap, ushort _numLayers, bgfx_texture_format_t _format, ulong _flags);
	
	/**
	 * Validate frame buffer parameters.
	 * Params:
	 * _num = Number of attachments.
	 * _attachment = Attachment texture info. See: `bgfx::Attachment`.
	 */
	bool bgfx_is_frame_buffer_valid(ubyte _num, const(bgfx_attachment_t)* _attachment);
	
	/**
	 * Calculate amount of memory required for texture.
	 * Params:
	 * _info = Resulting texture info structure. See: `TextureInfo`.
	 * _width = Width.
	 * _height = Height.
	 * _depth = Depth dimension of volume texture.
	 * _cubeMap = Indicates that texture contains cubemap.
	 * _hasMips = Indicates that texture contains full mip-map chain.
	 * _numLayers = Number of layers in texture array.
	 * _format = Texture format. See: `TextureFormat::Enum`.
	 */
	void bgfx_calc_texture_size(bgfx_texture_info_t* _info, ushort _width, ushort _height, ushort _depth, bool _cubeMap, bool _hasMips, ushort _numLayers, bgfx_texture_format_t _format);
	
	/**
	 * Create texture from memory buffer.
	 * Params:
	 * _mem = DDS, KTX or PVR texture binary data.
	 * _flags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
	 * flags. Default texture sampling mode is linear, and wrap mode is repeat.
	 * - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	 *   mode.
	 * - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	 *   sampling.
	 * _skip = Skip top level mips when parsing texture.
	 * _info = When non-`NULL` is specified it returns parsed texture information.
	 */
	bgfx_texture_handle_t bgfx_create_texture(const(bgfx_memory_t)* _mem, ulong _flags, ubyte _skip, bgfx_texture_info_t* _info);
	
	/**
	 * Create 2D texture.
	 * Params:
	 * _width = Width.
	 * _height = Height.
	 * _hasMips = Indicates that texture contains full mip-map chain.
	 * _numLayers = Number of layers in texture array. Must be 1 if caps
	 * `BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.
	 * _format = Texture format. See: `TextureFormat::Enum`.
	 * _flags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
	 * flags. Default texture sampling mode is linear, and wrap mode is repeat.
	 * - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	 *   mode.
	 * - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	 *   sampling.
	 * _mem = Texture data. If `_mem` is non-NULL, created texture will be immutable. If
	 * `_mem` is NULL content of the texture is uninitialized. When `_numLayers` is more than
	 * 1, expected memory layout is texture and all mips together for each array element.
	 */
	bgfx_texture_handle_t bgfx_create_texture_2d(ushort _width, ushort _height, bool _hasMips, ushort _numLayers, bgfx_texture_format_t _format, ulong _flags, const(bgfx_memory_t)* _mem);
	
	/**
	 * Create texture with size based on back-buffer ratio. Texture will maintain ratio
	 * if back buffer resolution changes.
	 * Params:
	 * _ratio = Texture size in respect to back-buffer size. See: `BackbufferRatio::Enum`.
	 * _hasMips = Indicates that texture contains full mip-map chain.
	 * _numLayers = Number of layers in texture array. Must be 1 if caps
	 * `BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.
	 * _format = Texture format. See: `TextureFormat::Enum`.
	 * _flags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
	 * flags. Default texture sampling mode is linear, and wrap mode is repeat.
	 * - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	 *   mode.
	 * - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	 *   sampling.
	 */
	bgfx_texture_handle_t bgfx_create_texture_2d_scaled(bgfx_backbuffer_ratio_t _ratio, bool _hasMips, ushort _numLayers, bgfx_texture_format_t _format, ulong _flags);
	
	/**
	 * Create 3D texture.
	 * Params:
	 * _width = Width.
	 * _height = Height.
	 * _depth = Depth.
	 * _hasMips = Indicates that texture contains full mip-map chain.
	 * _format = Texture format. See: `TextureFormat::Enum`.
	 * _flags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
	 * flags. Default texture sampling mode is linear, and wrap mode is repeat.
	 * - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	 *   mode.
	 * - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	 *   sampling.
	 * _mem = Texture data. If `_mem` is non-NULL, created texture will be immutable. If
	 * `_mem` is NULL content of the texture is uninitialized. When `_numLayers` is more than
	 * 1, expected memory layout is texture and all mips together for each array element.
	 */
	bgfx_texture_handle_t bgfx_create_texture_3d(ushort _width, ushort _height, ushort _depth, bool _hasMips, bgfx_texture_format_t _format, ulong _flags, const(bgfx_memory_t)* _mem);
	
	/**
	 * Create Cube texture.
	 * Params:
	 * _size = Cube side size.
	 * _hasMips = Indicates that texture contains full mip-map chain.
	 * _numLayers = Number of layers in texture array. Must be 1 if caps
	 * `BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.
	 * _format = Texture format. See: `TextureFormat::Enum`.
	 * _flags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
	 * flags. Default texture sampling mode is linear, and wrap mode is repeat.
	 * - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	 *   mode.
	 * - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	 *   sampling.
	 * _mem = Texture data. If `_mem` is non-NULL, created texture will be immutable. If
	 * `_mem` is NULL content of the texture is uninitialized. When `_numLayers` is more than
	 * 1, expected memory layout is texture and all mips together for each array element.
	 */
	bgfx_texture_handle_t bgfx_create_texture_cube(ushort _size, bool _hasMips, ushort _numLayers, bgfx_texture_format_t _format, ulong _flags, const(bgfx_memory_t)* _mem);
	
	/**
	 * Update 2D texture.
	 * Attention: It's valid to update only mutable texture. See `bgfx::createTexture2D` for more info.
	 * Params:
	 * _handle = Texture handle.
	 * _layer = Layer in texture array.
	 * _mip = Mip level.
	 * _x = X offset in texture.
	 * _y = Y offset in texture.
	 * _width = Width of texture block.
	 * _height = Height of texture block.
	 * _mem = Texture update data.
	 * _pitch = Pitch of input image (bytes). When _pitch is set to
	 * UINT16_MAX, it will be calculated internally based on _width.
	 */
	void bgfx_update_texture_2d(bgfx_texture_handle_t _handle, ushort _layer, ubyte _mip, ushort _x, ushort _y, ushort _width, ushort _height, const(bgfx_memory_t)* _mem, ushort _pitch);
	
	/**
	 * Update 3D texture.
	 * Attention: It's valid to update only mutable texture. See `bgfx::createTexture3D` for more info.
	 * Params:
	 * _handle = Texture handle.
	 * _mip = Mip level.
	 * _x = X offset in texture.
	 * _y = Y offset in texture.
	 * _z = Z offset in texture.
	 * _width = Width of texture block.
	 * _height = Height of texture block.
	 * _depth = Depth of texture block.
	 * _mem = Texture update data.
	 */
	void bgfx_update_texture_3d(bgfx_texture_handle_t _handle, ubyte _mip, ushort _x, ushort _y, ushort _z, ushort _width, ushort _height, ushort _depth, const(bgfx_memory_t)* _mem);
	
	/**
	 * Update Cube texture.
	 * Attention: It's valid to update only mutable texture. See `bgfx::createTextureCube` for more info.
	 * Params:
	 * _handle = Texture handle.
	 * _layer = Layer in texture array.
	 * _side = Cubemap side `BGFX_CUBE_MAP_<POSITIVE or NEGATIVE>_<X, Y or Z>`,
	 *   where 0 is +X, 1 is -X, 2 is +Y, 3 is -Y, 4 is +Z, and 5 is -Z.
	 *                  +----------+
	 *                  |-z       2|
	 *                  | ^  +y    |
	 *                  | |        |    Unfolded cube:
	 *                  | +---->+x |
	 *       +----------+----------+----------+----------+
	 *       |+y       1|+y       4|+y       0|+y       5|
	 *       | ^  -x    | ^  +z    | ^  +x    | ^  -z    |
	 *       | |        | |        | |        | |        |
	 *       | +---->+z | +---->+x | +---->-z | +---->-x |
	 *       +----------+----------+----------+----------+
	 *                  |+z       3|
	 *                  | ^  -y    |
	 *                  | |        |
	 *                  | +---->+x |
	 *                  +----------+
	 * _mip = Mip level.
	 * _x = X offset in texture.
	 * _y = Y offset in texture.
	 * _width = Width of texture block.
	 * _height = Height of texture block.
	 * _mem = Texture update data.
	 * _pitch = Pitch of input image (bytes). When _pitch is set to
	 * UINT16_MAX, it will be calculated internally based on _width.
	 */
	void bgfx_update_texture_cube(bgfx_texture_handle_t _handle, ushort _layer, ubyte _side, ubyte _mip, ushort _x, ushort _y, ushort _width, ushort _height, const(bgfx_memory_t)* _mem, ushort _pitch);
	
	/**
	 * Read back texture content.
	 * Attention: Texture must be created with `BGFX_TEXTURE_READ_BACK` flag.
	 * Attention: Availability depends on: `BGFX_CAPS_TEXTURE_READ_BACK`.
	 * Params:
	 * _handle = Texture handle.
	 * _data = Destination buffer.
	 * _mip = Mip level.
	 */
	uint bgfx_read_texture(bgfx_texture_handle_t _handle, void* _data, ubyte _mip);
	
	/**
	 * Set texture debug name.
	 * Params:
	 * _handle = Texture handle.
	 * _name = Texture name.
	 * _len = Texture name length (if length is INT32_MAX, it's expected
	 * that _name is zero terminated string.
	 */
	void bgfx_set_texture_name(bgfx_texture_handle_t _handle, const(char)* _name, int _len);
	
	/**
	 * Returns texture direct access pointer.
	 * Attention: Availability depends on: `BGFX_CAPS_TEXTURE_DIRECT_ACCESS`. This feature
	 *   is available on GPUs that have unified memory architecture (UMA) support.
	 * Params:
	 * _handle = Texture handle.
	 */
	void* bgfx_get_direct_access_ptr(bgfx_texture_handle_t _handle);
	
	/**
	 * Destroy texture.
	 * Params:
	 * _handle = Texture handle.
	 */
	void bgfx_destroy_texture(bgfx_texture_handle_t _handle);
	
	/**
	 * Create frame buffer (simple).
	 * Params:
	 * _width = Texture width.
	 * _height = Texture height.
	 * _format = Texture format. See: `TextureFormat::Enum`.
	 * _textureFlags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
	 * flags. Default texture sampling mode is linear, and wrap mode is repeat.
	 * - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	 *   mode.
	 * - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	 *   sampling.
	 */
	bgfx_frame_buffer_handle_t bgfx_create_frame_buffer(ushort _width, ushort _height, bgfx_texture_format_t _format, ulong _textureFlags);
	
	/**
	 * Create frame buffer with size based on back-buffer ratio. Frame buffer will maintain ratio
	 * if back buffer resolution changes.
	 * Params:
	 * _ratio = Frame buffer size in respect to back-buffer size. See:
	 * `BackbufferRatio::Enum`.
	 * _format = Texture format. See: `TextureFormat::Enum`.
	 * _textureFlags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
	 * flags. Default texture sampling mode is linear, and wrap mode is repeat.
	 * - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	 *   mode.
	 * - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	 *   sampling.
	 */
	bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_scaled(bgfx_backbuffer_ratio_t _ratio, bgfx_texture_format_t _format, ulong _textureFlags);
	
	/**
	 * Create MRT frame buffer from texture handles (simple).
	 * Params:
	 * _num = Number of texture handles.
	 * _handles = Texture attachments.
	 * _destroyTexture = If true, textures will be destroyed when
	 * frame buffer is destroyed.
	 */
	bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_from_handles(ubyte _num, const(bgfx_texture_handle_t)* _handles, bool _destroyTexture);
	
	/**
	 * Create MRT frame buffer from texture handles with specific layer and
	 * mip level.
	 * Params:
	 * _num = Number of attachments.
	 * _attachment = Attachment texture info. See: `bgfx::Attachment`.
	 * _destroyTexture = If true, textures will be destroyed when
	 * frame buffer is destroyed.
	 */
	bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_from_attachment(ubyte _num, const(bgfx_attachment_t)* _attachment, bool _destroyTexture);
	
	/**
	 * Create frame buffer for multiple window rendering.
	 * Remarks:
	 *   Frame buffer cannot be used for sampling.
	 * Attention: Availability depends on: `BGFX_CAPS_SWAP_CHAIN`.
	 * Params:
	 * _nwh = OS' target native window handle.
	 * _width = Window back buffer width.
	 * _height = Window back buffer height.
	 * _format = Window back buffer color format.
	 * _depthFormat = Window back buffer depth format.
	 */
	bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_from_nwh(void* _nwh, ushort _width, ushort _height, bgfx_texture_format_t _format, bgfx_texture_format_t _depthFormat);
	
	/**
	 * Set frame buffer debug name.
	 * Params:
	 * _handle = Frame buffer handle.
	 * _name = Frame buffer name.
	 * _len = Frame buffer name length (if length is INT32_MAX, it's expected
	 * that _name is zero terminated string.
	 */
	void bgfx_set_frame_buffer_name(bgfx_frame_buffer_handle_t _handle, const(char)* _name, int _len);
	
	/**
	 * Obtain texture handle of frame buffer attachment.
	 * Params:
	 * _handle = Frame buffer handle.
	 */
	bgfx_texture_handle_t bgfx_get_texture(bgfx_frame_buffer_handle_t _handle, ubyte _attachment);
	
	/**
	 * Destroy frame buffer.
	 * Params:
	 * _handle = Frame buffer handle.
	 */
	void bgfx_destroy_frame_buffer(bgfx_frame_buffer_handle_t _handle);
	
	/**
	 * Create shader uniform parameter.
	 * Remarks:
	 *   1. Uniform names are unique. It's valid to call `bgfx::createUniform`
	 *      multiple times with the same uniform name. The library will always
	 *      return the same handle, but the handle reference count will be
	 *      incremented. This means that the same number of `bgfx::destroyUniform`
	 *      must be called to properly destroy the uniform.
	 *   2. Predefined uniforms (declared in `bgfx_shader.sh`):
	 *      - `u_viewRect vec4(x, y, width, height)` - view rectangle for current
	 *        view, in pixels.
	 *      - `u_viewTexel vec4(1.0/width, 1.0/height, undef, undef)` - inverse
	 *        width and height
	 *      - `u_view mat4` - view matrix
	 *      - `u_invView mat4` - inverted view matrix
	 *      - `u_proj mat4` - projection matrix
	 *      - `u_invProj mat4` - inverted projection matrix
	 *      - `u_viewProj mat4` - concatenated view projection matrix
	 *      - `u_invViewProj mat4` - concatenated inverted view projection matrix
	 *      - `u_model mat4[BGFX_CONFIG_MAX_BONES]` - array of model matrices.
	 *      - `u_modelView mat4` - concatenated model view matrix, only first
	 *        model matrix from array is used.
	 *      - `u_modelViewProj mat4` - concatenated model view projection matrix.
	 *      - `u_alphaRef float` - alpha reference value for alpha test.
	 * Params:
	 * _name = Uniform name in shader.
	 * _type = Type of uniform (See: `bgfx::UniformType`).
	 * _num = Number of elements in array.
	 */
	bgfx_uniform_handle_t bgfx_create_uniform(const(char)* _name, bgfx_uniform_type_t _type, ushort _num);
	
	/**
	 * Retrieve uniform info.
	 * Params:
	 * _handle = Handle to uniform object.
	 * _info = Uniform info.
	 */
	void bgfx_get_uniform_info(bgfx_uniform_handle_t _handle, bgfx_uniform_info_t* _info);
	
	/**
	 * Destroy shader uniform parameter.
	 * Params:
	 * _handle = Handle to uniform object.
	 */
	void bgfx_destroy_uniform(bgfx_uniform_handle_t _handle);
	
	/**
	 * Create occlusion query.
	 */
	bgfx_occlusion_query_handle_t bgfx_create_occlusion_query();
	
	/**
	 * Retrieve occlusion query result from previous frame.
	 * Params:
	 * _handle = Handle to occlusion query object.
	 * _result = Number of pixels that passed test. This argument
	 * can be `NULL` if result of occlusion query is not needed.
	 */
	bgfx_occlusion_query_result_t bgfx_get_result(bgfx_occlusion_query_handle_t _handle, int* _result);
	
	/**
	 * Destroy occlusion query.
	 * Params:
	 * _handle = Handle to occlusion query object.
	 */
	void bgfx_destroy_occlusion_query(bgfx_occlusion_query_handle_t _handle);
	
	/**
	 * Set palette color value.
	 * Params:
	 * _index = Index into palette.
	 * _rgba = RGBA floating point values.
	 */
	void bgfx_set_palette_color(ubyte _index, const float[4] _rgba);
	
	/**
	 * Set palette color value.
	 * Params:
	 * _index = Index into palette.
	 * _rgba = Packed 32-bit RGBA value.
	 */
	void bgfx_set_palette_color_rgba8(ubyte _index, uint _rgba);
	
	/**
	 * Set view name.
	 * Remarks:
	 *   This is debug only feature.
	 *   In graphics debugger view name will appear as:
	 *       "nnnc <view name>"
	 *        ^  ^ ^
	 *        |  +--- compute (C)
	 *        +------ view id
	 * Params:
	 * _id = View id.
	 * _name = View name.
	 */
	void bgfx_set_view_name(bgfx_view_id_t _id, const(char)* _name);
	
	/**
	 * Set view rectangle. Draw primitive outside view will be clipped.
	 * Params:
	 * _id = View id.
	 * _x = Position x from the left corner of the window.
	 * _y = Position y from the top corner of the window.
	 * _width = Width of view port region.
	 * _height = Height of view port region.
	 */
	void bgfx_set_view_rect(bgfx_view_id_t _id, ushort _x, ushort _y, ushort _width, ushort _height);
	
	/**
	 * Set view rectangle. Draw primitive outside view will be clipped.
	 * Params:
	 * _id = View id.
	 * _x = Position x from the left corner of the window.
	 * _y = Position y from the top corner of the window.
	 * _ratio = Width and height will be set in respect to back-buffer size.
	 * See: `BackbufferRatio::Enum`.
	 */
	void bgfx_set_view_rect_ratio(bgfx_view_id_t _id, ushort _x, ushort _y, bgfx_backbuffer_ratio_t _ratio);
	
	/**
	 * Set view scissor. Draw primitive outside view will be clipped. When
	 * _x, _y, _width and _height are set to 0, scissor will be disabled.
	 * Params:
	 * _id = View id.
	 * _x = Position x from the left corner of the window.
	 * _y = Position y from the top corner of the window.
	 * _width = Width of view scissor region.
	 * _height = Height of view scissor region.
	 */
	void bgfx_set_view_scissor(bgfx_view_id_t _id, ushort _x, ushort _y, ushort _width, ushort _height);
	
	/**
	 * Set view clear flags.
	 * Params:
	 * _id = View id.
	 * _flags = Clear flags. Use `BGFX_CLEAR_NONE` to remove any clear
	 * operation. See: `BGFX_CLEAR_*`.
	 * _rgba = Color clear value.
	 * _depth = Depth clear value.
	 * _stencil = Stencil clear value.
	 */
	void bgfx_set_view_clear(bgfx_view_id_t _id, ushort _flags, uint _rgba, float _depth, ubyte _stencil);
	
	/**
	 * Set view clear flags with different clear color for each
	 * frame buffer texture. `bgfx::setPaletteColor` must be used to set up a
	 * clear color palette.
	 * Params:
	 * _id = View id.
	 * _flags = Clear flags. Use `BGFX_CLEAR_NONE` to remove any clear
	 * operation. See: `BGFX_CLEAR_*`.
	 * _depth = Depth clear value.
	 * _stencil = Stencil clear value.
	 * _c0 = Palette index for frame buffer attachment 0.
	 * _c1 = Palette index for frame buffer attachment 1.
	 * _c2 = Palette index for frame buffer attachment 2.
	 * _c3 = Palette index for frame buffer attachment 3.
	 * _c4 = Palette index for frame buffer attachment 4.
	 * _c5 = Palette index for frame buffer attachment 5.
	 * _c6 = Palette index for frame buffer attachment 6.
	 * _c7 = Palette index for frame buffer attachment 7.
	 */
	void bgfx_set_view_clear_mrt(bgfx_view_id_t _id, ushort _flags, float _depth, ubyte _stencil, ubyte _c0, ubyte _c1, ubyte _c2, ubyte _c3, ubyte _c4, ubyte _c5, ubyte _c6, ubyte _c7);
	
	/**
	 * Set view sorting mode.
	 * Remarks:
	 *   View mode must be set prior calling `bgfx::submit` for the view.
	 * Params:
	 * _id = View id.
	 * _mode = View sort mode. See `ViewMode::Enum`.
	 */
	void bgfx_set_view_mode(bgfx_view_id_t _id, bgfx_view_mode_t _mode);
	
	/**
	 * Set view frame buffer.
	 * Remarks:
	 *   Not persistent after `bgfx::reset` call.
	 * Params:
	 * _id = View id.
	 * _handle = Frame buffer handle. Passing `BGFX_INVALID_HANDLE` as
	 * frame buffer handle will draw primitives from this view into
	 * default back buffer.
	 */
	void bgfx_set_view_frame_buffer(bgfx_view_id_t _id, bgfx_frame_buffer_handle_t _handle);
	
	/**
	 * Set view's view matrix and projection matrix,
	 * all draw primitives in this view will use these two matrices.
	 * Params:
	 * _id = View id.
	 * _view = View matrix.
	 * _proj = Projection matrix.
	 */
	void bgfx_set_view_transform(bgfx_view_id_t _id, const(void)* _view, const(void)* _proj);
	
	/**
	 * Post submit view reordering.
	 * Params:
	 * _id = First view id.
	 * _num = Number of views to remap.
	 * _order = View remap id table. Passing `NULL` will reset view ids
	 * to default state.
	 */
	void bgfx_set_view_order(bgfx_view_id_t _id, ushort _num, const(bgfx_view_id_t)* _order);
	
	/**
	 * Reset all view settings to default.
	 */
	void bgfx_reset_view(bgfx_view_id_t _id);
	
	/**
	 * Begin submitting draw calls from thread.
	 * Params:
	 * _forThread = Explicitly request an encoder for a worker thread.
	 */
	bgfx_encoder_t* bgfx_encoder_begin(bool _forThread);
	
	/**
	 * End submitting draw calls from thread.
	 * Params:
	 * _encoder = Encoder.
	 */
	void bgfx_encoder_end(bgfx_encoder_t* _encoder);
	
	/**
	 * Sets a debug marker. This allows you to group graphics calls together for easy browsing in
	 * graphics debugging tools.
	 * Params:
	 * _marker = Marker string.
	 */
	void bgfx_encoder_set_marker(bgfx_encoder_t* _this, const(char)* _marker);
	
	/**
	 * Set render states for draw primitive.
	 * Remarks:
	 *   1. To set up more complex states use:
	 *      `BGFX_STATE_ALPHA_REF(_ref)`,
	 *      `BGFX_STATE_POINT_SIZE(_size)`,
	 *      `BGFX_STATE_BLEND_FUNC(_src, _dst)`,
	 *      `BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA)`,
	 *      `BGFX_STATE_BLEND_EQUATION(_equation)`,
	 *      `BGFX_STATE_BLEND_EQUATION_SEPARATE(_equationRGB, _equationA)`
	 *   2. `BGFX_STATE_BLEND_EQUATION_ADD` is set when no other blend
	 *      equation is specified.
	 * Params:
	 * _state = State flags. Default state for primitive type is
	 *   triangles. See: `BGFX_STATE_DEFAULT`.
	 *   - `BGFX_STATE_DEPTH_TEST_*` - Depth test function.
	 *   - `BGFX_STATE_BLEND_*` - See remark 1 about BGFX_STATE_BLEND_FUNC.
	 *   - `BGFX_STATE_BLEND_EQUATION_*` - See remark 2.
	 *   - `BGFX_STATE_CULL_*` - Backface culling mode.
	 *   - `BGFX_STATE_WRITE_*` - Enable R, G, B, A or Z write.
	 *   - `BGFX_STATE_MSAA` - Enable hardware multisample antialiasing.
	 *   - `BGFX_STATE_PT_[TRISTRIP/LINES/POINTS]` - Primitive type.
	 * _rgba = Sets blend factor used by `BGFX_STATE_BLEND_FACTOR` and
	 *   `BGFX_STATE_BLEND_INV_FACTOR` blend modes.
	 */
	void bgfx_encoder_set_state(bgfx_encoder_t* _this, ulong _state, uint _rgba);
	
	/**
	 * Set condition for rendering.
	 * Params:
	 * _handle = Occlusion query handle.
	 * _visible = Render if occlusion query is visible.
	 */
	void bgfx_encoder_set_condition(bgfx_encoder_t* _this, bgfx_occlusion_query_handle_t _handle, bool _visible);
	
	/**
	 * Set stencil test state.
	 * Params:
	 * _fstencil = Front stencil state.
	 * _bstencil = Back stencil state. If back is set to `BGFX_STENCIL_NONE`
	 * _fstencil is applied to both front and back facing primitives.
	 */
	void bgfx_encoder_set_stencil(bgfx_encoder_t* _this, uint _fstencil, uint _bstencil);
	
	/**
	 * Set scissor for draw primitive.
	 * Remarks:
	 *   To scissor for all primitives in view see `bgfx::setViewScissor`.
	 * Params:
	 * _x = Position x from the left corner of the window.
	 * _y = Position y from the top corner of the window.
	 * _width = Width of view scissor region.
	 * _height = Height of view scissor region.
	 */
	ushort bgfx_encoder_set_scissor(bgfx_encoder_t* _this, ushort _x, ushort _y, ushort _width, ushort _height);
	
	/**
	 * Set scissor from cache for draw primitive.
	 * Remarks:
	 *   To scissor for all primitives in view see `bgfx::setViewScissor`.
	 * Params:
	 * _cache = Index in scissor cache.
	 */
	void bgfx_encoder_set_scissor_cached(bgfx_encoder_t* _this, ushort _cache);
	
	/**
	 * Set model matrix for draw primitive. If it is not called,
	 * the model will be rendered with an identity model matrix.
	 * Params:
	 * _mtx = Pointer to first matrix in array.
	 * _num = Number of matrices in array.
	 */
	uint bgfx_encoder_set_transform(bgfx_encoder_t* _this, const(void)* _mtx, ushort _num);
	
	/**
	 *  Set model matrix from matrix cache for draw primitive.
	 * Params:
	 * _cache = Index in matrix cache.
	 * _num = Number of matrices from cache.
	 */
	void bgfx_encoder_set_transform_cached(bgfx_encoder_t* _this, uint _cache, ushort _num);
	
	/**
	 * Reserve matrices in internal matrix cache.
	 * Attention: Pointer returned can be modified until `bgfx::frame` is called.
	 * Params:
	 * _transform = Pointer to `Transform` structure.
	 * _num = Number of matrices.
	 */
	uint bgfx_encoder_alloc_transform(bgfx_encoder_t* _this, bgfx_transform_t* _transform, ushort _num);
	
	/**
	 * Set shader uniform parameter for draw primitive.
	 * Params:
	 * _handle = Uniform.
	 * _value = Pointer to uniform data.
	 * _num = Number of elements. Passing `UINT16_MAX` will
	 * use the _num passed on uniform creation.
	 */
	void bgfx_encoder_set_uniform(bgfx_encoder_t* _this, bgfx_uniform_handle_t _handle, const(void)* _value, ushort _num);
	
	/**
	 * Set index buffer for draw primitive.
	 * Params:
	 * _handle = Index buffer.
	 * _firstIndex = First index to render.
	 * _numIndices = Number of indices to render.
	 */
	void bgfx_encoder_set_index_buffer(bgfx_encoder_t* _this, bgfx_index_buffer_handle_t _handle, uint _firstIndex, uint _numIndices);
	
	/**
	 * Set index buffer for draw primitive.
	 * Params:
	 * _handle = Dynamic index buffer.
	 * _firstIndex = First index to render.
	 * _numIndices = Number of indices to render.
	 */
	void bgfx_encoder_set_dynamic_index_buffer(bgfx_encoder_t* _this, bgfx_dynamic_index_buffer_handle_t _handle, uint _firstIndex, uint _numIndices);
	
	/**
	 * Set index buffer for draw primitive.
	 * Params:
	 * _tib = Transient index buffer.
	 * _firstIndex = First index to render.
	 * _numIndices = Number of indices to render.
	 */
	void bgfx_encoder_set_transient_index_buffer(bgfx_encoder_t* _this, const(bgfx_transient_index_buffer_t)* _tib, uint _firstIndex, uint _numIndices);
	
	/**
	 * Set vertex buffer for draw primitive.
	 * Params:
	 * _stream = Vertex stream.
	 * _handle = Vertex buffer.
	 * _startVertex = First vertex to render.
	 * _numVertices = Number of vertices to render.
	 */
	void bgfx_encoder_set_vertex_buffer(bgfx_encoder_t* _this, ubyte _stream, bgfx_vertex_buffer_handle_t _handle, uint _startVertex, uint _numVertices);
	
	/**
	 * Set vertex buffer for draw primitive.
	 * Params:
	 * _stream = Vertex stream.
	 * _handle = Vertex buffer.
	 * _startVertex = First vertex to render.
	 * _numVertices = Number of vertices to render.
	 * _layoutHandle = Vertex layout for aliasing vertex buffer. If invalid
	 * handle is used, vertex layout used for creation
	 * of vertex buffer will be used.
	 */
	void bgfx_encoder_set_vertex_buffer_with_layout(bgfx_encoder_t* _this, ubyte _stream, bgfx_vertex_buffer_handle_t _handle, uint _startVertex, uint _numVertices, bgfx_vertex_layout_handle_t _layoutHandle);
	
	/**
	 * Set vertex buffer for draw primitive.
	 * Params:
	 * _stream = Vertex stream.
	 * _handle = Dynamic vertex buffer.
	 * _startVertex = First vertex to render.
	 * _numVertices = Number of vertices to render.
	 */
	void bgfx_encoder_set_dynamic_vertex_buffer(bgfx_encoder_t* _this, ubyte _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint _startVertex, uint _numVertices);
	
	void bgfx_encoder_set_dynamic_vertex_buffer_with_layout(bgfx_encoder_t* _this, ubyte _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint _startVertex, uint _numVertices, bgfx_vertex_layout_handle_t _layoutHandle);
	
	/**
	 * Set vertex buffer for draw primitive.
	 * Params:
	 * _stream = Vertex stream.
	 * _tvb = Transient vertex buffer.
	 * _startVertex = First vertex to render.
	 * _numVertices = Number of vertices to render.
	 */
	void bgfx_encoder_set_transient_vertex_buffer(bgfx_encoder_t* _this, ubyte _stream, const(bgfx_transient_vertex_buffer_t)* _tvb, uint _startVertex, uint _numVertices);
	
	/**
	 * Set vertex buffer for draw primitive.
	 * Params:
	 * _stream = Vertex stream.
	 * _tvb = Transient vertex buffer.
	 * _startVertex = First vertex to render.
	 * _numVertices = Number of vertices to render.
	 * _layoutHandle = Vertex layout for aliasing vertex buffer. If invalid
	 * handle is used, vertex layout used for creation
	 * of vertex buffer will be used.
	 */
	void bgfx_encoder_set_transient_vertex_buffer_with_layout(bgfx_encoder_t* _this, ubyte _stream, const(bgfx_transient_vertex_buffer_t)* _tvb, uint _startVertex, uint _numVertices, bgfx_vertex_layout_handle_t _layoutHandle);
	
	/**
	 * Set number of vertices for auto generated vertices use in conjunction
	 * with gl_VertexID.
	 * Attention: Availability depends on: `BGFX_CAPS_VERTEX_ID`.
	 * Params:
	 * _numVertices = Number of vertices.
	 */
	void bgfx_encoder_set_vertex_count(bgfx_encoder_t* _this, uint _numVertices);
	
	/**
	 * Set instance data buffer for draw primitive.
	 * Params:
	 * _idb = Transient instance data buffer.
	 * _start = First instance data.
	 * _num = Number of data instances.
	 */
	void bgfx_encoder_set_instance_data_buffer(bgfx_encoder_t* _this, const(bgfx_instance_data_buffer_t)* _idb, uint _start, uint _num);
	
	/**
	 * Set instance data buffer for draw primitive.
	 * Params:
	 * _handle = Vertex buffer.
	 * _startVertex = First instance data.
	 * _num = Number of data instances.
	 * Set instance data buffer for draw primitive.
	 */
	void bgfx_encoder_set_instance_data_from_vertex_buffer(bgfx_encoder_t* _this, bgfx_vertex_buffer_handle_t _handle, uint _startVertex, uint _num);
	
	/**
	 * Set instance data buffer for draw primitive.
	 * Params:
	 * _handle = Dynamic vertex buffer.
	 * _startVertex = First instance data.
	 * _num = Number of data instances.
	 */
	void bgfx_encoder_set_instance_data_from_dynamic_vertex_buffer(bgfx_encoder_t* _this, bgfx_dynamic_vertex_buffer_handle_t _handle, uint _startVertex, uint _num);
	
	/**
	 * Set number of instances for auto generated instances use in conjunction
	 * with gl_InstanceID.
	 * Attention: Availability depends on: `BGFX_CAPS_VERTEX_ID`.
	 */
	void bgfx_encoder_set_instance_count(bgfx_encoder_t* _this, uint _numInstances);
	
	/**
	 * Set texture stage for draw primitive.
	 * Params:
	 * _stage = Texture unit.
	 * _sampler = Program sampler.
	 * _handle = Texture handle.
	 * _flags = Texture sampling mode. Default value UINT32_MAX uses
	 *   texture sampling settings from the texture.
	 *   - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	 *     mode.
	 *   - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	 *     sampling.
	 */
	void bgfx_encoder_set_texture(bgfx_encoder_t* _this, ubyte _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint _flags);
	
	/**
	 * Submit an empty primitive for rendering. Uniforms and draw state
	 * will be applied but no geometry will be submitted. Useful in cases
	 * when no other draw/compute primitive is submitted to view, but it's
	 * desired to execute clear view.
	 * Remarks:
	 *   These empty draw calls will sort before ordinary draw calls.
	 * Params:
	 * _id = View id.
	 */
	void bgfx_encoder_touch(bgfx_encoder_t* _this, bgfx_view_id_t _id);
	
	/**
	 * Submit primitive for rendering.
	 * Params:
	 * _id = View id.
	 * _program = Program.
	 * _depth = Depth for sorting.
	 * _flags = Discard or preserve states. See `BGFX_DISCARD_*`.
	 */
	void bgfx_encoder_submit(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, uint _depth, ubyte _flags);
	
	/**
	 * Submit primitive with occlusion query for rendering.
	 * Params:
	 * _id = View id.
	 * _program = Program.
	 * _occlusionQuery = Occlusion query.
	 * _depth = Depth for sorting.
	 * _flags = Discard or preserve states. See `BGFX_DISCARD_*`.
	 */
	void bgfx_encoder_submit_occlusion_query(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_occlusion_query_handle_t _occlusionQuery, uint _depth, ubyte _flags);
	
	/**
	 * Submit primitive for rendering with index and instance data info from
	 * indirect buffer.
	 * Params:
	 * _id = View id.
	 * _program = Program.
	 * _indirectHandle = Indirect buffer.
	 * _start = First element in indirect buffer.
	 * _num = Number of dispatches.
	 * _depth = Depth for sorting.
	 * _flags = Discard or preserve states. See `BGFX_DISCARD_*`.
	 */
	void bgfx_encoder_submit_indirect(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, ushort _start, ushort _num, uint _depth, ubyte _flags);
	
	/**
	 * Set compute index buffer.
	 * Params:
	 * _stage = Compute stage.
	 * _handle = Index buffer handle.
	 * _access = Buffer access. See `Access::Enum`.
	 */
	void bgfx_encoder_set_compute_index_buffer(bgfx_encoder_t* _this, ubyte _stage, bgfx_index_buffer_handle_t _handle, bgfx_access_t _access);
	
	/**
	 * Set compute vertex buffer.
	 * Params:
	 * _stage = Compute stage.
	 * _handle = Vertex buffer handle.
	 * _access = Buffer access. See `Access::Enum`.
	 */
	void bgfx_encoder_set_compute_vertex_buffer(bgfx_encoder_t* _this, ubyte _stage, bgfx_vertex_buffer_handle_t _handle, bgfx_access_t _access);
	
	/**
	 * Set compute dynamic index buffer.
	 * Params:
	 * _stage = Compute stage.
	 * _handle = Dynamic index buffer handle.
	 * _access = Buffer access. See `Access::Enum`.
	 */
	void bgfx_encoder_set_compute_dynamic_index_buffer(bgfx_encoder_t* _this, ubyte _stage, bgfx_dynamic_index_buffer_handle_t _handle, bgfx_access_t _access);
	
	/**
	 * Set compute dynamic vertex buffer.
	 * Params:
	 * _stage = Compute stage.
	 * _handle = Dynamic vertex buffer handle.
	 * _access = Buffer access. See `Access::Enum`.
	 */
	void bgfx_encoder_set_compute_dynamic_vertex_buffer(bgfx_encoder_t* _this, ubyte _stage, bgfx_dynamic_vertex_buffer_handle_t _handle, bgfx_access_t _access);
	
	/**
	 * Set compute indirect buffer.
	 * Params:
	 * _stage = Compute stage.
	 * _handle = Indirect buffer handle.
	 * _access = Buffer access. See `Access::Enum`.
	 */
	void bgfx_encoder_set_compute_indirect_buffer(bgfx_encoder_t* _this, ubyte _stage, bgfx_indirect_buffer_handle_t _handle, bgfx_access_t _access);
	
	/**
	 * Set compute image from texture.
	 * Params:
	 * _stage = Compute stage.
	 * _handle = Texture handle.
	 * _mip = Mip level.
	 * _access = Image access. See `Access::Enum`.
	 * _format = Texture format. See: `TextureFormat::Enum`.
	 */
	void bgfx_encoder_set_image(bgfx_encoder_t* _this, ubyte _stage, bgfx_texture_handle_t _handle, ubyte _mip, bgfx_access_t _access, bgfx_texture_format_t _format);
	
	/**
	 * Dispatch compute.
	 * Params:
	 * _id = View id.
	 * _program = Compute program.
	 * _numX = Number of groups X.
	 * _numY = Number of groups Y.
	 * _numZ = Number of groups Z.
	 * _flags = Discard or preserve states. See `BGFX_DISCARD_*`.
	 */
	void bgfx_encoder_dispatch(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, uint _numX, uint _numY, uint _numZ, ubyte _flags);
	
	/**
	 * Dispatch compute indirect.
	 * Params:
	 * _id = View id.
	 * _program = Compute program.
	 * _indirectHandle = Indirect buffer.
	 * _start = First element in indirect buffer.
	 * _num = Number of dispatches.
	 * _flags = Discard or preserve states. See `BGFX_DISCARD_*`.
	 */
	void bgfx_encoder_dispatch_indirect(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, ushort _start, ushort _num, ubyte _flags);
	
	/**
	 * Discard previously set state for draw or compute call.
	 * Params:
	 * _flags = Discard or preserve states. See `BGFX_DISCARD_*`.
	 */
	void bgfx_encoder_discard(bgfx_encoder_t* _this, ubyte _flags);
	
	/**
	 * Blit 2D texture region between two 2D textures.
	 * Attention: Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
	 * Attention: Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
	 * Params:
	 * _id = View id.
	 * _dst = Destination texture handle.
	 * _dstMip = Destination texture mip level.
	 * _dstX = Destination texture X position.
	 * _dstY = Destination texture Y position.
	 * _dstZ = If texture is 2D this argument should be 0. If destination texture is cube
	 * this argument represents destination texture cube face. For 3D texture this argument
	 * represents destination texture Z position.
	 * _src = Source texture handle.
	 * _srcMip = Source texture mip level.
	 * _srcX = Source texture X position.
	 * _srcY = Source texture Y position.
	 * _srcZ = If texture is 2D this argument should be 0. If source texture is cube
	 * this argument represents source texture cube face. For 3D texture this argument
	 * represents source texture Z position.
	 * _width = Width of region.
	 * _height = Height of region.
	 * _depth = If texture is 3D this argument represents depth of region, otherwise it's
	 * unused.
	 */
	void bgfx_encoder_blit(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_texture_handle_t _dst, ubyte _dstMip, ushort _dstX, ushort _dstY, ushort _dstZ, bgfx_texture_handle_t _src, ubyte _srcMip, ushort _srcX, ushort _srcY, ushort _srcZ, ushort _width, ushort _height, ushort _depth);
	
	/**
	 * Request screen shot of window back buffer.
	 * Remarks:
	 *   `bgfx::CallbackI::screenShot` must be implemented.
	 * Attention: Frame buffer handle must be created with OS' target native window handle.
	 * Params:
	 * _handle = Frame buffer handle. If handle is `BGFX_INVALID_HANDLE` request will be
	 * made for main window back buffer.
	 * _filePath = Will be passed to `bgfx::CallbackI::screenShot` callback.
	 */
	void bgfx_request_screen_shot(bgfx_frame_buffer_handle_t _handle, const(char)* _filePath);
	
	/**
	 * Render frame.
	 * Attention: `bgfx::renderFrame` is blocking call. It waits for
	 *   `bgfx::frame` to be called from API thread to process frame.
	 *   If timeout value is passed call will timeout and return even
	 *   if `bgfx::frame` is not called.
	 * Warning: This call should be only used on platforms that don't
	 *   allow creating separate rendering thread. If it is called before
	 *   to bgfx::init, render thread won't be created by bgfx::init call.
	 * Params:
	 * _msecs = Timeout in milliseconds.
	 */
	bgfx_render_frame_t bgfx_render_frame(int _msecs);
	
	/**
	 * Set platform data.
	 * Warning: Must be called before `bgfx::init`.
	 * Params:
	 * _data = Platform data.
	 */
	void bgfx_set_platform_data(const(bgfx_platform_data_t)* _data);
	
	/**
	 * Get internal data for interop.
	 * Attention: It's expected you understand some bgfx internals before you
	 *   use this call.
	 * Warning: Must be called only on render thread.
	 */
	const(bgfx_internal_data_t)* bgfx_get_internal_data();
	
	/**
	 * Override internal texture with externally created texture. Previously
	 * created internal texture will released.
	 * Attention: It's expected you understand some bgfx internals before you
	 *   use this call.
	 * Warning: Must be called only on render thread.
	 * Params:
	 * _handle = Texture handle.
	 * _ptr = Native API pointer to texture.
	 */
	ulong bgfx_override_internal_texture_ptr(bgfx_texture_handle_t _handle, ulong _ptr);
	
	/**
	 * Override internal texture by creating new texture. Previously created
	 * internal texture will released.
	 * Attention: It's expected you understand some bgfx internals before you
	 *   use this call.
	 * Returns: Native API pointer to texture. If result is 0, texture is not created yet from the
	 *   main thread.
	 * Warning: Must be called only on render thread.
	 * Params:
	 * _handle = Texture handle.
	 * _width = Width.
	 * _height = Height.
	 * _numMips = Number of mip-maps.
	 * _format = Texture format. See: `TextureFormat::Enum`.
	 * _flags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
	 * flags. Default texture sampling mode is linear, and wrap mode is repeat.
	 * - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	 *   mode.
	 * - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	 *   sampling.
	 */
	ulong bgfx_override_internal_texture(bgfx_texture_handle_t _handle, ushort _width, ushort _height, ubyte _numMips, bgfx_texture_format_t _format, ulong _flags);
	
	/**
	 * Sets a debug marker. This allows you to group graphics calls together for easy browsing in
	 * graphics debugging tools.
	 * Params:
	 * _marker = Marker string.
	 */
	void bgfx_set_marker(const(char)* _marker);
	
	/**
	 * Set render states for draw primitive.
	 * Remarks:
	 *   1. To set up more complex states use:
	 *      `BGFX_STATE_ALPHA_REF(_ref)`,
	 *      `BGFX_STATE_POINT_SIZE(_size)`,
	 *      `BGFX_STATE_BLEND_FUNC(_src, _dst)`,
	 *      `BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA)`,
	 *      `BGFX_STATE_BLEND_EQUATION(_equation)`,
	 *      `BGFX_STATE_BLEND_EQUATION_SEPARATE(_equationRGB, _equationA)`
	 *   2. `BGFX_STATE_BLEND_EQUATION_ADD` is set when no other blend
	 *      equation is specified.
	 * Params:
	 * _state = State flags. Default state for primitive type is
	 *   triangles. See: `BGFX_STATE_DEFAULT`.
	 *   - `BGFX_STATE_DEPTH_TEST_*` - Depth test function.
	 *   - `BGFX_STATE_BLEND_*` - See remark 1 about BGFX_STATE_BLEND_FUNC.
	 *   - `BGFX_STATE_BLEND_EQUATION_*` - See remark 2.
	 *   - `BGFX_STATE_CULL_*` - Backface culling mode.
	 *   - `BGFX_STATE_WRITE_*` - Enable R, G, B, A or Z write.
	 *   - `BGFX_STATE_MSAA` - Enable hardware multisample antialiasing.
	 *   - `BGFX_STATE_PT_[TRISTRIP/LINES/POINTS]` - Primitive type.
	 * _rgba = Sets blend factor used by `BGFX_STATE_BLEND_FACTOR` and
	 *   `BGFX_STATE_BLEND_INV_FACTOR` blend modes.
	 */
	void bgfx_set_state(ulong _state, uint _rgba);
	
	/**
	 * Set condition for rendering.
	 * Params:
	 * _handle = Occlusion query handle.
	 * _visible = Render if occlusion query is visible.
	 */
	void bgfx_set_condition(bgfx_occlusion_query_handle_t _handle, bool _visible);
	
	/**
	 * Set stencil test state.
	 * Params:
	 * _fstencil = Front stencil state.
	 * _bstencil = Back stencil state. If back is set to `BGFX_STENCIL_NONE`
	 * _fstencil is applied to both front and back facing primitives.
	 */
	void bgfx_set_stencil(uint _fstencil, uint _bstencil);
	
	/**
	 * Set scissor for draw primitive.
	 * Remarks:
	 *   To scissor for all primitives in view see `bgfx::setViewScissor`.
	 * Params:
	 * _x = Position x from the left corner of the window.
	 * _y = Position y from the top corner of the window.
	 * _width = Width of view scissor region.
	 * _height = Height of view scissor region.
	 */
	ushort bgfx_set_scissor(ushort _x, ushort _y, ushort _width, ushort _height);
	
	/**
	 * Set scissor from cache for draw primitive.
	 * Remarks:
	 *   To scissor for all primitives in view see `bgfx::setViewScissor`.
	 * Params:
	 * _cache = Index in scissor cache.
	 */
	void bgfx_set_scissor_cached(ushort _cache);
	
	/**
	 * Set model matrix for draw primitive. If it is not called,
	 * the model will be rendered with an identity model matrix.
	 * Params:
	 * _mtx = Pointer to first matrix in array.
	 * _num = Number of matrices in array.
	 */
	uint bgfx_set_transform(const(void)* _mtx, ushort _num);
	
	/**
	 *  Set model matrix from matrix cache for draw primitive.
	 * Params:
	 * _cache = Index in matrix cache.
	 * _num = Number of matrices from cache.
	 */
	void bgfx_set_transform_cached(uint _cache, ushort _num);
	
	/**
	 * Reserve matrices in internal matrix cache.
	 * Attention: Pointer returned can be modified until `bgfx::frame` is called.
	 * Params:
	 * _transform = Pointer to `Transform` structure.
	 * _num = Number of matrices.
	 */
	uint bgfx_alloc_transform(bgfx_transform_t* _transform, ushort _num);
	
	/**
	 * Set shader uniform parameter for draw primitive.
	 * Params:
	 * _handle = Uniform.
	 * _value = Pointer to uniform data.
	 * _num = Number of elements. Passing `UINT16_MAX` will
	 * use the _num passed on uniform creation.
	 */
	void bgfx_set_uniform(bgfx_uniform_handle_t _handle, const(void)* _value, ushort _num);
	
	/**
	 * Set index buffer for draw primitive.
	 * Params:
	 * _handle = Index buffer.
	 * _firstIndex = First index to render.
	 * _numIndices = Number of indices to render.
	 */
	void bgfx_set_index_buffer(bgfx_index_buffer_handle_t _handle, uint _firstIndex, uint _numIndices);
	
	/**
	 * Set index buffer for draw primitive.
	 * Params:
	 * _handle = Dynamic index buffer.
	 * _firstIndex = First index to render.
	 * _numIndices = Number of indices to render.
	 */
	void bgfx_set_dynamic_index_buffer(bgfx_dynamic_index_buffer_handle_t _handle, uint _firstIndex, uint _numIndices);
	
	/**
	 * Set index buffer for draw primitive.
	 * Params:
	 * _tib = Transient index buffer.
	 * _firstIndex = First index to render.
	 * _numIndices = Number of indices to render.
	 */
	void bgfx_set_transient_index_buffer(const(bgfx_transient_index_buffer_t)* _tib, uint _firstIndex, uint _numIndices);
	
	/**
	 * Set vertex buffer for draw primitive.
	 * Params:
	 * _stream = Vertex stream.
	 * _handle = Vertex buffer.
	 * _startVertex = First vertex to render.
	 * _numVertices = Number of vertices to render.
	 */
	void bgfx_set_vertex_buffer(ubyte _stream, bgfx_vertex_buffer_handle_t _handle, uint _startVertex, uint _numVertices);
	
	/**
	 * Set vertex buffer for draw primitive.
	 * Params:
	 * _stream = Vertex stream.
	 * _handle = Vertex buffer.
	 * _startVertex = First vertex to render.
	 * _numVertices = Number of vertices to render.
	 * _layoutHandle = Vertex layout for aliasing vertex buffer. If invalid
	 * handle is used, vertex layout used for creation
	 * of vertex buffer will be used.
	 */
	void bgfx_set_vertex_buffer_with_layout(ubyte _stream, bgfx_vertex_buffer_handle_t _handle, uint _startVertex, uint _numVertices, bgfx_vertex_layout_handle_t _layoutHandle);
	
	/**
	 * Set vertex buffer for draw primitive.
	 * Params:
	 * _stream = Vertex stream.
	 * _handle = Dynamic vertex buffer.
	 * _startVertex = First vertex to render.
	 * _numVertices = Number of vertices to render.
	 */
	void bgfx_set_dynamic_vertex_buffer(ubyte _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint _startVertex, uint _numVertices);
	
	/**
	 * Set vertex buffer for draw primitive.
	 * Params:
	 * _stream = Vertex stream.
	 * _handle = Dynamic vertex buffer.
	 * _startVertex = First vertex to render.
	 * _numVertices = Number of vertices to render.
	 * _layoutHandle = Vertex layout for aliasing vertex buffer. If invalid
	 * handle is used, vertex layout used for creation
	 * of vertex buffer will be used.
	 */
	void bgfx_set_dynamic_vertex_buffer_with_layout(ubyte _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint _startVertex, uint _numVertices, bgfx_vertex_layout_handle_t _layoutHandle);
	
	/**
	 * Set vertex buffer for draw primitive.
	 * Params:
	 * _stream = Vertex stream.
	 * _tvb = Transient vertex buffer.
	 * _startVertex = First vertex to render.
	 * _numVertices = Number of vertices to render.
	 */
	void bgfx_set_transient_vertex_buffer(ubyte _stream, const(bgfx_transient_vertex_buffer_t)* _tvb, uint _startVertex, uint _numVertices);
	
	/**
	 * Set vertex buffer for draw primitive.
	 * Params:
	 * _stream = Vertex stream.
	 * _tvb = Transient vertex buffer.
	 * _startVertex = First vertex to render.
	 * _numVertices = Number of vertices to render.
	 * _layoutHandle = Vertex layout for aliasing vertex buffer. If invalid
	 * handle is used, vertex layout used for creation
	 * of vertex buffer will be used.
	 */
	void bgfx_set_transient_vertex_buffer_with_layout(ubyte _stream, const(bgfx_transient_vertex_buffer_t)* _tvb, uint _startVertex, uint _numVertices, bgfx_vertex_layout_handle_t _layoutHandle);
	
	/**
	 * Set number of vertices for auto generated vertices use in conjunction
	 * with gl_VertexID.
	 * Attention: Availability depends on: `BGFX_CAPS_VERTEX_ID`.
	 * Params:
	 * _numVertices = Number of vertices.
	 */
	void bgfx_set_vertex_count(uint _numVertices);
	
	/**
	 * Set instance data buffer for draw primitive.
	 * Params:
	 * _idb = Transient instance data buffer.
	 * _start = First instance data.
	 * _num = Number of data instances.
	 */
	void bgfx_set_instance_data_buffer(const(bgfx_instance_data_buffer_t)* _idb, uint _start, uint _num);
	
	/**
	 * Set instance data buffer for draw primitive.
	 * Params:
	 * _handle = Vertex buffer.
	 * _startVertex = First instance data.
	 * _num = Number of data instances.
	 * Set instance data buffer for draw primitive.
	 */
	void bgfx_set_instance_data_from_vertex_buffer(bgfx_vertex_buffer_handle_t _handle, uint _startVertex, uint _num);
	
	/**
	 * Set instance data buffer for draw primitive.
	 * Params:
	 * _handle = Dynamic vertex buffer.
	 * _startVertex = First instance data.
	 * _num = Number of data instances.
	 */
	void bgfx_set_instance_data_from_dynamic_vertex_buffer(bgfx_dynamic_vertex_buffer_handle_t _handle, uint _startVertex, uint _num);
	
	/**
	 * Set number of instances for auto generated instances use in conjunction
	 * with gl_InstanceID.
	 * Attention: Availability depends on: `BGFX_CAPS_VERTEX_ID`.
	 */
	void bgfx_set_instance_count(uint _numInstances);
	
	/**
	 * Set texture stage for draw primitive.
	 * Params:
	 * _stage = Texture unit.
	 * _sampler = Program sampler.
	 * _handle = Texture handle.
	 * _flags = Texture sampling mode. Default value UINT32_MAX uses
	 *   texture sampling settings from the texture.
	 *   - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	 *     mode.
	 *   - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	 *     sampling.
	 */
	void bgfx_set_texture(ubyte _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint _flags);
	
	/**
	 * Submit an empty primitive for rendering. Uniforms and draw state
	 * will be applied but no geometry will be submitted.
	 * Remarks:
	 *   These empty draw calls will sort before ordinary draw calls.
	 * Params:
	 * _id = View id.
	 */
	void bgfx_touch(bgfx_view_id_t _id);
	
	/**
	 * Submit primitive for rendering.
	 * Params:
	 * _id = View id.
	 * _program = Program.
	 * _depth = Depth for sorting.
	 * _flags = Which states to discard for next draw. See `BGFX_DISCARD_*`.
	 */
	void bgfx_submit(bgfx_view_id_t _id, bgfx_program_handle_t _program, uint _depth, ubyte _flags);
	
	/**
	 * Submit primitive with occlusion query for rendering.
	 * Params:
	 * _id = View id.
	 * _program = Program.
	 * _occlusionQuery = Occlusion query.
	 * _depth = Depth for sorting.
	 * _flags = Which states to discard for next draw. See `BGFX_DISCARD_*`.
	 */
	void bgfx_submit_occlusion_query(bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_occlusion_query_handle_t _occlusionQuery, uint _depth, ubyte _flags);
	
	/**
	 * Submit primitive for rendering with index and instance data info from
	 * indirect buffer.
	 * Params:
	 * _id = View id.
	 * _program = Program.
	 * _indirectHandle = Indirect buffer.
	 * _start = First element in indirect buffer.
	 * _num = Number of dispatches.
	 * _depth = Depth for sorting.
	 * _flags = Which states to discard for next draw. See `BGFX_DISCARD_*`.
	 */
	void bgfx_submit_indirect(bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, ushort _start, ushort _num, uint _depth, ubyte _flags);
	
	/**
	 * Set compute index buffer.
	 * Params:
	 * _stage = Compute stage.
	 * _handle = Index buffer handle.
	 * _access = Buffer access. See `Access::Enum`.
	 */
	void bgfx_set_compute_index_buffer(ubyte _stage, bgfx_index_buffer_handle_t _handle, bgfx_access_t _access);
	
	/**
	 * Set compute vertex buffer.
	 * Params:
	 * _stage = Compute stage.
	 * _handle = Vertex buffer handle.
	 * _access = Buffer access. See `Access::Enum`.
	 */
	void bgfx_set_compute_vertex_buffer(ubyte _stage, bgfx_vertex_buffer_handle_t _handle, bgfx_access_t _access);
	
	/**
	 * Set compute dynamic index buffer.
	 * Params:
	 * _stage = Compute stage.
	 * _handle = Dynamic index buffer handle.
	 * _access = Buffer access. See `Access::Enum`.
	 */
	void bgfx_set_compute_dynamic_index_buffer(ubyte _stage, bgfx_dynamic_index_buffer_handle_t _handle, bgfx_access_t _access);
	
	/**
	 * Set compute dynamic vertex buffer.
	 * Params:
	 * _stage = Compute stage.
	 * _handle = Dynamic vertex buffer handle.
	 * _access = Buffer access. See `Access::Enum`.
	 */
	void bgfx_set_compute_dynamic_vertex_buffer(ubyte _stage, bgfx_dynamic_vertex_buffer_handle_t _handle, bgfx_access_t _access);
	
	/**
	 * Set compute indirect buffer.
	 * Params:
	 * _stage = Compute stage.
	 * _handle = Indirect buffer handle.
	 * _access = Buffer access. See `Access::Enum`.
	 */
	void bgfx_set_compute_indirect_buffer(ubyte _stage, bgfx_indirect_buffer_handle_t _handle, bgfx_access_t _access);
	
	/**
	 * Set compute image from texture.
	 * Params:
	 * _stage = Compute stage.
	 * _handle = Texture handle.
	 * _mip = Mip level.
	 * _access = Image access. See `Access::Enum`.
	 * _format = Texture format. See: `TextureFormat::Enum`.
	 */
	void bgfx_set_image(ubyte _stage, bgfx_texture_handle_t _handle, ubyte _mip, bgfx_access_t _access, bgfx_texture_format_t _format);
	
	/**
	 * Dispatch compute.
	 * Params:
	 * _id = View id.
	 * _program = Compute program.
	 * _numX = Number of groups X.
	 * _numY = Number of groups Y.
	 * _numZ = Number of groups Z.
	 * _flags = Discard or preserve states. See `BGFX_DISCARD_*`.
	 */
	void bgfx_dispatch(bgfx_view_id_t _id, bgfx_program_handle_t _program, uint _numX, uint _numY, uint _numZ, ubyte _flags);
	
	/**
	 * Dispatch compute indirect.
	 * Params:
	 * _id = View id.
	 * _program = Compute program.
	 * _indirectHandle = Indirect buffer.
	 * _start = First element in indirect buffer.
	 * _num = Number of dispatches.
	 * _flags = Discard or preserve states. See `BGFX_DISCARD_*`.
	 */
	void bgfx_dispatch_indirect(bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, ushort _start, ushort _num, ubyte _flags);
	
	/**
	 * Discard previously set state for draw or compute call.
	 * Params:
	 * _flags = Draw/compute states to discard.
	 */
	void bgfx_discard(ubyte _flags);
	
	/**
	 * Blit 2D texture region between two 2D textures.
	 * Attention: Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
	 * Attention: Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
	 * Params:
	 * _id = View id.
	 * _dst = Destination texture handle.
	 * _dstMip = Destination texture mip level.
	 * _dstX = Destination texture X position.
	 * _dstY = Destination texture Y position.
	 * _dstZ = If texture is 2D this argument should be 0. If destination texture is cube
	 * this argument represents destination texture cube face. For 3D texture this argument
	 * represents destination texture Z position.
	 * _src = Source texture handle.
	 * _srcMip = Source texture mip level.
	 * _srcX = Source texture X position.
	 * _srcY = Source texture Y position.
	 * _srcZ = If texture is 2D this argument should be 0. If source texture is cube
	 * this argument represents source texture cube face. For 3D texture this argument
	 * represents source texture Z position.
	 * _width = Width of region.
	 * _height = Height of region.
	 * _depth = If texture is 3D this argument represents depth of region, otherwise it's
	 * unused.
	 */
	void bgfx_blit(bgfx_view_id_t _id, bgfx_texture_handle_t _dst, ubyte _dstMip, ushort _dstX, ushort _dstY, ushort _dstZ, bgfx_texture_handle_t _src, ubyte _srcMip, ushort _srcX, ushort _srcY, ushort _srcZ, ushort _width, ushort _height, ushort _depth);
	
}
else
{
	__gshared
	{
		/**
		 * Init attachment.
		 * Params:
		 * _handle = Render target texture handle.
		 * _access = Access. See `Access::Enum`.
		 * _layer = Cubemap side or depth layer/slice to use.
		 * _numLayers = Number of texture layer/slice(s) in array to use.
		 * _mip = Mip level.
		 * _resolve = Resolve flags. See: `BGFX_RESOLVE_*`
		 */
		alias da_bgfx_attachment_init = void function(bgfx_attachment_t* _this, bgfx_texture_handle_t _handle, bgfx_access_t _access, ushort _layer, ushort _numLayers, ushort _mip, ubyte _resolve);
		da_bgfx_attachment_init bgfx_attachment_init;
		
		/**
		 * Start VertexLayout.
		 * Params:
		 * _rendererType = Renderer backend type. See: `bgfx::RendererType`
		 */
		alias da_bgfx_vertex_layout_begin = bgfx_vertex_layout_t* function(bgfx_vertex_layout_t* _this, bgfx_renderer_type_t _rendererType);
		da_bgfx_vertex_layout_begin bgfx_vertex_layout_begin;
		
		/**
		 * Add attribute to VertexLayout.
		 * Remarks: Must be called between begin/end.
		 * Params:
		 * _attrib = Attribute semantics. See: `bgfx::Attrib`
		 * _num = Number of elements 1, 2, 3 or 4.
		 * _type = Element type.
		 * _normalized = When using fixed point AttribType (f.e. Uint8)
		 * value will be normalized for vertex shader usage. When normalized
		 * is set to true, AttribType::Uint8 value in range 0-255 will be
		 * in range 0.0-1.0 in vertex shader.
		 * _asInt = Packaging rule for vertexPack, vertexUnpack, and
		 * vertexConvert for AttribType::Uint8 and AttribType::Int16.
		 * Unpacking code must be implemented inside vertex shader.
		 */
		alias da_bgfx_vertex_layout_add = bgfx_vertex_layout_t* function(bgfx_vertex_layout_t* _this, bgfx_attrib_t _attrib, ubyte _num, bgfx_attrib_type_t _type, bool _normalized, bool _asInt);
		da_bgfx_vertex_layout_add bgfx_vertex_layout_add;
		
		/**
		 * Decode attribute.
		 * Params:
		 * _attrib = Attribute semantics. See: `bgfx::Attrib`
		 * _num = Number of elements.
		 * _type = Element type.
		 * _normalized = Attribute is normalized.
		 * _asInt = Attribute is packed as int.
		 */
		alias da_bgfx_vertex_layout_decode = void function(const(bgfx_vertex_layout_t)* _this, bgfx_attrib_t _attrib, ubyte* _num, bgfx_attrib_type_t* _type, bool* _normalized, bool* _asInt);
		da_bgfx_vertex_layout_decode bgfx_vertex_layout_decode;
		
		/**
		 * Returns `true` if VertexLayout contains attribute.
		 * Params:
		 * _attrib = Attribute semantics. See: `bgfx::Attrib`
		 */
		alias da_bgfx_vertex_layout_has = bool function(const(bgfx_vertex_layout_t)* _this, bgfx_attrib_t _attrib);
		da_bgfx_vertex_layout_has bgfx_vertex_layout_has;
		
		/**
		 * Skip `_num` bytes in vertex stream.
		 * Params:
		 * _num = Number of bytes to skip.
		 */
		alias da_bgfx_vertex_layout_skip = bgfx_vertex_layout_t* function(bgfx_vertex_layout_t* _this, ubyte _num);
		da_bgfx_vertex_layout_skip bgfx_vertex_layout_skip;
		
		/**
		 * End VertexLayout.
		 */
		alias da_bgfx_vertex_layout_end = void function(bgfx_vertex_layout_t* _this);
		da_bgfx_vertex_layout_end bgfx_vertex_layout_end;
		
		/**
		 * Pack vertex attribute into vertex stream format.
		 * Params:
		 * _input = Value to be packed into vertex stream.
		 * _inputNormalized = `true` if input value is already normalized.
		 * _attr = Attribute to pack.
		 * _layout = Vertex stream layout.
		 * _data = Destination vertex stream where data will be packed.
		 * _index = Vertex index that will be modified.
		 */
		alias da_bgfx_vertex_pack = void function(const float[4] _input, bool _inputNormalized, bgfx_attrib_t _attr, const(bgfx_vertex_layout_t)* _layout, void* _data, uint _index);
		da_bgfx_vertex_pack bgfx_vertex_pack;
		
		/**
		 * Unpack vertex attribute from vertex stream format.
		 * Params:
		 * _output = Result of unpacking.
		 * _attr = Attribute to unpack.
		 * _layout = Vertex stream layout.
		 * _data = Source vertex stream from where data will be unpacked.
		 * _index = Vertex index that will be unpacked.
		 */
		alias da_bgfx_vertex_unpack = void function(float[4] _output, bgfx_attrib_t _attr, const(bgfx_vertex_layout_t)* _layout, const(void)* _data, uint _index);
		da_bgfx_vertex_unpack bgfx_vertex_unpack;
		
		/**
		 * Converts vertex stream data from one vertex stream format to another.
		 * Params:
		 * _dstLayout = Destination vertex stream layout.
		 * _dstData = Destination vertex stream.
		 * _srcLayout = Source vertex stream layout.
		 * _srcData = Source vertex stream data.
		 * _num = Number of vertices to convert from source to destination.
		 */
		alias da_bgfx_vertex_convert = void function(const(bgfx_vertex_layout_t)* _dstLayout, void* _dstData, const(bgfx_vertex_layout_t)* _srcLayout, const(void)* _srcData, uint _num);
		da_bgfx_vertex_convert bgfx_vertex_convert;
		
		/**
		 * Weld vertices.
		 * Params:
		 * _output = Welded vertices remapping table. The size of buffer
		 * must be the same as number of vertices.
		 * _layout = Vertex stream layout.
		 * _data = Vertex stream.
		 * _num = Number of vertices in vertex stream.
		 * _index32 = Set to `true` if input indices are 32-bit.
		 * _epsilon = Error tolerance for vertex position comparison.
		 */
		alias da_bgfx_weld_vertices = uint function(void* _output, const(bgfx_vertex_layout_t)* _layout, const(void)* _data, uint _num, bool _index32, float _epsilon);
		da_bgfx_weld_vertices bgfx_weld_vertices;
		
		/**
		 * Convert index buffer for use with different primitive topologies.
		 * Params:
		 * _conversion = Conversion type, see `TopologyConvert::Enum`.
		 * _dst = Destination index buffer. If this argument is NULL
		 * function will return number of indices after conversion.
		 * _dstSize = Destination index buffer in bytes. It must be
		 * large enough to contain output indices. If destination size is
		 * insufficient index buffer will be truncated.
		 * _indices = Source indices.
		 * _numIndices = Number of input indices.
		 * _index32 = Set to `true` if input indices are 32-bit.
		 */
		alias da_bgfx_topology_convert = uint function(bgfx_topology_convert_t _conversion, void* _dst, uint _dstSize, const(void)* _indices, uint _numIndices, bool _index32);
		da_bgfx_topology_convert bgfx_topology_convert;
		
		/**
		 * Sort indices.
		 * Params:
		 * _sort = Sort order, see `TopologySort::Enum`.
		 * _dst = Destination index buffer.
		 * _dstSize = Destination index buffer in bytes. It must be
		 * large enough to contain output indices. If destination size is
		 * insufficient index buffer will be truncated.
		 * _dir = Direction (vector must be normalized).
		 * _pos = Position.
		 * _vertices = Pointer to first vertex represented as
		 * float x, y, z. Must contain at least number of vertices
		 * referencende by index buffer.
		 * _stride = Vertex stride.
		 * _indices = Source indices.
		 * _numIndices = Number of input indices.
		 * _index32 = Set to `true` if input indices are 32-bit.
		 */
		alias da_bgfx_topology_sort_tri_list = void function(bgfx_topology_sort_t _sort, void* _dst, uint _dstSize, const float[3] _dir, const float[3] _pos, const(void)* _vertices, uint _stride, const(void)* _indices, uint _numIndices, bool _index32);
		da_bgfx_topology_sort_tri_list bgfx_topology_sort_tri_list;
		
		/**
		 * Returns supported backend API renderers.
		 * Params:
		 * _max = Maximum number of elements in _enum array.
		 * _enum = Array where supported renderers will be written.
		 */
		alias da_bgfx_get_supported_renderers = ubyte function(ubyte _max, bgfx_renderer_type_t* _enum);
		da_bgfx_get_supported_renderers bgfx_get_supported_renderers;
		
		/**
		 * Returns name of renderer.
		 * Params:
		 * _type = Renderer backend type. See: `bgfx::RendererType`
		 */
		alias da_bgfx_get_renderer_name = const(char)* function(bgfx_renderer_type_t _type);
		da_bgfx_get_renderer_name bgfx_get_renderer_name;
		
		alias da_bgfx_init_ctor = void function(bgfx_init_t* _init);
		da_bgfx_init_ctor bgfx_init_ctor;
		
		/**
		 * Initialize the bgfx library.
		 * Params:
		 * _init = Initialization parameters. See: `bgfx::Init` for more info.
		 */
		alias da_bgfx_init = bool function(const(bgfx_init_t)* _init);
		da_bgfx_init bgfx_init;
		
		/**
		 * Shutdown bgfx library.
		 */
		alias da_bgfx_shutdown = void function();
		da_bgfx_shutdown bgfx_shutdown;
		
		/**
		 * Reset graphic settings and back-buffer size.
		 * Attention: This call doesn’t change the window size, it just resizes
		 *   the back-buffer. Your windowing code controls the window size.
		 * Params:
		 * _width = Back-buffer width.
		 * _height = Back-buffer height.
		 * _flags = See: `BGFX_RESET_*` for more info.
		 *   - `BGFX_RESET_NONE` - No reset flags.
		 *   - `BGFX_RESET_FULLSCREEN` - Not supported yet.
		 *   - `BGFX_RESET_MSAA_X[2/4/8/16]` - Enable 2, 4, 8 or 16 x MSAA.
		 *   - `BGFX_RESET_VSYNC` - Enable V-Sync.
		 *   - `BGFX_RESET_MAXANISOTROPY` - Turn on/off max anisotropy.
		 *   - `BGFX_RESET_CAPTURE` - Begin screen capture.
		 *   - `BGFX_RESET_FLUSH_AFTER_RENDER` - Flush rendering after submitting to GPU.
		 *   - `BGFX_RESET_FLIP_AFTER_RENDER` - This flag  specifies where flip
		 *     occurs. Default behaviour is that flip occurs before rendering new
		 *     frame. This flag only has effect when `BGFX_CONFIG_MULTITHREADED=0`.
		 *   - `BGFX_RESET_SRGB_BACKBUFFER` - Enable sRGB back-buffer.
		 * _format = Texture format. See: `TextureFormat::Enum`.
		 */
		alias da_bgfx_reset = void function(uint _width, uint _height, uint _flags, bgfx_texture_format_t _format);
		da_bgfx_reset bgfx_reset;
		
		/**
		 * Advance to next frame. When using multithreaded renderer, this call
		 * just swaps internal buffers, kicks render thread, and returns. In
		 * singlethreaded renderer this call does frame rendering.
		 * Params:
		 * _capture = Capture frame with graphics debugger.
		 */
		alias da_bgfx_frame = uint function(bool _capture);
		da_bgfx_frame bgfx_frame;
		
		/**
		 * Returns current renderer backend API type.
		 * Remarks:
		 *   Library must be initialized.
		 */
		alias da_bgfx_get_renderer_type = bgfx_renderer_type_t function();
		da_bgfx_get_renderer_type bgfx_get_renderer_type;
		
		/**
		 * Returns renderer capabilities.
		 * Remarks:
		 *   Library must be initialized.
		 */
		alias da_bgfx_get_caps = const(bgfx_caps_t)* function();
		da_bgfx_get_caps bgfx_get_caps;
		
		/**
		 * Returns performance counters.
		 * Attention: Pointer returned is valid until `bgfx::frame` is called.
		 */
		alias da_bgfx_get_stats = const(bgfx_stats_t)* function();
		da_bgfx_get_stats bgfx_get_stats;
		
		/**
		 * Allocate buffer to pass to bgfx calls. Data will be freed inside bgfx.
		 * Params:
		 * _size = Size to allocate.
		 */
		alias da_bgfx_alloc = const(bgfx_memory_t)* function(uint _size);
		da_bgfx_alloc bgfx_alloc;
		
		/**
		 * Allocate buffer and copy data into it. Data will be freed inside bgfx.
		 * Params:
		 * _data = Pointer to data to be copied.
		 * _size = Size of data to be copied.
		 */
		alias da_bgfx_copy = const(bgfx_memory_t)* function(const(void)* _data, uint _size);
		da_bgfx_copy bgfx_copy;
		
		/**
		 * Make reference to data to pass to bgfx. Unlike `bgfx::alloc`, this call
		 * doesn't allocate memory for data. It just copies the _data pointer. You
		 * can pass `ReleaseFn` function pointer to release this memory after it's
		 * consumed, otherwise you must make sure _data is available for at least 2
		 * `bgfx::frame` calls. `ReleaseFn` function must be able to be called
		 * from any thread.
		 * Attention: Data passed must be available for at least 2 `bgfx::frame` calls.
		 * Params:
		 * _data = Pointer to data.
		 * _size = Size of data.
		 */
		alias da_bgfx_make_ref = const(bgfx_memory_t)* function(const(void)* _data, uint _size);
		da_bgfx_make_ref bgfx_make_ref;
		
		/**
		 * Make reference to data to pass to bgfx. Unlike `bgfx::alloc`, this call
		 * doesn't allocate memory for data. It just copies the _data pointer. You
		 * can pass `ReleaseFn` function pointer to release this memory after it's
		 * consumed, otherwise you must make sure _data is available for at least 2
		 * `bgfx::frame` calls. `ReleaseFn` function must be able to be called
		 * from any thread.
		 * Attention: Data passed must be available for at least 2 `bgfx::frame` calls.
		 * Params:
		 * _data = Pointer to data.
		 * _size = Size of data.
		 * _releaseFn = Callback function to release memory after use.
		 * _userData = User data to be passed to callback function.
		 */
		alias da_bgfx_make_ref_release = const(bgfx_memory_t)* function(const(void)* _data, uint _size, void* _releaseFn, void* _userData);
		da_bgfx_make_ref_release bgfx_make_ref_release;
		
		/**
		 * Set debug flags.
		 * Params:
		 * _debug = Available flags:
		 *   - `BGFX_DEBUG_IFH` - Infinitely fast hardware. When this flag is set
		 *     all rendering calls will be skipped. This is useful when profiling
		 *     to quickly assess potential bottlenecks between CPU and GPU.
		 *   - `BGFX_DEBUG_PROFILER` - Enable profiler.
		 *   - `BGFX_DEBUG_STATS` - Display internal statistics.
		 *   - `BGFX_DEBUG_TEXT` - Display debug text.
		 *   - `BGFX_DEBUG_WIREFRAME` - Wireframe rendering. All rendering
		 *     primitives will be rendered as lines.
		 */
		alias da_bgfx_set_debug = void function(uint _debug);
		da_bgfx_set_debug bgfx_set_debug;
		
		/**
		 * Clear internal debug text buffer.
		 * Params:
		 * _attr = Background color.
		 * _small = Default 8x16 or 8x8 font.
		 */
		alias da_bgfx_dbg_text_clear = void function(ubyte _attr, bool _small);
		da_bgfx_dbg_text_clear bgfx_dbg_text_clear;
		
		/**
		 * Print formatted data to internal debug text character-buffer (VGA-compatible text mode).
		 * Params:
		 * _x = Position x from the left corner of the window.
		 * _y = Position y from the top corner of the window.
		 * _attr = Color palette. Where top 4-bits represent index of background, and bottom
		 * 4-bits represent foreground color from standard VGA text palette (ANSI escape codes).
		 * _format = `printf` style format.
		 */
		alias da_bgfx_dbg_text_printf = void function(ushort _x, ushort _y, ubyte _attr, const(char)* _format, ... );
		da_bgfx_dbg_text_printf bgfx_dbg_text_printf;
		
		/**
		 * Print formatted data from variable argument list to internal debug text character-buffer (VGA-compatible text mode).
		 * Params:
		 * _x = Position x from the left corner of the window.
		 * _y = Position y from the top corner of the window.
		 * _attr = Color palette. Where top 4-bits represent index of background, and bottom
		 * 4-bits represent foreground color from standard VGA text palette (ANSI escape codes).
		 * _format = `printf` style format.
		 * _argList = Variable arguments list for format string.
		 */
		alias da_bgfx_dbg_text_vprintf = void function(ushort _x, ushort _y, ubyte _attr, const(char)* _format, va_list _argList);
		da_bgfx_dbg_text_vprintf bgfx_dbg_text_vprintf;
		
		/**
		 * Draw image into internal debug text buffer.
		 * Params:
		 * _x = Position x from the left corner of the window.
		 * _y = Position y from the top corner of the window.
		 * _width = Image width.
		 * _height = Image height.
		 * _data = Raw image data (character/attribute raw encoding).
		 * _pitch = Image pitch in bytes.
		 */
		alias da_bgfx_dbg_text_image = void function(ushort _x, ushort _y, ushort _width, ushort _height, const(void)* _data, ushort _pitch);
		da_bgfx_dbg_text_image bgfx_dbg_text_image;
		
		/**
		 * Create static index buffer.
		 * Params:
		 * _mem = Index buffer data.
		 * _flags = Buffer creation flags.
		 *   - `BGFX_BUFFER_NONE` - No flags.
		 *   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
		 *   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
		 *       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
		 *   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
		 *   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
		 *       data is passed. If this flag is not specified, and more data is passed on update, the buffer
		 *       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
		 *       buffers.
		 *   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
		 *       index buffers.
		 */
		alias da_bgfx_create_index_buffer = bgfx_index_buffer_handle_t function(const(bgfx_memory_t)* _mem, ushort _flags);
		da_bgfx_create_index_buffer bgfx_create_index_buffer;
		
		/**
		 * Set static index buffer debug name.
		 * Params:
		 * _handle = Static index buffer handle.
		 * _name = Static index buffer name.
		 * _len = Static index buffer name length (if length is INT32_MAX, it's expected
		 * that _name is zero terminated string.
		 */
		alias da_bgfx_set_index_buffer_name = void function(bgfx_index_buffer_handle_t _handle, const(char)* _name, int _len);
		da_bgfx_set_index_buffer_name bgfx_set_index_buffer_name;
		
		/**
		 * Destroy static index buffer.
		 * Params:
		 * _handle = Static index buffer handle.
		 */
		alias da_bgfx_destroy_index_buffer = void function(bgfx_index_buffer_handle_t _handle);
		da_bgfx_destroy_index_buffer bgfx_destroy_index_buffer;
		
		/**
		 * Create vertex layout.
		 * Params:
		 * _layout = Vertex layout.
		 */
		alias da_bgfx_create_vertex_layout = bgfx_vertex_layout_handle_t function(const(bgfx_vertex_layout_t)* _layout);
		da_bgfx_create_vertex_layout bgfx_create_vertex_layout;
		
		/**
		 * Destroy vertex layout.
		 * Params:
		 * _layoutHandle = Vertex layout handle.
		 */
		alias da_bgfx_destroy_vertex_layout = void function(bgfx_vertex_layout_handle_t _layoutHandle);
		da_bgfx_destroy_vertex_layout bgfx_destroy_vertex_layout;
		
		/**
		 * Create static vertex buffer.
		 * Params:
		 * _mem = Vertex buffer data.
		 * _layout = Vertex layout.
		 * _flags = Buffer creation flags.
		 *  - `BGFX_BUFFER_NONE` - No flags.
		 *  - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
		 *  - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
		 *      is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
		 *  - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
		 *  - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
		 *      data is passed. If this flag is not specified, and more data is passed on update, the buffer
		 *      will be trimmed to fit the existing buffer size. This flag has effect only on dynamic buffers.
		 *  - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on index buffers.
		 */
		alias da_bgfx_create_vertex_buffer = bgfx_vertex_buffer_handle_t function(const(bgfx_memory_t)* _mem, const(bgfx_vertex_layout_t)* _layout, ushort _flags);
		da_bgfx_create_vertex_buffer bgfx_create_vertex_buffer;
		
		/**
		 * Set static vertex buffer debug name.
		 * Params:
		 * _handle = Static vertex buffer handle.
		 * _name = Static vertex buffer name.
		 * _len = Static vertex buffer name length (if length is INT32_MAX, it's expected
		 * that _name is zero terminated string.
		 */
		alias da_bgfx_set_vertex_buffer_name = void function(bgfx_vertex_buffer_handle_t _handle, const(char)* _name, int _len);
		da_bgfx_set_vertex_buffer_name bgfx_set_vertex_buffer_name;
		
		/**
		 * Destroy static vertex buffer.
		 * Params:
		 * _handle = Static vertex buffer handle.
		 */
		alias da_bgfx_destroy_vertex_buffer = void function(bgfx_vertex_buffer_handle_t _handle);
		da_bgfx_destroy_vertex_buffer bgfx_destroy_vertex_buffer;
		
		/**
		 * Create empty dynamic index buffer.
		 * Params:
		 * _num = Number of indices.
		 * _flags = Buffer creation flags.
		 *   - `BGFX_BUFFER_NONE` - No flags.
		 *   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
		 *   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
		 *       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
		 *   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
		 *   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
		 *       data is passed. If this flag is not specified, and more data is passed on update, the buffer
		 *       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
		 *       buffers.
		 *   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
		 *       index buffers.
		 */
		alias da_bgfx_create_dynamic_index_buffer = bgfx_dynamic_index_buffer_handle_t function(uint _num, ushort _flags);
		da_bgfx_create_dynamic_index_buffer bgfx_create_dynamic_index_buffer;
		
		/**
		 * Create a dynamic index buffer and initialize it.
		 * Params:
		 * _mem = Index buffer data.
		 * _flags = Buffer creation flags.
		 *   - `BGFX_BUFFER_NONE` - No flags.
		 *   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
		 *   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
		 *       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
		 *   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
		 *   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
		 *       data is passed. If this flag is not specified, and more data is passed on update, the buffer
		 *       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
		 *       buffers.
		 *   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
		 *       index buffers.
		 */
		alias da_bgfx_create_dynamic_index_buffer_mem = bgfx_dynamic_index_buffer_handle_t function(const(bgfx_memory_t)* _mem, ushort _flags);
		da_bgfx_create_dynamic_index_buffer_mem bgfx_create_dynamic_index_buffer_mem;
		
		/**
		 * Update dynamic index buffer.
		 * Params:
		 * _handle = Dynamic index buffer handle.
		 * _startIndex = Start index.
		 * _mem = Index buffer data.
		 */
		alias da_bgfx_update_dynamic_index_buffer = void function(bgfx_dynamic_index_buffer_handle_t _handle, uint _startIndex, const(bgfx_memory_t)* _mem);
		da_bgfx_update_dynamic_index_buffer bgfx_update_dynamic_index_buffer;
		
		/**
		 * Destroy dynamic index buffer.
		 * Params:
		 * _handle = Dynamic index buffer handle.
		 */
		alias da_bgfx_destroy_dynamic_index_buffer = void function(bgfx_dynamic_index_buffer_handle_t _handle);
		da_bgfx_destroy_dynamic_index_buffer bgfx_destroy_dynamic_index_buffer;
		
		/**
		 * Create empty dynamic vertex buffer.
		 * Params:
		 * _num = Number of vertices.
		 * _layout = Vertex layout.
		 * _flags = Buffer creation flags.
		 *   - `BGFX_BUFFER_NONE` - No flags.
		 *   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
		 *   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
		 *       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
		 *   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
		 *   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
		 *       data is passed. If this flag is not specified, and more data is passed on update, the buffer
		 *       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
		 *       buffers.
		 *   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
		 *       index buffers.
		 */
		alias da_bgfx_create_dynamic_vertex_buffer = bgfx_dynamic_vertex_buffer_handle_t function(uint _num, const(bgfx_vertex_layout_t)* _layout, ushort _flags);
		da_bgfx_create_dynamic_vertex_buffer bgfx_create_dynamic_vertex_buffer;
		
		/**
		 * Create dynamic vertex buffer and initialize it.
		 * Params:
		 * _mem = Vertex buffer data.
		 * _layout = Vertex layout.
		 * _flags = Buffer creation flags.
		 *   - `BGFX_BUFFER_NONE` - No flags.
		 *   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
		 *   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
		 *       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
		 *   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
		 *   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
		 *       data is passed. If this flag is not specified, and more data is passed on update, the buffer
		 *       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
		 *       buffers.
		 *   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
		 *       index buffers.
		 */
		alias da_bgfx_create_dynamic_vertex_buffer_mem = bgfx_dynamic_vertex_buffer_handle_t function(const(bgfx_memory_t)* _mem, const(bgfx_vertex_layout_t)* _layout, ushort _flags);
		da_bgfx_create_dynamic_vertex_buffer_mem bgfx_create_dynamic_vertex_buffer_mem;
		
		/**
		 * Update dynamic vertex buffer.
		 * Params:
		 * _handle = Dynamic vertex buffer handle.
		 * _startVertex = Start vertex.
		 * _mem = Vertex buffer data.
		 */
		alias da_bgfx_update_dynamic_vertex_buffer = void function(bgfx_dynamic_vertex_buffer_handle_t _handle, uint _startVertex, const(bgfx_memory_t)* _mem);
		da_bgfx_update_dynamic_vertex_buffer bgfx_update_dynamic_vertex_buffer;
		
		/**
		 * Destroy dynamic vertex buffer.
		 * Params:
		 * _handle = Dynamic vertex buffer handle.
		 */
		alias da_bgfx_destroy_dynamic_vertex_buffer = void function(bgfx_dynamic_vertex_buffer_handle_t _handle);
		da_bgfx_destroy_dynamic_vertex_buffer bgfx_destroy_dynamic_vertex_buffer;
		
		/**
		 * Returns number of requested or maximum available indices.
		 * Params:
		 * _num = Number of required indices.
		 * _index32 = Set to `true` if input indices will be 32-bit.
		 */
		alias da_bgfx_get_avail_transient_index_buffer = uint function(uint _num, bool _index32);
		da_bgfx_get_avail_transient_index_buffer bgfx_get_avail_transient_index_buffer;
		
		/**
		 * Returns number of requested or maximum available vertices.
		 * Params:
		 * _num = Number of required vertices.
		 * _layout = Vertex layout.
		 */
		alias da_bgfx_get_avail_transient_vertex_buffer = uint function(uint _num, const(bgfx_vertex_layout_t)* _layout);
		da_bgfx_get_avail_transient_vertex_buffer bgfx_get_avail_transient_vertex_buffer;
		
		/**
		 * Returns number of requested or maximum available instance buffer slots.
		 * Params:
		 * _num = Number of required instances.
		 * _stride = Stride per instance.
		 */
		alias da_bgfx_get_avail_instance_data_buffer = uint function(uint _num, ushort _stride);
		da_bgfx_get_avail_instance_data_buffer bgfx_get_avail_instance_data_buffer;
		
		/**
		 * Allocate transient index buffer.
		 * Params:
		 * _tib = TransientIndexBuffer structure is filled and is valid
		 * for the duration of frame, and it can be reused for multiple draw
		 * calls.
		 * _num = Number of indices to allocate.
		 * _index32 = Set to `true` if input indices will be 32-bit.
		 */
		alias da_bgfx_alloc_transient_index_buffer = void function(bgfx_transient_index_buffer_t* _tib, uint _num, bool _index32);
		da_bgfx_alloc_transient_index_buffer bgfx_alloc_transient_index_buffer;
		
		/**
		 * Allocate transient vertex buffer.
		 * Params:
		 * _tvb = TransientVertexBuffer structure is filled and is valid
		 * for the duration of frame, and it can be reused for multiple draw
		 * calls.
		 * _num = Number of vertices to allocate.
		 * _layout = Vertex layout.
		 */
		alias da_bgfx_alloc_transient_vertex_buffer = void function(bgfx_transient_vertex_buffer_t* _tvb, uint _num, const(bgfx_vertex_layout_t)* _layout);
		da_bgfx_alloc_transient_vertex_buffer bgfx_alloc_transient_vertex_buffer;
		
		/**
		 * Check for required space and allocate transient vertex and index
		 * buffers. If both space requirements are satisfied function returns
		 * true.
		 * Params:
		 * _tvb = TransientVertexBuffer structure is filled and is valid
		 * for the duration of frame, and it can be reused for multiple draw
		 * calls.
		 * _layout = Vertex layout.
		 * _numVertices = Number of vertices to allocate.
		 * _tib = TransientIndexBuffer structure is filled and is valid
		 * for the duration of frame, and it can be reused for multiple draw
		 * calls.
		 * _numIndices = Number of indices to allocate.
		 * _index32 = Set to `true` if input indices will be 32-bit.
		 */
		alias da_bgfx_alloc_transient_buffers = bool function(bgfx_transient_vertex_buffer_t* _tvb, const(bgfx_vertex_layout_t)* _layout, uint _numVertices, bgfx_transient_index_buffer_t* _tib, uint _numIndices, bool _index32);
		da_bgfx_alloc_transient_buffers bgfx_alloc_transient_buffers;
		
		/**
		 * Allocate instance data buffer.
		 * Params:
		 * _idb = InstanceDataBuffer structure is filled and is valid
		 * for duration of frame, and it can be reused for multiple draw
		 * calls.
		 * _num = Number of instances.
		 * _stride = Instance stride. Must be multiple of 16.
		 */
		alias da_bgfx_alloc_instance_data_buffer = void function(bgfx_instance_data_buffer_t* _idb, uint _num, ushort _stride);
		da_bgfx_alloc_instance_data_buffer bgfx_alloc_instance_data_buffer;
		
		/**
		 * Create draw indirect buffer.
		 * Params:
		 * _num = Number of indirect calls.
		 */
		alias da_bgfx_create_indirect_buffer = bgfx_indirect_buffer_handle_t function(uint _num);
		da_bgfx_create_indirect_buffer bgfx_create_indirect_buffer;
		
		/**
		 * Destroy draw indirect buffer.
		 * Params:
		 * _handle = Indirect buffer handle.
		 */
		alias da_bgfx_destroy_indirect_buffer = void function(bgfx_indirect_buffer_handle_t _handle);
		da_bgfx_destroy_indirect_buffer bgfx_destroy_indirect_buffer;
		
		/**
		 * Create shader from memory buffer.
		 * Params:
		 * _mem = Shader binary.
		 */
		alias da_bgfx_create_shader = bgfx_shader_handle_t function(const(bgfx_memory_t)* _mem);
		da_bgfx_create_shader bgfx_create_shader;
		
		/**
		 * Returns the number of uniforms and uniform handles used inside a shader.
		 * Remarks:
		 *   Only non-predefined uniforms are returned.
		 * Params:
		 * _handle = Shader handle.
		 * _uniforms = UniformHandle array where data will be stored.
		 * _max = Maximum capacity of array.
		 */
		alias da_bgfx_get_shader_uniforms = ushort function(bgfx_shader_handle_t _handle, bgfx_uniform_handle_t* _uniforms, ushort _max);
		da_bgfx_get_shader_uniforms bgfx_get_shader_uniforms;
		
		/**
		 * Set shader debug name.
		 * Params:
		 * _handle = Shader handle.
		 * _name = Shader name.
		 * _len = Shader name length (if length is INT32_MAX, it's expected
		 * that _name is zero terminated string).
		 */
		alias da_bgfx_set_shader_name = void function(bgfx_shader_handle_t _handle, const(char)* _name, int _len);
		da_bgfx_set_shader_name bgfx_set_shader_name;
		
		/**
		 * Destroy shader.
		 * Remarks: Once a shader program is created with _handle,
		 *   it is safe to destroy that shader.
		 * Params:
		 * _handle = Shader handle.
		 */
		alias da_bgfx_destroy_shader = void function(bgfx_shader_handle_t _handle);
		da_bgfx_destroy_shader bgfx_destroy_shader;
		
		/**
		 * Create program with vertex and fragment shaders.
		 * Params:
		 * _vsh = Vertex shader.
		 * _fsh = Fragment shader.
		 * _destroyShaders = If true, shaders will be destroyed when program is destroyed.
		 */
		alias da_bgfx_create_program = bgfx_program_handle_t function(bgfx_shader_handle_t _vsh, bgfx_shader_handle_t _fsh, bool _destroyShaders);
		da_bgfx_create_program bgfx_create_program;
		
		/**
		 * Create program with compute shader.
		 * Params:
		 * _csh = Compute shader.
		 * _destroyShaders = If true, shaders will be destroyed when program is destroyed.
		 */
		alias da_bgfx_create_compute_program = bgfx_program_handle_t function(bgfx_shader_handle_t _csh, bool _destroyShaders);
		da_bgfx_create_compute_program bgfx_create_compute_program;
		
		/**
		 * Destroy program.
		 * Params:
		 * _handle = Program handle.
		 */
		alias da_bgfx_destroy_program = void function(bgfx_program_handle_t _handle);
		da_bgfx_destroy_program bgfx_destroy_program;
		
		/**
		 * Validate texture parameters.
		 * Params:
		 * _depth = Depth dimension of volume texture.
		 * _cubeMap = Indicates that texture contains cubemap.
		 * _numLayers = Number of layers in texture array.
		 * _format = Texture format. See: `TextureFormat::Enum`.
		 * _flags = Texture flags. See `BGFX_TEXTURE_*`.
		 */
		alias da_bgfx_is_texture_valid = bool function(ushort _depth, bool _cubeMap, ushort _numLayers, bgfx_texture_format_t _format, ulong _flags);
		da_bgfx_is_texture_valid bgfx_is_texture_valid;
		
		/**
		 * Validate frame buffer parameters.
		 * Params:
		 * _num = Number of attachments.
		 * _attachment = Attachment texture info. See: `bgfx::Attachment`.
		 */
		alias da_bgfx_is_frame_buffer_valid = bool function(ubyte _num, const(bgfx_attachment_t)* _attachment);
		da_bgfx_is_frame_buffer_valid bgfx_is_frame_buffer_valid;
		
		/**
		 * Calculate amount of memory required for texture.
		 * Params:
		 * _info = Resulting texture info structure. See: `TextureInfo`.
		 * _width = Width.
		 * _height = Height.
		 * _depth = Depth dimension of volume texture.
		 * _cubeMap = Indicates that texture contains cubemap.
		 * _hasMips = Indicates that texture contains full mip-map chain.
		 * _numLayers = Number of layers in texture array.
		 * _format = Texture format. See: `TextureFormat::Enum`.
		 */
		alias da_bgfx_calc_texture_size = void function(bgfx_texture_info_t* _info, ushort _width, ushort _height, ushort _depth, bool _cubeMap, bool _hasMips, ushort _numLayers, bgfx_texture_format_t _format);
		da_bgfx_calc_texture_size bgfx_calc_texture_size;
		
		/**
		 * Create texture from memory buffer.
		 * Params:
		 * _mem = DDS, KTX or PVR texture binary data.
		 * _flags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
		 * flags. Default texture sampling mode is linear, and wrap mode is repeat.
		 * - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		 *   mode.
		 * - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		 *   sampling.
		 * _skip = Skip top level mips when parsing texture.
		 * _info = When non-`NULL` is specified it returns parsed texture information.
		 */
		alias da_bgfx_create_texture = bgfx_texture_handle_t function(const(bgfx_memory_t)* _mem, ulong _flags, ubyte _skip, bgfx_texture_info_t* _info);
		da_bgfx_create_texture bgfx_create_texture;
		
		/**
		 * Create 2D texture.
		 * Params:
		 * _width = Width.
		 * _height = Height.
		 * _hasMips = Indicates that texture contains full mip-map chain.
		 * _numLayers = Number of layers in texture array. Must be 1 if caps
		 * `BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.
		 * _format = Texture format. See: `TextureFormat::Enum`.
		 * _flags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
		 * flags. Default texture sampling mode is linear, and wrap mode is repeat.
		 * - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		 *   mode.
		 * - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		 *   sampling.
		 * _mem = Texture data. If `_mem` is non-NULL, created texture will be immutable. If
		 * `_mem` is NULL content of the texture is uninitialized. When `_numLayers` is more than
		 * 1, expected memory layout is texture and all mips together for each array element.
		 */
		alias da_bgfx_create_texture_2d = bgfx_texture_handle_t function(ushort _width, ushort _height, bool _hasMips, ushort _numLayers, bgfx_texture_format_t _format, ulong _flags, const(bgfx_memory_t)* _mem);
		da_bgfx_create_texture_2d bgfx_create_texture_2d;
		
		/**
		 * Create texture with size based on back-buffer ratio. Texture will maintain ratio
		 * if back buffer resolution changes.
		 * Params:
		 * _ratio = Texture size in respect to back-buffer size. See: `BackbufferRatio::Enum`.
		 * _hasMips = Indicates that texture contains full mip-map chain.
		 * _numLayers = Number of layers in texture array. Must be 1 if caps
		 * `BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.
		 * _format = Texture format. See: `TextureFormat::Enum`.
		 * _flags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
		 * flags. Default texture sampling mode is linear, and wrap mode is repeat.
		 * - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		 *   mode.
		 * - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		 *   sampling.
		 */
		alias da_bgfx_create_texture_2d_scaled = bgfx_texture_handle_t function(bgfx_backbuffer_ratio_t _ratio, bool _hasMips, ushort _numLayers, bgfx_texture_format_t _format, ulong _flags);
		da_bgfx_create_texture_2d_scaled bgfx_create_texture_2d_scaled;
		
		/**
		 * Create 3D texture.
		 * Params:
		 * _width = Width.
		 * _height = Height.
		 * _depth = Depth.
		 * _hasMips = Indicates that texture contains full mip-map chain.
		 * _format = Texture format. See: `TextureFormat::Enum`.
		 * _flags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
		 * flags. Default texture sampling mode is linear, and wrap mode is repeat.
		 * - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		 *   mode.
		 * - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		 *   sampling.
		 * _mem = Texture data. If `_mem` is non-NULL, created texture will be immutable. If
		 * `_mem` is NULL content of the texture is uninitialized. When `_numLayers` is more than
		 * 1, expected memory layout is texture and all mips together for each array element.
		 */
		alias da_bgfx_create_texture_3d = bgfx_texture_handle_t function(ushort _width, ushort _height, ushort _depth, bool _hasMips, bgfx_texture_format_t _format, ulong _flags, const(bgfx_memory_t)* _mem);
		da_bgfx_create_texture_3d bgfx_create_texture_3d;
		
		/**
		 * Create Cube texture.
		 * Params:
		 * _size = Cube side size.
		 * _hasMips = Indicates that texture contains full mip-map chain.
		 * _numLayers = Number of layers in texture array. Must be 1 if caps
		 * `BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.
		 * _format = Texture format. See: `TextureFormat::Enum`.
		 * _flags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
		 * flags. Default texture sampling mode is linear, and wrap mode is repeat.
		 * - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		 *   mode.
		 * - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		 *   sampling.
		 * _mem = Texture data. If `_mem` is non-NULL, created texture will be immutable. If
		 * `_mem` is NULL content of the texture is uninitialized. When `_numLayers` is more than
		 * 1, expected memory layout is texture and all mips together for each array element.
		 */
		alias da_bgfx_create_texture_cube = bgfx_texture_handle_t function(ushort _size, bool _hasMips, ushort _numLayers, bgfx_texture_format_t _format, ulong _flags, const(bgfx_memory_t)* _mem);
		da_bgfx_create_texture_cube bgfx_create_texture_cube;
		
		/**
		 * Update 2D texture.
		 * Attention: It's valid to update only mutable texture. See `bgfx::createTexture2D` for more info.
		 * Params:
		 * _handle = Texture handle.
		 * _layer = Layer in texture array.
		 * _mip = Mip level.
		 * _x = X offset in texture.
		 * _y = Y offset in texture.
		 * _width = Width of texture block.
		 * _height = Height of texture block.
		 * _mem = Texture update data.
		 * _pitch = Pitch of input image (bytes). When _pitch is set to
		 * UINT16_MAX, it will be calculated internally based on _width.
		 */
		alias da_bgfx_update_texture_2d = void function(bgfx_texture_handle_t _handle, ushort _layer, ubyte _mip, ushort _x, ushort _y, ushort _width, ushort _height, const(bgfx_memory_t)* _mem, ushort _pitch);
		da_bgfx_update_texture_2d bgfx_update_texture_2d;
		
		/**
		 * Update 3D texture.
		 * Attention: It's valid to update only mutable texture. See `bgfx::createTexture3D` for more info.
		 * Params:
		 * _handle = Texture handle.
		 * _mip = Mip level.
		 * _x = X offset in texture.
		 * _y = Y offset in texture.
		 * _z = Z offset in texture.
		 * _width = Width of texture block.
		 * _height = Height of texture block.
		 * _depth = Depth of texture block.
		 * _mem = Texture update data.
		 */
		alias da_bgfx_update_texture_3d = void function(bgfx_texture_handle_t _handle, ubyte _mip, ushort _x, ushort _y, ushort _z, ushort _width, ushort _height, ushort _depth, const(bgfx_memory_t)* _mem);
		da_bgfx_update_texture_3d bgfx_update_texture_3d;
		
		/**
		 * Update Cube texture.
		 * Attention: It's valid to update only mutable texture. See `bgfx::createTextureCube` for more info.
		 * Params:
		 * _handle = Texture handle.
		 * _layer = Layer in texture array.
		 * _side = Cubemap side `BGFX_CUBE_MAP_<POSITIVE or NEGATIVE>_<X, Y or Z>`,
		 *   where 0 is +X, 1 is -X, 2 is +Y, 3 is -Y, 4 is +Z, and 5 is -Z.
		 *                  +----------+
		 *                  |-z       2|
		 *                  | ^  +y    |
		 *                  | |        |    Unfolded cube:
		 *                  | +---->+x |
		 *       +----------+----------+----------+----------+
		 *       |+y       1|+y       4|+y       0|+y       5|
		 *       | ^  -x    | ^  +z    | ^  +x    | ^  -z    |
		 *       | |        | |        | |        | |        |
		 *       | +---->+z | +---->+x | +---->-z | +---->-x |
		 *       +----------+----------+----------+----------+
		 *                  |+z       3|
		 *                  | ^  -y    |
		 *                  | |        |
		 *                  | +---->+x |
		 *                  +----------+
		 * _mip = Mip level.
		 * _x = X offset in texture.
		 * _y = Y offset in texture.
		 * _width = Width of texture block.
		 * _height = Height of texture block.
		 * _mem = Texture update data.
		 * _pitch = Pitch of input image (bytes). When _pitch is set to
		 * UINT16_MAX, it will be calculated internally based on _width.
		 */
		alias da_bgfx_update_texture_cube = void function(bgfx_texture_handle_t _handle, ushort _layer, ubyte _side, ubyte _mip, ushort _x, ushort _y, ushort _width, ushort _height, const(bgfx_memory_t)* _mem, ushort _pitch);
		da_bgfx_update_texture_cube bgfx_update_texture_cube;
		
		/**
		 * Read back texture content.
		 * Attention: Texture must be created with `BGFX_TEXTURE_READ_BACK` flag.
		 * Attention: Availability depends on: `BGFX_CAPS_TEXTURE_READ_BACK`.
		 * Params:
		 * _handle = Texture handle.
		 * _data = Destination buffer.
		 * _mip = Mip level.
		 */
		alias da_bgfx_read_texture = uint function(bgfx_texture_handle_t _handle, void* _data, ubyte _mip);
		da_bgfx_read_texture bgfx_read_texture;
		
		/**
		 * Set texture debug name.
		 * Params:
		 * _handle = Texture handle.
		 * _name = Texture name.
		 * _len = Texture name length (if length is INT32_MAX, it's expected
		 * that _name is zero terminated string.
		 */
		alias da_bgfx_set_texture_name = void function(bgfx_texture_handle_t _handle, const(char)* _name, int _len);
		da_bgfx_set_texture_name bgfx_set_texture_name;
		
		/**
		 * Returns texture direct access pointer.
		 * Attention: Availability depends on: `BGFX_CAPS_TEXTURE_DIRECT_ACCESS`. This feature
		 *   is available on GPUs that have unified memory architecture (UMA) support.
		 * Params:
		 * _handle = Texture handle.
		 */
		alias da_bgfx_get_direct_access_ptr = void* function(bgfx_texture_handle_t _handle);
		da_bgfx_get_direct_access_ptr bgfx_get_direct_access_ptr;
		
		/**
		 * Destroy texture.
		 * Params:
		 * _handle = Texture handle.
		 */
		alias da_bgfx_destroy_texture = void function(bgfx_texture_handle_t _handle);
		da_bgfx_destroy_texture bgfx_destroy_texture;
		
		/**
		 * Create frame buffer (simple).
		 * Params:
		 * _width = Texture width.
		 * _height = Texture height.
		 * _format = Texture format. See: `TextureFormat::Enum`.
		 * _textureFlags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
		 * flags. Default texture sampling mode is linear, and wrap mode is repeat.
		 * - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		 *   mode.
		 * - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		 *   sampling.
		 */
		alias da_bgfx_create_frame_buffer = bgfx_frame_buffer_handle_t function(ushort _width, ushort _height, bgfx_texture_format_t _format, ulong _textureFlags);
		da_bgfx_create_frame_buffer bgfx_create_frame_buffer;
		
		/**
		 * Create frame buffer with size based on back-buffer ratio. Frame buffer will maintain ratio
		 * if back buffer resolution changes.
		 * Params:
		 * _ratio = Frame buffer size in respect to back-buffer size. See:
		 * `BackbufferRatio::Enum`.
		 * _format = Texture format. See: `TextureFormat::Enum`.
		 * _textureFlags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
		 * flags. Default texture sampling mode is linear, and wrap mode is repeat.
		 * - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		 *   mode.
		 * - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		 *   sampling.
		 */
		alias da_bgfx_create_frame_buffer_scaled = bgfx_frame_buffer_handle_t function(bgfx_backbuffer_ratio_t _ratio, bgfx_texture_format_t _format, ulong _textureFlags);
		da_bgfx_create_frame_buffer_scaled bgfx_create_frame_buffer_scaled;
		
		/**
		 * Create MRT frame buffer from texture handles (simple).
		 * Params:
		 * _num = Number of texture handles.
		 * _handles = Texture attachments.
		 * _destroyTexture = If true, textures will be destroyed when
		 * frame buffer is destroyed.
		 */
		alias da_bgfx_create_frame_buffer_from_handles = bgfx_frame_buffer_handle_t function(ubyte _num, const(bgfx_texture_handle_t)* _handles, bool _destroyTexture);
		da_bgfx_create_frame_buffer_from_handles bgfx_create_frame_buffer_from_handles;
		
		/**
		 * Create MRT frame buffer from texture handles with specific layer and
		 * mip level.
		 * Params:
		 * _num = Number of attachments.
		 * _attachment = Attachment texture info. See: `bgfx::Attachment`.
		 * _destroyTexture = If true, textures will be destroyed when
		 * frame buffer is destroyed.
		 */
		alias da_bgfx_create_frame_buffer_from_attachment = bgfx_frame_buffer_handle_t function(ubyte _num, const(bgfx_attachment_t)* _attachment, bool _destroyTexture);
		da_bgfx_create_frame_buffer_from_attachment bgfx_create_frame_buffer_from_attachment;
		
		/**
		 * Create frame buffer for multiple window rendering.
		 * Remarks:
		 *   Frame buffer cannot be used for sampling.
		 * Attention: Availability depends on: `BGFX_CAPS_SWAP_CHAIN`.
		 * Params:
		 * _nwh = OS' target native window handle.
		 * _width = Window back buffer width.
		 * _height = Window back buffer height.
		 * _format = Window back buffer color format.
		 * _depthFormat = Window back buffer depth format.
		 */
		alias da_bgfx_create_frame_buffer_from_nwh = bgfx_frame_buffer_handle_t function(void* _nwh, ushort _width, ushort _height, bgfx_texture_format_t _format, bgfx_texture_format_t _depthFormat);
		da_bgfx_create_frame_buffer_from_nwh bgfx_create_frame_buffer_from_nwh;
		
		/**
		 * Set frame buffer debug name.
		 * Params:
		 * _handle = Frame buffer handle.
		 * _name = Frame buffer name.
		 * _len = Frame buffer name length (if length is INT32_MAX, it's expected
		 * that _name is zero terminated string.
		 */
		alias da_bgfx_set_frame_buffer_name = void function(bgfx_frame_buffer_handle_t _handle, const(char)* _name, int _len);
		da_bgfx_set_frame_buffer_name bgfx_set_frame_buffer_name;
		
		/**
		 * Obtain texture handle of frame buffer attachment.
		 * Params:
		 * _handle = Frame buffer handle.
		 */
		alias da_bgfx_get_texture = bgfx_texture_handle_t function(bgfx_frame_buffer_handle_t _handle, ubyte _attachment);
		da_bgfx_get_texture bgfx_get_texture;
		
		/**
		 * Destroy frame buffer.
		 * Params:
		 * _handle = Frame buffer handle.
		 */
		alias da_bgfx_destroy_frame_buffer = void function(bgfx_frame_buffer_handle_t _handle);
		da_bgfx_destroy_frame_buffer bgfx_destroy_frame_buffer;
		
		/**
		 * Create shader uniform parameter.
		 * Remarks:
		 *   1. Uniform names are unique. It's valid to call `bgfx::createUniform`
		 *      multiple times with the same uniform name. The library will always
		 *      return the same handle, but the handle reference count will be
		 *      incremented. This means that the same number of `bgfx::destroyUniform`
		 *      must be called to properly destroy the uniform.
		 *   2. Predefined uniforms (declared in `bgfx_shader.sh`):
		 *      - `u_viewRect vec4(x, y, width, height)` - view rectangle for current
		 *        view, in pixels.
		 *      - `u_viewTexel vec4(1.0/width, 1.0/height, undef, undef)` - inverse
		 *        width and height
		 *      - `u_view mat4` - view matrix
		 *      - `u_invView mat4` - inverted view matrix
		 *      - `u_proj mat4` - projection matrix
		 *      - `u_invProj mat4` - inverted projection matrix
		 *      - `u_viewProj mat4` - concatenated view projection matrix
		 *      - `u_invViewProj mat4` - concatenated inverted view projection matrix
		 *      - `u_model mat4[BGFX_CONFIG_MAX_BONES]` - array of model matrices.
		 *      - `u_modelView mat4` - concatenated model view matrix, only first
		 *        model matrix from array is used.
		 *      - `u_modelViewProj mat4` - concatenated model view projection matrix.
		 *      - `u_alphaRef float` - alpha reference value for alpha test.
		 * Params:
		 * _name = Uniform name in shader.
		 * _type = Type of uniform (See: `bgfx::UniformType`).
		 * _num = Number of elements in array.
		 */
		alias da_bgfx_create_uniform = bgfx_uniform_handle_t function(const(char)* _name, bgfx_uniform_type_t _type, ushort _num);
		da_bgfx_create_uniform bgfx_create_uniform;
		
		/**
		 * Retrieve uniform info.
		 * Params:
		 * _handle = Handle to uniform object.
		 * _info = Uniform info.
		 */
		alias da_bgfx_get_uniform_info = void function(bgfx_uniform_handle_t _handle, bgfx_uniform_info_t* _info);
		da_bgfx_get_uniform_info bgfx_get_uniform_info;
		
		/**
		 * Destroy shader uniform parameter.
		 * Params:
		 * _handle = Handle to uniform object.
		 */
		alias da_bgfx_destroy_uniform = void function(bgfx_uniform_handle_t _handle);
		da_bgfx_destroy_uniform bgfx_destroy_uniform;
		
		/**
		 * Create occlusion query.
		 */
		alias da_bgfx_create_occlusion_query = bgfx_occlusion_query_handle_t function();
		da_bgfx_create_occlusion_query bgfx_create_occlusion_query;
		
		/**
		 * Retrieve occlusion query result from previous frame.
		 * Params:
		 * _handle = Handle to occlusion query object.
		 * _result = Number of pixels that passed test. This argument
		 * can be `NULL` if result of occlusion query is not needed.
		 */
		alias da_bgfx_get_result = bgfx_occlusion_query_result_t function(bgfx_occlusion_query_handle_t _handle, int* _result);
		da_bgfx_get_result bgfx_get_result;
		
		/**
		 * Destroy occlusion query.
		 * Params:
		 * _handle = Handle to occlusion query object.
		 */
		alias da_bgfx_destroy_occlusion_query = void function(bgfx_occlusion_query_handle_t _handle);
		da_bgfx_destroy_occlusion_query bgfx_destroy_occlusion_query;
		
		/**
		 * Set palette color value.
		 * Params:
		 * _index = Index into palette.
		 * _rgba = RGBA floating point values.
		 */
		alias da_bgfx_set_palette_color = void function(ubyte _index, const float[4] _rgba);
		da_bgfx_set_palette_color bgfx_set_palette_color;
		
		/**
		 * Set palette color value.
		 * Params:
		 * _index = Index into palette.
		 * _rgba = Packed 32-bit RGBA value.
		 */
		alias da_bgfx_set_palette_color_rgba8 = void function(ubyte _index, uint _rgba);
		da_bgfx_set_palette_color_rgba8 bgfx_set_palette_color_rgba8;
		
		/**
		 * Set view name.
		 * Remarks:
		 *   This is debug only feature.
		 *   In graphics debugger view name will appear as:
		 *       "nnnc <view name>"
		 *        ^  ^ ^
		 *        |  +--- compute (C)
		 *        +------ view id
		 * Params:
		 * _id = View id.
		 * _name = View name.
		 */
		alias da_bgfx_set_view_name = void function(bgfx_view_id_t _id, const(char)* _name);
		da_bgfx_set_view_name bgfx_set_view_name;
		
		/**
		 * Set view rectangle. Draw primitive outside view will be clipped.
		 * Params:
		 * _id = View id.
		 * _x = Position x from the left corner of the window.
		 * _y = Position y from the top corner of the window.
		 * _width = Width of view port region.
		 * _height = Height of view port region.
		 */
		alias da_bgfx_set_view_rect = void function(bgfx_view_id_t _id, ushort _x, ushort _y, ushort _width, ushort _height);
		da_bgfx_set_view_rect bgfx_set_view_rect;
		
		/**
		 * Set view rectangle. Draw primitive outside view will be clipped.
		 * Params:
		 * _id = View id.
		 * _x = Position x from the left corner of the window.
		 * _y = Position y from the top corner of the window.
		 * _ratio = Width and height will be set in respect to back-buffer size.
		 * See: `BackbufferRatio::Enum`.
		 */
		alias da_bgfx_set_view_rect_ratio = void function(bgfx_view_id_t _id, ushort _x, ushort _y, bgfx_backbuffer_ratio_t _ratio);
		da_bgfx_set_view_rect_ratio bgfx_set_view_rect_ratio;
		
		/**
		 * Set view scissor. Draw primitive outside view will be clipped. When
		 * _x, _y, _width and _height are set to 0, scissor will be disabled.
		 * Params:
		 * _id = View id.
		 * _x = Position x from the left corner of the window.
		 * _y = Position y from the top corner of the window.
		 * _width = Width of view scissor region.
		 * _height = Height of view scissor region.
		 */
		alias da_bgfx_set_view_scissor = void function(bgfx_view_id_t _id, ushort _x, ushort _y, ushort _width, ushort _height);
		da_bgfx_set_view_scissor bgfx_set_view_scissor;
		
		/**
		 * Set view clear flags.
		 * Params:
		 * _id = View id.
		 * _flags = Clear flags. Use `BGFX_CLEAR_NONE` to remove any clear
		 * operation. See: `BGFX_CLEAR_*`.
		 * _rgba = Color clear value.
		 * _depth = Depth clear value.
		 * _stencil = Stencil clear value.
		 */
		alias da_bgfx_set_view_clear = void function(bgfx_view_id_t _id, ushort _flags, uint _rgba, float _depth, ubyte _stencil);
		da_bgfx_set_view_clear bgfx_set_view_clear;
		
		/**
		 * Set view clear flags with different clear color for each
		 * frame buffer texture. `bgfx::setPaletteColor` must be used to set up a
		 * clear color palette.
		 * Params:
		 * _id = View id.
		 * _flags = Clear flags. Use `BGFX_CLEAR_NONE` to remove any clear
		 * operation. See: `BGFX_CLEAR_*`.
		 * _depth = Depth clear value.
		 * _stencil = Stencil clear value.
		 * _c0 = Palette index for frame buffer attachment 0.
		 * _c1 = Palette index for frame buffer attachment 1.
		 * _c2 = Palette index for frame buffer attachment 2.
		 * _c3 = Palette index for frame buffer attachment 3.
		 * _c4 = Palette index for frame buffer attachment 4.
		 * _c5 = Palette index for frame buffer attachment 5.
		 * _c6 = Palette index for frame buffer attachment 6.
		 * _c7 = Palette index for frame buffer attachment 7.
		 */
		alias da_bgfx_set_view_clear_mrt = void function(bgfx_view_id_t _id, ushort _flags, float _depth, ubyte _stencil, ubyte _c0, ubyte _c1, ubyte _c2, ubyte _c3, ubyte _c4, ubyte _c5, ubyte _c6, ubyte _c7);
		da_bgfx_set_view_clear_mrt bgfx_set_view_clear_mrt;
		
		/**
		 * Set view sorting mode.
		 * Remarks:
		 *   View mode must be set prior calling `bgfx::submit` for the view.
		 * Params:
		 * _id = View id.
		 * _mode = View sort mode. See `ViewMode::Enum`.
		 */
		alias da_bgfx_set_view_mode = void function(bgfx_view_id_t _id, bgfx_view_mode_t _mode);
		da_bgfx_set_view_mode bgfx_set_view_mode;
		
		/**
		 * Set view frame buffer.
		 * Remarks:
		 *   Not persistent after `bgfx::reset` call.
		 * Params:
		 * _id = View id.
		 * _handle = Frame buffer handle. Passing `BGFX_INVALID_HANDLE` as
		 * frame buffer handle will draw primitives from this view into
		 * default back buffer.
		 */
		alias da_bgfx_set_view_frame_buffer = void function(bgfx_view_id_t _id, bgfx_frame_buffer_handle_t _handle);
		da_bgfx_set_view_frame_buffer bgfx_set_view_frame_buffer;
		
		/**
		 * Set view's view matrix and projection matrix,
		 * all draw primitives in this view will use these two matrices.
		 * Params:
		 * _id = View id.
		 * _view = View matrix.
		 * _proj = Projection matrix.
		 */
		alias da_bgfx_set_view_transform = void function(bgfx_view_id_t _id, const(void)* _view, const(void)* _proj);
		da_bgfx_set_view_transform bgfx_set_view_transform;
		
		/**
		 * Post submit view reordering.
		 * Params:
		 * _id = First view id.
		 * _num = Number of views to remap.
		 * _order = View remap id table. Passing `NULL` will reset view ids
		 * to default state.
		 */
		alias da_bgfx_set_view_order = void function(bgfx_view_id_t _id, ushort _num, const(bgfx_view_id_t)* _order);
		da_bgfx_set_view_order bgfx_set_view_order;
		
		/**
		 * Reset all view settings to default.
		 */
		alias da_bgfx_reset_view = void function(bgfx_view_id_t _id);
		da_bgfx_reset_view bgfx_reset_view;
		
		/**
		 * Begin submitting draw calls from thread.
		 * Params:
		 * _forThread = Explicitly request an encoder for a worker thread.
		 */
		alias da_bgfx_encoder_begin = bgfx_encoder_t* function(bool _forThread);
		da_bgfx_encoder_begin bgfx_encoder_begin;
		
		/**
		 * End submitting draw calls from thread.
		 * Params:
		 * _encoder = Encoder.
		 */
		alias da_bgfx_encoder_end = void function(bgfx_encoder_t* _encoder);
		da_bgfx_encoder_end bgfx_encoder_end;
		
		/**
		 * Sets a debug marker. This allows you to group graphics calls together for easy browsing in
		 * graphics debugging tools.
		 * Params:
		 * _marker = Marker string.
		 */
		alias da_bgfx_encoder_set_marker = void function(bgfx_encoder_t* _this, const(char)* _marker);
		da_bgfx_encoder_set_marker bgfx_encoder_set_marker;
		
		/**
		 * Set render states for draw primitive.
		 * Remarks:
		 *   1. To set up more complex states use:
		 *      `BGFX_STATE_ALPHA_REF(_ref)`,
		 *      `BGFX_STATE_POINT_SIZE(_size)`,
		 *      `BGFX_STATE_BLEND_FUNC(_src, _dst)`,
		 *      `BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA)`,
		 *      `BGFX_STATE_BLEND_EQUATION(_equation)`,
		 *      `BGFX_STATE_BLEND_EQUATION_SEPARATE(_equationRGB, _equationA)`
		 *   2. `BGFX_STATE_BLEND_EQUATION_ADD` is set when no other blend
		 *      equation is specified.
		 * Params:
		 * _state = State flags. Default state for primitive type is
		 *   triangles. See: `BGFX_STATE_DEFAULT`.
		 *   - `BGFX_STATE_DEPTH_TEST_*` - Depth test function.
		 *   - `BGFX_STATE_BLEND_*` - See remark 1 about BGFX_STATE_BLEND_FUNC.
		 *   - `BGFX_STATE_BLEND_EQUATION_*` - See remark 2.
		 *   - `BGFX_STATE_CULL_*` - Backface culling mode.
		 *   - `BGFX_STATE_WRITE_*` - Enable R, G, B, A or Z write.
		 *   - `BGFX_STATE_MSAA` - Enable hardware multisample antialiasing.
		 *   - `BGFX_STATE_PT_[TRISTRIP/LINES/POINTS]` - Primitive type.
		 * _rgba = Sets blend factor used by `BGFX_STATE_BLEND_FACTOR` and
		 *   `BGFX_STATE_BLEND_INV_FACTOR` blend modes.
		 */
		alias da_bgfx_encoder_set_state = void function(bgfx_encoder_t* _this, ulong _state, uint _rgba);
		da_bgfx_encoder_set_state bgfx_encoder_set_state;
		
		/**
		 * Set condition for rendering.
		 * Params:
		 * _handle = Occlusion query handle.
		 * _visible = Render if occlusion query is visible.
		 */
		alias da_bgfx_encoder_set_condition = void function(bgfx_encoder_t* _this, bgfx_occlusion_query_handle_t _handle, bool _visible);
		da_bgfx_encoder_set_condition bgfx_encoder_set_condition;
		
		/**
		 * Set stencil test state.
		 * Params:
		 * _fstencil = Front stencil state.
		 * _bstencil = Back stencil state. If back is set to `BGFX_STENCIL_NONE`
		 * _fstencil is applied to both front and back facing primitives.
		 */
		alias da_bgfx_encoder_set_stencil = void function(bgfx_encoder_t* _this, uint _fstencil, uint _bstencil);
		da_bgfx_encoder_set_stencil bgfx_encoder_set_stencil;
		
		/**
		 * Set scissor for draw primitive.
		 * Remarks:
		 *   To scissor for all primitives in view see `bgfx::setViewScissor`.
		 * Params:
		 * _x = Position x from the left corner of the window.
		 * _y = Position y from the top corner of the window.
		 * _width = Width of view scissor region.
		 * _height = Height of view scissor region.
		 */
		alias da_bgfx_encoder_set_scissor = ushort function(bgfx_encoder_t* _this, ushort _x, ushort _y, ushort _width, ushort _height);
		da_bgfx_encoder_set_scissor bgfx_encoder_set_scissor;
		
		/**
		 * Set scissor from cache for draw primitive.
		 * Remarks:
		 *   To scissor for all primitives in view see `bgfx::setViewScissor`.
		 * Params:
		 * _cache = Index in scissor cache.
		 */
		alias da_bgfx_encoder_set_scissor_cached = void function(bgfx_encoder_t* _this, ushort _cache);
		da_bgfx_encoder_set_scissor_cached bgfx_encoder_set_scissor_cached;
		
		/**
		 * Set model matrix for draw primitive. If it is not called,
		 * the model will be rendered with an identity model matrix.
		 * Params:
		 * _mtx = Pointer to first matrix in array.
		 * _num = Number of matrices in array.
		 */
		alias da_bgfx_encoder_set_transform = uint function(bgfx_encoder_t* _this, const(void)* _mtx, ushort _num);
		da_bgfx_encoder_set_transform bgfx_encoder_set_transform;
		
		/**
		 *  Set model matrix from matrix cache for draw primitive.
		 * Params:
		 * _cache = Index in matrix cache.
		 * _num = Number of matrices from cache.
		 */
		alias da_bgfx_encoder_set_transform_cached = void function(bgfx_encoder_t* _this, uint _cache, ushort _num);
		da_bgfx_encoder_set_transform_cached bgfx_encoder_set_transform_cached;
		
		/**
		 * Reserve matrices in internal matrix cache.
		 * Attention: Pointer returned can be modified until `bgfx::frame` is called.
		 * Params:
		 * _transform = Pointer to `Transform` structure.
		 * _num = Number of matrices.
		 */
		alias da_bgfx_encoder_alloc_transform = uint function(bgfx_encoder_t* _this, bgfx_transform_t* _transform, ushort _num);
		da_bgfx_encoder_alloc_transform bgfx_encoder_alloc_transform;
		
		/**
		 * Set shader uniform parameter for draw primitive.
		 * Params:
		 * _handle = Uniform.
		 * _value = Pointer to uniform data.
		 * _num = Number of elements. Passing `UINT16_MAX` will
		 * use the _num passed on uniform creation.
		 */
		alias da_bgfx_encoder_set_uniform = void function(bgfx_encoder_t* _this, bgfx_uniform_handle_t _handle, const(void)* _value, ushort _num);
		da_bgfx_encoder_set_uniform bgfx_encoder_set_uniform;
		
		/**
		 * Set index buffer for draw primitive.
		 * Params:
		 * _handle = Index buffer.
		 * _firstIndex = First index to render.
		 * _numIndices = Number of indices to render.
		 */
		alias da_bgfx_encoder_set_index_buffer = void function(bgfx_encoder_t* _this, bgfx_index_buffer_handle_t _handle, uint _firstIndex, uint _numIndices);
		da_bgfx_encoder_set_index_buffer bgfx_encoder_set_index_buffer;
		
		/**
		 * Set index buffer for draw primitive.
		 * Params:
		 * _handle = Dynamic index buffer.
		 * _firstIndex = First index to render.
		 * _numIndices = Number of indices to render.
		 */
		alias da_bgfx_encoder_set_dynamic_index_buffer = void function(bgfx_encoder_t* _this, bgfx_dynamic_index_buffer_handle_t _handle, uint _firstIndex, uint _numIndices);
		da_bgfx_encoder_set_dynamic_index_buffer bgfx_encoder_set_dynamic_index_buffer;
		
		/**
		 * Set index buffer for draw primitive.
		 * Params:
		 * _tib = Transient index buffer.
		 * _firstIndex = First index to render.
		 * _numIndices = Number of indices to render.
		 */
		alias da_bgfx_encoder_set_transient_index_buffer = void function(bgfx_encoder_t* _this, const(bgfx_transient_index_buffer_t)* _tib, uint _firstIndex, uint _numIndices);
		da_bgfx_encoder_set_transient_index_buffer bgfx_encoder_set_transient_index_buffer;
		
		/**
		 * Set vertex buffer for draw primitive.
		 * Params:
		 * _stream = Vertex stream.
		 * _handle = Vertex buffer.
		 * _startVertex = First vertex to render.
		 * _numVertices = Number of vertices to render.
		 */
		alias da_bgfx_encoder_set_vertex_buffer = void function(bgfx_encoder_t* _this, ubyte _stream, bgfx_vertex_buffer_handle_t _handle, uint _startVertex, uint _numVertices);
		da_bgfx_encoder_set_vertex_buffer bgfx_encoder_set_vertex_buffer;
		
		/**
		 * Set vertex buffer for draw primitive.
		 * Params:
		 * _stream = Vertex stream.
		 * _handle = Vertex buffer.
		 * _startVertex = First vertex to render.
		 * _numVertices = Number of vertices to render.
		 * _layoutHandle = Vertex layout for aliasing vertex buffer. If invalid
		 * handle is used, vertex layout used for creation
		 * of vertex buffer will be used.
		 */
		alias da_bgfx_encoder_set_vertex_buffer_with_layout = void function(bgfx_encoder_t* _this, ubyte _stream, bgfx_vertex_buffer_handle_t _handle, uint _startVertex, uint _numVertices, bgfx_vertex_layout_handle_t _layoutHandle);
		da_bgfx_encoder_set_vertex_buffer_with_layout bgfx_encoder_set_vertex_buffer_with_layout;
		
		/**
		 * Set vertex buffer for draw primitive.
		 * Params:
		 * _stream = Vertex stream.
		 * _handle = Dynamic vertex buffer.
		 * _startVertex = First vertex to render.
		 * _numVertices = Number of vertices to render.
		 */
		alias da_bgfx_encoder_set_dynamic_vertex_buffer = void function(bgfx_encoder_t* _this, ubyte _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint _startVertex, uint _numVertices);
		da_bgfx_encoder_set_dynamic_vertex_buffer bgfx_encoder_set_dynamic_vertex_buffer;
		
		alias da_bgfx_encoder_set_dynamic_vertex_buffer_with_layout = void function(bgfx_encoder_t* _this, ubyte _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint _startVertex, uint _numVertices, bgfx_vertex_layout_handle_t _layoutHandle);
		da_bgfx_encoder_set_dynamic_vertex_buffer_with_layout bgfx_encoder_set_dynamic_vertex_buffer_with_layout;
		
		/**
		 * Set vertex buffer for draw primitive.
		 * Params:
		 * _stream = Vertex stream.
		 * _tvb = Transient vertex buffer.
		 * _startVertex = First vertex to render.
		 * _numVertices = Number of vertices to render.
		 */
		alias da_bgfx_encoder_set_transient_vertex_buffer = void function(bgfx_encoder_t* _this, ubyte _stream, const(bgfx_transient_vertex_buffer_t)* _tvb, uint _startVertex, uint _numVertices);
		da_bgfx_encoder_set_transient_vertex_buffer bgfx_encoder_set_transient_vertex_buffer;
		
		/**
		 * Set vertex buffer for draw primitive.
		 * Params:
		 * _stream = Vertex stream.
		 * _tvb = Transient vertex buffer.
		 * _startVertex = First vertex to render.
		 * _numVertices = Number of vertices to render.
		 * _layoutHandle = Vertex layout for aliasing vertex buffer. If invalid
		 * handle is used, vertex layout used for creation
		 * of vertex buffer will be used.
		 */
		alias da_bgfx_encoder_set_transient_vertex_buffer_with_layout = void function(bgfx_encoder_t* _this, ubyte _stream, const(bgfx_transient_vertex_buffer_t)* _tvb, uint _startVertex, uint _numVertices, bgfx_vertex_layout_handle_t _layoutHandle);
		da_bgfx_encoder_set_transient_vertex_buffer_with_layout bgfx_encoder_set_transient_vertex_buffer_with_layout;
		
		/**
		 * Set number of vertices for auto generated vertices use in conjunction
		 * with gl_VertexID.
		 * Attention: Availability depends on: `BGFX_CAPS_VERTEX_ID`.
		 * Params:
		 * _numVertices = Number of vertices.
		 */
		alias da_bgfx_encoder_set_vertex_count = void function(bgfx_encoder_t* _this, uint _numVertices);
		da_bgfx_encoder_set_vertex_count bgfx_encoder_set_vertex_count;
		
		/**
		 * Set instance data buffer for draw primitive.
		 * Params:
		 * _idb = Transient instance data buffer.
		 * _start = First instance data.
		 * _num = Number of data instances.
		 */
		alias da_bgfx_encoder_set_instance_data_buffer = void function(bgfx_encoder_t* _this, const(bgfx_instance_data_buffer_t)* _idb, uint _start, uint _num);
		da_bgfx_encoder_set_instance_data_buffer bgfx_encoder_set_instance_data_buffer;
		
		/**
		 * Set instance data buffer for draw primitive.
		 * Params:
		 * _handle = Vertex buffer.
		 * _startVertex = First instance data.
		 * _num = Number of data instances.
		 * Set instance data buffer for draw primitive.
		 */
		alias da_bgfx_encoder_set_instance_data_from_vertex_buffer = void function(bgfx_encoder_t* _this, bgfx_vertex_buffer_handle_t _handle, uint _startVertex, uint _num);
		da_bgfx_encoder_set_instance_data_from_vertex_buffer bgfx_encoder_set_instance_data_from_vertex_buffer;
		
		/**
		 * Set instance data buffer for draw primitive.
		 * Params:
		 * _handle = Dynamic vertex buffer.
		 * _startVertex = First instance data.
		 * _num = Number of data instances.
		 */
		alias da_bgfx_encoder_set_instance_data_from_dynamic_vertex_buffer = void function(bgfx_encoder_t* _this, bgfx_dynamic_vertex_buffer_handle_t _handle, uint _startVertex, uint _num);
		da_bgfx_encoder_set_instance_data_from_dynamic_vertex_buffer bgfx_encoder_set_instance_data_from_dynamic_vertex_buffer;
		
		/**
		 * Set number of instances for auto generated instances use in conjunction
		 * with gl_InstanceID.
		 * Attention: Availability depends on: `BGFX_CAPS_VERTEX_ID`.
		 */
		alias da_bgfx_encoder_set_instance_count = void function(bgfx_encoder_t* _this, uint _numInstances);
		da_bgfx_encoder_set_instance_count bgfx_encoder_set_instance_count;
		
		/**
		 * Set texture stage for draw primitive.
		 * Params:
		 * _stage = Texture unit.
		 * _sampler = Program sampler.
		 * _handle = Texture handle.
		 * _flags = Texture sampling mode. Default value UINT32_MAX uses
		 *   texture sampling settings from the texture.
		 *   - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		 *     mode.
		 *   - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		 *     sampling.
		 */
		alias da_bgfx_encoder_set_texture = void function(bgfx_encoder_t* _this, ubyte _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint _flags);
		da_bgfx_encoder_set_texture bgfx_encoder_set_texture;
		
		/**
		 * Submit an empty primitive for rendering. Uniforms and draw state
		 * will be applied but no geometry will be submitted. Useful in cases
		 * when no other draw/compute primitive is submitted to view, but it's
		 * desired to execute clear view.
		 * Remarks:
		 *   These empty draw calls will sort before ordinary draw calls.
		 * Params:
		 * _id = View id.
		 */
		alias da_bgfx_encoder_touch = void function(bgfx_encoder_t* _this, bgfx_view_id_t _id);
		da_bgfx_encoder_touch bgfx_encoder_touch;
		
		/**
		 * Submit primitive for rendering.
		 * Params:
		 * _id = View id.
		 * _program = Program.
		 * _depth = Depth for sorting.
		 * _flags = Discard or preserve states. See `BGFX_DISCARD_*`.
		 */
		alias da_bgfx_encoder_submit = void function(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, uint _depth, ubyte _flags);
		da_bgfx_encoder_submit bgfx_encoder_submit;
		
		/**
		 * Submit primitive with occlusion query for rendering.
		 * Params:
		 * _id = View id.
		 * _program = Program.
		 * _occlusionQuery = Occlusion query.
		 * _depth = Depth for sorting.
		 * _flags = Discard or preserve states. See `BGFX_DISCARD_*`.
		 */
		alias da_bgfx_encoder_submit_occlusion_query = void function(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_occlusion_query_handle_t _occlusionQuery, uint _depth, ubyte _flags);
		da_bgfx_encoder_submit_occlusion_query bgfx_encoder_submit_occlusion_query;
		
		/**
		 * Submit primitive for rendering with index and instance data info from
		 * indirect buffer.
		 * Params:
		 * _id = View id.
		 * _program = Program.
		 * _indirectHandle = Indirect buffer.
		 * _start = First element in indirect buffer.
		 * _num = Number of dispatches.
		 * _depth = Depth for sorting.
		 * _flags = Discard or preserve states. See `BGFX_DISCARD_*`.
		 */
		alias da_bgfx_encoder_submit_indirect = void function(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, ushort _start, ushort _num, uint _depth, ubyte _flags);
		da_bgfx_encoder_submit_indirect bgfx_encoder_submit_indirect;
		
		/**
		 * Set compute index buffer.
		 * Params:
		 * _stage = Compute stage.
		 * _handle = Index buffer handle.
		 * _access = Buffer access. See `Access::Enum`.
		 */
		alias da_bgfx_encoder_set_compute_index_buffer = void function(bgfx_encoder_t* _this, ubyte _stage, bgfx_index_buffer_handle_t _handle, bgfx_access_t _access);
		da_bgfx_encoder_set_compute_index_buffer bgfx_encoder_set_compute_index_buffer;
		
		/**
		 * Set compute vertex buffer.
		 * Params:
		 * _stage = Compute stage.
		 * _handle = Vertex buffer handle.
		 * _access = Buffer access. See `Access::Enum`.
		 */
		alias da_bgfx_encoder_set_compute_vertex_buffer = void function(bgfx_encoder_t* _this, ubyte _stage, bgfx_vertex_buffer_handle_t _handle, bgfx_access_t _access);
		da_bgfx_encoder_set_compute_vertex_buffer bgfx_encoder_set_compute_vertex_buffer;
		
		/**
		 * Set compute dynamic index buffer.
		 * Params:
		 * _stage = Compute stage.
		 * _handle = Dynamic index buffer handle.
		 * _access = Buffer access. See `Access::Enum`.
		 */
		alias da_bgfx_encoder_set_compute_dynamic_index_buffer = void function(bgfx_encoder_t* _this, ubyte _stage, bgfx_dynamic_index_buffer_handle_t _handle, bgfx_access_t _access);
		da_bgfx_encoder_set_compute_dynamic_index_buffer bgfx_encoder_set_compute_dynamic_index_buffer;
		
		/**
		 * Set compute dynamic vertex buffer.
		 * Params:
		 * _stage = Compute stage.
		 * _handle = Dynamic vertex buffer handle.
		 * _access = Buffer access. See `Access::Enum`.
		 */
		alias da_bgfx_encoder_set_compute_dynamic_vertex_buffer = void function(bgfx_encoder_t* _this, ubyte _stage, bgfx_dynamic_vertex_buffer_handle_t _handle, bgfx_access_t _access);
		da_bgfx_encoder_set_compute_dynamic_vertex_buffer bgfx_encoder_set_compute_dynamic_vertex_buffer;
		
		/**
		 * Set compute indirect buffer.
		 * Params:
		 * _stage = Compute stage.
		 * _handle = Indirect buffer handle.
		 * _access = Buffer access. See `Access::Enum`.
		 */
		alias da_bgfx_encoder_set_compute_indirect_buffer = void function(bgfx_encoder_t* _this, ubyte _stage, bgfx_indirect_buffer_handle_t _handle, bgfx_access_t _access);
		da_bgfx_encoder_set_compute_indirect_buffer bgfx_encoder_set_compute_indirect_buffer;
		
		/**
		 * Set compute image from texture.
		 * Params:
		 * _stage = Compute stage.
		 * _handle = Texture handle.
		 * _mip = Mip level.
		 * _access = Image access. See `Access::Enum`.
		 * _format = Texture format. See: `TextureFormat::Enum`.
		 */
		alias da_bgfx_encoder_set_image = void function(bgfx_encoder_t* _this, ubyte _stage, bgfx_texture_handle_t _handle, ubyte _mip, bgfx_access_t _access, bgfx_texture_format_t _format);
		da_bgfx_encoder_set_image bgfx_encoder_set_image;
		
		/**
		 * Dispatch compute.
		 * Params:
		 * _id = View id.
		 * _program = Compute program.
		 * _numX = Number of groups X.
		 * _numY = Number of groups Y.
		 * _numZ = Number of groups Z.
		 * _flags = Discard or preserve states. See `BGFX_DISCARD_*`.
		 */
		alias da_bgfx_encoder_dispatch = void function(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, uint _numX, uint _numY, uint _numZ, ubyte _flags);
		da_bgfx_encoder_dispatch bgfx_encoder_dispatch;
		
		/**
		 * Dispatch compute indirect.
		 * Params:
		 * _id = View id.
		 * _program = Compute program.
		 * _indirectHandle = Indirect buffer.
		 * _start = First element in indirect buffer.
		 * _num = Number of dispatches.
		 * _flags = Discard or preserve states. See `BGFX_DISCARD_*`.
		 */
		alias da_bgfx_encoder_dispatch_indirect = void function(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, ushort _start, ushort _num, ubyte _flags);
		da_bgfx_encoder_dispatch_indirect bgfx_encoder_dispatch_indirect;
		
		/**
		 * Discard previously set state for draw or compute call.
		 * Params:
		 * _flags = Discard or preserve states. See `BGFX_DISCARD_*`.
		 */
		alias da_bgfx_encoder_discard = void function(bgfx_encoder_t* _this, ubyte _flags);
		da_bgfx_encoder_discard bgfx_encoder_discard;
		
		/**
		 * Blit 2D texture region between two 2D textures.
		 * Attention: Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
		 * Attention: Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
		 * Params:
		 * _id = View id.
		 * _dst = Destination texture handle.
		 * _dstMip = Destination texture mip level.
		 * _dstX = Destination texture X position.
		 * _dstY = Destination texture Y position.
		 * _dstZ = If texture is 2D this argument should be 0. If destination texture is cube
		 * this argument represents destination texture cube face. For 3D texture this argument
		 * represents destination texture Z position.
		 * _src = Source texture handle.
		 * _srcMip = Source texture mip level.
		 * _srcX = Source texture X position.
		 * _srcY = Source texture Y position.
		 * _srcZ = If texture is 2D this argument should be 0. If source texture is cube
		 * this argument represents source texture cube face. For 3D texture this argument
		 * represents source texture Z position.
		 * _width = Width of region.
		 * _height = Height of region.
		 * _depth = If texture is 3D this argument represents depth of region, otherwise it's
		 * unused.
		 */
		alias da_bgfx_encoder_blit = void function(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_texture_handle_t _dst, ubyte _dstMip, ushort _dstX, ushort _dstY, ushort _dstZ, bgfx_texture_handle_t _src, ubyte _srcMip, ushort _srcX, ushort _srcY, ushort _srcZ, ushort _width, ushort _height, ushort _depth);
		da_bgfx_encoder_blit bgfx_encoder_blit;
		
		/**
		 * Request screen shot of window back buffer.
		 * Remarks:
		 *   `bgfx::CallbackI::screenShot` must be implemented.
		 * Attention: Frame buffer handle must be created with OS' target native window handle.
		 * Params:
		 * _handle = Frame buffer handle. If handle is `BGFX_INVALID_HANDLE` request will be
		 * made for main window back buffer.
		 * _filePath = Will be passed to `bgfx::CallbackI::screenShot` callback.
		 */
		alias da_bgfx_request_screen_shot = void function(bgfx_frame_buffer_handle_t _handle, const(char)* _filePath);
		da_bgfx_request_screen_shot bgfx_request_screen_shot;
		
		/**
		 * Render frame.
		 * Attention: `bgfx::renderFrame` is blocking call. It waits for
		 *   `bgfx::frame` to be called from API thread to process frame.
		 *   If timeout value is passed call will timeout and return even
		 *   if `bgfx::frame` is not called.
		 * Warning: This call should be only used on platforms that don't
		 *   allow creating separate rendering thread. If it is called before
		 *   to bgfx::init, render thread won't be created by bgfx::init call.
		 * Params:
		 * _msecs = Timeout in milliseconds.
		 */
		alias da_bgfx_render_frame = bgfx_render_frame_t function(int _msecs);
		da_bgfx_render_frame bgfx_render_frame;
		
		/**
		 * Set platform data.
		 * Warning: Must be called before `bgfx::init`.
		 * Params:
		 * _data = Platform data.
		 */
		alias da_bgfx_set_platform_data = void function(const(bgfx_platform_data_t)* _data);
		da_bgfx_set_platform_data bgfx_set_platform_data;
		
		/**
		 * Get internal data for interop.
		 * Attention: It's expected you understand some bgfx internals before you
		 *   use this call.
		 * Warning: Must be called only on render thread.
		 */
		alias da_bgfx_get_internal_data = const(bgfx_internal_data_t)* function();
		da_bgfx_get_internal_data bgfx_get_internal_data;
		
		/**
		 * Override internal texture with externally created texture. Previously
		 * created internal texture will released.
		 * Attention: It's expected you understand some bgfx internals before you
		 *   use this call.
		 * Warning: Must be called only on render thread.
		 * Params:
		 * _handle = Texture handle.
		 * _ptr = Native API pointer to texture.
		 */
		alias da_bgfx_override_internal_texture_ptr = ulong function(bgfx_texture_handle_t _handle, ulong _ptr);
		da_bgfx_override_internal_texture_ptr bgfx_override_internal_texture_ptr;
		
		/**
		 * Override internal texture by creating new texture. Previously created
		 * internal texture will released.
		 * Attention: It's expected you understand some bgfx internals before you
		 *   use this call.
		 * Returns: Native API pointer to texture. If result is 0, texture is not created yet from the
		 *   main thread.
		 * Warning: Must be called only on render thread.
		 * Params:
		 * _handle = Texture handle.
		 * _width = Width.
		 * _height = Height.
		 * _numMips = Number of mip-maps.
		 * _format = Texture format. See: `TextureFormat::Enum`.
		 * _flags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
		 * flags. Default texture sampling mode is linear, and wrap mode is repeat.
		 * - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		 *   mode.
		 * - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		 *   sampling.
		 */
		alias da_bgfx_override_internal_texture = ulong function(bgfx_texture_handle_t _handle, ushort _width, ushort _height, ubyte _numMips, bgfx_texture_format_t _format, ulong _flags);
		da_bgfx_override_internal_texture bgfx_override_internal_texture;
		
		/**
		 * Sets a debug marker. This allows you to group graphics calls together for easy browsing in
		 * graphics debugging tools.
		 * Params:
		 * _marker = Marker string.
		 */
		alias da_bgfx_set_marker = void function(const(char)* _marker);
		da_bgfx_set_marker bgfx_set_marker;
		
		/**
		 * Set render states for draw primitive.
		 * Remarks:
		 *   1. To set up more complex states use:
		 *      `BGFX_STATE_ALPHA_REF(_ref)`,
		 *      `BGFX_STATE_POINT_SIZE(_size)`,
		 *      `BGFX_STATE_BLEND_FUNC(_src, _dst)`,
		 *      `BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA)`,
		 *      `BGFX_STATE_BLEND_EQUATION(_equation)`,
		 *      `BGFX_STATE_BLEND_EQUATION_SEPARATE(_equationRGB, _equationA)`
		 *   2. `BGFX_STATE_BLEND_EQUATION_ADD` is set when no other blend
		 *      equation is specified.
		 * Params:
		 * _state = State flags. Default state for primitive type is
		 *   triangles. See: `BGFX_STATE_DEFAULT`.
		 *   - `BGFX_STATE_DEPTH_TEST_*` - Depth test function.
		 *   - `BGFX_STATE_BLEND_*` - See remark 1 about BGFX_STATE_BLEND_FUNC.
		 *   - `BGFX_STATE_BLEND_EQUATION_*` - See remark 2.
		 *   - `BGFX_STATE_CULL_*` - Backface culling mode.
		 *   - `BGFX_STATE_WRITE_*` - Enable R, G, B, A or Z write.
		 *   - `BGFX_STATE_MSAA` - Enable hardware multisample antialiasing.
		 *   - `BGFX_STATE_PT_[TRISTRIP/LINES/POINTS]` - Primitive type.
		 * _rgba = Sets blend factor used by `BGFX_STATE_BLEND_FACTOR` and
		 *   `BGFX_STATE_BLEND_INV_FACTOR` blend modes.
		 */
		alias da_bgfx_set_state = void function(ulong _state, uint _rgba);
		da_bgfx_set_state bgfx_set_state;
		
		/**
		 * Set condition for rendering.
		 * Params:
		 * _handle = Occlusion query handle.
		 * _visible = Render if occlusion query is visible.
		 */
		alias da_bgfx_set_condition = void function(bgfx_occlusion_query_handle_t _handle, bool _visible);
		da_bgfx_set_condition bgfx_set_condition;
		
		/**
		 * Set stencil test state.
		 * Params:
		 * _fstencil = Front stencil state.
		 * _bstencil = Back stencil state. If back is set to `BGFX_STENCIL_NONE`
		 * _fstencil is applied to both front and back facing primitives.
		 */
		alias da_bgfx_set_stencil = void function(uint _fstencil, uint _bstencil);
		da_bgfx_set_stencil bgfx_set_stencil;
		
		/**
		 * Set scissor for draw primitive.
		 * Remarks:
		 *   To scissor for all primitives in view see `bgfx::setViewScissor`.
		 * Params:
		 * _x = Position x from the left corner of the window.
		 * _y = Position y from the top corner of the window.
		 * _width = Width of view scissor region.
		 * _height = Height of view scissor region.
		 */
		alias da_bgfx_set_scissor = ushort function(ushort _x, ushort _y, ushort _width, ushort _height);
		da_bgfx_set_scissor bgfx_set_scissor;
		
		/**
		 * Set scissor from cache for draw primitive.
		 * Remarks:
		 *   To scissor for all primitives in view see `bgfx::setViewScissor`.
		 * Params:
		 * _cache = Index in scissor cache.
		 */
		alias da_bgfx_set_scissor_cached = void function(ushort _cache);
		da_bgfx_set_scissor_cached bgfx_set_scissor_cached;
		
		/**
		 * Set model matrix for draw primitive. If it is not called,
		 * the model will be rendered with an identity model matrix.
		 * Params:
		 * _mtx = Pointer to first matrix in array.
		 * _num = Number of matrices in array.
		 */
		alias da_bgfx_set_transform = uint function(const(void)* _mtx, ushort _num);
		da_bgfx_set_transform bgfx_set_transform;
		
		/**
		 *  Set model matrix from matrix cache for draw primitive.
		 * Params:
		 * _cache = Index in matrix cache.
		 * _num = Number of matrices from cache.
		 */
		alias da_bgfx_set_transform_cached = void function(uint _cache, ushort _num);
		da_bgfx_set_transform_cached bgfx_set_transform_cached;
		
		/**
		 * Reserve matrices in internal matrix cache.
		 * Attention: Pointer returned can be modified until `bgfx::frame` is called.
		 * Params:
		 * _transform = Pointer to `Transform` structure.
		 * _num = Number of matrices.
		 */
		alias da_bgfx_alloc_transform = uint function(bgfx_transform_t* _transform, ushort _num);
		da_bgfx_alloc_transform bgfx_alloc_transform;
		
		/**
		 * Set shader uniform parameter for draw primitive.
		 * Params:
		 * _handle = Uniform.
		 * _value = Pointer to uniform data.
		 * _num = Number of elements. Passing `UINT16_MAX` will
		 * use the _num passed on uniform creation.
		 */
		alias da_bgfx_set_uniform = void function(bgfx_uniform_handle_t _handle, const(void)* _value, ushort _num);
		da_bgfx_set_uniform bgfx_set_uniform;
		
		/**
		 * Set index buffer for draw primitive.
		 * Params:
		 * _handle = Index buffer.
		 * _firstIndex = First index to render.
		 * _numIndices = Number of indices to render.
		 */
		alias da_bgfx_set_index_buffer = void function(bgfx_index_buffer_handle_t _handle, uint _firstIndex, uint _numIndices);
		da_bgfx_set_index_buffer bgfx_set_index_buffer;
		
		/**
		 * Set index buffer for draw primitive.
		 * Params:
		 * _handle = Dynamic index buffer.
		 * _firstIndex = First index to render.
		 * _numIndices = Number of indices to render.
		 */
		alias da_bgfx_set_dynamic_index_buffer = void function(bgfx_dynamic_index_buffer_handle_t _handle, uint _firstIndex, uint _numIndices);
		da_bgfx_set_dynamic_index_buffer bgfx_set_dynamic_index_buffer;
		
		/**
		 * Set index buffer for draw primitive.
		 * Params:
		 * _tib = Transient index buffer.
		 * _firstIndex = First index to render.
		 * _numIndices = Number of indices to render.
		 */
		alias da_bgfx_set_transient_index_buffer = void function(const(bgfx_transient_index_buffer_t)* _tib, uint _firstIndex, uint _numIndices);
		da_bgfx_set_transient_index_buffer bgfx_set_transient_index_buffer;
		
		/**
		 * Set vertex buffer for draw primitive.
		 * Params:
		 * _stream = Vertex stream.
		 * _handle = Vertex buffer.
		 * _startVertex = First vertex to render.
		 * _numVertices = Number of vertices to render.
		 */
		alias da_bgfx_set_vertex_buffer = void function(ubyte _stream, bgfx_vertex_buffer_handle_t _handle, uint _startVertex, uint _numVertices);
		da_bgfx_set_vertex_buffer bgfx_set_vertex_buffer;
		
		/**
		 * Set vertex buffer for draw primitive.
		 * Params:
		 * _stream = Vertex stream.
		 * _handle = Vertex buffer.
		 * _startVertex = First vertex to render.
		 * _numVertices = Number of vertices to render.
		 * _layoutHandle = Vertex layout for aliasing vertex buffer. If invalid
		 * handle is used, vertex layout used for creation
		 * of vertex buffer will be used.
		 */
		alias da_bgfx_set_vertex_buffer_with_layout = void function(ubyte _stream, bgfx_vertex_buffer_handle_t _handle, uint _startVertex, uint _numVertices, bgfx_vertex_layout_handle_t _layoutHandle);
		da_bgfx_set_vertex_buffer_with_layout bgfx_set_vertex_buffer_with_layout;
		
		/**
		 * Set vertex buffer for draw primitive.
		 * Params:
		 * _stream = Vertex stream.
		 * _handle = Dynamic vertex buffer.
		 * _startVertex = First vertex to render.
		 * _numVertices = Number of vertices to render.
		 */
		alias da_bgfx_set_dynamic_vertex_buffer = void function(ubyte _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint _startVertex, uint _numVertices);
		da_bgfx_set_dynamic_vertex_buffer bgfx_set_dynamic_vertex_buffer;
		
		/**
		 * Set vertex buffer for draw primitive.
		 * Params:
		 * _stream = Vertex stream.
		 * _handle = Dynamic vertex buffer.
		 * _startVertex = First vertex to render.
		 * _numVertices = Number of vertices to render.
		 * _layoutHandle = Vertex layout for aliasing vertex buffer. If invalid
		 * handle is used, vertex layout used for creation
		 * of vertex buffer will be used.
		 */
		alias da_bgfx_set_dynamic_vertex_buffer_with_layout = void function(ubyte _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint _startVertex, uint _numVertices, bgfx_vertex_layout_handle_t _layoutHandle);
		da_bgfx_set_dynamic_vertex_buffer_with_layout bgfx_set_dynamic_vertex_buffer_with_layout;
		
		/**
		 * Set vertex buffer for draw primitive.
		 * Params:
		 * _stream = Vertex stream.
		 * _tvb = Transient vertex buffer.
		 * _startVertex = First vertex to render.
		 * _numVertices = Number of vertices to render.
		 */
		alias da_bgfx_set_transient_vertex_buffer = void function(ubyte _stream, const(bgfx_transient_vertex_buffer_t)* _tvb, uint _startVertex, uint _numVertices);
		da_bgfx_set_transient_vertex_buffer bgfx_set_transient_vertex_buffer;
		
		/**
		 * Set vertex buffer for draw primitive.
		 * Params:
		 * _stream = Vertex stream.
		 * _tvb = Transient vertex buffer.
		 * _startVertex = First vertex to render.
		 * _numVertices = Number of vertices to render.
		 * _layoutHandle = Vertex layout for aliasing vertex buffer. If invalid
		 * handle is used, vertex layout used for creation
		 * of vertex buffer will be used.
		 */
		alias da_bgfx_set_transient_vertex_buffer_with_layout = void function(ubyte _stream, const(bgfx_transient_vertex_buffer_t)* _tvb, uint _startVertex, uint _numVertices, bgfx_vertex_layout_handle_t _layoutHandle);
		da_bgfx_set_transient_vertex_buffer_with_layout bgfx_set_transient_vertex_buffer_with_layout;
		
		/**
		 * Set number of vertices for auto generated vertices use in conjunction
		 * with gl_VertexID.
		 * Attention: Availability depends on: `BGFX_CAPS_VERTEX_ID`.
		 * Params:
		 * _numVertices = Number of vertices.
		 */
		alias da_bgfx_set_vertex_count = void function(uint _numVertices);
		da_bgfx_set_vertex_count bgfx_set_vertex_count;
		
		/**
		 * Set instance data buffer for draw primitive.
		 * Params:
		 * _idb = Transient instance data buffer.
		 * _start = First instance data.
		 * _num = Number of data instances.
		 */
		alias da_bgfx_set_instance_data_buffer = void function(const(bgfx_instance_data_buffer_t)* _idb, uint _start, uint _num);
		da_bgfx_set_instance_data_buffer bgfx_set_instance_data_buffer;
		
		/**
		 * Set instance data buffer for draw primitive.
		 * Params:
		 * _handle = Vertex buffer.
		 * _startVertex = First instance data.
		 * _num = Number of data instances.
		 * Set instance data buffer for draw primitive.
		 */
		alias da_bgfx_set_instance_data_from_vertex_buffer = void function(bgfx_vertex_buffer_handle_t _handle, uint _startVertex, uint _num);
		da_bgfx_set_instance_data_from_vertex_buffer bgfx_set_instance_data_from_vertex_buffer;
		
		/**
		 * Set instance data buffer for draw primitive.
		 * Params:
		 * _handle = Dynamic vertex buffer.
		 * _startVertex = First instance data.
		 * _num = Number of data instances.
		 */
		alias da_bgfx_set_instance_data_from_dynamic_vertex_buffer = void function(bgfx_dynamic_vertex_buffer_handle_t _handle, uint _startVertex, uint _num);
		da_bgfx_set_instance_data_from_dynamic_vertex_buffer bgfx_set_instance_data_from_dynamic_vertex_buffer;
		
		/**
		 * Set number of instances for auto generated instances use in conjunction
		 * with gl_InstanceID.
		 * Attention: Availability depends on: `BGFX_CAPS_VERTEX_ID`.
		 */
		alias da_bgfx_set_instance_count = void function(uint _numInstances);
		da_bgfx_set_instance_count bgfx_set_instance_count;
		
		/**
		 * Set texture stage for draw primitive.
		 * Params:
		 * _stage = Texture unit.
		 * _sampler = Program sampler.
		 * _handle = Texture handle.
		 * _flags = Texture sampling mode. Default value UINT32_MAX uses
		 *   texture sampling settings from the texture.
		 *   - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		 *     mode.
		 *   - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		 *     sampling.
		 */
		alias da_bgfx_set_texture = void function(ubyte _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint _flags);
		da_bgfx_set_texture bgfx_set_texture;
		
		/**
		 * Submit an empty primitive for rendering. Uniforms and draw state
		 * will be applied but no geometry will be submitted.
		 * Remarks:
		 *   These empty draw calls will sort before ordinary draw calls.
		 * Params:
		 * _id = View id.
		 */
		alias da_bgfx_touch = void function(bgfx_view_id_t _id);
		da_bgfx_touch bgfx_touch;
		
		/**
		 * Submit primitive for rendering.
		 * Params:
		 * _id = View id.
		 * _program = Program.
		 * _depth = Depth for sorting.
		 * _flags = Which states to discard for next draw. See `BGFX_DISCARD_*`.
		 */
		alias da_bgfx_submit = void function(bgfx_view_id_t _id, bgfx_program_handle_t _program, uint _depth, ubyte _flags);
		da_bgfx_submit bgfx_submit;
		
		/**
		 * Submit primitive with occlusion query for rendering.
		 * Params:
		 * _id = View id.
		 * _program = Program.
		 * _occlusionQuery = Occlusion query.
		 * _depth = Depth for sorting.
		 * _flags = Which states to discard for next draw. See `BGFX_DISCARD_*`.
		 */
		alias da_bgfx_submit_occlusion_query = void function(bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_occlusion_query_handle_t _occlusionQuery, uint _depth, ubyte _flags);
		da_bgfx_submit_occlusion_query bgfx_submit_occlusion_query;
		
		/**
		 * Submit primitive for rendering with index and instance data info from
		 * indirect buffer.
		 * Params:
		 * _id = View id.
		 * _program = Program.
		 * _indirectHandle = Indirect buffer.
		 * _start = First element in indirect buffer.
		 * _num = Number of dispatches.
		 * _depth = Depth for sorting.
		 * _flags = Which states to discard for next draw. See `BGFX_DISCARD_*`.
		 */
		alias da_bgfx_submit_indirect = void function(bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, ushort _start, ushort _num, uint _depth, ubyte _flags);
		da_bgfx_submit_indirect bgfx_submit_indirect;
		
		/**
		 * Set compute index buffer.
		 * Params:
		 * _stage = Compute stage.
		 * _handle = Index buffer handle.
		 * _access = Buffer access. See `Access::Enum`.
		 */
		alias da_bgfx_set_compute_index_buffer = void function(ubyte _stage, bgfx_index_buffer_handle_t _handle, bgfx_access_t _access);
		da_bgfx_set_compute_index_buffer bgfx_set_compute_index_buffer;
		
		/**
		 * Set compute vertex buffer.
		 * Params:
		 * _stage = Compute stage.
		 * _handle = Vertex buffer handle.
		 * _access = Buffer access. See `Access::Enum`.
		 */
		alias da_bgfx_set_compute_vertex_buffer = void function(ubyte _stage, bgfx_vertex_buffer_handle_t _handle, bgfx_access_t _access);
		da_bgfx_set_compute_vertex_buffer bgfx_set_compute_vertex_buffer;
		
		/**
		 * Set compute dynamic index buffer.
		 * Params:
		 * _stage = Compute stage.
		 * _handle = Dynamic index buffer handle.
		 * _access = Buffer access. See `Access::Enum`.
		 */
		alias da_bgfx_set_compute_dynamic_index_buffer = void function(ubyte _stage, bgfx_dynamic_index_buffer_handle_t _handle, bgfx_access_t _access);
		da_bgfx_set_compute_dynamic_index_buffer bgfx_set_compute_dynamic_index_buffer;
		
		/**
		 * Set compute dynamic vertex buffer.
		 * Params:
		 * _stage = Compute stage.
		 * _handle = Dynamic vertex buffer handle.
		 * _access = Buffer access. See `Access::Enum`.
		 */
		alias da_bgfx_set_compute_dynamic_vertex_buffer = void function(ubyte _stage, bgfx_dynamic_vertex_buffer_handle_t _handle, bgfx_access_t _access);
		da_bgfx_set_compute_dynamic_vertex_buffer bgfx_set_compute_dynamic_vertex_buffer;
		
		/**
		 * Set compute indirect buffer.
		 * Params:
		 * _stage = Compute stage.
		 * _handle = Indirect buffer handle.
		 * _access = Buffer access. See `Access::Enum`.
		 */
		alias da_bgfx_set_compute_indirect_buffer = void function(ubyte _stage, bgfx_indirect_buffer_handle_t _handle, bgfx_access_t _access);
		da_bgfx_set_compute_indirect_buffer bgfx_set_compute_indirect_buffer;
		
		/**
		 * Set compute image from texture.
		 * Params:
		 * _stage = Compute stage.
		 * _handle = Texture handle.
		 * _mip = Mip level.
		 * _access = Image access. See `Access::Enum`.
		 * _format = Texture format. See: `TextureFormat::Enum`.
		 */
		alias da_bgfx_set_image = void function(ubyte _stage, bgfx_texture_handle_t _handle, ubyte _mip, bgfx_access_t _access, bgfx_texture_format_t _format);
		da_bgfx_set_image bgfx_set_image;
		
		/**
		 * Dispatch compute.
		 * Params:
		 * _id = View id.
		 * _program = Compute program.
		 * _numX = Number of groups X.
		 * _numY = Number of groups Y.
		 * _numZ = Number of groups Z.
		 * _flags = Discard or preserve states. See `BGFX_DISCARD_*`.
		 */
		alias da_bgfx_dispatch = void function(bgfx_view_id_t _id, bgfx_program_handle_t _program, uint _numX, uint _numY, uint _numZ, ubyte _flags);
		da_bgfx_dispatch bgfx_dispatch;
		
		/**
		 * Dispatch compute indirect.
		 * Params:
		 * _id = View id.
		 * _program = Compute program.
		 * _indirectHandle = Indirect buffer.
		 * _start = First element in indirect buffer.
		 * _num = Number of dispatches.
		 * _flags = Discard or preserve states. See `BGFX_DISCARD_*`.
		 */
		alias da_bgfx_dispatch_indirect = void function(bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, ushort _start, ushort _num, ubyte _flags);
		da_bgfx_dispatch_indirect bgfx_dispatch_indirect;
		
		/**
		 * Discard previously set state for draw or compute call.
		 * Params:
		 * _flags = Draw/compute states to discard.
		 */
		alias da_bgfx_discard = void function(ubyte _flags);
		da_bgfx_discard bgfx_discard;
		
		/**
		 * Blit 2D texture region between two 2D textures.
		 * Attention: Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
		 * Attention: Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
		 * Params:
		 * _id = View id.
		 * _dst = Destination texture handle.
		 * _dstMip = Destination texture mip level.
		 * _dstX = Destination texture X position.
		 * _dstY = Destination texture Y position.
		 * _dstZ = If texture is 2D this argument should be 0. If destination texture is cube
		 * this argument represents destination texture cube face. For 3D texture this argument
		 * represents destination texture Z position.
		 * _src = Source texture handle.
		 * _srcMip = Source texture mip level.
		 * _srcX = Source texture X position.
		 * _srcY = Source texture Y position.
		 * _srcZ = If texture is 2D this argument should be 0. If source texture is cube
		 * this argument represents source texture cube face. For 3D texture this argument
		 * represents source texture Z position.
		 * _width = Width of region.
		 * _height = Height of region.
		 * _depth = If texture is 3D this argument represents depth of region, otherwise it's
		 * unused.
		 */
		alias da_bgfx_blit = void function(bgfx_view_id_t _id, bgfx_texture_handle_t _dst, ubyte _dstMip, ushort _dstX, ushort _dstY, ushort _dstZ, bgfx_texture_handle_t _src, ubyte _srcMip, ushort _srcX, ushort _srcY, ushort _srcZ, ushort _width, ushort _height, ushort _depth);
		da_bgfx_blit bgfx_blit;
		
	}
}
