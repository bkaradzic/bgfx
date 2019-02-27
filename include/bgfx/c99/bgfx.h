/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
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
    BGFX_UNIFORM_TYPE_SAMPLER,
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
    bgfx_access_t access;
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
typedef enum bgfx_render_frame
{
    BGFX_RENDER_FRAME_NO_CONTEXT,
    BGFX_RENDER_FRAME_RENDER,
    BGFX_RENDER_FRAME_TIMEOUT,
    BGFX_RENDER_FRAME_EXITING,

    BGFX_RENDER_FRAME_COUNT

} bgfx_render_frame_t;

/**/
typedef struct bgfx_internal_data
{
    const struct bgfx_caps* caps;
    void* context;

} bgfx_internal_data_t;

/**/
typedef struct bgfx_encoder_s bgfx_encoder_t;

#include "bgfx.idl.h"

/**/
typedef bgfx_interface_vtbl_t* (*PFN_BGFX_GET_INTERFACE)(uint32_t _version);

/**/
BGFX_C_API bgfx_interface_vtbl_t* bgfx_get_interface(uint32_t _version);

#endif // BGFX_C99_H_HEADER_GUARD
