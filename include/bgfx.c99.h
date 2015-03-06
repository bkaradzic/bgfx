/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 *
 * vim: set tabstop=4 expandtab:
 */

#ifndef BGFX_C99_H_HEADER_GUARD
#define BGFX_C99_H_HEADER_GUARD

#include <stdbool.h> // bool
#include <stdint.h>  // uint32_t
#include <stdlib.h>  // size_t

#include "bgfxdefines.h"

typedef enum bgfx_renderer_type
{
    BGFX_RENDERER_TYPE_NULL,
    BGFX_RENDERER_TYPE_DIRECT3D9,
    BGFX_RENDERER_TYPE_DIRECT3D11,
    BGFX_RENDERER_TYPE_DIRECT3D12,
    BGFX_RENDERER_TYPE_OPENGLES,
    BGFX_RENDERER_TYPE_OPENGL,
    BGFX_RENDERER_TYPE_VULKAN,

    BGFX_RENDERER_TYPE_COUNT

} bgfx_renderer_type_t;

typedef enum bgfx_access
{
    BGFX_ACCESS_READ,
    BGFX_ACCESS_WRITE,
    BGFX_ACCESS_READWRITE,

    BGFX_ACCESS_COUNT

} bgfx_access_t;

typedef enum bgfx_attrib
{
    BGFX_ATTRIB_POSITION,
    BGFX_ATTRIB_NORMAL,
    BGFX_ATTRIB_TANGENT,
    BGFX_ATTRIB_BITANGENT,
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

} bgfx_attrib_t;

typedef enum bgfx_attrib_type
{
    BGFX_ATTRIB_TYPE_UINT8,
    BGFX_ATTRIB_TYPE_INT16,
    BGFX_ATTRIB_TYPE_HALF,
    BGFX_ATTRIB_TYPE_FLOAT,

    BGFX_ATTRIB_TYPE_COUNT

} bgfx_attrib_type_t;

typedef enum bgfx_texture_format
{
    BGFX_TEXTURE_FORMAT_BC1,
    BGFX_TEXTURE_FORMAT_BC2,
    BGFX_TEXTURE_FORMAT_BC3,
    BGFX_TEXTURE_FORMAT_BC4,
    BGFX_TEXTURE_FORMAT_BC5,
    BGFX_TEXTURE_FORMAT_BC6H,
    BGFX_TEXTURE_FORMAT_BC7,
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

    BGFX_TEXTURE_FORMAT_R1,
    BGFX_TEXTURE_FORMAT_R8,
    BGFX_TEXTURE_FORMAT_R16,
    BGFX_TEXTURE_FORMAT_R16F,
    BGFX_TEXTURE_FORMAT_R32,
    BGFX_TEXTURE_FORMAT_R32F,
    BGFX_TEXTURE_FORMAT_RG8,
    BGFX_TEXTURE_FORMAT_RG16,
    BGFX_TEXTURE_FORMAT_RG16F,
    BGFX_TEXTURE_FORMAT_RG32,
    BGFX_TEXTURE_FORMAT_RG32F,
    BGFX_TEXTURE_FORMAT_BGRA8,
    BGFX_TEXTURE_FORMAT_RGBA8,
    BGFX_TEXTURE_FORMAT_RGBA16,
    BGFX_TEXTURE_FORMAT_RGBA16F,
    BGFX_TEXTURE_FORMAT_RGBA32,
    BGFX_TEXTURE_FORMAT_RGBA32F,
    BGFX_TEXTURE_FORMAT_R5G6B5,
    BGFX_TEXTURE_FORMAT_RGBA4,
    BGFX_TEXTURE_FORMAT_RGB5A1,
    BGFX_TEXTURE_FORMAT_RGB10A2,
    BGFX_TEXTURE_FORMAT_R11G11B10F,

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

} bgfx_texture_format_t;

typedef enum bgfx_uniform_type
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

} bgfx_uniform_type_t;

#define BGFX_HANDLE_T(_name) \
    typedef struct _name { uint16_t idx; } _name##_t;

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

/**
 */
typedef struct bgfx_memory
{
    uint8_t* data;
    uint32_t size;

} bgfx_memory_t;

/**
 */
typedef struct bgfx_transform
{
    float* data;
    uint16_t num;

} bgfx_transform_t;

/**
 * Eye
 */
typedef struct bgfx_hmd_eye
{
    float rotation[4];
    float translation[3];
    float fov[4];
    float adjust[3];
    float pixelsPerTanAngle[2];

} bgfx_hmd_eye_t;

/**
 * HMD
 */
typedef struct bgfx_hmd
{
    bgfx_hmd_eye_t eye[2];
    uint16_t width;
    uint16_t height;

} bgfx_hmd_t;

/**
 * Vertex declaration.
 */
typedef struct bgfx_vertex_decl
{
    uint32_t hash;
    uint16_t stride;
    uint16_t offset[BGFX_ATTRIB_COUNT];
    uint8_t  attributes[BGFX_ATTRIB_COUNT];

} bgfx_vertex_decl_t;

/**
 */
typedef struct bgfx_transient_index_buffer
{
    uint8_t* data;
    uint32_t size;
    bgfx_index_buffer_handle_t handle;
    uint32_t startIndex;

} bgfx_transient_index_buffer_t;

/**
 */
typedef struct bgfx_transient_vertex_buffer
{
    uint8_t* data;
    uint32_t size;
    uint32_t startVertex;
    uint16_t stride;
    bgfx_vertex_buffer_handle_t handle;
    bgfx_vertex_decl_handle_t decl;

} bgfx_transient_vertex_buffer_t;

/**
 */
typedef struct bgfx_instance_data_buffer
{
    uint8_t* data;
    uint32_t size;
    uint32_t offset;
    uint32_t num;
    uint16_t stride;
    bgfx_vertex_buffer_handle_t handle;

} bgfx_instance_data_buffer_t;

/**
 */
typedef struct bgfx_texture_info
{
    bgfx_texture_format_t format;
    uint32_t storageSize;
    uint16_t width;
    uint16_t height;
    uint16_t depth;
    uint8_t numMips;
    uint8_t bitsPerPixel;
    bool    cubeMap;

} bgfx_texture_info_t;

/**
 *  Renderer capabilities.
 */
typedef struct bgfx_caps
{
    /**
     *  Renderer backend type.
     */
    bgfx_renderer_type_t rendererType;

    /**
     *  Supported functionality, it includes emulated functionality.
     *  Checking supported and not emulated will give functionality
     *  natively supported by renderer.
     */
    uint64_t supported;

    uint16_t maxTextureSize;    /* < Maximum texture size.             */
    uint16_t maxViews;          /* < Maximum views.                    */
    uint16_t maxDrawCalls;      /* < Maximum draw calls.               */
    uint8_t  maxFBAttachments;  /* < Maximum frame buffer attachments. */

    /**
     *  Supported texture formats.
     *   `BGFX_CAPS_FORMAT_TEXTURE_NONE` - not supported
     *   `BGFX_CAPS_FORMAT_TEXTURE_COLOR` - supported
     *   `BGFX_CAPS_FORMAT_TEXTURE_EMULATED` - emulated
     *   `BGFX_CAPS_FORMAT_TEXTURE_VERTEX` - supported vertex texture
     */
    uint8_t formats[BGFX_TEXTURE_FORMAT_COUNT];

} bgfx_caps_t;

/**
 */
typedef enum bgfx_fatal
{
    BGFX_FATAL_DEBUG_CHECK,
    BGFX_FATAL_MINIMUM_REQUIRED_SPECS,
    BGFX_FATAL_INVALID_SHADER,
    BGFX_FATAL_UNABLE_TO_INITIALIZE,
    BGFX_FATAL_UNABLE_TO_CREATE_TEXTURE,
    BGFX_FATAL_DEVICE_LOST,

    BGFX_FATAL_COUNT

} bgfx_fatal_t;

#ifndef BGFX_SHARED_LIB_BUILD
#    define BGFX_SHARED_LIB_BUILD 0
#endif // BGFX_SHARED_LIB_BUILD

#ifndef BGFX_SHARED_LIB_USE
#    define BGFX_SHARED_LIB_USE 0
#endif // BGFX_SHARED_LIB_USE

#if defined(_MSC_VER)
#   define BGFX_VTBL_CALL __stdcall
#   define BGFX_VTBL_THIS  // passed via ecx
#   define BGFX_VTBL_THIS_ // passed via ecx
#   if BGFX_SHARED_LIB_BUILD
#       define BGFX_SHARED_LIB_API __declspec(dllexport)
#   elif BGFX_SHARED_LIB_USE
#       define BGFX_SHARED_LIB_API __declspec(dllimport)
#   else
#       define BGFX_SHARED_LIB_API
#   endif // BGFX_SHARED_LIB_*
#else
#   define BGFX_VTBL_CALL
#   define BGFX_VTBL_THIS  BGFX_VTBL_INTEFRACE _this
#   define BGFX_VTBL_THIS_ BGFX_VTBL_INTEFRACE _this,
#   define BGFX_SHARED_LIB_API
#endif // defined(_MSC_VER)

#if defined(__cplusplus)
#   define BGFX_C_API extern "C" BGFX_SHARED_LIB_API
#else
#   define BGFX_C_API BGFX_SHARED_LIB_API
#endif // defined(__cplusplus)

/**
 */
typedef struct bgfx_callback_interface
{
    const struct bgfx_callback_vtbl* vtbl;

} bgfx_callback_interface_t;

/**
 *  Callback interface to implement application specific behavior.
 *  Cached items are currently used only for OpenGL binary shaders.
 *
 *  NOTE:
 *    'fatal' callback can be called from any thread. Other callbacks
 *    are called from the render thread.
 */
typedef struct bgfx_callback_vtbl
{
#   define BGFX_VTBL_INTEFRACE bgfx_callback_interface_t

    void* ctor;

    /**
     *  If fatal code code is not BGFX_FATAL_DEBUG_CHECK this callback is
     *  called on unrecoverable error. It's not safe to continue, inform
     *  user and terminate application from this call.
     */
    void (BGFX_VTBL_CALL *fatal)(BGFX_VTBL_THIS_ bgfx_fatal_t _code, const char* _str);

    /**
     *  Return size of for cached item. Return 0 if no cached item was
     *  found.
     */
    uint32_t (BGFX_VTBL_CALL *cache_read_size)(BGFX_VTBL_THIS_ uint64_t _id);

    /**
     *  Read cached item.
     */
    bool (BGFX_VTBL_CALL *cache_read)(BGFX_VTBL_THIS_ uint64_t _id, void* _data, uint32_t _size);

    /**
     *  Write cached item.
     */
    void (BGFX_VTBL_CALL *cache_write)(BGFX_VTBL_THIS_ uint64_t _id, const void* _data, uint32_t _size);

    /**
     *  Screenshot captured. Screenshot format is always 4-byte BGRA.
     */
    void (BGFX_VTBL_CALL *screen_shot)(BGFX_VTBL_THIS_ const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _data, uint32_t _size, bool _yflip);

    /**
     *  Called when capture begins.
     */
    void (BGFX_VTBL_CALL *capture_begin)(BGFX_VTBL_THIS_ uint32_t _width, uint32_t _height, uint32_t _pitch, bgfx_texture_format_t _format, bool _yflip);

    /**
     *  Called when capture ends.
     */
    void (BGFX_VTBL_CALL *capture_end)(BGFX_VTBL_THIS);

    /**
     *  Captured frame.
     */
    void (BGFX_VTBL_CALL *capture_frame)(BGFX_VTBL_THIS_ const void* _data, uint32_t _size);

#   undef BGFX_VTBL_INTEFRACE

} bgfx_callback_vtbl_t;

/**
 */
typedef struct bgfx_reallocator_interface
{
    const struct bgfx_reallocator_vtbl* vtbl;

} bgfx_reallocator_interface_t;

/**
 */
typedef struct bgfx_reallocator_vtbl
{
#   define BGFX_VTBL_INTEFRACE bgfx_reallocator_interface_t

    void* ctor;
    void* (BGFX_VTBL_CALL *alloc)(BGFX_VTBL_THIS_ size_t _size, size_t _align, const char* _file, uint32_t _line);
    void  (BGFX_VTBL_CALL *free)(BGFX_VTBL_THIS_ void* _ptr, size_t _align, const char* _file, uint32_t _line);
    void* (BGFX_VTBL_CALL *realloc)(BGFX_VTBL_THIS_ void* _ptr, size_t _size, size_t _align, const char* _file, uint32_t _line);

#   undef BGFX_VTBL_INTEFRACE

} bgfx_reallocator_vtbl_t;

/**
 *  Start vertex declaration.
 */
BGFX_C_API void bgfx_vertex_decl_begin(bgfx_vertex_decl_t* _decl, bgfx_renderer_type_t _renderer);

/**
 *  Add attribute to vertex declaration.
 *
 *  @param _attrib Attribute semantics.
 *  @param _num Number of elements 1, 2, 3 or 4.
 *  @param _type Element type.
 *  @param _normalized When using fixed point AttribType (f.e. Uint8)
 *    value will be normalized for vertex shader usage. When normalized
 *    is set to true, AttribType::Uint8 value in range 0-255 will be
 *    in range 0.0-1.0 in vertex shader.
 *  @param _asInt Packaging rule for vertexPack, vertexUnpack, and
 *    vertexConvert for AttribType::Uint8 and AttribType::Int16.
 *    Unpacking code must be implemented inside vertex shader.
 *
 *  NOTE:
 *    Must be called between begin/end.
 */
BGFX_C_API void bgfx_vertex_decl_add(bgfx_vertex_decl_t* _decl, bgfx_attrib_t _attrib, uint8_t _num, bgfx_attrib_type_t _type, bool _normalized, bool _asInt);

/**
 *  Skip _num bytes in vertex stream.
 */
BGFX_C_API void bgfx_vertex_decl_skip(bgfx_vertex_decl_t* _decl, uint8_t _num);

/**
 *  End vertex declaration.
 */
BGFX_C_API void bgfx_vertex_decl_end(bgfx_vertex_decl_t* _decl);

/**
 *  Pack vec4 into vertex stream format.
 */
BGFX_C_API void bgfx_vertex_pack(const float _input[4], bool _inputNormalized, bgfx_attrib_t _attr, const bgfx_vertex_decl_t* _decl, void* _data, uint32_t _index);

/**
 *  Unpack vec4 from vertex stream format.
 */
BGFX_C_API void bgfx_vertex_unpack(float _output[4], bgfx_attrib_t _attr, const bgfx_vertex_decl_t* _decl, const void* _data, uint32_t _index);

/**
 *  Converts vertex stream data from one vertex stream format to another.
 *
 *  @param _destDecl Destination vertex stream declaration.
 *  @param _destData Destination vertex stream.
 *  @param _srcDecl Source vertex stream declaration.
 *  @param _srcData Source vertex stream data.
 *  @param _num Number of vertices to convert from source to destination.
 */
BGFX_C_API void bgfx_vertex_convert(const bgfx_vertex_decl_t* _destDecl, void* _destData, const bgfx_vertex_decl_t* _srcDecl, const void* _srcData, uint32_t _num);

/**
 *  Weld vertices.
 *
 *  @param _output Welded vertices remapping table. The size of buffer
 *    must be the same as number of vertices.
 *  @param _decl Vertex stream declaration.
 *  @param _data Vertex stream.
 *  @param _num Number of vertices in vertex stream.
 *  @param _epsilon Error tolerance for vertex position comparison.
 *  @returns Number of unique vertices after vertex welding.
 */
BGFX_C_API uint16_t bgfx_weld_vertices(uint16_t* _output, const bgfx_vertex_decl_t* _decl, const void* _data, uint16_t _num, float _epsilon);

/**
 *  Swizzle RGBA8 image to BGRA8.
 *
 *  @param _width Width of input image (pixels).
 *  @param _height Height of input image (pixels).
 *  @param _pitch Pitch of input image (bytes).
 *  @param _src Source image.
 *  @param _dst Destination image. Must be the same size as input image.
 *    _dst might be pointer to the same memory as _src.
 */
BGFX_C_API void bgfx_image_swizzle_bgra8(uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _src, void* _dst);

/**
 *  Downsample RGBA8 image with 2x2 pixel average filter.
 *
 *  @param _width Width of input image (pixels).
 *  @param _height Height of input image (pixels).
 *  @param _pitch Pitch of input image (bytes).
 *  @param _src Source image.
 *  @param _dst Destination image. Must be at least quarter size of
 *    input image. _dst might be pointer to the same memory as _src.
 */
BGFX_C_API void bgfx_image_rgba8_downsample_2x2(uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _src, void* _dst);

/**
 *  Returns supported backend API renderers.
 */
BGFX_C_API uint8_t bgfx_get_supported_renderers(bgfx_renderer_type_t _enum[BGFX_RENDERER_TYPE_COUNT]);

/**
 *  Returns name of renderer.
 */
BGFX_C_API const char* bgfx_get_renderer_name(bgfx_renderer_type_t _type);

/**
 *  Initialize bgfx library.
 *
 *  @param _type Select rendering backend. When set to RendererType::Count
 *    default rendering backend will be selected.
 *
 *  @param _callback Provide application specific callback interface.
 *    See: CallbackI
 *
 *  @param _reallocator Custom allocator. When custom allocator is not
 *    specified, library uses default CRT allocator. The library assumes
 *    custom allocator is thread safe.
 */
BGFX_C_API void bgfx_init(bgfx_renderer_type_t _type, bgfx_callback_interface_t* _callback, bgfx_reallocator_interface_t* _allocator);

/**
 *  Shutdown bgfx library.
 */
BGFX_C_API void bgfx_shutdown();

/**
 *  Reset graphic settings.
 */
BGFX_C_API void bgfx_reset(uint32_t _width, uint32_t _height, uint32_t _flags);

/**
 *  Advance to next frame. When using multithreaded renderer, this call
 *  just swaps internal buffers, kicks render thread, and returns. In
 *  singlethreaded renderer this call does frame rendering.
 *
 *  @returns Current frame number. This might be used in conjunction with
 *    double/multi buffering data outside the library and passing it to
 *    library via makeRef calls.
 */
BGFX_C_API uint32_t bgfx_frame();

/**
 *  Returns current renderer backend API type.
 *
 *  NOTE:
 *    Library must be initialized.
 */
BGFX_C_API bgfx_renderer_type_t bgfx_get_renderer_type();

/**
 *  Returns renderer capabilities.
 *
 *  NOTE:
 *    Library must be initialized.
 */
BGFX_C_API const bgfx_caps_t* bgfx_get_caps();

/**
 * Returns HMD info.
 */
BGFX_C_API const bgfx_hmd_t* bgfx_get_hmd();

/**
 *  Allocate buffer to pass to bgfx calls. Data will be freed inside bgfx.
 */
BGFX_C_API const bgfx_memory_t* bgfx_alloc(uint32_t _size);

/**
 *  Allocate buffer and copy data into it. Data will be freed inside bgfx.
 */
BGFX_C_API const bgfx_memory_t* bgfx_copy(const void* _data, uint32_t _size);

/**
 *  Make reference to data to pass to bgfx. Unlike bgfx::alloc this call
 *  doesn't allocate memory for data. It just copies pointer to data.
 *  You must make sure data is available for at least 2 bgfx::frame calls.
 */
BGFX_C_API const bgfx_memory_t* bgfx_make_ref(const void* _data, uint32_t _size);

/**
 *  Set debug flags.
 *
 *  @param _debug Available flags:
 *
 *    BGFX_DEBUG_IFH - Infinitely fast hardware. When this flag is set
 *      all rendering calls will be skipped. It's useful when profiling
 *      to quickly assess bottleneck between CPU and GPU.
 *
 *    BGFX_DEBUG_STATS - Display internal statistics.
 *
 *    BGFX_DEBUG_TEXT - Display debug text.
 *
 *    BGFX_DEBUG_WIREFRAME - Wireframe rendering. All rendering
 *      primitives will be rendered as lines.
 */
BGFX_C_API void bgfx_set_debug(uint32_t _debug);

/**
 *  Clear internal debug text buffer.
 */
BGFX_C_API void bgfx_dbg_text_clear(uint8_t _attr, bool _small);

/**
 *  Print into internal debug text buffer.
 */
BGFX_C_API void bgfx_dbg_text_printf(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, ...);

/**
 *  Draw image into internal debug text buffer.
 *
 *  @param _x      X position from top-left.
 *  @param _y      Y position from top-left.
 *  @param _width  Image width.
 *  @param _height Image height.
 *  @param _data   Raw image data (character/attribute raw encoding).
 *  @param _pitch  Image pitch in bytes.
 */
BGFX_C_API void bgfx_dbg_text_image(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const void* _data, uint16_t _pitch);

/**
 *  Create static index buffer.
 *
 *  NOTE:
 *    Only 16-bit index buffer is supported.
 */
BGFX_C_API bgfx_index_buffer_handle_t bgfx_create_index_buffer(const bgfx_memory_t* _mem);

/**
 *  Destroy static index buffer.
 */
BGFX_C_API void bgfx_destroy_index_buffer(bgfx_index_buffer_handle_t _handle);

/**
 *  Create static vertex buffer.
 *
 *  @param _mem Vertex buffer data.
 *  @param _decl Vertex declaration.
 *  @returns Static vertex buffer handle.
 */
BGFX_C_API bgfx_vertex_buffer_handle_t bgfx_create_vertex_buffer(const bgfx_memory_t* _mem, const bgfx_vertex_decl_t* _decl, uint8_t _flags);

/**
 *  Destroy static vertex buffer.
 *
 *  @param _handle Static vertex buffer handle.
 */
BGFX_C_API void bgfx_destroy_vertex_buffer(bgfx_vertex_buffer_handle_t _handle);

/**
 *  Create empty dynamic index buffer.
 *
 *  @param _num Number of indices.
 *
 *  NOTE:
 *    Only 16-bit index buffer is supported.
 */
BGFX_C_API bgfx_dynamic_index_buffer_handle_t bgfx_create_dynamic_index_buffer(uint32_t _num);

/**
 *  Create dynamic index buffer and initialized it.
 *
 *  @param _mem Index buffer data.
 *
 *  NOTE:
 *    Only 16-bit index buffer is supported.
 */
BGFX_C_API bgfx_dynamic_index_buffer_handle_t bgfx_create_dynamic_index_buffer_mem(const bgfx_memory_t* _mem);

/**
 *  Update dynamic index buffer.
 *
 *  @param _handle Dynamic index buffer handle.
 *  @param _mem Index buffer data.
 */
BGFX_C_API void bgfx_update_dynamic_index_buffer(bgfx_dynamic_index_buffer_handle_t _handle, const bgfx_memory_t* _mem);

/**
 *  Destroy dynamic index buffer.
 *
 *  @param _handle Dynamic index buffer handle.
 */
BGFX_C_API void bgfx_destroy_dynamic_index_buffer(bgfx_dynamic_index_buffer_handle_t _handle);

/**
 *  Create empty dynamic vertex buffer.
 *
 *  @param _num Number of vertices.
 *  @param _decl Vertex declaration.
 */
BGFX_C_API bgfx_dynamic_vertex_buffer_handle_t bgfx_create_dynamic_vertex_buffer(uint32_t _num, const bgfx_vertex_decl_t* _decl, uint8_t _flags);

/**
 *  Create dynamic vertex buffer and initialize it.
 *
 *  @param _mem Vertex buffer data.
 *  @param _decl Vertex declaration.
 */
BGFX_C_API bgfx_dynamic_vertex_buffer_handle_t bgfx_create_dynamic_vertex_buffer_mem(const bgfx_memory_t* _mem, const bgfx_vertex_decl_t* _decl);

/**
 *  Update dynamic vertex buffer.
 */
BGFX_C_API void bgfx_update_dynamic_vertex_buffer(bgfx_dynamic_vertex_buffer_handle_t _handle, const bgfx_memory_t* _mem);

/**
 *  Destroy dynamic vertex buffer.
 */
BGFX_C_API void bgfx_destroy_dynamic_vertex_buffer(bgfx_dynamic_vertex_buffer_handle_t _handle);

/**
 *  Returns true if internal transient index buffer has enough space.
 *
 *  @param _num Number of indices.
 */
BGFX_C_API bool bgfx_check_avail_transient_index_buffer(uint32_t _num);

/**
 *  Returns true if internal transient vertex buffer has enough space.
 *
 *  @param _num Number of vertices.
 *  @param _decl Vertex declaration.
 */
BGFX_C_API bool bgfx_check_avail_transient_vertex_buffer(uint32_t _num, const bgfx_vertex_decl_t* _decl);

/**
 *  Returns true if internal instance data buffer has enough space.
 *
 *  @param _num Number of instances.
 *  @param _stride Stride per instance.
 */
BGFX_C_API bool bgfx_check_avail_instance_data_buffer(uint32_t _num, uint16_t _stride);

/**
 *  Returns true if both internal transient index and vertex buffer have
 *  enough space.
 *
 *  @param _numVertices Number of vertices.
 *  @param _decl Vertex declaration.
 *  @param _numIndices Number of indices.
 */
BGFX_C_API bool bgfx_check_avail_transient_buffers(uint32_t _numVertices, const bgfx_vertex_decl_t* _decl, uint32_t _numIndices);

/**
 *  Allocate transient index buffer.
 *
 *  @param[out] _tib TransientIndexBuffer structure is filled and is valid
 *    for the duration of frame, and it can be reused for multiple draw
 *    calls.
 *  @param _num Number of indices to allocate.
 *
 *  NOTE:
 *    1. You must call setIndexBuffer after alloc in order to avoid memory
 *       leak.
 *    2. Only 16-bit index buffer is supported.
 */
BGFX_C_API void bgfx_alloc_transient_index_buffer(bgfx_transient_index_buffer_t* _tib, uint32_t _num);

/**
 *  Allocate transient vertex buffer.
 *
 *  @param[out] _tvb TransientVertexBuffer structure is filled and is valid
 *    for the duration of frame, and it can be reused for multiple draw
 *    calls.
 *  @param _num Number of vertices to allocate.
 *  @param _decl Vertex declaration.
 *
 *  NOTE:
 *    You must call setVertexBuffer after alloc in order to avoid memory
 *    leak.
 */
BGFX_C_API void bgfx_alloc_transient_vertex_buffer(bgfx_transient_vertex_buffer_t* _tvb, uint32_t _num, const bgfx_vertex_decl_t* _decl);

/**
 *  Check for required space and allocate transient vertex and index
 *  buffers. If both space requirements are satisfied function returns
 *  true.
 *
 *  NOTE:
 *    Only 16-bit index buffer is supported.
 */
BGFX_C_API bool bgfx_alloc_transient_buffers(bgfx_transient_vertex_buffer_t* _tvb, const bgfx_vertex_decl_t* _decl, uint32_t _numVertices, bgfx_transient_index_buffer_t* _tib, uint32_t _numIndices);

/**
 *  Allocate instance data buffer.
 *
 *  NOTE:
 *    You must call setInstanceDataBuffer after alloc in order to avoid
 *    memory leak.
 */
BGFX_C_API const bgfx_instance_data_buffer_t* bgfx_alloc_instance_data_buffer(uint32_t _num, uint16_t _stride);

/**
 *  Create shader from memory buffer.
 */
BGFX_C_API bgfx_shader_handle_t bgfx_create_shader(const bgfx_memory_t* _mem);

/**
 *  Returns num of uniforms, and uniform handles used inside shader.
 *
 *  @param _handle Shader handle.
 *  @param _uniforms UniformHandle array where data will be stored.
 *  @param _max Maximum capacity of array.
 *  @returns Number of uniforms used by shader.
 *
 *  NOTE:
 *    Only non-predefined uniforms are returned.
 */
BGFX_C_API uint16_t bgfx_get_shader_uniforms(bgfx_shader_handle_t _handle, bgfx_uniform_handle_t* _uniforms, uint16_t _max);

/**
 *  Destroy shader. Once program is created with shader it is safe to
 *  destroy shader.
 */
BGFX_C_API void bgfx_destroy_shader(bgfx_shader_handle_t _handle);

/**
 *  Create program with vertex and fragment shaders.
 *
 *  @param _vsh Vertex shader.
 *  @param _fsh Fragment shader.
 *  @param _destroyShaders If true, shaders will be destroyed when
 *    program is destroyed.
 *  @returns Program handle if vertex shader output and fragment shader
 *    input are matching, otherwise returns invalid program handle.
 */
BGFX_C_API bgfx_program_handle_t bgfx_create_program(bgfx_shader_handle_t _vsh, bgfx_shader_handle_t _fsh, bool _destroyShaders);

/**
 *  Destroy program.
 */
BGFX_C_API void bgfx_destroy_program(bgfx_program_handle_t _handle);

/**
 *  Calculate amount of memory required for texture.
 */
BGFX_C_API void bgfx_calc_texture_size(bgfx_texture_info_t* _info, uint16_t _width, uint16_t _height, uint16_t _depth, bool _cubeMap, uint8_t _numMips, bgfx_texture_format_t _format);

/**
 *  Create texture from memory buffer.
 *
 *  @param _mem DDS, KTX or PVR texture data.
 *  @param _flags Default texture sampling mode is linear, and wrap mode
 *    is repeat.
 *
 *    BGFX_TEXTURE_[U/V/W]_[MIRROR/CLAMP] - Mirror or clamp to edge wrap
 *      mode.
 *
 *    BGFX_TEXTURE_[MIN/MAG/MIP]_[POINT/ANISOTROPIC] - Point or anisotropic
 *      sampling.
 *
 *  @param _skip Skip top level mips when parsing texture.
 *  @param _info Returns parsed texture information.
 *  @returns Texture handle.
 */
BGFX_C_API bgfx_texture_handle_t bgfx_create_texture(const bgfx_memory_t* _mem, uint32_t _flags, uint8_t _skip, bgfx_texture_info_t* _info);

/**
 *  Create 2D texture.
 *
 *  @param _width
 *  @param _height
 *  @param _numMips
 *  @param _format
 *  @param _flags
 *  @param _mem
 */
BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_2d(uint16_t _width, uint16_t _height, uint8_t _numMips, bgfx_texture_format_t _format, uint32_t _flags, const bgfx_memory_t* _mem);

/**
 *  Create 3D texture.
 *
 *  @param _width
 *  @param _height
 *  @param _depth
 *  @param _numMips
 *  @param _format
 *  @param _flags
 *  @param _mem
 */
BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_3d(uint16_t _width, uint16_t _height, uint16_t _depth, uint8_t _numMips, bgfx_texture_format_t _format, uint32_t _flags, const bgfx_memory_t* _mem);

/**
 *  Create Cube texture.
 *
 *  @param _size
 *  @param _numMips
 *  @param _format
 *  @param _flags
 *  @param _mem
 */
BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_cube(uint16_t _size, uint8_t _numMips, bgfx_texture_format_t _format, uint32_t _flags, const bgfx_memory_t* _mem);

/**
 *  Update 2D texture.
 *
 *  @param _handle
 *  @param _mip
 *  @param _x
 *  @param _y
 *  @param _width
 *  @param _height
 *  @param _mem
 *  @param _pitch Pitch of input image (bytes). When _pitch is set to
 *    UINT16_MAX, it will be calculated internally based on _width.
 */
BGFX_C_API void bgfx_update_texture_2d(bgfx_texture_handle_t _handle, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const bgfx_memory_t* _mem, uint16_t _pitch);

/**
 *  Update 3D texture.
 *
 *  @param _handle
 *  @param _mip
 *  @param _x
 *  @param _y
 *  @param _z
 *  @param _width
 *  @param _height
 *  @param _depth
 *  @param _mem
 */
BGFX_C_API void bgfx_update_texture_3d(bgfx_texture_handle_t _handle, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _z, uint16_t _width, uint16_t _height, uint16_t _depth, const bgfx_memory_t* _mem);

/**
 *  Update Cube texture.
 *
 *  @param _handle
 *  @param _side Cubemap side, where 0 is +X, 1 is -X, 2 is +Y, 3 is
 *    -Y, 4 is +Z, and 5 is -Z.
 *
 *               +----------+
 *               |-z       2|
 *               | ^  +y    |
 *               | |        |
 *               | +---->+x |
 *    +----------+----------+----------+----------+
 *    |+y       1|+y       4|+y       0|+y       5|
 *    | ^  -x    | ^  +z    | ^  +x    | ^  -z    |
 *    | |        | |        | |        | |        |
 *    | +---->+z | +---->+x | +---->-z | +---->-x |
 *    +----------+----------+----------+----------+
 *               |+z       3|
 *               | ^  -y    |
 *               | |        |
 *               | +---->+x |
 *               +----------+
 *
 *  @param _mip
 *  @param _x
 *  @param _y
 *  @param _width
 *  @param _height
 *  @param _mem
 *  @param _pitch Pitch of input image (bytes). When _pitch is set to
 *    UINT16_MAX, it will be calculated internally based on _width.
 */
BGFX_C_API void bgfx_update_texture_cube(bgfx_texture_handle_t _handle, uint8_t _side, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const bgfx_memory_t* _mem, uint16_t _pitch);

/**
 *  Destroy texture.
 */
BGFX_C_API void bgfx_destroy_texture(bgfx_texture_handle_t _handle);

/**
 *  Create frame buffer (simple).
 *
 *  @param _width Texture width.
 *  @param _height Texture height.
 *  @param _format Texture format.
 *  @param _textureFlags Texture flags.
 */
BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer(uint16_t _width, uint16_t _height, bgfx_texture_format_t _format, uint32_t _textureFlags);

/**
 *  Create frame buffer.
 *
 *  @param _num Number of texture attachments.
 *  @param _handles Texture attachments.
 *  @param _destroyTextures If true, textures will be destroyed when
 *    frame buffer is destroyed.
 */
BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_from_handles(uint8_t _num, bgfx_texture_handle_t* _handles, bool _destroyTextures);

/**
 *  Create frame buffer for multiple window rendering.
 *
 *  @param _nwh OS' target native window handle.
 *  @param _width Window back buffer width.
 *  @param _height Window back buffer height.
 *  @param _depthFormat Window back buffer depth format.
 *
 *  NOTE:
 *    Frame buffer cannnot be used for sampling.
 */
BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_from_nwh(void* _nwh, uint16_t _width, uint16_t _height, bgfx_texture_format_t _depthFormat);

/**
 *  Destroy frame buffer.
 */
BGFX_C_API void bgfx_destroy_frame_buffer(bgfx_frame_buffer_handle_t _handle);

/**
 *  Create shader uniform parameter.
 *
 *  @param _name Uniform name in shader.
 *  @param _type Type of uniform (See: UniformType).
 *  @param _num Number of elements in array.
 *
 *  Predefined uniforms:
 *
 *    u_viewRect vec4(x, y, width, height) - view rectangle for current
 *      view.
 *
 *    u_viewTexel vec4(1.0/width, 1.0/height, undef, undef) - inverse
 *      width and height
 *
 *    u_view mat4 - view matrix
 *
 *    u_invView mat4 - inverted view matrix
 *
 *    u_proj mat4 - projection matrix
 *
 *    u_invProj mat4 - inverted projection matrix
 *
 *    u_viewProj mat4 - concatenated view projection matrix
 *
 *    u_invViewProj mat4 - concatenated inverted view projection matrix
 *
 *    u_model mat4[BGFX_CONFIG_MAX_BONES] - array of model matrices.
 *
 *    u_modelView mat4 - concatenated model view matrix, only first
 *      model matrix from array is used.
 *
 *    u_modelViewProj mat4 - concatenated model view projection matrix.
 *
 *    u_alphaRef float - alpha reference value for alpha test.
 */
BGFX_C_API bgfx_uniform_handle_t bgfx_create_uniform(const char* _name, bgfx_uniform_type_t _type, uint16_t _num);

/**
 *  Destroy shader uniform parameter.
 */
BGFX_C_API void bgfx_destroy_uniform(bgfx_uniform_handle_t _handle);

/**
 *  Set clear color palette value.
 *
 *  @param _index Index into palette.
 *  @param _rgba RGBA floating point value.
 */
BGFX_C_API void bgfx_set_clear_color(uint8_t _index, const float _rgba[4]);

/**
 *  Set view name.
 *
 *  @param _id View id.
 *  @param _name View name.
 *
 *  NOTE:
 *    This is debug only feature.
 */
BGFX_C_API void bgfx_set_view_name(uint8_t _id, const char* _name);

/**
 *  Set view rectangle. Draw primitive outside view will be clipped.
 *
 *  @param _id View id.
 *  @param _x Position x from the left corner of the window.
 *  @param _y Position y from the top corner of the window.
 *  @param _width Width of view port region.
 *  @param _height Height of view port region.
 */
BGFX_C_API void bgfx_set_view_rect(uint8_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

/**
 *  Set view scissor. Draw primitive outside view will be clipped. When
 *  _x, _y, _width and _height are set to 0, scissor will be disabled.
 *
 *  @param _x Position x from the left corner of the window.
 *  @param _y Position y from the top corner of the window.
 *  @param _width Width of scissor region.
 *  @param _height Height of scissor region.
 */
BGFX_C_API void bgfx_set_view_scissor(uint8_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

/**
 *  Set view clear flags.
 *
 *  @param _id View id.
 *  @param _flags Clear flags. Use BGFX_CLEAR_NONE to remove any clear
 *    operation. See: BGFX_CLEAR_*.
 *  @param _rgba Color clear value.
 *  @param _depth Depth clear value.
 *  @param _stencil Stencil clear value.
 */
BGFX_C_API void bgfx_set_view_clear(uint8_t _id, uint16_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil);

/**
 *  Set view clear flags with different clear color for each
 *  frame buffer texture. Must use setClearColor to setup clear color
 *  palette.

 *  @param _id View id.
 *  @param _flags Clear flags. Use BGFX_CLEAR_NONE to remove any clear
 *  operation. See: BGFX_CLEAR_*.
 *  @param _depth Depth clear value.
 *  @param _stencil Stencil clear value.
 */
BGFX_C_API void bgfx_set_view_clear_mrt(uint8_t _id, uint16_t _flags, float _depth, uint8_t _stencil, uint8_t _0, uint8_t _1, uint8_t _2, uint8_t _3, uint8_t _4, uint8_t _5, uint8_t _6, uint8_t _7);

/**
 *  Set view into sequential mode. Draw calls will be sorted in the same
 *  order in which submit calls were called.
 */
BGFX_C_API void bgfx_set_view_seq(uint8_t _id, bool _enabled);

/**
 *  Set view frame buffer.
 *
 *  @param _id View id.
 *  @param _handle Frame buffer handle. Passing BGFX_INVALID_HANDLE as
 *    frame buffer handle will draw primitives from this view into
 *    default back buffer.
 */
BGFX_C_API void bgfx_set_view_frame_buffer(uint8_t _id, bgfx_frame_buffer_handle_t _handle);

/**
 *  Set view view and projection matrices, all draw primitives in this
 *  view will use these matrices.
 */
BGFX_C_API void bgfx_set_view_transform(uint8_t _id, const void* _view, const void* _proj);

/**
 *  Set view view and projection matrices, all draw primitives in this
 *  view will use these matrices.
 */
BGFX_C_API void bgfx_set_view_transform_stereo(uint8_t _id, const void* _view, const void* _projL, uint8_t _flags, const void* _projR);

/**
 *  Sets debug marker.
 */
BGFX_C_API void bgfx_set_marker(const char* _marker);

/**
 *  Set render states for draw primitive.
 *
 *  @param _state State flags. Default state for primitive type is
 *    triangles. See: BGFX_STATE_DEFAULT.
 *
 *    BGFX_STATE_ALPHA_WRITE - Enable alpha write.
 *    BGFX_STATE_DEPTH_WRITE - Enable depth write.
 *    BGFX_STATE_DEPTH_TEST_* - Depth test function.
 *    BGFX_STATE_BLEND_* - See NOTE 1: BGFX_STATE_BLEND_FUNC.
 *    BGFX_STATE_BLEND_EQUATION_* - See NOTE 2.
 *    BGFX_STATE_CULL_* - Backface culling mode.
 *    BGFX_STATE_RGB_WRITE - Enable RGB write.
 *    BGFX_STATE_MSAA - Enable MSAA.
 *    BGFX_STATE_PT_[LINES/POINTS] - Primitive type.
 *
 *  @param _rgba Sets blend factor used by BGFX_STATE_BLEND_FACTOR and
 *    BGFX_STATE_BLEND_INV_FACTOR blend modes.
 *
 *  NOTE:
 *    1. Use BGFX_STATE_ALPHA_REF, BGFX_STATE_POINT_SIZE and
 *       BGFX_STATE_BLEND_FUNC macros to setup more complex states.
 *    2. BGFX_STATE_BLEND_EQUATION_ADD is set when no other blend
 *       equation is specified.
 */
BGFX_C_API void bgfx_set_state(uint64_t _state, uint32_t _rgba);

/**
 *  Set stencil test state.
 *
 *  @param _fstencil Front stencil state.
 *  @param _bstencil Back stencil state. If back is set to BGFX_STENCIL_NONE
 *    _fstencil is applied to both front and back facing primitives.
 */
BGFX_C_API void bgfx_set_stencil(uint32_t _fstencil, uint32_t _bstencil);

/**
 *  Set scissor for draw primitive. For scissor for all primitives in
 *  view see setViewScissor.
 *
 *  @param _x Position x from the left corner of the window.
 *  @param _y Position y from the top corner of the window.
 *  @param _width Width of scissor region.
 *  @param _height Height of scissor region.
 *  @returns Scissor cache index.
 */
BGFX_C_API uint16_t bgfx_set_scissor(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

/**
 *  Set scissor from cache for draw primitive.
 *
 *  @param _cache Index in scissor cache. Passing UINT16_MAX unset primitive
 *    scissor and primitive will use view scissor instead.
 */
BGFX_C_API void bgfx_set_scissor_cached(uint16_t _cache);

/**
 *  Set model matrix for draw primitive. If it is not called model will
 *  be rendered with identity model matrix.
 *
 *  @param _mtx Pointer to first matrix in array.
 *  @param _num Number of matrices in array.
 *  @returns index into matrix cache in case the same model matrix has
 *    to be used for other draw primitive call.
 */
BGFX_C_API uint32_t bgfx_set_transform(const void* _mtx, uint16_t _num);

/**
 *  Reserve `_num` matrices in internal matrix cache. Pointer returned
 *  can be modifed until `bgfx::frame` is called.
 *
 *  @param _transform Pointer to `Transform` structure.
 *  @param _num Number of matrices.
 *  @returns index into matrix cache.
 */
BGFX_C_API uint32_t bgfx_alloc_transform(bgfx_transform_t* _transform, uint16_t _num);

/**
 *  Set model matrix from matrix cache for draw primitive.
 *
 *  @param _cache Index in matrix cache.
 *  @param _num Number of matrices from cache.
 */
BGFX_C_API void bgfx_set_transform_cached(uint32_t _cache, uint16_t _num);

/**
 *  Set shader uniform parameter for draw primitive.
 */
BGFX_C_API void bgfx_set_uniform(bgfx_uniform_handle_t _handle, const void* _value, uint16_t _num);

/**
 *  Set index buffer for draw primitive.
 */
BGFX_C_API void bgfx_set_index_buffer(bgfx_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices);

/**
 *  Set index buffer for draw primitive.
 */
BGFX_C_API void bgfx_set_dynamic_index_buffer(bgfx_dynamic_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices);

/**
 *  Set index buffer for draw primitive.
 */
BGFX_C_API void bgfx_set_transient_index_buffer(const bgfx_transient_index_buffer_t* _tib, uint32_t _firstIndex, uint32_t _numIndices);

/**
 *  Set vertex buffer for draw primitive.
 */
BGFX_C_API void bgfx_set_vertex_buffer(bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices);

/**
 *  Set vertex buffer for draw primitive.
 */
BGFX_C_API void bgfx_set_dynamic_vertex_buffer(bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _numVertices);

/**
 *  Set vertex buffer for draw primitive.
 */
BGFX_C_API void bgfx_set_transient_vertex_buffer(const bgfx_transient_vertex_buffer_t* _tvb, uint32_t _startVertex, uint32_t _numVertices);

/**
 *  Set instance data buffer for draw primitive.
 */
BGFX_C_API void bgfx_set_instance_data_buffer(const bgfx_instance_data_buffer_t* _idb, uint32_t _num);

/**
 *  Set program for draw primitive.
 */
BGFX_C_API void bgfx_set_program(bgfx_program_handle_t _handle);

/**
 *  Set texture stage for draw primitive.
 *
 *  @param _stage Texture unit.
 *  @param _sampler Program sampler.
 *  @param _handle Texture handle.
 *  @param _flags Texture sampling mode. Default value UINT32_MAX uses
 *    texture sampling settings from the texture.
 *
 *    BGFX_TEXTURE_[U/V/W]_[MIRROR/CLAMP] - Mirror or clamp to edge wrap
 *      mode.
 *
 *    BGFX_TEXTURE_[MIN/MAG/MIP]_[POINT/ANISOTROPIC] - Point or anisotropic
 *      sampling.
 *
 *  @param _flags Texture sampler filtering flags. UINT32_MAX use the
 *    sampler filtering mode set by texture.
 */
BGFX_C_API void bgfx_set_texture(uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint32_t _flags);

/**
 *  Set texture stage for draw primitive.
 *
 *  @param _stage Texture unit.
 *  @param _sampler Program sampler.
 *  @param _handle Frame buffer handle.
 *  @param _attachment Attachment index.
 *  @param _flags Texture sampling mode. Default value UINT32_MAX uses
 *    texture sampling settings from the texture.
 *
 *    BGFX_TEXTURE_[U/V/W]_[MIRROR/CLAMP] - Mirror or clamp to edge wrap
 *      mode.
 *
 *    BGFX_TEXTURE_[MIN/MAG/MIP]_[POINT/ANISOTROPIC] - Point or anisotropic
 *      sampling.
 */
BGFX_C_API void bgfx_set_texture_from_frame_buffer(uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_frame_buffer_handle_t _handle, uint8_t _attachment, uint32_t _flags);

/**
 *  Submit primitive for rendering into single view.
 *
 *  @param _id View id.
 *  @param _depth Depth for sorting.
 *  @returns Number of draw calls.
 */
BGFX_C_API uint32_t bgfx_submit(uint8_t _id, int32_t _depth);

/**
 *
 */
BGFX_C_API void bgfx_set_image(uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint8_t _mip, bgfx_access_t _access, bgfx_texture_format_t _format);

/**
 *
 */
BGFX_C_API void bgfx_set_image_from_frame_buffer(uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_frame_buffer_handle_t _handle, uint8_t _attachment, bgfx_access_t _access, bgfx_texture_format_t _format);

/**
 * Dispatch compute.
 */
BGFX_C_API void bgfx_dispatch(uint8_t _id, bgfx_program_handle_t _handle, uint16_t _numX, uint16_t _numY, uint16_t _numZ, uint8_t _flags);

/**
 *  Discard all previously set state for draw call.
 */
BGFX_C_API void bgfx_discard();

/**
 *  Request screen shot.
 *
 *  @param _filePath Will be passed to CallbackI::screenShot callback.
 *
 *  NOTE:
 *    CallbackI::screenShot must be implemented.
 */
BGFX_C_API void bgfx_save_screen_shot(const char* _filePath);

#endif // BGFX_C99_H_HEADER_GUARD
