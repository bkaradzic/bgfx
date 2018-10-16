/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 *
 * vim: set tabstop=4 expandtab:
 */

#ifndef BGFX_C99_H_HEADER_GUARD
#define BGFX_C99_H_HEADER_GUARD

#include <stdarg.h>  // va_list
#include <stdbool.h> // bool
#include <stdint.h>  // uint32_t
#include <stdlib.h>  // size_t

#include <bx/platform.h>

#if !defined(BGFX_INVALID_HANDLE)
#   define BGFX_INVALID_HANDLE { UINT16_MAX }
#endif // !defined(BGFX_INVALID_HANDLE)

#ifndef BGFX_SHARED_LIB_BUILD
#    define BGFX_SHARED_LIB_BUILD 0
#endif // BGFX_SHARED_LIB_BUILD

#ifndef BGFX_SHARED_LIB_USE
#    define BGFX_SHARED_LIB_USE 0
#endif // BGFX_SHARED_LIB_USE

#if BX_PLATFORM_WINDOWS
#   define BGFX_SYMBOL_EXPORT __declspec(dllexport)
#   define BGFX_SYMBOL_IMPORT __declspec(dllimport)
#else
#   define BGFX_SYMBOL_EXPORT __attribute__((visibility("default")))
#   define BGFX_SYMBOL_IMPORT
#endif // BX_PLATFORM_WINDOWS

#if BGFX_SHARED_LIB_BUILD
#   define BGFX_SHARED_LIB_API BGFX_SYMBOL_EXPORT
#elif BGFX_SHARED_LIB_USE
#   define BGFX_SHARED_LIB_API BGFX_SYMBOL_IMPORT
#else
#   define BGFX_SHARED_LIB_API
#endif // BGFX_SHARED_LIB_*

#if defined(__cplusplus)
#   define BGFX_C_API extern "C" BGFX_SHARED_LIB_API
#else
#   define BGFX_C_API BGFX_SHARED_LIB_API
#endif // defined(__cplusplus)

#include "../defines.h"

typedef enum bgfx_renderer_type
{
    BGFX_RENDERER_TYPE_NOOP,
    BGFX_RENDERER_TYPE_DIRECT3D9,
    BGFX_RENDERER_TYPE_DIRECT3D11,
    BGFX_RENDERER_TYPE_DIRECT3D12,
    BGFX_RENDERER_TYPE_GNM,
    BGFX_RENDERER_TYPE_METAL,
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
    BGFX_ATTRIB_COLOR2,
    BGFX_ATTRIB_COLOR3,
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
    BGFX_ATTRIB_TYPE_UINT10,
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
    BGFX_TEXTURE_FORMAT_ATC,
    BGFX_TEXTURE_FORMAT_ATCE,
    BGFX_TEXTURE_FORMAT_ATCI,
    BGFX_TEXTURE_FORMAT_ASTC4x4,
    BGFX_TEXTURE_FORMAT_ASTC5x5,
    BGFX_TEXTURE_FORMAT_ASTC6x6,
    BGFX_TEXTURE_FORMAT_ASTC8x5,
    BGFX_TEXTURE_FORMAT_ASTC8x6,
    BGFX_TEXTURE_FORMAT_ASTC10x5,

    BGFX_TEXTURE_FORMAT_UNKNOWN,

    BGFX_TEXTURE_FORMAT_R1,
    BGFX_TEXTURE_FORMAT_A8,
    BGFX_TEXTURE_FORMAT_R8,
    BGFX_TEXTURE_FORMAT_R8I,
    BGFX_TEXTURE_FORMAT_R8U,
    BGFX_TEXTURE_FORMAT_R8S,
    BGFX_TEXTURE_FORMAT_R16,
    BGFX_TEXTURE_FORMAT_R16I,
    BGFX_TEXTURE_FORMAT_R16U,
    BGFX_TEXTURE_FORMAT_R16F,
    BGFX_TEXTURE_FORMAT_R16S,
    BGFX_TEXTURE_FORMAT_R32I,
    BGFX_TEXTURE_FORMAT_R32U,
    BGFX_TEXTURE_FORMAT_R32F,
    BGFX_TEXTURE_FORMAT_RG8,
    BGFX_TEXTURE_FORMAT_RG8I,
    BGFX_TEXTURE_FORMAT_RG8U,
    BGFX_TEXTURE_FORMAT_RG8S,
    BGFX_TEXTURE_FORMAT_RG16,
    BGFX_TEXTURE_FORMAT_RG16I,
    BGFX_TEXTURE_FORMAT_RG16U,
    BGFX_TEXTURE_FORMAT_RG16F,
    BGFX_TEXTURE_FORMAT_RG16S,
    BGFX_TEXTURE_FORMAT_RG32I,
    BGFX_TEXTURE_FORMAT_RG32U,
    BGFX_TEXTURE_FORMAT_RG32F,
    BGFX_TEXTURE_FORMAT_RGB8,
    BGFX_TEXTURE_FORMAT_RGB8I,
    BGFX_TEXTURE_FORMAT_RGB8U,
    BGFX_TEXTURE_FORMAT_RGB8S,
    BGFX_TEXTURE_FORMAT_RGB9E5F,
    BGFX_TEXTURE_FORMAT_BGRA8,
    BGFX_TEXTURE_FORMAT_RGBA8,
    BGFX_TEXTURE_FORMAT_RGBA8I,
    BGFX_TEXTURE_FORMAT_RGBA8U,
    BGFX_TEXTURE_FORMAT_RGBA8S,
    BGFX_TEXTURE_FORMAT_RGBA16,
    BGFX_TEXTURE_FORMAT_RGBA16I,
    BGFX_TEXTURE_FORMAT_RGBA16U,
    BGFX_TEXTURE_FORMAT_RGBA16F,
    BGFX_TEXTURE_FORMAT_RGBA16S,
    BGFX_TEXTURE_FORMAT_RGBA32I,
    BGFX_TEXTURE_FORMAT_RGBA32U,
    BGFX_TEXTURE_FORMAT_RGBA32F,
    BGFX_TEXTURE_FORMAT_R5G6B5,
    BGFX_TEXTURE_FORMAT_RGBA4,
    BGFX_TEXTURE_FORMAT_RGB5A1,
    BGFX_TEXTURE_FORMAT_RGB10A2,
    BGFX_TEXTURE_FORMAT_RG11B10F,

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
    BGFX_UNIFORM_TYPE_INT1,
    BGFX_UNIFORM_TYPE_END,

    BGFX_UNIFORM_TYPE_VEC4,
    BGFX_UNIFORM_TYPE_MAT3,
    BGFX_UNIFORM_TYPE_MAT4,

    BGFX_UNIFORM_TYPE_COUNT

} bgfx_uniform_type_t;

typedef enum bgfx_backbuffer_ratio
{
    BGFX_BACKBUFFER_RATIO_EQUAL,
    BGFX_BACKBUFFER_RATIO_HALF,
    BGFX_BACKBUFFER_RATIO_QUARTER,
    BGFX_BACKBUFFER_RATIO_EIGHTH,
    BGFX_BACKBUFFER_RATIO_SIXTEENTH,
    BGFX_BACKBUFFER_RATIO_DOUBLE,

    BGFX_BACKBUFFER_RATIO_COUNT

} bgfx_backbuffer_ratio_t;

typedef enum bgfx_occlusion_query_result
{
    BGFX_OCCLUSION_QUERY_RESULT_INVISIBLE,
    BGFX_OCCLUSION_QUERY_RESULT_VISIBLE,
    BGFX_OCCLUSION_QUERY_RESULT_NORESULT,

    BGFX_OCCLUSION_QUERY_RESULT_COUNT

} bgfx_occlusion_query_result_t;

typedef enum bgfx_topology
{
    BGFX_TOPOLOGY_TRI_LIST,
    BGFX_TOPOLOGY_TRI_STRIP,
    BGFX_TOPOLOGY_LINE_LIST,
    BGFX_TOPOLOGY_LINE_STRIP,
    BGFX_TOPOLOGY_POINT_LIST,

    BGFX_TOPOLOGY_COUNT

} bgfx_topology_t;

typedef enum bgfx_topology_convert
{
    BGFX_TOPOLOGY_CONVERT_TRI_LIST_FLIP_WINDING,
    BGFX_TOPOLOGY_CONVERT_TRI_STRIP_FLIP_WINDING,
    BGFX_TOPOLOGY_CONVERT_TRI_LIST_TO_LINE_LIST,
    BGFX_TOPOLOGY_CONVERT_TRI_STRIP_TO_TRI_LIST,
    BGFX_TOPOLOGY_CONVERT_LINE_STRIP_TO_LINE_LIST,

    BGFX_TOPOLOGY_CONVERT_COUNT

} bgfx_topology_convert_t;

typedef enum bgfx_topology_sort
{
    BGFX_TOPOLOGY_SORT_DIRECTION_FRONT_TO_BACK_MIN,
    BGFX_TOPOLOGY_SORT_DIRECTION_FRONT_TO_BACK_AVG,
    BGFX_TOPOLOGY_SORT_DIRECTION_FRONT_TO_BACK_MAX,
    BGFX_TOPOLOGY_SORT_DIRECTION_BACK_TO_FRONT_MIN,
    BGFX_TOPOLOGY_SORT_DIRECTION_BACK_TO_FRONT_AVG,
    BGFX_TOPOLOGY_SORT_DIRECTION_BACK_TO_FRONT_MAX,
    BGFX_TOPOLOGY_SORT_DISTANCE_FRONT_TO_BACK_MIN,
    BGFX_TOPOLOGY_SORT_DISTANCE_FRONT_TO_BACK_AVG,
    BGFX_TOPOLOGY_SORT_DISTANCE_FRONT_TO_BACK_MAX,
    BGFX_TOPOLOGY_SORT_DISTANCE_BACK_TO_FRONT_MIN,
    BGFX_TOPOLOGY_SORT_DISTANCE_BACK_TO_FRONT_AVG,
    BGFX_TOPOLOGY_SORT_DISTANCE_BACK_TO_FRONT_MAX,

    BGFX_TOPOLOGY_SORT_COUNT

} bgfx_topology_sort_t;

typedef enum bgfx_view_mode
{
    BGFX_VIEW_MODE_DEFAULT,
    BGFX_VIEW_MODE_SEQUENTIAL,
    BGFX_VIEW_MODE_DEPTH_ASCENDING,
    BGFX_VIEW_MODE_DEPTH_DESCENDING,

    BGFX_VIEW_MODE_CCOUNT

} bgfx_view_mode_t;

#define BGFX_HANDLE_T(_name) \
    typedef struct _name##_s { uint16_t idx; } _name##_t

BGFX_HANDLE_T(bgfx_dynamic_index_buffer_handle);
BGFX_HANDLE_T(bgfx_dynamic_vertex_buffer_handle);
BGFX_HANDLE_T(bgfx_frame_buffer_handle);
BGFX_HANDLE_T(bgfx_index_buffer_handle);
BGFX_HANDLE_T(bgfx_indirect_buffer_handle);
BGFX_HANDLE_T(bgfx_occlusion_query_handle);
BGFX_HANDLE_T(bgfx_program_handle);
BGFX_HANDLE_T(bgfx_shader_handle);
BGFX_HANDLE_T(bgfx_texture_handle);
BGFX_HANDLE_T(bgfx_uniform_handle);
BGFX_HANDLE_T(bgfx_vertex_buffer_handle);
BGFX_HANDLE_T(bgfx_vertex_decl_handle);

#undef BGFX_HANDLE_T

/**/
typedef void (*bgfx_release_fn_t)(void* _ptr, void* _userData);

/**/
typedef struct bgfx_memory_s
{
    uint8_t* data;
    uint32_t size;

} bgfx_memory_t;

/**/
typedef struct bgfx_transform_s
{
    float* data;
    uint16_t num;

} bgfx_transform_t;

/**/
typedef uint16_t bgfx_view_id_t;

/**/
typedef struct bgfx_view_stats_s
{
    char           name[256];
    bgfx_view_id_t view;
    int64_t        cpuTimeElapsed;
    int64_t        gpuTimeElapsed;

} bgfx_view_stats_t;

typedef struct bgfx_encoder_stats_s
{
    int64_t cpuTimeBegin;
    int64_t cpuTimeEnd;

} bgfx_encoder_stats_t;

/**/
typedef struct bgfx_stats_s
{
    int64_t cpuTimeFrame;
    int64_t cpuTimeBegin;
    int64_t cpuTimeEnd;
    int64_t cpuTimerFreq;

    int64_t gpuTimeBegin;
    int64_t gpuTimeEnd;
    int64_t gpuTimerFreq;

    int64_t waitRender;
    int64_t waitSubmit;

    uint32_t numDraw;
    uint32_t numCompute;
    uint32_t numBlit;
    uint32_t maxGpuLatency;

    uint16_t numDynamicIndexBuffers;
    uint16_t numDynamicVertexBuffers;
    uint16_t numFrameBuffers;
    uint16_t numIndexBuffers;
    uint16_t numOcclusionQueries;
    uint16_t numPrograms;
    uint16_t numShaders;
    uint16_t numTextures;
    uint16_t numUniforms;
    uint16_t numVertexBuffers;
    uint16_t numVertexDecls;

    int64_t textureMemoryUsed;
    int64_t rtMemoryUsed;
    int32_t transientVbUsed;
    int32_t transientIbUsed;

    uint32_t numPrims[BGFX_TOPOLOGY_COUNT];

    int64_t gpuMemoryMax;
    int64_t gpuMemoryUsed;

    uint16_t width;
    uint16_t height;
    uint16_t textWidth;
    uint16_t textHeight;

    uint16_t           numViews;
    bgfx_view_stats_t* viewStats;

    uint8_t               numEncoders;
    bgfx_encoder_stats_t* encoderStats;

} bgfx_stats_t;

/**/
typedef struct bgfx_vertex_decl_s
{
    uint32_t hash;
    uint16_t stride;
    uint16_t offset[BGFX_ATTRIB_COUNT];
    uint16_t attributes[BGFX_ATTRIB_COUNT];

} bgfx_vertex_decl_t;

/**/
typedef struct bgfx_transient_index_buffer_s
{
    uint8_t* data;
    uint32_t size;
    bgfx_index_buffer_handle_t handle;
    uint32_t startIndex;

} bgfx_transient_index_buffer_t;

/**/
typedef struct bgfx_transient_vertex_buffer_s
{
    uint8_t* data;
    uint32_t size;
    uint32_t startVertex;
    uint16_t stride;
    bgfx_vertex_buffer_handle_t handle;
    bgfx_vertex_decl_handle_t decl;

} bgfx_transient_vertex_buffer_t;

/**/
typedef struct bgfx_instance_data_buffer_s
{
    uint8_t* data;
    uint32_t size;
    uint32_t offset;
    uint32_t num;
    uint16_t stride;
    bgfx_vertex_buffer_handle_t handle;

} bgfx_instance_data_buffer_t;

/**/
typedef struct bgfx_texture_info_s
{
    bgfx_texture_format_t format;
    uint32_t storageSize;
    uint16_t width;
    uint16_t height;
    uint16_t depth;
    uint16_t numLayers;
    uint8_t numMips;
    uint8_t bitsPerPixel;
    bool    cubeMap;

} bgfx_texture_info_t;

/**/
typedef struct bgfx_uniform_info_s
{
    char name[256];
    bgfx_uniform_type_t type;
    uint16_t num;

} bgfx_uniform_info_t;

/**/
typedef struct bgfx_attachment_s
{
    bgfx_texture_handle_t handle;
    uint16_t mip;
    uint16_t layer;
    uint8_t  resolve;

} bgfx_attachment_t;

/**/
typedef struct bgfx_caps_gpu_s
{
    uint16_t vendorId;
    uint16_t deviceId;

} bgfx_caps_gpu_t;

typedef struct bgfx_caps_limits_s
{
    uint32_t maxDrawCalls;
    uint32_t maxBlits;
    uint32_t maxTextureSize;
    uint32_t maxTextureLayers;
    uint32_t maxViews;
    uint32_t maxFrameBuffers;
    uint32_t maxFBAttachments;
    uint32_t maxPrograms;
    uint32_t maxShaders;
    uint32_t maxTextures;
    uint32_t maxTextureSamplers;
    uint32_t maxComputeBindings;
    uint32_t maxVertexDecls;
    uint32_t maxVertexStreams;
    uint32_t maxIndexBuffers;
    uint32_t maxVertexBuffers;
    uint32_t maxDynamicIndexBuffers;
    uint32_t maxDynamicVertexBuffers;
    uint32_t maxUniforms;
    uint32_t maxOcclusionQueries;
    uint32_t maxEncoders;
    uint32_t transientVbSize;
    uint32_t transientIbSize;

} bgfx_caps_limits_t;

/**/
typedef struct bgfx_caps_s
{
    bgfx_renderer_type_t rendererType;

    uint64_t supported;

    uint16_t vendorId;
    uint16_t deviceId;
    bool     homogeneousDepth;
    bool     originBottomLeft;
    uint8_t  numGPUs;

    bgfx_caps_gpu_t gpu[4];
    bgfx_caps_limits_t limits;

    uint16_t formats[BGFX_TEXTURE_FORMAT_COUNT];

} bgfx_caps_t;

/**/
typedef enum bgfx_fatal_s
{
    BGFX_FATAL_DEBUG_CHECK,
    BGFX_FATAL_INVALID_SHADER,
    BGFX_FATAL_UNABLE_TO_INITIALIZE,
    BGFX_FATAL_UNABLE_TO_CREATE_TEXTURE,
    BGFX_FATAL_DEVICE_LOST,

    BGFX_FATAL_COUNT

} bgfx_fatal_t;

/**/
typedef struct bgfx_callback_interface_s
{
    const struct bgfx_callback_vtbl_s* vtbl;

} bgfx_callback_interface_t;

/**/
typedef struct bgfx_callback_vtbl_s
{
    void (*fatal)(bgfx_callback_interface_t* _this, const char* _filePath, uint16_t _line, bgfx_fatal_t _code, const char* _str);
    void (*trace_vargs)(bgfx_callback_interface_t* _this, const char* _filePath, uint16_t _line, const char* _format, va_list _argList);
    void (*profiler_begin)(bgfx_callback_interface_t* _this, const char* _name, uint32_t _abgr, const char* _filePath, uint16_t _line);
    void (*profiler_begin_literal)(bgfx_callback_interface_t* _this, const char* _name, uint32_t _abgr, const char* _filePath, uint16_t _line);
    void (*profiler_end)(bgfx_callback_interface_t* _this);
    uint32_t (*cache_read_size)(bgfx_callback_interface_t* _this, uint64_t _id);
    bool (*cache_read)(bgfx_callback_interface_t* _this, uint64_t _id, void* _data, uint32_t _size);
    void (*cache_write)(bgfx_callback_interface_t* _this, uint64_t _id, const void* _data, uint32_t _size);
    void (*screen_shot)(bgfx_callback_interface_t* _this, const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _data, uint32_t _size, bool _yflip);
    void (*capture_begin)(bgfx_callback_interface_t* _this, uint32_t _width, uint32_t _height, uint32_t _pitch, bgfx_texture_format_t _format, bool _yflip);
    void (*capture_end)(bgfx_callback_interface_t* _this);
    void (*capture_frame)(bgfx_callback_interface_t* _this, const void* _data, uint32_t _size);

} bgfx_callback_vtbl_t;

/**/
typedef struct bgfx_allocator_interface_s
{
    const struct bgfx_allocator_vtbl_s* vtbl;

} bgfx_allocator_interface_t;

/**/
typedef struct bgfx_allocator_vtbl_s
{
    void* (*realloc)(bgfx_allocator_interface_t* _this, void* _ptr, size_t _size, size_t _align, const char* _file, uint32_t _line);

} bgfx_allocator_vtbl_t;

/**/
typedef struct bgfx_platform_data
{
    void* ndt;
    void* nwh;
    void* context;
    void* backBuffer;
    void* backBufferDS;

} bgfx_platform_data_t;

/**/
typedef struct bgfx_resolution_s
{
    bgfx_texture_format_t format;
    uint32_t width;
    uint32_t height;
    uint32_t reset;
    uint8_t  numBackBuffers;
    uint8_t  maxFrameLatency;

} bgfx_resolution_t;

/**/
typedef struct bgfx_init_limits_s
{
    uint16_t maxEncoders;
    uint32_t transientVbSize;
    uint32_t transientIbSize;

} bgfx_init_limits_t;

/**/
typedef struct bgfx_init_s
{
    bgfx_renderer_type_t type;
    uint16_t vendorId;
    uint16_t deviceId;
    bool debug;
    bool profile;

    bgfx_platform_data_t platformData;
    bgfx_resolution_t    resolution;
    bgfx_init_limits_t   limits;

    bgfx_callback_interface_t*  callback;
    bgfx_allocator_interface_t* allocator;

} bgfx_init_t;

/**/
BGFX_C_API void bgfx_vertex_decl_begin(bgfx_vertex_decl_t* _decl, bgfx_renderer_type_t _renderer);

/**/
BGFX_C_API void bgfx_vertex_decl_add(bgfx_vertex_decl_t* _decl, bgfx_attrib_t _attrib, uint8_t _num, bgfx_attrib_type_t _type, bool _normalized, bool _asInt);

/**/
BGFX_C_API void bgfx_vertex_decl_decode(const bgfx_vertex_decl_t* _decl, bgfx_attrib_t _attrib, uint8_t* _num, bgfx_attrib_type_t* _type, bool* _normalized, bool* _asInt);

/**/
BGFX_C_API bool bgfx_vertex_decl_has(const bgfx_vertex_decl_t* _decl, bgfx_attrib_t _attrib);

/**/
BGFX_C_API void bgfx_vertex_decl_skip(bgfx_vertex_decl_t* _decl, uint8_t _num);

/**/
BGFX_C_API void bgfx_vertex_decl_end(bgfx_vertex_decl_t* _decl);

/**/
BGFX_C_API void bgfx_vertex_pack(const float _input[4], bool _inputNormalized, bgfx_attrib_t _attr, const bgfx_vertex_decl_t* _decl, void* _data, uint32_t _index);

/**/
BGFX_C_API void bgfx_vertex_unpack(float _output[4], bgfx_attrib_t _attr, const bgfx_vertex_decl_t* _decl, const void* _data, uint32_t _index);

/**/
BGFX_C_API void bgfx_vertex_convert(const bgfx_vertex_decl_t* _destDecl, void* _destData, const bgfx_vertex_decl_t* _srcDecl, const void* _srcData, uint32_t _num);

/**/
BGFX_C_API uint16_t bgfx_weld_vertices(uint16_t* _output, const bgfx_vertex_decl_t* _decl, const void* _data, uint16_t _num, float _epsilon);

/**/
BGFX_C_API uint32_t bgfx_topology_convert(bgfx_topology_convert_t _conversion, void* _dst, uint32_t _dstSize, const void* _indices, uint32_t _numIndices, bool _index32);

/**/
BGFX_C_API void bgfx_topology_sort_tri_list(bgfx_topology_sort_t _sort, void* _dst, uint32_t _dstSize, const float _dir[3], const float _pos[3], const void* _vertices, uint32_t _stride, const void* _indices, uint32_t _numIndices, bool _index32);

/**/
BGFX_C_API uint8_t bgfx_get_supported_renderers(uint8_t _max, bgfx_renderer_type_t* _enum);

/**/
BGFX_C_API const char* bgfx_get_renderer_name(bgfx_renderer_type_t _type);

/**/
BGFX_C_API void bgfx_init_ctor(bgfx_init_t* _init);

/**/
BGFX_C_API bool bgfx_init(const bgfx_init_t* _init);

/**/
BGFX_C_API void bgfx_shutdown(void);

/**/
BGFX_C_API void bgfx_reset(uint32_t _width, uint32_t _height, uint32_t _flags, bgfx_texture_format_t _format);

/**/
BGFX_C_API struct bgfx_encoder_s* bgfx_begin(void);

/**/
BGFX_C_API void bgfx_end(struct bgfx_encoder_s* _encoder);

/**/
BGFX_C_API uint32_t bgfx_frame(bool _capture);

/**/
BGFX_C_API bgfx_renderer_type_t bgfx_get_renderer_type(void);

/**/
BGFX_C_API const bgfx_caps_t* bgfx_get_caps(void);

/**/
BGFX_C_API const bgfx_stats_t* bgfx_get_stats(void);

/**/
BGFX_C_API const bgfx_memory_t* bgfx_alloc(uint32_t _size);

/**/
BGFX_C_API const bgfx_memory_t* bgfx_copy(const void* _data, uint32_t _size);

/**/
BGFX_C_API const bgfx_memory_t* bgfx_make_ref(const void* _data, uint32_t _size);

/**/
BGFX_C_API const bgfx_memory_t* bgfx_make_ref_release(const void* _data, uint32_t _size, bgfx_release_fn_t _releaseFn, void* _userData);

/**/
BGFX_C_API void bgfx_set_debug(uint32_t _debug);

/**/
BGFX_C_API void bgfx_dbg_text_clear(uint8_t _attr, bool _small);

/**/
BGFX_C_API void bgfx_dbg_text_printf(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, ...);

/**/
BGFX_C_API void bgfx_dbg_text_vprintf(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, va_list _argList);

/**/
BGFX_C_API void bgfx_dbg_text_image(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const void* _data, uint16_t _pitch);

/**/
BGFX_C_API bgfx_index_buffer_handle_t bgfx_create_index_buffer(const bgfx_memory_t* _mem, uint16_t _flags);

/**/
BGFX_C_API void bgfx_destroy_index_buffer(bgfx_index_buffer_handle_t _handle);

/**/
BGFX_C_API bgfx_vertex_buffer_handle_t bgfx_create_vertex_buffer(const bgfx_memory_t* _mem, const bgfx_vertex_decl_t* _decl, uint16_t _flags);

/**/
BGFX_C_API void bgfx_destroy_vertex_buffer(bgfx_vertex_buffer_handle_t _handle);

/**/
BGFX_C_API bgfx_dynamic_index_buffer_handle_t bgfx_create_dynamic_index_buffer(uint32_t _num, uint16_t _flags);

/**/
BGFX_C_API bgfx_dynamic_index_buffer_handle_t bgfx_create_dynamic_index_buffer_mem(const bgfx_memory_t* _mem, uint16_t _flags);

/**/
BGFX_C_API void bgfx_update_dynamic_index_buffer(bgfx_dynamic_index_buffer_handle_t _handle, uint32_t _startIndex, const bgfx_memory_t* _mem);

/**/
BGFX_C_API void bgfx_destroy_dynamic_index_buffer(bgfx_dynamic_index_buffer_handle_t _handle);

/**/
BGFX_C_API bgfx_dynamic_vertex_buffer_handle_t bgfx_create_dynamic_vertex_buffer(uint32_t _num, const bgfx_vertex_decl_t* _decl, uint16_t _flags);

/**/
BGFX_C_API bgfx_dynamic_vertex_buffer_handle_t bgfx_create_dynamic_vertex_buffer_mem(const bgfx_memory_t* _mem, const bgfx_vertex_decl_t* _decl, uint16_t _flags);

/**/
BGFX_C_API void bgfx_update_dynamic_vertex_buffer(bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, const bgfx_memory_t* _mem);

/**/
BGFX_C_API void bgfx_destroy_dynamic_vertex_buffer(bgfx_dynamic_vertex_buffer_handle_t _handle);

/**/
BGFX_C_API uint32_t bgfx_get_avail_transient_index_buffer(uint32_t _num);

/**/
BGFX_C_API uint32_t bgfx_get_avail_transient_vertex_buffer(uint32_t _num, const bgfx_vertex_decl_t* _decl);

/**/
BGFX_C_API uint32_t bgfx_get_avail_instance_data_buffer(uint32_t _num, uint16_t _stride);

/**/
BGFX_C_API void bgfx_alloc_transient_index_buffer(bgfx_transient_index_buffer_t* _tib, uint32_t _num);

/**/
BGFX_C_API void bgfx_alloc_transient_vertex_buffer(bgfx_transient_vertex_buffer_t* _tvb, uint32_t _num, const bgfx_vertex_decl_t* _decl);

/**/
BGFX_C_API bool bgfx_alloc_transient_buffers(bgfx_transient_vertex_buffer_t* _tvb, const bgfx_vertex_decl_t* _decl, uint32_t _numVertices, bgfx_transient_index_buffer_t* _tib, uint32_t _numIndices);

/**/
BGFX_C_API void bgfx_alloc_instance_data_buffer(bgfx_instance_data_buffer_t* _idb, uint32_t _num, uint16_t _stride);

/**/
BGFX_C_API bgfx_indirect_buffer_handle_t bgfx_create_indirect_buffer(uint32_t _num);

/**/
BGFX_C_API void bgfx_destroy_indirect_buffer(bgfx_indirect_buffer_handle_t _handle);

/**/
BGFX_C_API bgfx_shader_handle_t bgfx_create_shader(const bgfx_memory_t* _mem);

/**/
BGFX_C_API uint16_t bgfx_get_shader_uniforms(bgfx_shader_handle_t _handle, bgfx_uniform_handle_t* _uniforms, uint16_t _max);

/**/
BGFX_C_API void bgfx_get_uniform_info(bgfx_uniform_handle_t _handle, bgfx_uniform_info_t* _info);

/**/
BGFX_C_API void bgfx_set_shader_name(bgfx_shader_handle_t _handle, const char* _name, int32_t _len);

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
BGFX_C_API void bgfx_calc_texture_size(bgfx_texture_info_t* _info, uint16_t _width, uint16_t _height, uint16_t _depth, bool _cubeMap, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format);

/**/
BGFX_C_API bgfx_texture_handle_t bgfx_create_texture(const bgfx_memory_t* _mem, uint64_t _flags, uint8_t _skip, bgfx_texture_info_t* _info);

/**/
BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_2d(uint16_t _width, uint16_t _height, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format, uint64_t _flags, const bgfx_memory_t* _mem);

/**/
BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_2d_scaled(bgfx_backbuffer_ratio_t _ratio, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format, uint64_t _flags);

/**/
BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_3d(uint16_t _width, uint16_t _height, uint16_t _depth, bool _hasMips, bgfx_texture_format_t _format, uint64_t _flags, const bgfx_memory_t* _mem);

/**/
BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_cube(uint16_t _size, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format, uint64_t _flags, const bgfx_memory_t* _mem);

/**/
BGFX_C_API void bgfx_update_texture_2d(bgfx_texture_handle_t _handle, uint16_t _layer, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const bgfx_memory_t* _mem, uint16_t _pitch);

/**/
BGFX_C_API void bgfx_update_texture_3d(bgfx_texture_handle_t _handle, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _z, uint16_t _width, uint16_t _height, uint16_t _depth, const bgfx_memory_t* _mem);

/**/
BGFX_C_API void bgfx_update_texture_cube(bgfx_texture_handle_t _handle, uint16_t _layer, uint8_t _side, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const bgfx_memory_t* _mem, uint16_t _pitch);

/**/
BGFX_C_API uint32_t bgfx_read_texture(bgfx_texture_handle_t _handle, void* _data, uint8_t _mip);

/**/
BGFX_C_API void bgfx_set_texture_name(bgfx_texture_handle_t _handle, const char* _name, int32_t _len);

/**/
BGFX_C_API void bgfx_destroy_texture(bgfx_texture_handle_t _handle);

/**/
BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer(uint16_t _width, uint16_t _height, bgfx_texture_format_t _format, uint64_t _textureFlags);

/**/
BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_scaled(bgfx_backbuffer_ratio_t _ratio, bgfx_texture_format_t _format, uint64_t _textureFlags);

/**/
BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_from_handles(uint8_t _num, const bgfx_texture_handle_t* _handles, bool _destroyTextures);

/**/
BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_from_attachment(uint8_t _num, const bgfx_attachment_t* _attachment, bool _destroyTextures);

/**/
BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_from_nwh(void* _nwh, uint16_t _width, uint16_t _height, bgfx_texture_format_t _format, bgfx_texture_format_t _depthFormat);

/**/
BGFX_C_API bgfx_texture_handle_t bgfx_get_texture(bgfx_frame_buffer_handle_t _handle, uint8_t _attachment);

/**/
BGFX_C_API void bgfx_destroy_frame_buffer(bgfx_frame_buffer_handle_t _handle);

/**/
BGFX_C_API bgfx_uniform_handle_t bgfx_create_uniform(const char* _name, bgfx_uniform_type_t _type, uint16_t _num);

/**/
BGFX_C_API void bgfx_destroy_uniform(bgfx_uniform_handle_t _handle);

/**/
BGFX_C_API bgfx_occlusion_query_handle_t bgfx_create_occlusion_query(void);

/**/
BGFX_C_API bgfx_occlusion_query_result_t bgfx_get_result(bgfx_occlusion_query_handle_t _handle, int32_t* _result);

/**/
BGFX_C_API void bgfx_destroy_occlusion_query(bgfx_occlusion_query_handle_t _handle);

/**/
BGFX_C_API void bgfx_set_palette_color(uint8_t _index, const float _rgba[4]);

/**/
BGFX_C_API void bgfx_set_view_name(bgfx_view_id_t _id, const char* _name);

/**/
BGFX_C_API void bgfx_set_view_rect(bgfx_view_id_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

/**/
BGFX_C_API void bgfx_set_view_rect_auto(bgfx_view_id_t _id, uint16_t _x, uint16_t _y, bgfx_backbuffer_ratio_t _ratio);

/**/
BGFX_C_API void bgfx_set_view_scissor(bgfx_view_id_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

/**/
BGFX_C_API void bgfx_set_view_clear(bgfx_view_id_t _id, uint16_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil);

/**/
BGFX_C_API void bgfx_set_view_clear_mrt(bgfx_view_id_t _id, uint16_t _flags, float _depth, uint8_t _stencil, uint8_t _0, uint8_t _1, uint8_t _2, uint8_t _3, uint8_t _4, uint8_t _5, uint8_t _6, uint8_t _7);

/**/
BGFX_C_API void bgfx_set_view_mode(bgfx_view_id_t _id, bgfx_view_mode_t _mode);

/**/
BGFX_C_API void bgfx_set_view_frame_buffer(bgfx_view_id_t _id, bgfx_frame_buffer_handle_t _handle);

/**/
BGFX_C_API void bgfx_set_view_transform(bgfx_view_id_t _id, const void* _view, const void* _proj);

/**/
BGFX_C_API void bgfx_set_view_transform_stereo(bgfx_view_id_t _id, const void* _view, const void* _projL, uint8_t _flags, const void* _projR);

/**/
BGFX_C_API void bgfx_set_view_order(bgfx_view_id_t _id, uint16_t _num, const bgfx_view_id_t* _order);

/**/
BGFX_C_API void bgfx_reset_view(bgfx_view_id_t _id);

/**/
BGFX_C_API void bgfx_set_marker(const char* _marker);

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
BGFX_C_API uint32_t bgfx_set_transform(const void* _mtx, uint16_t _num);

/**/
BGFX_C_API uint32_t bgfx_alloc_transform(bgfx_transform_t* _transform, uint16_t _num);

/**/
BGFX_C_API void bgfx_set_transform_cached(uint32_t _cache, uint16_t _num);

/**/
BGFX_C_API void bgfx_set_uniform(bgfx_uniform_handle_t _handle, const void* _value, uint16_t _num);

/**/
BGFX_C_API void bgfx_set_index_buffer(bgfx_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices);

/**/
BGFX_C_API void bgfx_set_dynamic_index_buffer(bgfx_dynamic_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices);

/**/
BGFX_C_API void bgfx_set_transient_index_buffer(const bgfx_transient_index_buffer_t* _tib, uint32_t _firstIndex, uint32_t _numIndices);

/**/
BGFX_C_API void bgfx_set_vertex_buffer(uint8_t _stream, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices);

/**/
BGFX_C_API void bgfx_set_dynamic_vertex_buffer(uint8_t _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices);

/**/
BGFX_C_API void bgfx_set_transient_vertex_buffer(uint8_t _stream, const bgfx_transient_vertex_buffer_t* _tvb, uint32_t _startVertex, uint32_t _numVertices);

/**/
BGFX_C_API void bgfx_set_vertex_count(uint32_t _numVertices);

/**/
BGFX_C_API void bgfx_set_instance_data_buffer(const bgfx_instance_data_buffer_t* _idb, uint32_t _start, uint32_t _num);

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
BGFX_C_API void bgfx_submit(bgfx_view_id_t _id, bgfx_program_handle_t _handle, uint32_t _depth, bool _preserveState);

/**/
BGFX_C_API void bgfx_submit_occlusion_query(bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_occlusion_query_handle_t _occlusionQuery, uint32_t _depth, bool _preserveState);

/**/
BGFX_C_API void bgfx_submit_indirect(bgfx_view_id_t _id, bgfx_program_handle_t _handle, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, uint32_t _depth, bool _preserveState);

/**/
BGFX_C_API void bgfx_set_image(uint8_t _stage, bgfx_texture_handle_t _handle, uint8_t _mip, bgfx_access_t _access, bgfx_texture_format_t _format);

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
BGFX_C_API void bgfx_dispatch(bgfx_view_id_t _id, bgfx_program_handle_t _handle, uint32_t _numX, uint32_t _numY, uint32_t _numZ, uint8_t _flags);

/**/
BGFX_C_API void bgfx_dispatch_indirect(bgfx_view_id_t _id, bgfx_program_handle_t _handle, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, uint8_t _flags);

/**/
BGFX_C_API void bgfx_discard(void);

/**/
BGFX_C_API void bgfx_blit(bgfx_view_id_t _id, bgfx_texture_handle_t _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, bgfx_texture_handle_t _src, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth);

/**/
BGFX_C_API void bgfx_encoder_set_marker(struct bgfx_encoder_s* _encoder, const char* _marker);

/**/
BGFX_C_API void bgfx_encoder_set_state(struct bgfx_encoder_s* _encoder, uint64_t _state, uint32_t _rgba);

/**/
BGFX_C_API void bgfx_encoder_set_condition(struct bgfx_encoder_s* _encoder, bgfx_occlusion_query_handle_t _handle, bool _visible);

/**/
BGFX_C_API void bgfx_encoder_set_stencil(struct bgfx_encoder_s* _encoder, uint32_t _fstencil, uint32_t _bstencil);

/**/
BGFX_C_API uint16_t bgfx_encoder_set_scissor(struct bgfx_encoder_s* _encoder, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

/**/
BGFX_C_API void bgfx_encoder_set_scissor_cached(struct bgfx_encoder_s* _encoder, uint16_t _cache);

/**/
BGFX_C_API uint32_t bgfx_encoder_set_transform(struct bgfx_encoder_s* _encoder, const void* _mtx, uint16_t _num);

/**/
BGFX_C_API uint32_t bgfx_encoder_alloc_transform(struct bgfx_encoder_s* _encoder, bgfx_transform_t* _transform, uint16_t _num);

/**/
BGFX_C_API void bgfx_encoder_set_transform_cached(struct bgfx_encoder_s* _encoder, uint32_t _cache, uint16_t _num);

/**/
BGFX_C_API void bgfx_encoder_set_uniform(struct bgfx_encoder_s* _encoder, bgfx_uniform_handle_t _handle, const void* _value, uint16_t _num);

/**/
BGFX_C_API void bgfx_encoder_set_index_buffer(struct bgfx_encoder_s* _encoder, bgfx_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices);

/**/
BGFX_C_API void bgfx_encoder_set_dynamic_index_buffer(struct bgfx_encoder_s* _encoder, bgfx_dynamic_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices);

/**/
BGFX_C_API void bgfx_encoder_set_transient_index_buffer(struct bgfx_encoder_s* _encoder, const bgfx_transient_index_buffer_t* _tib, uint32_t _firstIndex, uint32_t _numIndices);

/**/
BGFX_C_API void bgfx_encoder_set_vertex_buffer(struct bgfx_encoder_s* _encoder, uint8_t _stream, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices);

/**/
BGFX_C_API void bgfx_encoder_set_dynamic_vertex_buffer(struct bgfx_encoder_s* _encoder, uint8_t _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices);

/**/
BGFX_C_API void bgfx_encoder_set_transient_vertex_buffer(struct bgfx_encoder_s* _encoder, uint8_t _stream, const bgfx_transient_vertex_buffer_t* _tvb, uint32_t _startVertex, uint32_t _numVertices);

/**/
BGFX_C_API void bgfx_encoder_set_vertex_count(struct bgfx_encoder_s* _encoder, uint32_t _numVertices);

/**/
BGFX_C_API void bgfx_encoder_set_instance_data_buffer(struct bgfx_encoder_s* _encoder, const bgfx_instance_data_buffer_t* _idb, uint32_t _start, uint32_t _num);

/**/
BGFX_C_API void bgfx_encoder_set_instance_data_from_vertex_buffer(struct bgfx_encoder_s* _encoder, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num);

/**/
BGFX_C_API void bgfx_encoder_set_instance_data_from_dynamic_vertex_buffer(struct bgfx_encoder_s* _encoder, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num);

/**/
BGFX_C_API void bgfx_encoder_set_texture(struct bgfx_encoder_s* _encoder, uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint32_t _flags);

/**/
BGFX_C_API void bgfx_encoder_touch(struct bgfx_encoder_s* _encoder, bgfx_view_id_t _id);

/**/
BGFX_C_API void bgfx_encoder_submit(struct bgfx_encoder_s* _encoder, bgfx_view_id_t _id, bgfx_program_handle_t _handle, uint32_t _depth, bool _preserveState);

/**/
BGFX_C_API void bgfx_encoder_submit_occlusion_query(struct bgfx_encoder_s* _encoder, bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_occlusion_query_handle_t _occlusionQuery, uint32_t _depth, bool _preserveState);

/**/
BGFX_C_API void bgfx_encoder_submit_indirect(struct bgfx_encoder_s* _encoder, bgfx_view_id_t _id, bgfx_program_handle_t _handle, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, uint32_t _depth, bool _preserveState);

/**/
BGFX_C_API void bgfx_encoder_set_image(struct bgfx_encoder_s* _encoder, uint8_t _stage, bgfx_texture_handle_t _handle, uint8_t _mip, bgfx_access_t _access, bgfx_texture_format_t _format);

/**/
BGFX_C_API void bgfx_encoder_set_compute_index_buffer(struct bgfx_encoder_s* _encoder, uint8_t _stage, bgfx_index_buffer_handle_t _handle, bgfx_access_t _access);

/**/
BGFX_C_API void bgfx_encoder_set_compute_vertex_buffer(struct bgfx_encoder_s* _encoder, uint8_t _stage, bgfx_vertex_buffer_handle_t _handle, bgfx_access_t _access);

/**/
BGFX_C_API void bgfx_encoder_set_compute_dynamic_index_buffer(struct bgfx_encoder_s* _encoder, uint8_t _stage, bgfx_dynamic_index_buffer_handle_t _handle, bgfx_access_t _access);

/**/
BGFX_C_API void bgfx_encoder_set_compute_dynamic_vertex_buffer(struct bgfx_encoder_s* _encoder, uint8_t _stage, bgfx_dynamic_vertex_buffer_handle_t _handle, bgfx_access_t _access);

/**/
BGFX_C_API void bgfx_encoder_set_compute_indirect_buffer(struct bgfx_encoder_s* _encoder, uint8_t _stage, bgfx_indirect_buffer_handle_t _handle, bgfx_access_t _access);

/**/
BGFX_C_API void bgfx_encoder_dispatch(struct bgfx_encoder_s* _encoder, bgfx_view_id_t _id, bgfx_program_handle_t _handle, uint32_t _numX, uint32_t _numY, uint32_t _numZ, uint8_t _flags);

/**/
BGFX_C_API void bgfx_encoder_dispatch_indirect(struct bgfx_encoder_s* _encoder, bgfx_view_id_t _id, bgfx_program_handle_t _handle, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, uint8_t _flags);

/**/
BGFX_C_API void bgfx_encoder_discard(struct bgfx_encoder_s* _encoder);

/**/
BGFX_C_API void bgfx_encoder_blit(struct bgfx_encoder_s* _encoder, bgfx_view_id_t _id, bgfx_texture_handle_t _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, bgfx_texture_handle_t _src, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth);

/**/
BGFX_C_API void bgfx_request_screen_shot(bgfx_frame_buffer_handle_t _handle, const char* _filePath);

#endif // BGFX_C99_H_HEADER_GUARD
