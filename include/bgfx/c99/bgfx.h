/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

/*
 *
 * AUTO GENERATED FROM IDL! DO NOT EDIT! (source : temp.bgfx.h)
 *
 * More info about IDL:
 * https://gist.github.com/bkaradzic/05a1c86a6dd57bf86e2d828878e88dc2#bgfx-is-switching-to-idl-to-generate-api
 *
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

#if BX_PLATFORM_WINDOWS || BX_PLATFORM_WINRT
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

/**
 * Fatal error enum.
 *
 */
typedef enum bgfx_fatal
{
    BGFX_FATAL_DEBUG_CHECK,                   /** ( 0)                                */
    BGFX_FATAL_INVALID_SHADER,                /** ( 1)                                */
    BGFX_FATAL_UNABLE_TO_INITIALIZE,          /** ( 2)                                */
    BGFX_FATAL_UNABLE_TO_CREATE_TEXTURE,      /** ( 3)                                */
    BGFX_FATAL_DEVICE_LOST,                   /** ( 4)                                */

    BGFX_FATAL_COUNT

} bgfx_fatal_t;

/**
 * Renderer backend type enum.
 *
 */
typedef enum bgfx_renderer_type
{
    BGFX_RENDERER_TYPE_NOOP,                  /** ( 0) No rendering.                  */
    BGFX_RENDERER_TYPE_DIRECT3D9,             /** ( 1) Direct3D 9.0                   */
    BGFX_RENDERER_TYPE_DIRECT3D11,            /** ( 2) Direct3D 11.0                  */
    BGFX_RENDERER_TYPE_DIRECT3D12,            /** ( 3) Direct3D 12.0                  */
    BGFX_RENDERER_TYPE_GNM,                   /** ( 4) GNM                            */
    BGFX_RENDERER_TYPE_METAL,                 /** ( 5) Metal                          */
    BGFX_RENDERER_TYPE_NVN,                   /** ( 6) NVN                            */
    BGFX_RENDERER_TYPE_OPENGLES,              /** ( 7) OpenGL ES 2.0+                 */
    BGFX_RENDERER_TYPE_OPENGL,                /** ( 8) OpenGL 2.1+                    */
    BGFX_RENDERER_TYPE_VULKAN,                /** ( 9) Vulkan                         */
    BGFX_RENDERER_TYPE_WEBGPU,                /** (10) WebGPU                         */

    BGFX_RENDERER_TYPE_COUNT

} bgfx_renderer_type_t;

/**
 * Access mode enum.
 *
 */
typedef enum bgfx_access
{
    BGFX_ACCESS_READ,                         /** ( 0) Read.                          */
    BGFX_ACCESS_WRITE,                        /** ( 1) Write.                         */
    BGFX_ACCESS_READWRITE,                    /** ( 2) Read and write.                */

    BGFX_ACCESS_COUNT

} bgfx_access_t;

/**
 * Vertex attribute enum.
 *
 */
typedef enum bgfx_attrib
{
    BGFX_ATTRIB_POSITION,                     /** ( 0) a_position                     */
    BGFX_ATTRIB_NORMAL,                       /** ( 1) a_normal                       */
    BGFX_ATTRIB_TANGENT,                      /** ( 2) a_tangent                      */
    BGFX_ATTRIB_BITANGENT,                    /** ( 3) a_bitangent                    */
    BGFX_ATTRIB_COLOR0,                       /** ( 4) a_color0                       */
    BGFX_ATTRIB_COLOR1,                       /** ( 5) a_color1                       */
    BGFX_ATTRIB_COLOR2,                       /** ( 6) a_color2                       */
    BGFX_ATTRIB_COLOR3,                       /** ( 7) a_color3                       */
    BGFX_ATTRIB_INDICES,                      /** ( 8) a_indices                      */
    BGFX_ATTRIB_WEIGHT,                       /** ( 9) a_weight                       */
    BGFX_ATTRIB_TEXCOORD0,                    /** (10) a_texcoord0                    */
    BGFX_ATTRIB_TEXCOORD1,                    /** (11) a_texcoord1                    */
    BGFX_ATTRIB_TEXCOORD2,                    /** (12) a_texcoord2                    */
    BGFX_ATTRIB_TEXCOORD3,                    /** (13) a_texcoord3                    */
    BGFX_ATTRIB_TEXCOORD4,                    /** (14) a_texcoord4                    */
    BGFX_ATTRIB_TEXCOORD5,                    /** (15) a_texcoord5                    */
    BGFX_ATTRIB_TEXCOORD6,                    /** (16) a_texcoord6                    */
    BGFX_ATTRIB_TEXCOORD7,                    /** (17) a_texcoord7                    */

    BGFX_ATTRIB_COUNT

} bgfx_attrib_t;

/**
 * Vertex attribute type enum.
 *
 */
typedef enum bgfx_attrib_type
{
    BGFX_ATTRIB_TYPE_UINT8,                   /** ( 0) Uint8                          */
    BGFX_ATTRIB_TYPE_UINT10,                  /** ( 1) Uint10, availability depends on: `BGFX_CAPS_VERTEX_ATTRIB_UINT10`. */
    BGFX_ATTRIB_TYPE_INT16,                   /** ( 2) Int16                          */
    BGFX_ATTRIB_TYPE_HALF,                    /** ( 3) Half, availability depends on: `BGFX_CAPS_VERTEX_ATTRIB_HALF`. */
    BGFX_ATTRIB_TYPE_FLOAT,                   /** ( 4) Float                          */

    BGFX_ATTRIB_TYPE_COUNT

} bgfx_attrib_type_t;

/**
 * Texture format enum.
 * Notation:
 *       RGBA16S
 *       ^   ^ ^
 *       |   | +-- [ ]Unorm
 *       |   |     [F]loat
 *       |   |     [S]norm
 *       |   |     [I]nt
 *       |   |     [U]int
 *       |   +---- Number of bits per component
 *       +-------- Components
 * @attention Availability depends on Caps (see: formats).
 *
 */
typedef enum bgfx_texture_format
{
    BGFX_TEXTURE_FORMAT_BC1,                  /** ( 0) DXT1 R5G6B5A1                  */
    BGFX_TEXTURE_FORMAT_BC2,                  /** ( 1) DXT3 R5G6B5A4                  */
    BGFX_TEXTURE_FORMAT_BC3,                  /** ( 2) DXT5 R5G6B5A8                  */
    BGFX_TEXTURE_FORMAT_BC4,                  /** ( 3) LATC1/ATI1 R8                  */
    BGFX_TEXTURE_FORMAT_BC5,                  /** ( 4) LATC2/ATI2 RG8                 */
    BGFX_TEXTURE_FORMAT_BC6H,                 /** ( 5) BC6H RGB16F                    */
    BGFX_TEXTURE_FORMAT_BC7,                  /** ( 6) BC7 RGB 4-7 bits per color channel, 0-8 bits alpha */
    BGFX_TEXTURE_FORMAT_ETC1,                 /** ( 7) ETC1 RGB8                      */
    BGFX_TEXTURE_FORMAT_ETC2,                 /** ( 8) ETC2 RGB8                      */
    BGFX_TEXTURE_FORMAT_ETC2A,                /** ( 9) ETC2 RGBA8                     */
    BGFX_TEXTURE_FORMAT_ETC2A1,               /** (10) ETC2 RGB8A1                    */
    BGFX_TEXTURE_FORMAT_PTC12,                /** (11) PVRTC1 RGB 2BPP                */
    BGFX_TEXTURE_FORMAT_PTC14,                /** (12) PVRTC1 RGB 4BPP                */
    BGFX_TEXTURE_FORMAT_PTC12A,               /** (13) PVRTC1 RGBA 2BPP               */
    BGFX_TEXTURE_FORMAT_PTC14A,               /** (14) PVRTC1 RGBA 4BPP               */
    BGFX_TEXTURE_FORMAT_PTC22,                /** (15) PVRTC2 RGBA 2BPP               */
    BGFX_TEXTURE_FORMAT_PTC24,                /** (16) PVRTC2 RGBA 4BPP               */
    BGFX_TEXTURE_FORMAT_ATC,                  /** (17) ATC RGB 4BPP                   */
    BGFX_TEXTURE_FORMAT_ATCE,                 /** (18) ATCE RGBA 8 BPP explicit alpha */
    BGFX_TEXTURE_FORMAT_ATCI,                 /** (19) ATCI RGBA 8 BPP interpolated alpha */
    BGFX_TEXTURE_FORMAT_ASTC4X4,              /** (20) ASTC 4x4 8.0 BPP               */
    BGFX_TEXTURE_FORMAT_ASTC5X5,              /** (21) ASTC 5x5 5.12 BPP              */
    BGFX_TEXTURE_FORMAT_ASTC6X6,              /** (22) ASTC 6x6 3.56 BPP              */
    BGFX_TEXTURE_FORMAT_ASTC8X5,              /** (23) ASTC 8x5 3.20 BPP              */
    BGFX_TEXTURE_FORMAT_ASTC8X6,              /** (24) ASTC 8x6 2.67 BPP              */
    BGFX_TEXTURE_FORMAT_ASTC10X5,             /** (25) ASTC 10x5 2.56 BPP             */
    BGFX_TEXTURE_FORMAT_UNKNOWN,              /** (26) Compressed formats above.      */
    BGFX_TEXTURE_FORMAT_R1,                   /** (27)                                */
    BGFX_TEXTURE_FORMAT_A8,                   /** (28)                                */
    BGFX_TEXTURE_FORMAT_R8,                   /** (29)                                */
    BGFX_TEXTURE_FORMAT_R8I,                  /** (30)                                */
    BGFX_TEXTURE_FORMAT_R8U,                  /** (31)                                */
    BGFX_TEXTURE_FORMAT_R8S,                  /** (32)                                */
    BGFX_TEXTURE_FORMAT_R16,                  /** (33)                                */
    BGFX_TEXTURE_FORMAT_R16I,                 /** (34)                                */
    BGFX_TEXTURE_FORMAT_R16U,                 /** (35)                                */
    BGFX_TEXTURE_FORMAT_R16F,                 /** (36)                                */
    BGFX_TEXTURE_FORMAT_R16S,                 /** (37)                                */
    BGFX_TEXTURE_FORMAT_R32I,                 /** (38)                                */
    BGFX_TEXTURE_FORMAT_R32U,                 /** (39)                                */
    BGFX_TEXTURE_FORMAT_R32F,                 /** (40)                                */
    BGFX_TEXTURE_FORMAT_RG8,                  /** (41)                                */
    BGFX_TEXTURE_FORMAT_RG8I,                 /** (42)                                */
    BGFX_TEXTURE_FORMAT_RG8U,                 /** (43)                                */
    BGFX_TEXTURE_FORMAT_RG8S,                 /** (44)                                */
    BGFX_TEXTURE_FORMAT_RG16,                 /** (45)                                */
    BGFX_TEXTURE_FORMAT_RG16I,                /** (46)                                */
    BGFX_TEXTURE_FORMAT_RG16U,                /** (47)                                */
    BGFX_TEXTURE_FORMAT_RG16F,                /** (48)                                */
    BGFX_TEXTURE_FORMAT_RG16S,                /** (49)                                */
    BGFX_TEXTURE_FORMAT_RG32I,                /** (50)                                */
    BGFX_TEXTURE_FORMAT_RG32U,                /** (51)                                */
    BGFX_TEXTURE_FORMAT_RG32F,                /** (52)                                */
    BGFX_TEXTURE_FORMAT_RGB8,                 /** (53)                                */
    BGFX_TEXTURE_FORMAT_RGB8I,                /** (54)                                */
    BGFX_TEXTURE_FORMAT_RGB8U,                /** (55)                                */
    BGFX_TEXTURE_FORMAT_RGB8S,                /** (56)                                */
    BGFX_TEXTURE_FORMAT_RGB9E5F,              /** (57)                                */
    BGFX_TEXTURE_FORMAT_BGRA8,                /** (58)                                */
    BGFX_TEXTURE_FORMAT_RGBA8,                /** (59)                                */
    BGFX_TEXTURE_FORMAT_RGBA8I,               /** (60)                                */
    BGFX_TEXTURE_FORMAT_RGBA8U,               /** (61)                                */
    BGFX_TEXTURE_FORMAT_RGBA8S,               /** (62)                                */
    BGFX_TEXTURE_FORMAT_RGBA16,               /** (63)                                */
    BGFX_TEXTURE_FORMAT_RGBA16I,              /** (64)                                */
    BGFX_TEXTURE_FORMAT_RGBA16U,              /** (65)                                */
    BGFX_TEXTURE_FORMAT_RGBA16F,              /** (66)                                */
    BGFX_TEXTURE_FORMAT_RGBA16S,              /** (67)                                */
    BGFX_TEXTURE_FORMAT_RGBA32I,              /** (68)                                */
    BGFX_TEXTURE_FORMAT_RGBA32U,              /** (69)                                */
    BGFX_TEXTURE_FORMAT_RGBA32F,              /** (70)                                */
    BGFX_TEXTURE_FORMAT_R5G6B5,               /** (71)                                */
    BGFX_TEXTURE_FORMAT_RGBA4,                /** (72)                                */
    BGFX_TEXTURE_FORMAT_RGB5A1,               /** (73)                                */
    BGFX_TEXTURE_FORMAT_RGB10A2,              /** (74)                                */
    BGFX_TEXTURE_FORMAT_RG11B10F,             /** (75)                                */
    BGFX_TEXTURE_FORMAT_UNKNOWNDEPTH,         /** (76) Depth formats below.           */
    BGFX_TEXTURE_FORMAT_D16,                  /** (77)                                */
    BGFX_TEXTURE_FORMAT_D24,                  /** (78)                                */
    BGFX_TEXTURE_FORMAT_D24S8,                /** (79)                                */
    BGFX_TEXTURE_FORMAT_D32,                  /** (80)                                */
    BGFX_TEXTURE_FORMAT_D16F,                 /** (81)                                */
    BGFX_TEXTURE_FORMAT_D24F,                 /** (82)                                */
    BGFX_TEXTURE_FORMAT_D32F,                 /** (83)                                */
    BGFX_TEXTURE_FORMAT_D0S8,                 /** (84)                                */

    BGFX_TEXTURE_FORMAT_COUNT

} bgfx_texture_format_t;

/**
 * Uniform type enum.
 *
 */
typedef enum bgfx_uniform_type
{
    BGFX_UNIFORM_TYPE_SAMPLER,                /** ( 0) Sampler.                       */
    BGFX_UNIFORM_TYPE_END,                    /** ( 1) Reserved, do not use.          */
    BGFX_UNIFORM_TYPE_VEC4,                   /** ( 2) 4 floats vector.               */
    BGFX_UNIFORM_TYPE_MAT3,                   /** ( 3) 3x3 matrix.                    */
    BGFX_UNIFORM_TYPE_MAT4,                   /** ( 4) 4x4 matrix.                    */

    BGFX_UNIFORM_TYPE_COUNT

} bgfx_uniform_type_t;

/**
 * Backbuffer ratio enum.
 *
 */
typedef enum bgfx_backbuffer_ratio
{
    BGFX_BACKBUFFER_RATIO_EQUAL,              /** ( 0) Equal to backbuffer.           */
    BGFX_BACKBUFFER_RATIO_HALF,               /** ( 1) One half size of backbuffer.   */
    BGFX_BACKBUFFER_RATIO_QUARTER,            /** ( 2) One quarter size of backbuffer. */
    BGFX_BACKBUFFER_RATIO_EIGHTH,             /** ( 3) One eighth size of backbuffer. */
    BGFX_BACKBUFFER_RATIO_SIXTEENTH,          /** ( 4) One sixteenth size of backbuffer. */
    BGFX_BACKBUFFER_RATIO_DOUBLE,             /** ( 5) Double size of backbuffer.     */

    BGFX_BACKBUFFER_RATIO_COUNT

} bgfx_backbuffer_ratio_t;

/**
 * Occlusion query result.
 *
 */
typedef enum bgfx_occlusion_query_result
{
    BGFX_OCCLUSION_QUERY_RESULT_INVISIBLE,    /** ( 0) Query failed test.             */
    BGFX_OCCLUSION_QUERY_RESULT_VISIBLE,      /** ( 1) Query passed test.             */
    BGFX_OCCLUSION_QUERY_RESULT_NORESULT,     /** ( 2) Query result is not available yet. */

    BGFX_OCCLUSION_QUERY_RESULT_COUNT

} bgfx_occlusion_query_result_t;

/**
 * Primitive topology.
 *
 */
typedef enum bgfx_topology
{
    BGFX_TOPOLOGY_TRI_LIST,                   /** ( 0) Triangle list.                 */
    BGFX_TOPOLOGY_TRI_STRIP,                  /** ( 1) Triangle strip.                */
    BGFX_TOPOLOGY_LINE_LIST,                  /** ( 2) Line list.                     */
    BGFX_TOPOLOGY_LINE_STRIP,                 /** ( 3) Line strip.                    */
    BGFX_TOPOLOGY_POINT_LIST,                 /** ( 4) Point list.                    */

    BGFX_TOPOLOGY_COUNT

} bgfx_topology_t;

/**
 * Topology conversion function.
 *
 */
typedef enum bgfx_topology_convert
{
    BGFX_TOPOLOGY_CONVERT_TRI_LIST_FLIP_WINDING, /** ( 0) Flip winding order of triangle list. */
    BGFX_TOPOLOGY_CONVERT_TRI_STRIP_FLIP_WINDING, /** ( 1) Flip winding order of trinagle strip. */
    BGFX_TOPOLOGY_CONVERT_TRI_LIST_TO_LINE_LIST, /** ( 2) Convert triangle list to line list. */
    BGFX_TOPOLOGY_CONVERT_TRI_STRIP_TO_TRI_LIST, /** ( 3) Convert triangle strip to triangle list. */
    BGFX_TOPOLOGY_CONVERT_LINE_STRIP_TO_LINE_LIST, /** ( 4) Convert line strip to line list. */

    BGFX_TOPOLOGY_CONVERT_COUNT

} bgfx_topology_convert_t;

/**
 * Topology sort order.
 *
 */
typedef enum bgfx_topology_sort
{
    BGFX_TOPOLOGY_SORT_DIRECTION_FRONT_TO_BACK_MIN, /** ( 0)                                */
    BGFX_TOPOLOGY_SORT_DIRECTION_FRONT_TO_BACK_AVG, /** ( 1)                                */
    BGFX_TOPOLOGY_SORT_DIRECTION_FRONT_TO_BACK_MAX, /** ( 2)                                */
    BGFX_TOPOLOGY_SORT_DIRECTION_BACK_TO_FRONT_MIN, /** ( 3)                                */
    BGFX_TOPOLOGY_SORT_DIRECTION_BACK_TO_FRONT_AVG, /** ( 4)                                */
    BGFX_TOPOLOGY_SORT_DIRECTION_BACK_TO_FRONT_MAX, /** ( 5)                                */
    BGFX_TOPOLOGY_SORT_DISTANCE_FRONT_TO_BACK_MIN, /** ( 6)                                */
    BGFX_TOPOLOGY_SORT_DISTANCE_FRONT_TO_BACK_AVG, /** ( 7)                                */
    BGFX_TOPOLOGY_SORT_DISTANCE_FRONT_TO_BACK_MAX, /** ( 8)                                */
    BGFX_TOPOLOGY_SORT_DISTANCE_BACK_TO_FRONT_MIN, /** ( 9)                                */
    BGFX_TOPOLOGY_SORT_DISTANCE_BACK_TO_FRONT_AVG, /** (10)                                */
    BGFX_TOPOLOGY_SORT_DISTANCE_BACK_TO_FRONT_MAX, /** (11)                                */

    BGFX_TOPOLOGY_SORT_COUNT

} bgfx_topology_sort_t;

/**
 * View mode sets draw call sort order.
 *
 */
typedef enum bgfx_view_mode
{
    BGFX_VIEW_MODE_DEFAULT,                   /** ( 0) Default sort order.            */
    BGFX_VIEW_MODE_SEQUENTIAL,                /** ( 1) Sort in the same order in which submit calls were called. */
    BGFX_VIEW_MODE_DEPTH_ASCENDING,           /** ( 2) Sort draw call depth in ascending order. */
    BGFX_VIEW_MODE_DEPTH_DESCENDING,          /** ( 3) Sort draw call depth in descending order. */

    BGFX_VIEW_MODE_COUNT

} bgfx_view_mode_t;

/**
 * Render frame enum.
 *
 */
typedef enum bgfx_render_frame
{
    BGFX_RENDER_FRAME_NO_CONTEXT,             /** ( 0) Renderer context is not created yet. */
    BGFX_RENDER_FRAME_RENDER,                 /** ( 1) Renderer context is created and rendering. */
    BGFX_RENDER_FRAME_TIMEOUT,                /** ( 2) Renderer context wait for main thread signal timed out without rendering. */
    BGFX_RENDER_FRAME_EXITING,                /** ( 3) Renderer context is getting destroyed. */

    BGFX_RENDER_FRAME_COUNT

} bgfx_render_frame_t;


/**/
typedef uint16_t bgfx_view_id_t;

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
typedef struct bgfx_interface_vtbl bgfx_interface_vtbl_t;

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

typedef struct bgfx_dynamic_index_buffer_handle_s { uint16_t idx; } bgfx_dynamic_index_buffer_handle_t;

typedef struct bgfx_dynamic_vertex_buffer_handle_s { uint16_t idx; } bgfx_dynamic_vertex_buffer_handle_t;

typedef struct bgfx_frame_buffer_handle_s { uint16_t idx; } bgfx_frame_buffer_handle_t;

typedef struct bgfx_index_buffer_handle_s { uint16_t idx; } bgfx_index_buffer_handle_t;

typedef struct bgfx_indirect_buffer_handle_s { uint16_t idx; } bgfx_indirect_buffer_handle_t;

typedef struct bgfx_occlusion_query_handle_s { uint16_t idx; } bgfx_occlusion_query_handle_t;

typedef struct bgfx_program_handle_s { uint16_t idx; } bgfx_program_handle_t;

typedef struct bgfx_shader_handle_s { uint16_t idx; } bgfx_shader_handle_t;

typedef struct bgfx_texture_handle_s { uint16_t idx; } bgfx_texture_handle_t;

typedef struct bgfx_uniform_handle_s { uint16_t idx; } bgfx_uniform_handle_t;

typedef struct bgfx_vertex_buffer_handle_s { uint16_t idx; } bgfx_vertex_buffer_handle_t;

typedef struct bgfx_vertex_layout_handle_s { uint16_t idx; } bgfx_vertex_layout_handle_t;


#define BGFX_HANDLE_IS_VALID(h) ((h).idx != UINT16_MAX)

/**
 * Memory release callback.
 *
 * @param[in] _ptr Pointer to allocated data.
 * @param[in] _userData User defined data if needed.
 *
 */
typedef void (*bgfx_release_fn_t)(void* _ptr, void* _userData);

/**
 * GPU info.
 *
 */
typedef struct bgfx_caps_gpu_s
{
    uint16_t             vendorId;           /** Vendor PCI id. See `BGFX_PCI_ID_*`.      */
    uint16_t             deviceId;           /** Device id.                               */

} bgfx_caps_gpu_t;

/**
 * Renderer runtime limits.
 *
 */
typedef struct bgfx_caps_limits_s
{
    uint32_t             maxDrawCalls;       /** Maximum number of draw calls.            */
    uint32_t             maxBlits;           /** Maximum number of blit calls.            */
    uint32_t             maxTextureSize;     /** Maximum texture size.                    */
    uint32_t             maxTextureLayers;   /** Maximum texture layers.                  */
    uint32_t             maxViews;           /** Maximum number of views.                 */
    uint32_t             maxFrameBuffers;    /** Maximum number of frame buffer handles.  */
    uint32_t             maxFBAttachments;   /** Maximum number of frame buffer attachments. */
    uint32_t             maxPrograms;        /** Maximum number of program handles.       */
    uint32_t             maxShaders;         /** Maximum number of shader handles.        */
    uint32_t             maxTextures;        /** Maximum number of texture handles.       */
    uint32_t             maxTextureSamplers; /** Maximum number of texture samplers.      */
    uint32_t             maxComputeBindings; /** Maximum number of compute bindings.      */
    uint32_t             maxVertexLayouts;   /** Maximum number of vertex format layouts. */
    uint32_t             maxVertexStreams;   /** Maximum number of vertex streams.        */
    uint32_t             maxIndexBuffers;    /** Maximum number of index buffer handles.  */
    uint32_t             maxVertexBuffers;   /** Maximum number of vertex buffer handles. */
    uint32_t             maxDynamicIndexBuffers; /** Maximum number of dynamic index buffer handles. */
    uint32_t             maxDynamicVertexBuffers; /** Maximum number of dynamic vertex buffer handles. */
    uint32_t             maxUniforms;        /** Maximum number of uniform handles.       */
    uint32_t             maxOcclusionQueries; /** Maximum number of occlusion query handles. */
    uint32_t             maxEncoders;        /** Maximum number of encoder threads.       */
    uint32_t             minResourceCbSize;  /** Minimum resource command buffer size.    */
    uint32_t             transientVbSize;    /** Maximum transient vertex buffer size.    */
    uint32_t             transientIbSize;    /** Maximum transient index buffer size.     */

} bgfx_caps_limits_t;

/**
 * Renderer capabilities.
 *
 */
typedef struct bgfx_caps_s
{
    bgfx_renderer_type_t rendererType;       /** Renderer backend type. See: `bgfx::RendererType` */
    
    /**
     * Supported functionality.
     *   @attention See BGFX_CAPS_* flags at https://bkaradzic.github.io/bgfx/bgfx.html#available-caps
     */
    uint64_t             supported;
    uint16_t             vendorId;           /** Selected GPU vendor PCI id.              */
    uint16_t             deviceId;           /** Selected GPU device id.                  */
    bool                 homogeneousDepth;   /** True when NDC depth is in [-1, 1] range, otherwise its [0, 1]. */
    bool                 originBottomLeft;   /** True when NDC origin is at bottom left.  */
    uint8_t              numGPUs;            /** Number of enumerated GPUs.               */
    bgfx_caps_gpu_t      gpu[4];             /** Enumerated GPUs.                         */
    bgfx_caps_limits_t   limits;             /** Renderer runtime limits.                 */
    
    /**
     * Supported texture format capabilities flags:
     *   - `BGFX_CAPS_FORMAT_TEXTURE_NONE` - Texture format is not supported.
     *   - `BGFX_CAPS_FORMAT_TEXTURE_2D` - Texture format is supported.
     *   - `BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB` - Texture as sRGB format is supported.
     *   - `BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED` - Texture format is emulated.
     *   - `BGFX_CAPS_FORMAT_TEXTURE_3D` - Texture format is supported.
     *   - `BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB` - Texture as sRGB format is supported.
     *   - `BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED` - Texture format is emulated.
     *   - `BGFX_CAPS_FORMAT_TEXTURE_CUBE` - Texture format is supported.
     *   - `BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB` - Texture as sRGB format is supported.
     *   - `BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED` - Texture format is emulated.
     *   - `BGFX_CAPS_FORMAT_TEXTURE_VERTEX` - Texture format can be used from vertex shader.
     *   - `BGFX_CAPS_FORMAT_TEXTURE_IMAGE_READ` - Texture format can be used as image
     *     and read from.
     *   - `BGFX_CAPS_FORMAT_TEXTURE_IMAGE_WRITE` - Texture format can be used as image
     *     and written to.
     *   - `BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER` - Texture format can be used as frame
     *     buffer.
     *   - `BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA` - Texture format can be used as MSAA
     *     frame buffer.
     *   - `BGFX_CAPS_FORMAT_TEXTURE_MSAA` - Texture can be sampled as MSAA.
     *   - `BGFX_CAPS_FORMAT_TEXTURE_MIP_AUTOGEN` - Texture format supports auto-generated
     *     mips.
     */
    uint16_t             formats[BGFX_TEXTURE_FORMAT_COUNT];

} bgfx_caps_t;

/**
 * Internal data.
 *
 */
typedef struct bgfx_internal_data_s
{
    const bgfx_caps_t*   caps;               /** Renderer capabilities.                   */
    void*                context;            /** GL context, or D3D device.               */

} bgfx_internal_data_t;

/**
 * Platform data.
 *
 */
typedef struct bgfx_platform_data_s
{
    void*                ndt;                /** Native display type (*nix specific).     */
    
    /**
     * Native window handle. If `NULL` bgfx will create headless
     * context/device if renderer API supports it.
     */
    void*                nwh;
    void*                context;            /** GL context, or D3D device. If `NULL`, bgfx will create context/device. */
    
    /**
     * GL back-buffer, or D3D render target view. If `NULL` bgfx will
     * create back-buffer color surface.
     */
    void*                backBuffer;
    
    /**
     * Backbuffer depth/stencil. If `NULL` bgfx will create back-buffer
     * depth/stencil surface.
     */
    void*                backBufferDS;

} bgfx_platform_data_t;

/**
 * Backbuffer resolution and reset parameters.
 *
 */
typedef struct bgfx_resolution_s
{
    bgfx_texture_format_t format;            /** Backbuffer format.                       */
    uint32_t             width;              /** Backbuffer width.                        */
    uint32_t             height;             /** Backbuffer height.                       */
    uint32_t             reset;              /** Reset parameters.                        */
    uint8_t              numBackBuffers;     /** Number of back buffers.                  */
    uint8_t              maxFrameLatency;    /** Maximum frame latency.                   */

} bgfx_resolution_t;

/**
 * Configurable runtime limits parameters.
 *
 */
typedef struct bgfx_init_limits_s
{
    uint16_t             maxEncoders;        /** Maximum number of encoder threads.       */
    uint32_t             minResourceCbSize;  /** Minimum resource command buffer size.    */
    uint32_t             transientVbSize;    /** Maximum transient vertex buffer size.    */
    uint32_t             transientIbSize;    /** Maximum transient index buffer size.     */

} bgfx_init_limits_t;

/**
 * Initialization parameters used by `bgfx::init`.
 *
 */
typedef struct bgfx_init_s
{
    
    /**
     * Select rendering backend. When set to RendererType::Count
     * a default rendering backend will be selected appropriate to the platform.
     * See: `bgfx::RendererType`
     */
    bgfx_renderer_type_t type;
    
    /**
     * Vendor PCI id. If set to `BGFX_PCI_ID_NONE` it will select the first
     * device.
     *   - `BGFX_PCI_ID_NONE` - Autoselect adapter.
     *   - `BGFX_PCI_ID_SOFTWARE_RASTERIZER` - Software rasterizer.
     *   - `BGFX_PCI_ID_AMD` - AMD adapter.
     *   - `BGFX_PCI_ID_INTEL` - Intel adapter.
     *   - `BGFX_PCI_ID_NVIDIA` - nVidia adapter.
     */
    uint16_t             vendorId;
    
    /**
     * Device id. If set to 0 it will select first device, or device with
     * matching id.
     */
    uint16_t             deviceId;
    bool                 debug;              /** Enable device for debuging.              */
    bool                 profile;            /** Enable device for profiling.             */
    bgfx_platform_data_t platformData;       /** Platform data.                           */
    bgfx_resolution_t    resolution;         /** Backbuffer resolution and reset parameters. See: `bgfx::Resolution`. */
    bgfx_init_limits_t   limits;             /** Configurable runtime limits parameters.  */
    
    /**
     * Provide application specific callback interface.
     * See: `bgfx::CallbackI`
     */
    bgfx_callback_interface_t* callback;
    
    /**
     * Custom allocator. When a custom allocator is not
     * specified, bgfx uses the CRT allocator. Bgfx assumes
     * custom allocator is thread safe.
     */
    bgfx_allocator_interface_t* allocator;

} bgfx_init_t;

/**
 * Memory must be obtained by calling `bgfx::alloc`, `bgfx::copy`, or `bgfx::makeRef`.
 * @attention It is illegal to create this structure on stack and pass it to any bgfx API.
 *
 */
typedef struct bgfx_memory_s
{
    uint8_t*             data;               /** Pointer to data.                         */
    uint32_t             size;               /** Data size.                               */

} bgfx_memory_t;

/**
 * Transient index buffer.
 *
 */
typedef struct bgfx_transient_index_buffer_s
{
    uint8_t*             data;               /** Pointer to data.                         */
    uint32_t             size;               /** Data size.                               */
    uint32_t             startIndex;         /** First index.                             */
    bgfx_index_buffer_handle_t handle;       /** Index buffer handle.                     */

} bgfx_transient_index_buffer_t;

/**
 * Transient vertex buffer.
 *
 */
typedef struct bgfx_transient_vertex_buffer_s
{
    uint8_t*             data;               /** Pointer to data.                         */
    uint32_t             size;               /** Data size.                               */
    uint32_t             startVertex;        /** First vertex.                            */
    uint16_t             stride;             /** Vertex stride.                           */
    bgfx_vertex_buffer_handle_t handle;      /** Vertex buffer handle.                    */
    bgfx_vertex_layout_handle_t layoutHandle; /** Vertex layout handle.                    */

} bgfx_transient_vertex_buffer_t;

/**
 * Instance data buffer info.
 *
 */
typedef struct bgfx_instance_data_buffer_s
{
    uint8_t*             data;               /** Pointer to data.                         */
    uint32_t             size;               /** Data size.                               */
    uint32_t             offset;             /** Offset in vertex buffer.                 */
    uint32_t             num;                /** Number of instances.                     */
    uint16_t             stride;             /** Vertex buffer stride.                    */
    bgfx_vertex_buffer_handle_t handle;      /** Vertex buffer object handle.             */

} bgfx_instance_data_buffer_t;

/**
 * Texture info.
 *
 */
typedef struct bgfx_texture_info_s
{
    bgfx_texture_format_t format;            /** Texture format.                          */
    uint32_t             storageSize;        /** Total amount of bytes required to store texture. */
    uint16_t             width;              /** Texture width.                           */
    uint16_t             height;             /** Texture height.                          */
    uint16_t             depth;              /** Texture depth.                           */
    uint16_t             numLayers;          /** Number of layers in texture array.       */
    uint8_t              numMips;            /** Number of MIP maps.                      */
    uint8_t              bitsPerPixel;       /** Format bits per pixel.                   */
    bool                 cubeMap;            /** Texture is cubemap.                      */

} bgfx_texture_info_t;

/**
 * Uniform info.
 *
 */
typedef struct bgfx_uniform_info_s
{
    char                 name[256];          /** Uniform name.                            */
    bgfx_uniform_type_t  type;               /** Uniform type.                            */
    uint16_t             num;                /** Number of elements in array.             */

} bgfx_uniform_info_t;

/**
 * Frame buffer texture attachment info.
 *
 */
typedef struct bgfx_attachment_s
{
    bgfx_access_t        access;             /** Attachement access. See `Access::Enum`.  */
    bgfx_texture_handle_t handle;            /** Render target texture handle.            */
    uint16_t             mip;                /** Mip level.                               */
    uint16_t             layer;              /** Cubemap side or depth layer/slice.       */
    uint8_t              resolve;            /** Resolve flags. See: `BGFX_RESOLVE_*`     */

} bgfx_attachment_t;

/**
 * Transform data.
 *
 */
typedef struct bgfx_transform_s
{
    float*               data;               /** Pointer to first 4x4 matrix.             */
    uint16_t             num;                /** Number of matrices.                      */

} bgfx_transform_t;

/**
 * View stats.
 *
 */
typedef struct bgfx_view_stats_s
{
    char                 name[256];          /** View name.                               */
    bgfx_view_id_t       view;               /** View id.                                 */
    int64_t              cpuTimeBegin;       /** CPU (submit) begin time.                 */
    int64_t              cpuTimeEnd;         /** CPU (submit) end time.                   */
    int64_t              gpuTimeBegin;       /** GPU begin time.                          */
    int64_t              gpuTimeEnd;         /** GPU end time.                            */

} bgfx_view_stats_t;

/**
 * Encoder stats.
 *
 */
typedef struct bgfx_encoder_stats_s
{
    int64_t              cpuTimeBegin;       /** Encoder thread CPU submit begin time.    */
    int64_t              cpuTimeEnd;         /** Encoder thread CPU submit end time.      */

} bgfx_encoder_stats_t;

/**
 * Renderer statistics data.
 * @remarks All time values are high-resolution timestamps, while
 * time frequencies define timestamps-per-second for that hardware.
 *
 */
typedef struct bgfx_stats_s
{
    int64_t              cpuTimeFrame;       /** CPU time between two `bgfx::frame` calls. */
    int64_t              cpuTimeBegin;       /** Render thread CPU submit begin time.     */
    int64_t              cpuTimeEnd;         /** Render thread CPU submit end time.       */
    int64_t              cpuTimerFreq;       /** CPU timer frequency. Timestamps-per-second */
    int64_t              gpuTimeBegin;       /** GPU frame begin time.                    */
    int64_t              gpuTimeEnd;         /** GPU frame end time.                      */
    int64_t              gpuTimerFreq;       /** GPU timer frequency.                     */
    int64_t              waitRender;         /** Time spent waiting for render backend thread to finish issuing draw commands to underlying graphics API. */
    int64_t              waitSubmit;         /** Time spent waiting for submit thread to advance to next frame. */
    uint32_t             numDraw;            /** Number of draw calls submitted.          */
    uint32_t             numCompute;         /** Number of compute calls submitted.       */
    uint32_t             numBlit;            /** Number of blit calls submitted.          */
    uint32_t             maxGpuLatency;      /** GPU driver latency.                      */
    uint16_t             numDynamicIndexBuffers; /** Number of used dynamic index buffers.    */
    uint16_t             numDynamicVertexBuffers; /** Number of used dynamic vertex buffers.   */
    uint16_t             numFrameBuffers;    /** Number of used frame buffers.            */
    uint16_t             numIndexBuffers;    /** Number of used index buffers.            */
    uint16_t             numOcclusionQueries; /** Number of used occlusion queries.        */
    uint16_t             numPrograms;        /** Number of used programs.                 */
    uint16_t             numShaders;         /** Number of used shaders.                  */
    uint16_t             numTextures;        /** Number of used textures.                 */
    uint16_t             numUniforms;        /** Number of used uniforms.                 */
    uint16_t             numVertexBuffers;   /** Number of used vertex buffers.           */
    uint16_t             numVertexLayouts;   /** Number of used vertex layouts.           */
    int64_t              textureMemoryUsed;  /** Estimate of texture memory used.         */
    int64_t              rtMemoryUsed;       /** Estimate of render target memory used.   */
    int32_t              transientVbUsed;    /** Amount of transient vertex buffer used.  */
    int32_t              transientIbUsed;    /** Amount of transient index buffer used.   */
    uint32_t             numPrims[BGFX_TOPOLOGY_COUNT]; /** Number of primitives rendered.           */
    int64_t              gpuMemoryMax;       /** Maximum available GPU memory for application. */
    int64_t              gpuMemoryUsed;      /** Amount of GPU memory used by the application. */
    uint16_t             width;              /** Backbuffer width in pixels.              */
    uint16_t             height;             /** Backbuffer height in pixels.             */
    uint16_t             textWidth;          /** Debug text width in characters.          */
    uint16_t             textHeight;         /** Debug text height in characters.         */
    uint16_t             numViews;           /** Number of view stats.                    */
    bgfx_view_stats_t*   viewStats;          /** Array of View stats.                     */
    uint8_t              numEncoders;        /** Number of encoders used during frame.    */
    bgfx_encoder_stats_t* encoderStats;      /** Array of encoder stats.                  */

} bgfx_stats_t;

/**
 * Vertex layout.
 *
 */
typedef struct bgfx_vertex_layout_s
{
    uint32_t             hash;               /** Hash.                                    */
    uint16_t             stride;             /** Stride.                                  */
    uint16_t             offset[BGFX_ATTRIB_COUNT]; /** Attribute offsets.                       */
    uint16_t             attributes[BGFX_ATTRIB_COUNT]; /** Used attributes.                         */

} bgfx_vertex_layout_t;

/**
 * Encoders are used for submitting draw calls from multiple threads. Only one encoder
 * per thread should be used. Use `bgfx::begin()` to obtain an encoder for a thread.
 *
 */
struct bgfx_encoder_s;
typedef struct bgfx_encoder_s bgfx_encoder_t;



/**
 * Init attachment.
 *
 * @param[in] _handle Render target texture handle.
 * @param[in] _access Access. See `Access::Enum`.
 * @param[in] _layer Cubemap side or depth layer/slice.
 * @param[in] _mip Mip level.
 * @param[in] _resolve Resolve flags. See: `BGFX_RESOLVE_*`
 *
 */
BGFX_C_API void bgfx_attachment_init(bgfx_attachment_t* _this, bgfx_texture_handle_t _handle, bgfx_access_t _access, uint16_t _layer, uint16_t _mip, uint8_t _resolve);

/**
 * Start VertexLayout.
 *
 * @param[in] _rendererType
 *
 */
BGFX_C_API bgfx_vertex_layout_t* bgfx_vertex_layout_begin(bgfx_vertex_layout_t* _this, bgfx_renderer_type_t _rendererType);

/**
 * Add attribute to VertexLayout.
 * @remarks Must be called between begin/end.
 *
 * @param[in] _attrib Attribute semantics. See: `bgfx::Attrib`
 * @param[in] _num Number of elements 1, 2, 3 or 4.
 * @param[in] _type Element type.
 * @param[in] _normalized When using fixed point AttribType (f.e. Uint8)
 *  value will be normalized for vertex shader usage. When normalized
 *  is set to true, AttribType::Uint8 value in range 0-255 will be
 *  in range 0.0-1.0 in vertex shader.
 * @param[in] _asInt Packaging rule for vertexPack, vertexUnpack, and
 *  vertexConvert for AttribType::Uint8 and AttribType::Int16.
 *  Unpacking code must be implemented inside vertex shader.
 *
 */
BGFX_C_API bgfx_vertex_layout_t* bgfx_vertex_layout_add(bgfx_vertex_layout_t* _this, bgfx_attrib_t _attrib, uint8_t _num, bgfx_attrib_type_t _type, bool _normalized, bool _asInt);

/**
 * Decode attribute.
 *
 * @param[in] _attrib Attribute semantics. See: `bgfx::Attrib`
 * @param[out] _num Number of elements.
 * @param[out] _type Element type.
 * @param[out] _normalized Attribute is normalized.
 * @param[out] _asInt Attribute is packed as int.
 *
 */
BGFX_C_API void bgfx_vertex_layout_decode(const bgfx_vertex_layout_t* _this, bgfx_attrib_t _attrib, uint8_t * _num, bgfx_attrib_type_t * _type, bool * _normalized, bool * _asInt);

/**
 * Returns true if VertexLayout contains attribute.
 *
 * @param[in] _attrib Attribute semantics. See: `bgfx::Attrib`
 *
 */
BGFX_C_API bool bgfx_vertex_layout_has(const bgfx_vertex_layout_t* _this, bgfx_attrib_t _attrib);

/**
 * Skip `_num` bytes in vertex stream.
 *
 * @param[in] _num
 *
 */
BGFX_C_API bgfx_vertex_layout_t* bgfx_vertex_layout_skip(bgfx_vertex_layout_t* _this, uint8_t _num);

/**
 * End VertexLayout.
 *
 */
BGFX_C_API void bgfx_vertex_layout_end(bgfx_vertex_layout_t* _this);

/**
 * Pack vertex attribute into vertex stream format.
 *
 * @param[in] _input Value to be packed into vertex stream.
 * @param[in] _inputNormalized `true` if input value is already normalized.
 * @param[in] _attr Attribute to pack.
 * @param[in] _layout Vertex stream layout.
 * @param[in] _data Destination vertex stream where data will be packed.
 * @param[in] _index Vertex index that will be modified.
 *
 */
BGFX_C_API void bgfx_vertex_pack(const float _input[4], bool _inputNormalized, bgfx_attrib_t _attr, const bgfx_vertex_layout_t * _layout, void* _data, uint32_t _index);

/**
 * Unpack vertex attribute from vertex stream format.
 *
 * @param[out] _output Result of unpacking.
 * @param[in] _attr Attribute to unpack.
 * @param[in] _layout Vertex stream layout.
 * @param[in] _data Source vertex stream from where data will be unpacked.
 * @param[in] _index Vertex index that will be unpacked.
 *
 */
BGFX_C_API void bgfx_vertex_unpack(float _output[4], bgfx_attrib_t _attr, const bgfx_vertex_layout_t * _layout, const void* _data, uint32_t _index);

/**
 * Converts vertex stream data from one vertex stream format to another.
 *
 * @param[in] _dstLayout Destination vertex stream layout.
 * @param[in] _dstData Destination vertex stream.
 * @param[in] _srcLayout Source vertex stream layout.
 * @param[in] _srcData Source vertex stream data.
 * @param[in] _num Number of vertices to convert from source to destination.
 *
 */
BGFX_C_API void bgfx_vertex_convert(const bgfx_vertex_layout_t * _dstLayout, void* _dstData, const bgfx_vertex_layout_t * _srcLayout, const void* _srcData, uint32_t _num);

/**
 * Weld vertices.
 *
 * @param[in] _output Welded vertices remapping table. The size of buffer
 *  must be the same as number of vertices.
 * @param[in] _layout Vertex stream layout.
 * @param[in] _data Vertex stream.
 * @param[in] _num Number of vertices in vertex stream.
 * @param[in] _index32 Set to `true` if input indices are 32-bit.
 * @param[in] _epsilon Error tolerance for vertex position comparison.
 *
 * @returns Number of unique vertices after vertex welding.
 *
 */
BGFX_C_API uint32_t bgfx_weld_vertices(void* _output, const bgfx_vertex_layout_t * _layout, const void* _data, uint32_t _num, bool _index32, float _epsilon);

/**
 * Convert index buffer for use with different primitive topologies.
 *
 * @param[in] _conversion Conversion type, see `TopologyConvert::Enum`.
 * @param[out] _dst Destination index buffer. If this argument is NULL
 *  function will return number of indices after conversion.
 * @param[in] _dstSize Destination index buffer in bytes. It must be
 *  large enough to contain output indices. If destination size is
 *  insufficient index buffer will be truncated.
 * @param[in] _indices Source indices.
 * @param[in] _numIndices Number of input indices.
 * @param[in] _index32 Set to `true` if input indices are 32-bit.
 *
 * @returns Number of output indices after conversion.
 *
 */
BGFX_C_API uint32_t bgfx_topology_convert(bgfx_topology_convert_t _conversion, void* _dst, uint32_t _dstSize, const void* _indices, uint32_t _numIndices, bool _index32);

/**
 * Sort indices.
 *
 * @param[in] _sort Sort order, see `TopologySort::Enum`.
 * @param[out] _dst Destination index buffer.
 * @param[in] _dstSize Destination index buffer in bytes. It must be
 *  large enough to contain output indices. If destination size is
 *  insufficient index buffer will be truncated.
 * @param[in] _dir Direction (vector must be normalized).
 * @param[in] _pos Position.
 * @param[in] _vertices Pointer to first vertex represented as
 *  float x, y, z. Must contain at least number of vertices
 *  referencende by index buffer.
 * @param[in] _stride Vertex stride.
 * @param[in] _indices Source indices.
 * @param[in] _numIndices Number of input indices.
 * @param[in] _index32 Set to `true` if input indices are 32-bit.
 *
 */
BGFX_C_API void bgfx_topology_sort_tri_list(bgfx_topology_sort_t _sort, void* _dst, uint32_t _dstSize, const float _dir[3], const float _pos[3], const void* _vertices, uint32_t _stride, const void* _indices, uint32_t _numIndices, bool _index32);

/**
 * Returns supported backend API renderers.
 *
 * @param[in] _max Maximum number of elements in _enum array.
 * @param[inout] _enum Array where supported renderers will be written.
 *
 * @returns Number of supported renderers.
 *
 */
BGFX_C_API uint8_t bgfx_get_supported_renderers(uint8_t _max, bgfx_renderer_type_t* _enum);

/**
 * Returns name of renderer.
 *
 * @param[in] _type Renderer backend type. See: `bgfx::RendererType`
 *
 * @returns Name of renderer.
 *
 */
BGFX_C_API const char* bgfx_get_renderer_name(bgfx_renderer_type_t _type);
BGFX_C_API void bgfx_init_ctor(bgfx_init_t* _init);

/**
 * Initialize bgfx library.
 *
 * @param[in] _init Initialization parameters. See: `bgfx::Init` for more info.
 *
 * @returns `true` if initialization was successful.
 *
 */
BGFX_C_API bool bgfx_init(const bgfx_init_t * _init);

/**
 * Shutdown bgfx library.
 *
 */
BGFX_C_API void bgfx_shutdown(void);

/**
 * Reset graphic settings and back-buffer size.
 * @attention This call doesn't actually change window size, it just
 *   resizes back-buffer. Windowing code has to change window size.
 *
 * @param[in] _width Back-buffer width.
 * @param[in] _height Back-buffer height.
 * @param[in] _flags See: `BGFX_RESET_*` for more info.
 *    - `BGFX_RESET_NONE` - No reset flags.
 *    - `BGFX_RESET_FULLSCREEN` - Not supported yet.
 *    - `BGFX_RESET_MSAA_X[2/4/8/16]` - Enable 2, 4, 8 or 16 x MSAA.
 *    - `BGFX_RESET_VSYNC` - Enable V-Sync.
 *    - `BGFX_RESET_MAXANISOTROPY` - Turn on/off max anisotropy.
 *    - `BGFX_RESET_CAPTURE` - Begin screen capture.
 *    - `BGFX_RESET_FLUSH_AFTER_RENDER` - Flush rendering after submitting to GPU.
 *    - `BGFX_RESET_FLIP_AFTER_RENDER` - This flag  specifies where flip
 *      occurs. Default behaviour is that flip occurs before rendering new
 *      frame. This flag only has effect when `BGFX_CONFIG_MULTITHREADED=0`.
 *    - `BGFX_RESET_SRGB_BACKBUFFER` - Enable sRGB backbuffer.
 * @param[in] _format Texture format. See: `TextureFormat::Enum`.
 *
 */
BGFX_C_API void bgfx_reset(uint32_t _width, uint32_t _height, uint32_t _flags, bgfx_texture_format_t _format);

/**
 * Advance to next frame. When using multithreaded renderer, this call
 * just swaps internal buffers, kicks render thread, and returns. In
 * singlethreaded renderer this call does frame rendering.
 *
 * @param[in] _capture Capture frame with graphics debugger.
 *
 * @returns Current frame number. This might be used in conjunction with
 *  double/multi buffering data outside the library and passing it to
 *  library via `bgfx::makeRef` calls.
 *
 */
BGFX_C_API uint32_t bgfx_frame(bool _capture);

/**
 * Returns current renderer backend API type.
 * @remarks
 *   Library must be initialized.
 *
 */
BGFX_C_API bgfx_renderer_type_t bgfx_get_renderer_type(void);

/**
 * Returns renderer capabilities.
 * @remarks
 *   Library must be initialized.
 *
 */
BGFX_C_API const bgfx_caps_t* bgfx_get_caps(void);

/**
 * Returns performance counters.
 * @attention Pointer returned is valid until `bgfx::frame` is called.
 *
 */
BGFX_C_API const bgfx_stats_t* bgfx_get_stats(void);

/**
 * Allocate buffer to pass to bgfx calls. Data will be freed inside bgfx.
 *
 * @param[in] _size Size to allocate.
 *
 * @returns Allocated memory.
 *
 */
BGFX_C_API const bgfx_memory_t* bgfx_alloc(uint32_t _size);

/**
 * Allocate buffer and copy data into it. Data will be freed inside bgfx.
 *
 * @param[in] _data Pointer to data to be copied.
 * @param[in] _size Size of data to be copied.
 *
 * @returns Allocated memory.
 *
 */
BGFX_C_API const bgfx_memory_t* bgfx_copy(const void* _data, uint32_t _size);

/**
 * Make reference to data to pass to bgfx. Unlike `bgfx::alloc`, this call
 * doesn't allocate memory for data. It just copies the _data pointer. You
 * can pass `ReleaseFn` function pointer to release this memory after it's
 * consumed, otherwise you must make sure _data is available for at least 2
 * `bgfx::frame` calls. `ReleaseFn` function must be able to be called
 * from any thread.
 * @attention Data passed must be available for at least 2 `bgfx::frame` calls.
 *
 * @param[in] _data Pointer to data.
 * @param[in] _size Size of data.
 *
 * @returns Referenced memory.
 *
 */
BGFX_C_API const bgfx_memory_t* bgfx_make_ref(const void* _data, uint32_t _size);

/**
 * Make reference to data to pass to bgfx. Unlike `bgfx::alloc`, this call
 * doesn't allocate memory for data. It just copies the _data pointer. You
 * can pass `ReleaseFn` function pointer to release this memory after it's
 * consumed, otherwise you must make sure _data is available for at least 2
 * `bgfx::frame` calls. `ReleaseFn` function must be able to be called
 * from any thread.
 * @attention Data passed must be available for at least 2 `bgfx::frame` calls.
 *
 * @param[in] _data Pointer to data.
 * @param[in] _size Size of data.
 * @param[in] _releaseFn Callback function to release memory after use.
 * @param[in] _userData User data to be passed to callback function.
 *
 * @returns Referenced memory.
 *
 */
BGFX_C_API const bgfx_memory_t* bgfx_make_ref_release(const void* _data, uint32_t _size, bgfx_release_fn_t _releaseFn, void* _userData);

/**
 * Set debug flags.
 *
 * @param[in] _debug Available flags:
 *    - `BGFX_DEBUG_IFH` - Infinitely fast hardware. When this flag is set
 *      all rendering calls will be skipped. This is useful when profiling
 *      to quickly assess potential bottlenecks between CPU and GPU.
 *    - `BGFX_DEBUG_PROFILER` - Enable profiler.
 *    - `BGFX_DEBUG_STATS` - Display internal statistics.
 *    - `BGFX_DEBUG_TEXT` - Display debug text.
 *    - `BGFX_DEBUG_WIREFRAME` - Wireframe rendering. All rendering
 *      primitives will be rendered as lines.
 *
 */
BGFX_C_API void bgfx_set_debug(uint32_t _debug);

/**
 * Clear internal debug text buffer.
 *
 * @param[in] _attr Background color.
 * @param[in] _small Default 8x16 or 8x8 font.
 *
 */
BGFX_C_API void bgfx_dbg_text_clear(uint8_t _attr, bool _small);

/**
 * Print formatted data to internal debug text character-buffer (VGA-compatible text mode).
 *
 * @param[in] _x Position x from the left corner of the window.
 * @param[in] _y Position y from the top corner of the window.
 * @param[in] _attr Color palette. Where top 4-bits represent index of background, and bottom
 *  4-bits represent foreground color from standard VGA text palette (ANSI escape codes).
 * @param[in] _format `printf` style format.
 * @param[in]
 *
 */
BGFX_C_API void bgfx_dbg_text_printf(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, ... );

/**
 * Print formatted data from variable argument list to internal debug text character-buffer (VGA-compatible text mode).
 *
 * @param[in] _x Position x from the left corner of the window.
 * @param[in] _y Position y from the top corner of the window.
 * @param[in] _attr Color palette. Where top 4-bits represent index of background, and bottom
 *  4-bits represent foreground color from standard VGA text palette (ANSI escape codes).
 * @param[in] _format `printf` style format.
 * @param[in] _argList Variable arguments list for format string.
 *
 */
BGFX_C_API void bgfx_dbg_text_vprintf(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, va_list _argList);

/**
 * Draw image into internal debug text buffer.
 *
 * @param[in] _x Position x from the left corner of the window.
 * @param[in] _y Position y from the top corner of the window.
 * @param[in] _width Image width.
 * @param[in] _height Image height.
 * @param[in] _data Raw image data (character/attribute raw encoding).
 * @param[in] _pitch Image pitch in bytes.
 *
 */
BGFX_C_API void bgfx_dbg_text_image(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const void* _data, uint16_t _pitch);

/**
 * Create static index buffer.
 *
 * @param[in] _mem Index buffer data.
 * @param[in] _flags Buffer creation flags.
 *    - `BGFX_BUFFER_NONE` - No flags.
 *    - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
 *    - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
 *        is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
 *    - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
 *    - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
 *        data is passed. If this flag is not specified, and more data is passed on update, the buffer
 *        will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
 *        buffers.
 *    - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
 *        index buffers.
 *
 */
BGFX_C_API bgfx_index_buffer_handle_t bgfx_create_index_buffer(const bgfx_memory_t* _mem, uint16_t _flags);

/**
 * Set static index buffer debug name.
 *
 * @param[in] _handle Static index buffer handle.
 * @param[in] _name Static index buffer name.
 * @param[in] _len Static index buffer name length (if length is INT32_MAX, it's expected
 *  that _name is zero terminated string.
 *
 */
BGFX_C_API void bgfx_set_index_buffer_name(bgfx_index_buffer_handle_t _handle, const char* _name, int32_t _len);

/**
 * Destroy static index buffer.
 *
 * @param[in] _handle Static index buffer handle.
 *
 */
BGFX_C_API void bgfx_destroy_index_buffer(bgfx_index_buffer_handle_t _handle);

/**
 * Create vertex layout.
 *
 * @param[in] _layout Vertex layout.
 *
 */
BGFX_C_API bgfx_vertex_layout_handle_t bgfx_create_vertex_layout(const bgfx_vertex_layout_t * _layout);

/**
 * Destroy vertex layout.
 *
 * @param[in] _layoutHandle Vertex layout handle.
 *
 */
BGFX_C_API void bgfx_destroy_vertex_layout(bgfx_vertex_layout_handle_t _layoutHandle);

/**
 * Create static vertex buffer.
 *
 * @param[in] _mem Vertex buffer data.
 * @param[in] _layout Vertex layout.
 * @param[in] _flags Buffer creation flags.
 *   - `BGFX_BUFFER_NONE` - No flags.
 *   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
 *   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
 *       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
 *   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
 *   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
 *       data is passed. If this flag is not specified, and more data is passed on update, the buffer
 *       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic buffers.
 *   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on index buffers.
 *
 * @returns Static vertex buffer handle.
 *
 */
BGFX_C_API bgfx_vertex_buffer_handle_t bgfx_create_vertex_buffer(const bgfx_memory_t* _mem, const bgfx_vertex_layout_t * _layout, uint16_t _flags);

/**
 * Set static vertex buffer debug name.
 *
 * @param[in] _handle Static vertex buffer handle.
 * @param[in] _name Static vertex buffer name.
 * @param[in] _len Static vertex buffer name length (if length is INT32_MAX, it's expected
 *  that _name is zero terminated string.
 *
 */
BGFX_C_API void bgfx_set_vertex_buffer_name(bgfx_vertex_buffer_handle_t _handle, const char* _name, int32_t _len);

/**
 * Destroy static vertex buffer.
 *
 * @param[in] _handle Static vertex buffer handle.
 *
 */
BGFX_C_API void bgfx_destroy_vertex_buffer(bgfx_vertex_buffer_handle_t _handle);

/**
 * Create empty dynamic index buffer.
 *
 * @param[in] _num Number of indices.
 * @param[in] _flags Buffer creation flags.
 *    - `BGFX_BUFFER_NONE` - No flags.
 *    - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
 *    - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
 *        is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
 *    - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
 *    - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
 *        data is passed. If this flag is not specified, and more data is passed on update, the buffer
 *        will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
 *        buffers.
 *    - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
 *        index buffers.
 *
 * @returns Dynamic index buffer handle.
 *
 */
BGFX_C_API bgfx_dynamic_index_buffer_handle_t bgfx_create_dynamic_index_buffer(uint32_t _num, uint16_t _flags);

/**
 * Create dynamic index buffer and initialized it.
 *
 * @param[in] _mem Index buffer data.
 * @param[in] _flags Buffer creation flags.
 *    - `BGFX_BUFFER_NONE` - No flags.
 *    - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
 *    - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
 *        is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
 *    - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
 *    - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
 *        data is passed. If this flag is not specified, and more data is passed on update, the buffer
 *        will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
 *        buffers.
 *    - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
 *        index buffers.
 *
 * @returns Dynamic index buffer handle.
 *
 */
BGFX_C_API bgfx_dynamic_index_buffer_handle_t bgfx_create_dynamic_index_buffer_mem(const bgfx_memory_t* _mem, uint16_t _flags);

/**
 * Update dynamic index buffer.
 *
 * @param[in] _handle Dynamic index buffer handle.
 * @param[in] _startIndex Start index.
 * @param[in] _mem Index buffer data.
 *
 */
BGFX_C_API void bgfx_update_dynamic_index_buffer(bgfx_dynamic_index_buffer_handle_t _handle, uint32_t _startIndex, const bgfx_memory_t* _mem);

/**
 * Destroy dynamic index buffer.
 *
 * @param[in] _handle Dynamic index buffer handle.
 *
 */
BGFX_C_API void bgfx_destroy_dynamic_index_buffer(bgfx_dynamic_index_buffer_handle_t _handle);

/**
 * Create empty dynamic vertex buffer.
 *
 * @param[in] _num Number of vertices.
 * @param[in] _layout Vertex layout.
 * @param[in] _flags Buffer creation flags.
 *    - `BGFX_BUFFER_NONE` - No flags.
 *    - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
 *    - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
 *        is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
 *    - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
 *    - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
 *        data is passed. If this flag is not specified, and more data is passed on update, the buffer
 *        will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
 *        buffers.
 *    - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
 *        index buffers.
 *
 * @returns Dynamic vertex buffer handle.
 *
 */
BGFX_C_API bgfx_dynamic_vertex_buffer_handle_t bgfx_create_dynamic_vertex_buffer(uint32_t _num, const bgfx_vertex_layout_t* _layout, uint16_t _flags);

/**
 * Create dynamic vertex buffer and initialize it.
 *
 * @param[in] _mem Vertex buffer data.
 * @param[in] _layout Vertex layout.
 * @param[in] _flags Buffer creation flags.
 *    - `BGFX_BUFFER_NONE` - No flags.
 *    - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
 *    - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
 *        is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
 *    - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
 *    - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
 *        data is passed. If this flag is not specified, and more data is passed on update, the buffer
 *        will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
 *        buffers.
 *    - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
 *        index buffers.
 *
 * @returns Dynamic vertex buffer handle.
 *
 */
BGFX_C_API bgfx_dynamic_vertex_buffer_handle_t bgfx_create_dynamic_vertex_buffer_mem(const bgfx_memory_t* _mem, const bgfx_vertex_layout_t* _layout, uint16_t _flags);

/**
 * Update dynamic vertex buffer.
 *
 * @param[in] _handle Dynamic vertex buffer handle.
 * @param[in] _startVertex Start vertex.
 * @param[in] _mem Vertex buffer data.
 *
 */
BGFX_C_API void bgfx_update_dynamic_vertex_buffer(bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, const bgfx_memory_t* _mem);

/**
 * Destroy dynamic vertex buffer.
 *
 * @param[in] _handle Dynamic vertex buffer handle.
 *
 */
BGFX_C_API void bgfx_destroy_dynamic_vertex_buffer(bgfx_dynamic_vertex_buffer_handle_t _handle);

/**
 * Returns number of requested or maximum available indices.
 *
 * @param[in] _num Number of required indices.
 *
 * @returns Number of requested or maximum available indices.
 *
 */
BGFX_C_API uint32_t bgfx_get_avail_transient_index_buffer(uint32_t _num);

/**
 * Returns number of requested or maximum available vertices.
 *
 * @param[in] _num Number of required vertices.
 * @param[in] _layout Vertex layout.
 *
 * @returns Number of requested or maximum available vertices.
 *
 */
BGFX_C_API uint32_t bgfx_get_avail_transient_vertex_buffer(uint32_t _num, const bgfx_vertex_layout_t * _layout);

/**
 * Returns number of requested or maximum available instance buffer slots.
 *
 * @param[in] _num Number of required instances.
 * @param[in] _stride Stride per instance.
 *
 * @returns Number of requested or maximum available instance buffer slots.
 *
 */
BGFX_C_API uint32_t bgfx_get_avail_instance_data_buffer(uint32_t _num, uint16_t _stride);

/**
 * Allocate transient index buffer.
 * @remarks
 *   Only 16-bit index buffer is supported.
 *
 * @param[out] _tib TransientIndexBuffer structure is filled and is valid
 *  for the duration of frame, and it can be reused for multiple draw
 *  calls.
 * @param[in] _num Number of indices to allocate.
 *
 */
BGFX_C_API void bgfx_alloc_transient_index_buffer(bgfx_transient_index_buffer_t* _tib, uint32_t _num);

/**
 * Allocate transient vertex buffer.
 *
 * @param[out] _tvb TransientVertexBuffer structure is filled and is valid
 *  for the duration of frame, and it can be reused for multiple draw
 *  calls.
 * @param[in] _num Number of vertices to allocate.
 * @param[in] _layout Vertex layout.
 *
 */
BGFX_C_API void bgfx_alloc_transient_vertex_buffer(bgfx_transient_vertex_buffer_t* _tvb, uint32_t _num, const bgfx_vertex_layout_t * _layout);

/**
 * Check for required space and allocate transient vertex and index
 * buffers. If both space requirements are satisfied function returns
 * true.
 * @remarks
 *   Only 16-bit index buffer is supported.
 *
 * @param[out] _tvb TransientVertexBuffer structure is filled and is valid
 *  for the duration of frame, and it can be reused for multiple draw
 *  calls.
 * @param[in] _layout Vertex layout.
 * @param[in] _numVertices Number of vertices to allocate.
 * @param[out] _tib TransientIndexBuffer structure is filled and is valid
 *  for the duration of frame, and it can be reused for multiple draw
 *  calls.
 * @param[in] _numIndices Number of indices to allocate.
 *
 */
BGFX_C_API bool bgfx_alloc_transient_buffers(bgfx_transient_vertex_buffer_t* _tvb, const bgfx_vertex_layout_t * _layout, uint32_t _numVertices, bgfx_transient_index_buffer_t* _tib, uint32_t _numIndices);

/**
 * Allocate instance data buffer.
 *
 * @param[out] _idb InstanceDataBuffer structure is filled and is valid
 *  for duration of frame, and it can be reused for multiple draw
 *  calls.
 * @param[in] _num Number of instances.
 * @param[in] _stride Instance stride. Must be multiple of 16.
 *
 */
BGFX_C_API void bgfx_alloc_instance_data_buffer(bgfx_instance_data_buffer_t* _idb, uint32_t _num, uint16_t _stride);

/**
 * Create draw indirect buffer.
 *
 * @param[in] _num Number of indirect calls.
 *
 * @returns Indirect buffer handle.
 *
 */
BGFX_C_API bgfx_indirect_buffer_handle_t bgfx_create_indirect_buffer(uint32_t _num);

/**
 * Destroy draw indirect buffer.
 *
 * @param[in] _handle Indirect buffer handle.
 *
 */
BGFX_C_API void bgfx_destroy_indirect_buffer(bgfx_indirect_buffer_handle_t _handle);

/**
 * Create shader from memory buffer.
 *
 * @param[in] _mem Shader binary.
 *
 * @returns Shader handle.
 *
 */
BGFX_C_API bgfx_shader_handle_t bgfx_create_shader(const bgfx_memory_t* _mem);

/**
 * Returns the number of uniforms and uniform handles used inside a shader.
 * @remarks
 *   Only non-predefined uniforms are returned.
 *
 * @param[in] _handle Shader handle.
 * @param[out] _uniforms UniformHandle array where data will be stored.
 * @param[in] _max Maximum capacity of array.
 *
 * @returns Number of uniforms used by shader.
 *
 */
BGFX_C_API uint16_t bgfx_get_shader_uniforms(bgfx_shader_handle_t _handle, bgfx_uniform_handle_t* _uniforms, uint16_t _max);

/**
 * Set shader debug name.
 *
 * @param[in] _handle Shader handle.
 * @param[in] _name Shader name.
 * @param[in] _len Shader name length (if length is INT32_MAX, it's expected
 *  that _name is zero terminated string).
 *
 */
BGFX_C_API void bgfx_set_shader_name(bgfx_shader_handle_t _handle, const char* _name, int32_t _len);

/**
 * Destroy shader.
 * @remark Once a shader program is created with _handle,
 *   it is safe to destroy that shader.
 *
 * @param[in] _handle Shader handle.
 *
 */
BGFX_C_API void bgfx_destroy_shader(bgfx_shader_handle_t _handle);

/**
 * Create program with vertex and fragment shaders.
 *
 * @param[in] _vsh Vertex shader.
 * @param[in] _fsh Fragment shader.
 * @param[in] _destroyShaders If true, shaders will be destroyed when program is destroyed.
 *
 * @returns Program handle if vertex shader output and fragment shader
 *  input are matching, otherwise returns invalid program handle.
 *
 */
BGFX_C_API bgfx_program_handle_t bgfx_create_program(bgfx_shader_handle_t _vsh, bgfx_shader_handle_t _fsh, bool _destroyShaders);

/**
 * Create program with compute shader.
 *
 * @param[in] _csh Compute shader.
 * @param[in] _destroyShaders If true, shaders will be destroyed when program is destroyed.
 *
 * @returns Program handle.
 *
 */
BGFX_C_API bgfx_program_handle_t bgfx_create_compute_program(bgfx_shader_handle_t _csh, bool _destroyShaders);

/**
 * Destroy program.
 *
 * @param[in] _handle Program handle.
 *
 */
BGFX_C_API void bgfx_destroy_program(bgfx_program_handle_t _handle);

/**
 * Validate texture parameters.
 *
 * @param[in] _depth Depth dimension of volume texture.
 * @param[in] _cubeMap Indicates that texture contains cubemap.
 * @param[in] _numLayers Number of layers in texture array.
 * @param[in] _format Texture format. See: `TextureFormat::Enum`.
 * @param[in] _flags Texture flags. See `BGFX_TEXTURE_*`.
 *
 * @returns True if texture can be successfully created.
 *
 */
BGFX_C_API bool bgfx_is_texture_valid(uint16_t _depth, bool _cubeMap, uint16_t _numLayers, bgfx_texture_format_t _format, uint64_t _flags);

/**
 * Calculate amount of memory required for texture.
 *
 * @param[out] _info Resulting texture info structure. See: `TextureInfo`.
 * @param[in] _width Width.
 * @param[in] _height Height.
 * @param[in] _depth Depth dimension of volume texture.
 * @param[in] _cubeMap Indicates that texture contains cubemap.
 * @param[in] _hasMips Indicates that texture contains full mip-map chain.
 * @param[in] _numLayers Number of layers in texture array.
 * @param[in] _format Texture format. See: `TextureFormat::Enum`.
 *
 */
BGFX_C_API void bgfx_calc_texture_size(bgfx_texture_info_t * _info, uint16_t _width, uint16_t _height, uint16_t _depth, bool _cubeMap, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format);

/**
 * Create texture from memory buffer.
 *
 * @param[in] _mem DDS, KTX or PVR texture binary data.
 * @param[in] _flags Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
 *  flags. Default texture sampling mode is linear, and wrap mode is repeat.
 *  - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
 *    mode.
 *  - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
 *    sampling.
 * @param[in] _skip Skip top level mips when parsing texture.
 * @param[out] _info When non-`NULL` is specified it returns parsed texture information.
 *
 * @returns Texture handle.
 *
 */
BGFX_C_API bgfx_texture_handle_t bgfx_create_texture(const bgfx_memory_t* _mem, uint64_t _flags, uint8_t _skip, bgfx_texture_info_t* _info);

/**
 * Create 2D texture.
 *
 * @param[in] _width Width.
 * @param[in] _height Height.
 * @param[in] _hasMips Indicates that texture contains full mip-map chain.
 * @param[in] _numLayers Number of layers in texture array. Must be 1 if caps
 *  `BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.
 * @param[in] _format Texture format. See: `TextureFormat::Enum`.
 * @param[in] _flags Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
 *  flags. Default texture sampling mode is linear, and wrap mode is repeat.
 *  - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
 *    mode.
 *  - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
 *    sampling.
 * @param[in] _mem Texture data. If `_mem` is non-NULL, created texture will be immutable. If
 *  `_mem` is NULL content of the texture is uninitialized. When `_numLayers` is more than
 *  1, expected memory layout is texture and all mips together for each array element.
 *
 * @returns Texture handle.
 *
 */
BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_2d(uint16_t _width, uint16_t _height, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format, uint64_t _flags, const bgfx_memory_t* _mem);

/**
 * Create texture with size based on backbuffer ratio. Texture will maintain ratio
 * if back buffer resolution changes.
 *
 * @param[in] _ratio Texture size in respect to back-buffer size. See: `BackbufferRatio::Enum`.
 * @param[in] _hasMips Indicates that texture contains full mip-map chain.
 * @param[in] _numLayers Number of layers in texture array. Must be 1 if caps
 *  `BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.
 * @param[in] _format Texture format. See: `TextureFormat::Enum`.
 * @param[in] _flags Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
 *  flags. Default texture sampling mode is linear, and wrap mode is repeat.
 *  - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
 *    mode.
 *  - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
 *    sampling.
 *
 * @returns Texture handle.
 *
 */
BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_2d_scaled(bgfx_backbuffer_ratio_t _ratio, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format, uint64_t _flags);

/**
 * Create 3D texture.
 *
 * @param[in] _width Width.
 * @param[in] _height Height.
 * @param[in] _depth Depth.
 * @param[in] _hasMips Indicates that texture contains full mip-map chain.
 * @param[in] _format Texture format. See: `TextureFormat::Enum`.
 * @param[in] _flags Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
 *  flags. Default texture sampling mode is linear, and wrap mode is repeat.
 *  - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
 *    mode.
 *  - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
 *    sampling.
 * @param[in] _mem Texture data. If `_mem` is non-NULL, created texture will be immutable. If
 *  `_mem` is NULL content of the texture is uninitialized. When `_numLayers` is more than
 *  1, expected memory layout is texture and all mips together for each array element.
 *
 * @returns Texture handle.
 *
 */
BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_3d(uint16_t _width, uint16_t _height, uint16_t _depth, bool _hasMips, bgfx_texture_format_t _format, uint64_t _flags, const bgfx_memory_t* _mem);

/**
 * Create Cube texture.
 *
 * @param[in] _size Cube side size.
 * @param[in] _hasMips Indicates that texture contains full mip-map chain.
 * @param[in] _numLayers Number of layers in texture array. Must be 1 if caps
 *  `BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.
 * @param[in] _format Texture format. See: `TextureFormat::Enum`.
 * @param[in] _flags Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
 *  flags. Default texture sampling mode is linear, and wrap mode is repeat.
 *  - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
 *    mode.
 *  - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
 *    sampling.
 * @param[in] _mem Texture data. If `_mem` is non-NULL, created texture will be immutable. If
 *  `_mem` is NULL content of the texture is uninitialized. When `_numLayers` is more than
 *  1, expected memory layout is texture and all mips together for each array element.
 *
 * @returns Texture handle.
 *
 */
BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_cube(uint16_t _size, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format, uint64_t _flags, const bgfx_memory_t* _mem);

/**
 * Update 2D texture.
 * @attention It's valid to update only mutable texture. See `bgfx::createTexture2D` for more info.
 *
 * @param[in] _handle Texture handle.
 * @param[in] _layer Layer in texture array.
 * @param[in] _mip Mip level.
 * @param[in] _x X offset in texture.
 * @param[in] _y Y offset in texture.
 * @param[in] _width Width of texture block.
 * @param[in] _height Height of texture block.
 * @param[in] _mem Texture update data.
 * @param[in] _pitch Pitch of input image (bytes). When _pitch is set to
 *  UINT16_MAX, it will be calculated internally based on _width.
 *
 */
BGFX_C_API void bgfx_update_texture_2d(bgfx_texture_handle_t _handle, uint16_t _layer, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const bgfx_memory_t* _mem, uint16_t _pitch);

/**
 * Update 3D texture.
 * @attention It's valid to update only mutable texture. See `bgfx::createTexture3D` for more info.
 *
 * @param[in] _handle Texture handle.
 * @param[in] _mip Mip level.
 * @param[in] _x X offset in texture.
 * @param[in] _y Y offset in texture.
 * @param[in] _z Z offset in texture.
 * @param[in] _width Width of texture block.
 * @param[in] _height Height of texture block.
 * @param[in] _depth Depth of texture block.
 * @param[in] _mem Texture update data.
 *
 */
BGFX_C_API void bgfx_update_texture_3d(bgfx_texture_handle_t _handle, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _z, uint16_t _width, uint16_t _height, uint16_t _depth, const bgfx_memory_t* _mem);

/**
 * Update Cube texture.
 * @attention It's valid to update only mutable texture. See `bgfx::createTextureCube` for more info.
 *
 * @param[in] _handle Texture handle.
 * @param[in] _layer Layer in texture array.
 * @param[in] _side Cubemap side `BGFX_CUBE_MAP_<POSITIVE or NEGATIVE>_<X, Y or Z>`,
 *    where 0 is +X, 1 is -X, 2 is +Y, 3 is -Y, 4 is +Z, and 5 is -Z.
 *                   +----------+
 *                   |-z       2|
 *                   | ^  +y    |
 *                   | |        |    Unfolded cube:
 *                   | +---->+x |
 *        +----------+----------+----------+----------+
 *        |+y       1|+y       4|+y       0|+y       5|
 *        | ^  -x    | ^  +z    | ^  +x    | ^  -z    |
 *        | |        | |        | |        | |        |
 *        | +---->+z | +---->+x | +---->-z | +---->-x |
 *        +----------+----------+----------+----------+
 *                   |+z       3|
 *                   | ^  -y    |
 *                   | |        |
 *                   | +---->+x |
 *                   +----------+
 * @param[in] _mip Mip level.
 * @param[in] _x X offset in texture.
 * @param[in] _y Y offset in texture.
 * @param[in] _width Width of texture block.
 * @param[in] _height Height of texture block.
 * @param[in] _mem Texture update data.
 * @param[in] _pitch Pitch of input image (bytes). When _pitch is set to
 *  UINT16_MAX, it will be calculated internally based on _width.
 *
 */
BGFX_C_API void bgfx_update_texture_cube(bgfx_texture_handle_t _handle, uint16_t _layer, uint8_t _side, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const bgfx_memory_t* _mem, uint16_t _pitch);

/**
 * Read back texture content.
 * @attention Texture must be created with `BGFX_TEXTURE_READ_BACK` flag.
 * @attention Availability depends on: `BGFX_CAPS_TEXTURE_READ_BACK`.
 *
 * @param[in] _handle Texture handle.
 * @param[in] _data Destination buffer.
 * @param[in] _mip Mip level.
 *
 * @returns Frame number when the result will be available. See: `bgfx::frame`.
 *
 */
BGFX_C_API uint32_t bgfx_read_texture(bgfx_texture_handle_t _handle, void* _data, uint8_t _mip);

/**
 * Set texture debug name.
 *
 * @param[in] _handle Texture handle.
 * @param[in] _name Texture name.
 * @param[in] _len Texture name length (if length is INT32_MAX, it's expected
 *  that _name is zero terminated string.
 *
 */
BGFX_C_API void bgfx_set_texture_name(bgfx_texture_handle_t _handle, const char* _name, int32_t _len);

/**
 * Returns texture direct access pointer.
 * @attention Availability depends on: `BGFX_CAPS_TEXTURE_DIRECT_ACCESS`. This feature
 *   is available on GPUs that have unified memory architecture (UMA) support.
 *
 * @param[in] _handle Texture handle.
 *
 * @returns Pointer to texture memory. If returned pointer is `NULL` direct access
 *  is not available for this texture. If pointer is `UINTPTR_MAX` sentinel value
 *  it means texture is pending creation. Pointer returned can be cached and it
 *  will be valid until texture is destroyed.
 *
 */
BGFX_C_API void* bgfx_get_direct_access_ptr(bgfx_texture_handle_t _handle);

/**
 * Destroy texture.
 *
 * @param[in] _handle Texture handle.
 *
 */
BGFX_C_API void bgfx_destroy_texture(bgfx_texture_handle_t _handle);

/**
 * Create frame buffer (simple).
 *
 * @param[in] _width Texture width.
 * @param[in] _height Texture height.
 * @param[in] _format Texture format. See: `TextureFormat::Enum`.
 * @param[in] _textureFlags Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
 *  flags. Default texture sampling mode is linear, and wrap mode is repeat.
 *  - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
 *    mode.
 *  - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
 *    sampling.
 *
 * @returns Frame buffer handle.
 *
 */
BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer(uint16_t _width, uint16_t _height, bgfx_texture_format_t _format, uint64_t _textureFlags);

/**
 * Create frame buffer with size based on backbuffer ratio. Frame buffer will maintain ratio
 * if back buffer resolution changes.
 *
 * @param[in] _ratio Frame buffer size in respect to back-buffer size. See:
 *  `BackbufferRatio::Enum`.
 * @param[in] _format Texture format. See: `TextureFormat::Enum`.
 * @param[in] _textureFlags Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
 *  flags. Default texture sampling mode is linear, and wrap mode is repeat.
 *  - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
 *    mode.
 *  - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
 *    sampling.
 *
 * @returns Frame buffer handle.
 *
 */
BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_scaled(bgfx_backbuffer_ratio_t _ratio, bgfx_texture_format_t _format, uint64_t _textureFlags);

/**
 * Create MRT frame buffer from texture handles (simple).
 *
 * @param[in] _num Number of texture handles.
 * @param[in] _handles Texture attachments.
 * @param[in] _destroyTexture If true, textures will be destroyed when
 *  frame buffer is destroyed.
 *
 * @returns Frame buffer handle.
 *
 */
BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_from_handles(uint8_t _num, const bgfx_texture_handle_t* _handles, bool _destroyTexture);

/**
 * Create MRT frame buffer from texture handles with specific layer and
 * mip level.
 *
 * @param[in] _num Number of attachements.
 * @param[in] _attachment Attachment texture info. See: `bgfx::Attachment`.
 * @param[in] _destroyTexture If true, textures will be destroyed when
 *  frame buffer is destroyed.
 *
 * @returns Frame buffer handle.
 *
 */
BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_from_attachment(uint8_t _num, const bgfx_attachment_t* _attachment, bool _destroyTexture);

/**
 * Create frame buffer for multiple window rendering.
 * @remarks
 *   Frame buffer cannot be used for sampling.
 * @attention Availability depends on: `BGFX_CAPS_SWAP_CHAIN`.
 *
 * @param[in] _nwh OS' target native window handle.
 * @param[in] _width Window back buffer width.
 * @param[in] _height Window back buffer height.
 * @param[in] _format Window back buffer color format.
 * @param[in] _depthFormat Window back buffer depth format.
 *
 * @returns Frame buffer handle.
 *
 */
BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_from_nwh(void* _nwh, uint16_t _width, uint16_t _height, bgfx_texture_format_t _format, bgfx_texture_format_t _depthFormat);

/**
 * Set frame buffer debug name.
 *
 * @param[in] _handle Frame buffer handle.
 * @param[in] _name Frame buffer name.
 * @param[in] _len Frame buffer name length (if length is INT32_MAX, it's expected
 *  that _name is zero terminated string.
 *
 */
BGFX_C_API void bgfx_set_frame_buffer_name(bgfx_frame_buffer_handle_t _handle, const char* _name, int32_t _len);

/**
 * Obtain texture handle of frame buffer attachment.
 *
 * @param[in] _handle Frame buffer handle.
 * @param[in] _attachment
 *
 */
BGFX_C_API bgfx_texture_handle_t bgfx_get_texture(bgfx_frame_buffer_handle_t _handle, uint8_t _attachment);

/**
 * Destroy frame buffer.
 *
 * @param[in] _handle Frame buffer handle.
 *
 */
BGFX_C_API void bgfx_destroy_frame_buffer(bgfx_frame_buffer_handle_t _handle);

/**
 * Create shader uniform parameter.
 * @remarks
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
 *
 * @param[in] _name Uniform name in shader.
 * @param[in] _type Type of uniform (See: `bgfx::UniformType`).
 * @param[in] _num Number of elements in array.
 *
 * @returns Handle to uniform object.
 *
 */
BGFX_C_API bgfx_uniform_handle_t bgfx_create_uniform(const char* _name, bgfx_uniform_type_t _type, uint16_t _num);

/**
 * Retrieve uniform info.
 *
 * @param[in] _handle Handle to uniform object.
 * @param[out] _info Uniform info.
 *
 */
BGFX_C_API void bgfx_get_uniform_info(bgfx_uniform_handle_t _handle, bgfx_uniform_info_t * _info);

/**
 * Destroy shader uniform parameter.
 *
 * @param[in] _handle Handle to uniform object.
 *
 */
BGFX_C_API void bgfx_destroy_uniform(bgfx_uniform_handle_t _handle);

/**
 * Create occlusion query.
 *
 */
BGFX_C_API bgfx_occlusion_query_handle_t bgfx_create_occlusion_query(void);

/**
 * Retrieve occlusion query result from previous frame.
 *
 * @param[in] _handle Handle to occlusion query object.
 * @param[out] _result Number of pixels that passed test. This argument
 *  can be `NULL` if result of occlusion query is not needed.
 *
 * @returns Occlusion query result.
 *
 */
BGFX_C_API bgfx_occlusion_query_result_t bgfx_get_result(bgfx_occlusion_query_handle_t _handle, int32_t* _result);

/**
 * Destroy occlusion query.
 *
 * @param[in] _handle Handle to occlusion query object.
 *
 */
BGFX_C_API void bgfx_destroy_occlusion_query(bgfx_occlusion_query_handle_t _handle);

/**
 * Set palette color value.
 *
 * @param[in] _index Index into palette.
 * @param[in] _rgba RGBA floating point values.
 *
 */
BGFX_C_API void bgfx_set_palette_color(uint8_t _index, const float _rgba[4]);

/**
 * Set palette color value.
 *
 * @param[in] _index Index into palette.
 * @param[in] _rgba Packed 32-bit RGBA value.
 *
 */
BGFX_C_API void bgfx_set_palette_color_rgba8(uint8_t _index, uint32_t _rgba);

/**
 * Set view name.
 * @remarks
 *   This is debug only feature.
 *   In graphics debugger view name will appear as:
 *       "nnnc <view name>"
 *        ^  ^ ^
 *        |  +--- compute (C)
 *        +------ view id
 *
 * @param[in] _id View id.
 * @param[in] _name View name.
 *
 */
BGFX_C_API void bgfx_set_view_name(bgfx_view_id_t _id, const char* _name);

/**
 * Set view rectangle. Draw primitive outside view will be clipped.
 *
 * @param[in] _id View id.
 * @param[in] _x Position x from the left corner of the window.
 * @param[in] _y Position y from the top corner of the window.
 * @param[in] _width Width of view port region.
 * @param[in] _height Height of view port region.
 *
 */
BGFX_C_API void bgfx_set_view_rect(bgfx_view_id_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

/**
 * Set view rectangle. Draw primitive outside view will be clipped.
 *
 * @param[in] _id View id.
 * @param[in] _x Position x from the left corner of the window.
 * @param[in] _y Position y from the top corner of the window.
 * @param[in] _ratio Width and height will be set in respect to back-buffer size.
 *  See: `BackbufferRatio::Enum`.
 *
 */
BGFX_C_API void bgfx_set_view_rect_ratio(bgfx_view_id_t _id, uint16_t _x, uint16_t _y, bgfx_backbuffer_ratio_t _ratio);

/**
 * Set view scissor. Draw primitive outside view will be clipped. When
 * _x, _y, _width and _height are set to 0, scissor will be disabled.
 *
 * @param[in] _id View id.
 * @param[in] _x Position x from the left corner of the window.
 * @param[in] _y Position y from the top corner of the window.
 * @param[in] _width Width of view scissor region.
 * @param[in] _height Height of view scissor region.
 *
 */
BGFX_C_API void bgfx_set_view_scissor(bgfx_view_id_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

/**
 * Set view clear flags.
 *
 * @param[in] _id View id.
 * @param[in] _flags Clear flags. Use `BGFX_CLEAR_NONE` to remove any clear
 *  operation. See: `BGFX_CLEAR_*`.
 * @param[in] _rgba Color clear value.
 * @param[in] _depth Depth clear value.
 * @param[in] _stencil Stencil clear value.
 *
 */
BGFX_C_API void bgfx_set_view_clear(bgfx_view_id_t _id, uint16_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil);

/**
 * Set view clear flags with different clear color for each
 * frame buffer texture. Must use `bgfx::setPaletteColor` to setup clear color
 * palette.
 *
 * @param[in] _id View id.
 * @param[in] _flags Clear flags. Use `BGFX_CLEAR_NONE` to remove any clear
 *  operation. See: `BGFX_CLEAR_*`.
 * @param[in] _depth Depth clear value.
 * @param[in] _stencil Stencil clear value.
 * @param[in] _c0 Palette index for frame buffer attachment 0.
 * @param[in] _c1 Palette index for frame buffer attachment 1.
 * @param[in] _c2 Palette index for frame buffer attachment 2.
 * @param[in] _c3 Palette index for frame buffer attachment 3.
 * @param[in] _c4 Palette index for frame buffer attachment 4.
 * @param[in] _c5 Palette index for frame buffer attachment 5.
 * @param[in] _c6 Palette index for frame buffer attachment 6.
 * @param[in] _c7 Palette index for frame buffer attachment 7.
 *
 */
BGFX_C_API void bgfx_set_view_clear_mrt(bgfx_view_id_t _id, uint16_t _flags, float _depth, uint8_t _stencil, uint8_t _c0, uint8_t _c1, uint8_t _c2, uint8_t _c3, uint8_t _c4, uint8_t _c5, uint8_t _c6, uint8_t _c7);

/**
 * Set view sorting mode.
 * @remarks
 *   View mode must be set prior calling `bgfx::submit` for the view.
 *
 * @param[in] _id View id.
 * @param[in] _mode View sort mode. See `ViewMode::Enum`.
 *
 */
BGFX_C_API void bgfx_set_view_mode(bgfx_view_id_t _id, bgfx_view_mode_t _mode);

/**
 * Set view frame buffer.
 * @remarks
 *   Not persistent after `bgfx::reset` call.
 *
 * @param[in] _id View id.
 * @param[in] _handle Frame buffer handle. Passing `BGFX_INVALID_HANDLE` as
 *  frame buffer handle will draw primitives from this view into
 *  default back buffer.
 *
 */
BGFX_C_API void bgfx_set_view_frame_buffer(bgfx_view_id_t _id, bgfx_frame_buffer_handle_t _handle);

/**
 * Set view view and projection matrices, all draw primitives in this
 * view will use these matrices.
 *
 * @param[in] _id View id.
 * @param[in] _view View matrix.
 * @param[in] _proj Projection matrix.
 *
 */
BGFX_C_API void bgfx_set_view_transform(bgfx_view_id_t _id, const void* _view, const void* _proj);

/**
 * Post submit view reordering.
 *
 * @param[in] _id First view id.
 * @param[in] _num Number of views to remap.
 * @param[in] _order View remap id table. Passing `NULL` will reset view ids
 *  to default state.
 *
 */
BGFX_C_API void bgfx_set_view_order(bgfx_view_id_t _id, uint16_t _num, const bgfx_view_id_t* _order);

/**
 * Reset all view settings to default.
 *
 * @param[in] _id
 *
 */
BGFX_C_API void bgfx_reset_view(bgfx_view_id_t _id);

/**
 * Begin submitting draw calls from thread.
 *
 * @param[in] _forThread Explicitly request an encoder for a worker thread.
 *
 * @returns Encoder.
 *
 */
BGFX_C_API bgfx_encoder_t* bgfx_encoder_begin(bool _forThread);

/**
 * End submitting draw calls from thread.
 *
 * @param[in] _encoder Encoder.
 *
 */
BGFX_C_API void bgfx_encoder_end(bgfx_encoder_t* _encoder);

/**
 * Sets a debug marker. This allows you to group graphics calls together for easy browsing in
 * graphics debugging tools.
 *
 * @param[in] _marker Marker string.
 *
 */
BGFX_C_API void bgfx_encoder_set_marker(bgfx_encoder_t* _this, const char* _marker);

/**
 * Set render states for draw primitive.
 * @remarks
 *   1. To setup more complex states use:
 *      `BGFX_STATE_ALPHA_REF(_ref)`,
 *      `BGFX_STATE_POINT_SIZE(_size)`,
 *      `BGFX_STATE_BLEND_FUNC(_src, _dst)`,
 *      `BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA)`,
 *      `BGFX_STATE_BLEND_EQUATION(_equation)`,
 *      `BGFX_STATE_BLEND_EQUATION_SEPARATE(_equationRGB, _equationA)`
 *   2. `BGFX_STATE_BLEND_EQUATION_ADD` is set when no other blend
 *      equation is specified.
 *
 * @param[in] _state State flags. Default state for primitive type is
 *    triangles. See: `BGFX_STATE_DEFAULT`.
 *    - `BGFX_STATE_DEPTH_TEST_*` - Depth test function.
 *    - `BGFX_STATE_BLEND_*` - See remark 1 about BGFX_STATE_BLEND_FUNC.
 *    - `BGFX_STATE_BLEND_EQUATION_*` - See remark 2.
 *    - `BGFX_STATE_CULL_*` - Backface culling mode.
 *    - `BGFX_STATE_WRITE_*` - Enable R, G, B, A or Z write.
 *    - `BGFX_STATE_MSAA` - Enable hardware multisample antialiasing.
 *    - `BGFX_STATE_PT_[TRISTRIP/LINES/POINTS]` - Primitive type.
 * @param[in] _rgba Sets blend factor used by `BGFX_STATE_BLEND_FACTOR` and
 *    `BGFX_STATE_BLEND_INV_FACTOR` blend modes.
 *
 */
BGFX_C_API void bgfx_encoder_set_state(bgfx_encoder_t* _this, uint64_t _state, uint32_t _rgba);

/**
 * Set condition for rendering.
 *
 * @param[in] _handle Occlusion query handle.
 * @param[in] _visible Render if occlusion query is visible.
 *
 */
BGFX_C_API void bgfx_encoder_set_condition(bgfx_encoder_t* _this, bgfx_occlusion_query_handle_t _handle, bool _visible);

/**
 * Set stencil test state.
 *
 * @param[in] _fstencil Front stencil state.
 * @param[in] _bstencil Back stencil state. If back is set to `BGFX_STENCIL_NONE`
 *  _fstencil is applied to both front and back facing primitives.
 *
 */
BGFX_C_API void bgfx_encoder_set_stencil(bgfx_encoder_t* _this, uint32_t _fstencil, uint32_t _bstencil);

/**
 * Set scissor for draw primitive.
 * @remark
 *   To scissor for all primitives in view see `bgfx::setViewScissor`.
 *
 * @param[in] _x Position x from the left corner of the window.
 * @param[in] _y Position y from the top corner of the window.
 * @param[in] _width Width of view scissor region.
 * @param[in] _height Height of view scissor region.
 *
 * @returns Scissor cache index.
 *
 */
BGFX_C_API uint16_t bgfx_encoder_set_scissor(bgfx_encoder_t* _this, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

/**
 * Set scissor from cache for draw primitive.
 * @remark
 *   To scissor for all primitives in view see `bgfx::setViewScissor`.
 *
 * @param[in] _cache Index in scissor cache.
 *
 */
BGFX_C_API void bgfx_encoder_set_scissor_cached(bgfx_encoder_t* _this, uint16_t _cache);

/**
 * Set model matrix for draw primitive. If it is not called,
 * the model will be rendered with an identity model matrix.
 *
 * @param[in] _mtx Pointer to first matrix in array.
 * @param[in] _num Number of matrices in array.
 *
 * @returns Index into matrix cache in case the same model matrix has
 *  to be used for other draw primitive call.
 *
 */
BGFX_C_API uint32_t bgfx_encoder_set_transform(bgfx_encoder_t* _this, const void* _mtx, uint16_t _num);

/**
 *  Set model matrix from matrix cache for draw primitive.
 *
 * @param[in] _cache Index in matrix cache.
 * @param[in] _num Number of matrices from cache.
 *
 */
BGFX_C_API void bgfx_encoder_set_transform_cached(bgfx_encoder_t* _this, uint32_t _cache, uint16_t _num);

/**
 * Reserve matrices in internal matrix cache.
 * @attention Pointer returned can be modifed until `bgfx::frame` is called.
 *
 * @param[out] _transform Pointer to `Transform` structure.
 * @param[in] _num Number of matrices.
 *
 * @returns Index in matrix cache.
 *
 */
BGFX_C_API uint32_t bgfx_encoder_alloc_transform(bgfx_encoder_t* _this, bgfx_transform_t* _transform, uint16_t _num);

/**
 * Set shader uniform parameter for draw primitive.
 *
 * @param[in] _handle Uniform.
 * @param[in] _value Pointer to uniform data.
 * @param[in] _num Number of elements. Passing `UINT16_MAX` will
 *  use the _num passed on uniform creation.
 *
 */
BGFX_C_API void bgfx_encoder_set_uniform(bgfx_encoder_t* _this, bgfx_uniform_handle_t _handle, const void* _value, uint16_t _num);

/**
 * Set index buffer for draw primitive.
 *
 * @param[in] _handle Index buffer.
 * @param[in] _firstIndex First index to render.
 * @param[in] _numIndices Number of indices to render.
 *
 */
BGFX_C_API void bgfx_encoder_set_index_buffer(bgfx_encoder_t* _this, bgfx_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices);

/**
 * Set index buffer for draw primitive.
 *
 * @param[in] _handle Dynamic index buffer.
 * @param[in] _firstIndex First index to render.
 * @param[in] _numIndices Number of indices to render.
 *
 */
BGFX_C_API void bgfx_encoder_set_dynamic_index_buffer(bgfx_encoder_t* _this, bgfx_dynamic_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices);

/**
 * Set index buffer for draw primitive.
 *
 * @param[in] _tib Transient index buffer.
 * @param[in] _firstIndex First index to render.
 * @param[in] _numIndices Number of indices to render.
 *
 */
BGFX_C_API void bgfx_encoder_set_transient_index_buffer(bgfx_encoder_t* _this, const bgfx_transient_index_buffer_t* _tib, uint32_t _firstIndex, uint32_t _numIndices);

/**
 * Set vertex buffer for draw primitive.
 *
 * @param[in] _stream Vertex stream.
 * @param[in] _handle Vertex buffer.
 * @param[in] _startVertex First vertex to render.
 * @param[in] _numVertices Number of vertices to render.
 *
 */
BGFX_C_API void bgfx_encoder_set_vertex_buffer(bgfx_encoder_t* _this, uint8_t _stream, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices);

/**
 * Set vertex buffer for draw primitive.
 *
 * @param[in] _stream Vertex stream.
 * @param[in] _handle Vertex buffer.
 * @param[in] _startVertex First vertex to render.
 * @param[in] _numVertices Number of vertices to render.
 * @param[in] _layoutHandle Vertex layout for aliasing vertex buffer. If invalid
 *  handle is used, vertex layout used for creation
 *  of vertex buffer will be used.
 *
 */
BGFX_C_API void bgfx_encoder_set_vertex_buffer_with_layout(bgfx_encoder_t* _this, uint8_t _stream, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices, bgfx_vertex_layout_handle_t _layoutHandle);

/**
 * Set vertex buffer for draw primitive.
 *
 * @param[in] _stream Vertex stream.
 * @param[in] _handle Dynamic vertex buffer.
 * @param[in] _startVertex First vertex to render.
 * @param[in] _numVertices Number of vertices to render.
 *
 */
BGFX_C_API void bgfx_encoder_set_dynamic_vertex_buffer(bgfx_encoder_t* _this, uint8_t _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices);
BGFX_C_API void bgfx_encoder_set_dynamic_vertex_buffer_with_layout(bgfx_encoder_t* _this, uint8_t _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices, bgfx_vertex_layout_handle_t _layoutHandle);

/**
 * Set vertex buffer for draw primitive.
 *
 * @param[in] _stream Vertex stream.
 * @param[in] _tvb Transient vertex buffer.
 * @param[in] _startVertex First vertex to render.
 * @param[in] _numVertices Number of vertices to render.
 *
 */
BGFX_C_API void bgfx_encoder_set_transient_vertex_buffer(bgfx_encoder_t* _this, uint8_t _stream, const bgfx_transient_vertex_buffer_t* _tvb, uint32_t _startVertex, uint32_t _numVertices);

/**
 * Set vertex buffer for draw primitive.
 *
 * @param[in] _stream Vertex stream.
 * @param[in] _tvb Transient vertex buffer.
 * @param[in] _startVertex First vertex to render.
 * @param[in] _numVertices Number of vertices to render.
 * @param[in] _layoutHandle Vertex layout for aliasing vertex buffer. If invalid
 *  handle is used, vertex layout used for creation
 *  of vertex buffer will be used.
 *
 */
BGFX_C_API void bgfx_encoder_set_transient_vertex_buffer_with_layout(bgfx_encoder_t* _this, uint8_t _stream, const bgfx_transient_vertex_buffer_t* _tvb, uint32_t _startVertex, uint32_t _numVertices, bgfx_vertex_layout_handle_t _layoutHandle);

/**
 * Set number of vertices for auto generated vertices use in conjuction
 * with gl_VertexID.
 * @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
 *
 * @param[in] _numVertices Number of vertices.
 *
 */
BGFX_C_API void bgfx_encoder_set_vertex_count(bgfx_encoder_t* _this, uint32_t _numVertices);

/**
 * Set instance data buffer for draw primitive.
 *
 * @param[in] _idb Transient instance data buffer.
 * @param[in] _start First instance data.
 * @param[in] _num Number of data instances.
 *
 */
BGFX_C_API void bgfx_encoder_set_instance_data_buffer(bgfx_encoder_t* _this, const bgfx_instance_data_buffer_t* _idb, uint32_t _start, uint32_t _num);

/**
 * Set instance data buffer for draw primitive.
 *
 * @param[in] _handle Vertex buffer.
 * @param[in] _startVertex First instance data.
 * @param[in] _num Number of data instances.
 *  Set instance data buffer for draw primitive.
 *
 */
BGFX_C_API void bgfx_encoder_set_instance_data_from_vertex_buffer(bgfx_encoder_t* _this, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num);

/**
 * Set instance data buffer for draw primitive.
 *
 * @param[in] _handle Dynamic vertex buffer.
 * @param[in] _startVertex First instance data.
 * @param[in] _num Number of data instances.
 *
 */
BGFX_C_API void bgfx_encoder_set_instance_data_from_dynamic_vertex_buffer(bgfx_encoder_t* _this, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num);

/**
 * Set number of instances for auto generated instances use in conjuction
 * with gl_InstanceID.
 * @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
 *
 * @param[in] _numInstances
 *
 */
BGFX_C_API void bgfx_encoder_set_instance_count(bgfx_encoder_t* _this, uint32_t _numInstances);

/**
 * Set texture stage for draw primitive.
 *
 * @param[in] _stage Texture unit.
 * @param[in] _sampler Program sampler.
 * @param[in] _handle Texture handle.
 * @param[in] _flags Texture sampling mode. Default value UINT32_MAX uses
 *    texture sampling settings from the texture.
 *    - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
 *      mode.
 *    - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
 *      sampling.
 *
 */
BGFX_C_API void bgfx_encoder_set_texture(bgfx_encoder_t* _this, uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint32_t _flags);

/**
 * Submit an empty primitive for rendering. Uniforms and draw state
 * will be applied but no geometry will be submitted. Useful in cases
 * when no other draw/compute primitive is submitted to view, but it's
 * desired to execute clear view.
 * @remark
 *   These empty draw calls will sort before ordinary draw calls.
 *
 * @param[in] _id View id.
 *
 */
BGFX_C_API void bgfx_encoder_touch(bgfx_encoder_t* _this, bgfx_view_id_t _id);

/**
 * Submit primitive for rendering.
 *
 * @param[in] _id View id.
 * @param[in] _program Program.
 * @param[in] _depth Depth for sorting.
 * @param[in] _flags Discard or preserve states. See `BGFX_DISCARD_*`.
 *
 */
BGFX_C_API void bgfx_encoder_submit(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, uint32_t _depth, uint8_t _flags);

/**
 * Submit primitive with occlusion query for rendering.
 *
 * @param[in] _id View id.
 * @param[in] _program Program.
 * @param[in] _occlusionQuery Occlusion query.
 * @param[in] _depth Depth for sorting.
 * @param[in] _flags Discard or preserve states. See `BGFX_DISCARD_*`.
 *
 */
BGFX_C_API void bgfx_encoder_submit_occlusion_query(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_occlusion_query_handle_t _occlusionQuery, uint32_t _depth, uint8_t _flags);

/**
 * Submit primitive for rendering with index and instance data info from
 * indirect buffer.
 *
 * @param[in] _id View id.
 * @param[in] _program Program.
 * @param[in] _indirectHandle Indirect buffer.
 * @param[in] _start First element in indirect buffer.
 * @param[in] _num Number of dispatches.
 * @param[in] _depth Depth for sorting.
 * @param[in] _flags Discard or preserve states. See `BGFX_DISCARD_*`.
 *
 */
BGFX_C_API void bgfx_encoder_submit_indirect(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, uint32_t _depth, uint8_t _flags);

/**
 * Set compute index buffer.
 *
 * @param[in] _stage Compute stage.
 * @param[in] _handle Index buffer handle.
 * @param[in] _access Buffer access. See `Access::Enum`.
 *
 */
BGFX_C_API void bgfx_encoder_set_compute_index_buffer(bgfx_encoder_t* _this, uint8_t _stage, bgfx_index_buffer_handle_t _handle, bgfx_access_t _access);

/**
 * Set compute vertex buffer.
 *
 * @param[in] _stage Compute stage.
 * @param[in] _handle Vertex buffer handle.
 * @param[in] _access Buffer access. See `Access::Enum`.
 *
 */
BGFX_C_API void bgfx_encoder_set_compute_vertex_buffer(bgfx_encoder_t* _this, uint8_t _stage, bgfx_vertex_buffer_handle_t _handle, bgfx_access_t _access);

/**
 * Set compute dynamic index buffer.
 *
 * @param[in] _stage Compute stage.
 * @param[in] _handle Dynamic index buffer handle.
 * @param[in] _access Buffer access. See `Access::Enum`.
 *
 */
BGFX_C_API void bgfx_encoder_set_compute_dynamic_index_buffer(bgfx_encoder_t* _this, uint8_t _stage, bgfx_dynamic_index_buffer_handle_t _handle, bgfx_access_t _access);

/**
 * Set compute dynamic vertex buffer.
 *
 * @param[in] _stage Compute stage.
 * @param[in] _handle Dynamic vertex buffer handle.
 * @param[in] _access Buffer access. See `Access::Enum`.
 *
 */
BGFX_C_API void bgfx_encoder_set_compute_dynamic_vertex_buffer(bgfx_encoder_t* _this, uint8_t _stage, bgfx_dynamic_vertex_buffer_handle_t _handle, bgfx_access_t _access);

/**
 * Set compute indirect buffer.
 *
 * @param[in] _stage Compute stage.
 * @param[in] _handle Indirect buffer handle.
 * @param[in] _access Buffer access. See `Access::Enum`.
 *
 */
BGFX_C_API void bgfx_encoder_set_compute_indirect_buffer(bgfx_encoder_t* _this, uint8_t _stage, bgfx_indirect_buffer_handle_t _handle, bgfx_access_t _access);

/**
 * Set compute image from texture.
 *
 * @param[in] _stage Compute stage.
 * @param[in] _handle Texture handle.
 * @param[in] _mip Mip level.
 * @param[in] _access Image access. See `Access::Enum`.
 * @param[in] _format Texture format. See: `TextureFormat::Enum`.
 *
 */
BGFX_C_API void bgfx_encoder_set_image(bgfx_encoder_t* _this, uint8_t _stage, bgfx_texture_handle_t _handle, uint8_t _mip, bgfx_access_t _access, bgfx_texture_format_t _format);

/**
 * Dispatch compute.
 *
 * @param[in] _id View id.
 * @param[in] _program Compute program.
 * @param[in] _numX Number of groups X.
 * @param[in] _numY Number of groups Y.
 * @param[in] _numZ Number of groups Z.
 * @param[in] _flags Discard or preserve states. See `BGFX_DISCARD_*`.
 *
 */
BGFX_C_API void bgfx_encoder_dispatch(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, uint32_t _numX, uint32_t _numY, uint32_t _numZ, uint8_t _flags);

/**
 * Dispatch compute indirect.
 *
 * @param[in] _id View id.
 * @param[in] _program Compute program.
 * @param[in] _indirectHandle Indirect buffer.
 * @param[in] _start First element in indirect buffer.
 * @param[in] _num Number of dispatches.
 * @param[in] _flags Discard or preserve states. See `BGFX_DISCARD_*`.
 *
 */
BGFX_C_API void bgfx_encoder_dispatch_indirect(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, uint8_t _flags);

/**
 * Discard previously set state for draw or compute call.
 *
 * @param[in] _flags Discard or preserve states. See `BGFX_DISCARD_*`.
 *
 */
BGFX_C_API void bgfx_encoder_discard(bgfx_encoder_t* _this, uint8_t _flags);

/**
 * Blit 2D texture region between two 2D textures.
 * @attention Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
 * @attention Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
 *
 * @param[in] _id View id.
 * @param[in] _dst Destination texture handle.
 * @param[in] _dstMip Destination texture mip level.
 * @param[in] _dstX Destination texture X position.
 * @param[in] _dstY Destination texture Y position.
 * @param[in] _dstZ If texture is 2D this argument should be 0. If destination texture is cube
 *  this argument represents destination texture cube face. For 3D texture this argument
 *  represents destination texture Z position.
 * @param[in] _src Source texture handle.
 * @param[in] _srcMip Source texture mip level.
 * @param[in] _srcX Source texture X position.
 * @param[in] _srcY Source texture Y position.
 * @param[in] _srcZ If texture is 2D this argument should be 0. If source texture is cube
 *  this argument represents source texture cube face. For 3D texture this argument
 *  represents source texture Z position.
 * @param[in] _width Width of region.
 * @param[in] _height Height of region.
 * @param[in] _depth If texture is 3D this argument represents depth of region, otherwise it's
 *  unused.
 *
 */
BGFX_C_API void bgfx_encoder_blit(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_texture_handle_t _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, bgfx_texture_handle_t _src, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth);

/**
 * Request screen shot of window back buffer.
 * @remarks
 *   `bgfx::CallbackI::screenShot` must be implemented.
 * @attention Frame buffer handle must be created with OS' target native window handle.
 *
 * @param[in] _handle Frame buffer handle. If handle is `BGFX_INVALID_HANDLE` request will be
 *  made for main window back buffer.
 * @param[in] _filePath Will be passed to `bgfx::CallbackI::screenShot` callback.
 *
 */
BGFX_C_API void bgfx_request_screen_shot(bgfx_frame_buffer_handle_t _handle, const char* _filePath);

/**
 * Render frame.
 * @attention `bgfx::renderFrame` is blocking call. It waits for
 *   `bgfx::frame` to be called from API thread to process frame.
 *   If timeout value is passed call will timeout and return even
 *   if `bgfx::frame` is not called.
 * @warning This call should be only used on platforms that don't
 *   allow creating separate rendering thread. If it is called before
 *   to bgfx::init, render thread won't be created by bgfx::init call.
 *
 * @param[in] _msecs Timeout in milliseconds.
 *
 * @returns Current renderer context state. See: `bgfx::RenderFrame`.
 *
 */
BGFX_C_API bgfx_render_frame_t bgfx_render_frame(int32_t _msecs);

/**
 * Set platform data.
 * @warning Must be called before `bgfx::init`.
 *
 * @param[in] _data Platform data.
 *
 */
BGFX_C_API void bgfx_set_platform_data(const bgfx_platform_data_t * _data);

/**
 * Get internal data for interop.
 * @attention It's expected you understand some bgfx internals before you
 *   use this call.
 * @warning Must be called only on render thread.
 *
 */
BGFX_C_API const bgfx_internal_data_t* bgfx_get_internal_data(void);

/**
 * Override internal texture with externally created texture. Previously
 * created internal texture will released.
 * @attention It's expected you understand some bgfx internals before you
 *   use this call.
 * @warning Must be called only on render thread.
 *
 * @param[in] _handle Texture handle.
 * @param[in] _ptr Native API pointer to texture.
 *
 * @returns Native API pointer to texture. If result is 0, texture is not created
 *  yet from the main thread.
 *
 */
BGFX_C_API uintptr_t bgfx_override_internal_texture_ptr(bgfx_texture_handle_t _handle, uintptr_t _ptr);

/**
 * Override internal texture by creating new texture. Previously created
 * internal texture will released.
 * @attention It's expected you understand some bgfx internals before you
 *   use this call.
 * @returns Native API pointer to texture. If result is 0, texture is not created yet from the
 *   main thread.
 * @warning Must be called only on render thread.
 *
 * @param[in] _handle Texture handle.
 * @param[in] _width Width.
 * @param[in] _height Height.
 * @param[in] _numMips Number of mip-maps.
 * @param[in] _format Texture format. See: `TextureFormat::Enum`.
 * @param[in] _flags Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
 *  flags. Default texture sampling mode is linear, and wrap mode is repeat.
 *  - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
 *    mode.
 *  - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
 *    sampling.
 *
 * @returns Native API pointer to texture. If result is 0, texture is not created
 *  yet from the main thread.
 *
 */
BGFX_C_API uintptr_t bgfx_override_internal_texture(bgfx_texture_handle_t _handle, uint16_t _width, uint16_t _height, uint8_t _numMips, bgfx_texture_format_t _format, uint64_t _flags);

/**
 * Sets a debug marker. This allows you to group graphics calls together for easy browsing in
 * graphics debugging tools.
 *
 * @param[in] _marker Marker string.
 *
 */
BGFX_C_API void bgfx_set_marker(const char* _marker);

/**
 * Set render states for draw primitive.
 * @remarks
 *   1. To setup more complex states use:
 *      `BGFX_STATE_ALPHA_REF(_ref)`,
 *      `BGFX_STATE_POINT_SIZE(_size)`,
 *      `BGFX_STATE_BLEND_FUNC(_src, _dst)`,
 *      `BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA)`,
 *      `BGFX_STATE_BLEND_EQUATION(_equation)`,
 *      `BGFX_STATE_BLEND_EQUATION_SEPARATE(_equationRGB, _equationA)`
 *   2. `BGFX_STATE_BLEND_EQUATION_ADD` is set when no other blend
 *      equation is specified.
 *
 * @param[in] _state State flags. Default state for primitive type is
 *    triangles. See: `BGFX_STATE_DEFAULT`.
 *    - `BGFX_STATE_DEPTH_TEST_*` - Depth test function.
 *    - `BGFX_STATE_BLEND_*` - See remark 1 about BGFX_STATE_BLEND_FUNC.
 *    - `BGFX_STATE_BLEND_EQUATION_*` - See remark 2.
 *    - `BGFX_STATE_CULL_*` - Backface culling mode.
 *    - `BGFX_STATE_WRITE_*` - Enable R, G, B, A or Z write.
 *    - `BGFX_STATE_MSAA` - Enable hardware multisample antialiasing.
 *    - `BGFX_STATE_PT_[TRISTRIP/LINES/POINTS]` - Primitive type.
 * @param[in] _rgba Sets blend factor used by `BGFX_STATE_BLEND_FACTOR` and
 *    `BGFX_STATE_BLEND_INV_FACTOR` blend modes.
 *
 */
BGFX_C_API void bgfx_set_state(uint64_t _state, uint32_t _rgba);

/**
 * Set condition for rendering.
 *
 * @param[in] _handle Occlusion query handle.
 * @param[in] _visible Render if occlusion query is visible.
 *
 */
BGFX_C_API void bgfx_set_condition(bgfx_occlusion_query_handle_t _handle, bool _visible);

/**
 * Set stencil test state.
 *
 * @param[in] _fstencil Front stencil state.
 * @param[in] _bstencil Back stencil state. If back is set to `BGFX_STENCIL_NONE`
 *  _fstencil is applied to both front and back facing primitives.
 *
 */
BGFX_C_API void bgfx_set_stencil(uint32_t _fstencil, uint32_t _bstencil);

/**
 * Set scissor for draw primitive.
 * @remark
 *   To scissor for all primitives in view see `bgfx::setViewScissor`.
 *
 * @param[in] _x Position x from the left corner of the window.
 * @param[in] _y Position y from the top corner of the window.
 * @param[in] _width Width of view scissor region.
 * @param[in] _height Height of view scissor region.
 *
 * @returns Scissor cache index.
 *
 */
BGFX_C_API uint16_t bgfx_set_scissor(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

/**
 * Set scissor from cache for draw primitive.
 * @remark
 *   To scissor for all primitives in view see `bgfx::setViewScissor`.
 *
 * @param[in] _cache Index in scissor cache.
 *
 */
BGFX_C_API void bgfx_set_scissor_cached(uint16_t _cache);

/**
 * Set model matrix for draw primitive. If it is not called,
 * the model will be rendered with an identity model matrix.
 *
 * @param[in] _mtx Pointer to first matrix in array.
 * @param[in] _num Number of matrices in array.
 *
 * @returns Index into matrix cache in case the same model matrix has
 *  to be used for other draw primitive call.
 *
 */
BGFX_C_API uint32_t bgfx_set_transform(const void* _mtx, uint16_t _num);

/**
 *  Set model matrix from matrix cache for draw primitive.
 *
 * @param[in] _cache Index in matrix cache.
 * @param[in] _num Number of matrices from cache.
 *
 */
BGFX_C_API void bgfx_set_transform_cached(uint32_t _cache, uint16_t _num);

/**
 * Reserve matrices in internal matrix cache.
 * @attention Pointer returned can be modifed until `bgfx::frame` is called.
 *
 * @param[out] _transform Pointer to `Transform` structure.
 * @param[in] _num Number of matrices.
 *
 * @returns Index in matrix cache.
 *
 */
BGFX_C_API uint32_t bgfx_alloc_transform(bgfx_transform_t* _transform, uint16_t _num);

/**
 * Set shader uniform parameter for draw primitive.
 *
 * @param[in] _handle Uniform.
 * @param[in] _value Pointer to uniform data.
 * @param[in] _num Number of elements. Passing `UINT16_MAX` will
 *  use the _num passed on uniform creation.
 *
 */
BGFX_C_API void bgfx_set_uniform(bgfx_uniform_handle_t _handle, const void* _value, uint16_t _num);

/**
 * Set index buffer for draw primitive.
 *
 * @param[in] _handle Index buffer.
 * @param[in] _firstIndex First index to render.
 * @param[in] _numIndices Number of indices to render.
 *
 */
BGFX_C_API void bgfx_set_index_buffer(bgfx_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices);

/**
 * Set index buffer for draw primitive.
 *
 * @param[in] _handle Dynamic index buffer.
 * @param[in] _firstIndex First index to render.
 * @param[in] _numIndices Number of indices to render.
 *
 */
BGFX_C_API void bgfx_set_dynamic_index_buffer(bgfx_dynamic_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices);

/**
 * Set index buffer for draw primitive.
 *
 * @param[in] _tib Transient index buffer.
 * @param[in] _firstIndex First index to render.
 * @param[in] _numIndices Number of indices to render.
 *
 */
BGFX_C_API void bgfx_set_transient_index_buffer(const bgfx_transient_index_buffer_t* _tib, uint32_t _firstIndex, uint32_t _numIndices);

/**
 * Set vertex buffer for draw primitive.
 *
 * @param[in] _stream Vertex stream.
 * @param[in] _handle Vertex buffer.
 * @param[in] _startVertex First vertex to render.
 * @param[in] _numVertices Number of vertices to render.
 *
 */
BGFX_C_API void bgfx_set_vertex_buffer(uint8_t _stream, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices);

/**
 * Set vertex buffer for draw primitive.
 *
 * @param[in] _stream Vertex stream.
 * @param[in] _handle Vertex buffer.
 * @param[in] _startVertex First vertex to render.
 * @param[in] _numVertices Number of vertices to render.
 * @param[in] _layoutHandle Vertex layout for aliasing vertex buffer. If invalid
 *  handle is used, vertex layout used for creation
 *  of vertex buffer will be used.
 *
 */
BGFX_C_API void bgfx_set_vertex_buffer_with_layout(uint8_t _stream, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices, bgfx_vertex_layout_handle_t _layoutHandle);

/**
 * Set vertex buffer for draw primitive.
 *
 * @param[in] _stream Vertex stream.
 * @param[in] _handle Dynamic vertex buffer.
 * @param[in] _startVertex First vertex to render.
 * @param[in] _numVertices Number of vertices to render.
 *
 */
BGFX_C_API void bgfx_set_dynamic_vertex_buffer(uint8_t _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices);

/**
 * Set vertex buffer for draw primitive.
 *
 * @param[in] _stream Vertex stream.
 * @param[in] _handle Dynamic vertex buffer.
 * @param[in] _startVertex First vertex to render.
 * @param[in] _numVertices Number of vertices to render.
 * @param[in] _layoutHandle Vertex layout for aliasing vertex buffer. If invalid
 *  handle is used, vertex layout used for creation
 *  of vertex buffer will be used.
 *
 */
BGFX_C_API void bgfx_set_dynamic_vertex_buffer_with_layout(uint8_t _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices, bgfx_vertex_layout_handle_t _layoutHandle);

/**
 * Set vertex buffer for draw primitive.
 *
 * @param[in] _stream Vertex stream.
 * @param[in] _tvb Transient vertex buffer.
 * @param[in] _startVertex First vertex to render.
 * @param[in] _numVertices Number of vertices to render.
 *
 */
BGFX_C_API void bgfx_set_transient_vertex_buffer(uint8_t _stream, const bgfx_transient_vertex_buffer_t* _tvb, uint32_t _startVertex, uint32_t _numVertices);

/**
 * Set vertex buffer for draw primitive.
 *
 * @param[in] _stream Vertex stream.
 * @param[in] _tvb Transient vertex buffer.
 * @param[in] _startVertex First vertex to render.
 * @param[in] _numVertices Number of vertices to render.
 * @param[in] _layoutHandle Vertex layout for aliasing vertex buffer. If invalid
 *  handle is used, vertex layout used for creation
 *  of vertex buffer will be used.
 *
 */
BGFX_C_API void bgfx_set_transient_vertex_buffer_with_layout(uint8_t _stream, const bgfx_transient_vertex_buffer_t* _tvb, uint32_t _startVertex, uint32_t _numVertices, bgfx_vertex_layout_handle_t _layoutHandle);

/**
 * Set number of vertices for auto generated vertices use in conjuction
 * with gl_VertexID.
 * @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
 *
 * @param[in] _numVertices Number of vertices.
 *
 */
BGFX_C_API void bgfx_set_vertex_count(uint32_t _numVertices);

/**
 * Set instance data buffer for draw primitive.
 *
 * @param[in] _idb Transient instance data buffer.
 * @param[in] _start First instance data.
 * @param[in] _num Number of data instances.
 *
 */
BGFX_C_API void bgfx_set_instance_data_buffer(const bgfx_instance_data_buffer_t* _idb, uint32_t _start, uint32_t _num);

/**
 * Set instance data buffer for draw primitive.
 *
 * @param[in] _handle Vertex buffer.
 * @param[in] _startVertex First instance data.
 * @param[in] _num Number of data instances.
 *  Set instance data buffer for draw primitive.
 *
 */
BGFX_C_API void bgfx_set_instance_data_from_vertex_buffer(bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num);

/**
 * Set instance data buffer for draw primitive.
 *
 * @param[in] _handle Dynamic vertex buffer.
 * @param[in] _startVertex First instance data.
 * @param[in] _num Number of data instances.
 *
 */
BGFX_C_API void bgfx_set_instance_data_from_dynamic_vertex_buffer(bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num);

/**
 * Set number of instances for auto generated instances use in conjuction
 * with gl_InstanceID.
 * @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
 *
 * @param[in] _numInstances
 *
 */
BGFX_C_API void bgfx_set_instance_count(uint32_t _numInstances);

/**
 * Set texture stage for draw primitive.
 *
 * @param[in] _stage Texture unit.
 * @param[in] _sampler Program sampler.
 * @param[in] _handle Texture handle.
 * @param[in] _flags Texture sampling mode. Default value UINT32_MAX uses
 *    texture sampling settings from the texture.
 *    - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
 *      mode.
 *    - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
 *      sampling.
 *
 */
BGFX_C_API void bgfx_set_texture(uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint32_t _flags);

/**
 * Submit an empty primitive for rendering. Uniforms and draw state
 * will be applied but no geometry will be submitted.
 * @remark
 *   These empty draw calls will sort before ordinary draw calls.
 *
 * @param[in] _id View id.
 *
 */
BGFX_C_API void bgfx_touch(bgfx_view_id_t _id);

/**
 * Submit primitive for rendering.
 *
 * @param[in] _id View id.
 * @param[in] _program Program.
 * @param[in] _depth Depth for sorting.
 * @param[in] _flags Which states to discard for next draw. See BGFX_DISCARD_
 *
 */
BGFX_C_API void bgfx_submit(bgfx_view_id_t _id, bgfx_program_handle_t _program, uint32_t _depth, uint8_t _flags);

/**
 * Submit primitive with occlusion query for rendering.
 *
 * @param[in] _id View id.
 * @param[in] _program Program.
 * @param[in] _occlusionQuery Occlusion query.
 * @param[in] _depth Depth for sorting.
 * @param[in] _flags Which states to discard for next draw. See BGFX_DISCARD_
 *
 */
BGFX_C_API void bgfx_submit_occlusion_query(bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_occlusion_query_handle_t _occlusionQuery, uint32_t _depth, uint8_t _flags);

/**
 * Submit primitive for rendering with index and instance data info from
 * indirect buffer.
 *
 * @param[in] _id View id.
 * @param[in] _program Program.
 * @param[in] _indirectHandle Indirect buffer.
 * @param[in] _start First element in indirect buffer.
 * @param[in] _num Number of dispatches.
 * @param[in] _depth Depth for sorting.
 * @param[in] _flags Which states to discard for next draw. See BGFX_DISCARD_
 *
 */
BGFX_C_API void bgfx_submit_indirect(bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, uint32_t _depth, uint8_t _flags);

/**
 * Set compute index buffer.
 *
 * @param[in] _stage Compute stage.
 * @param[in] _handle Index buffer handle.
 * @param[in] _access Buffer access. See `Access::Enum`.
 *
 */
BGFX_C_API void bgfx_set_compute_index_buffer(uint8_t _stage, bgfx_index_buffer_handle_t _handle, bgfx_access_t _access);

/**
 * Set compute vertex buffer.
 *
 * @param[in] _stage Compute stage.
 * @param[in] _handle Vertex buffer handle.
 * @param[in] _access Buffer access. See `Access::Enum`.
 *
 */
BGFX_C_API void bgfx_set_compute_vertex_buffer(uint8_t _stage, bgfx_vertex_buffer_handle_t _handle, bgfx_access_t _access);

/**
 * Set compute dynamic index buffer.
 *
 * @param[in] _stage Compute stage.
 * @param[in] _handle Dynamic index buffer handle.
 * @param[in] _access Buffer access. See `Access::Enum`.
 *
 */
BGFX_C_API void bgfx_set_compute_dynamic_index_buffer(uint8_t _stage, bgfx_dynamic_index_buffer_handle_t _handle, bgfx_access_t _access);

/**
 * Set compute dynamic vertex buffer.
 *
 * @param[in] _stage Compute stage.
 * @param[in] _handle Dynamic vertex buffer handle.
 * @param[in] _access Buffer access. See `Access::Enum`.
 *
 */
BGFX_C_API void bgfx_set_compute_dynamic_vertex_buffer(uint8_t _stage, bgfx_dynamic_vertex_buffer_handle_t _handle, bgfx_access_t _access);

/**
 * Set compute indirect buffer.
 *
 * @param[in] _stage Compute stage.
 * @param[in] _handle Indirect buffer handle.
 * @param[in] _access Buffer access. See `Access::Enum`.
 *
 */
BGFX_C_API void bgfx_set_compute_indirect_buffer(uint8_t _stage, bgfx_indirect_buffer_handle_t _handle, bgfx_access_t _access);

/**
 * Set compute image from texture.
 *
 * @param[in] _stage Compute stage.
 * @param[in] _handle Texture handle.
 * @param[in] _mip Mip level.
 * @param[in] _access Image access. See `Access::Enum`.
 * @param[in] _format Texture format. See: `TextureFormat::Enum`.
 *
 */
BGFX_C_API void bgfx_set_image(uint8_t _stage, bgfx_texture_handle_t _handle, uint8_t _mip, bgfx_access_t _access, bgfx_texture_format_t _format);

/**
 * Dispatch compute.
 *
 * @param[in] _id View id.
 * @param[in] _program Compute program.
 * @param[in] _numX Number of groups X.
 * @param[in] _numY Number of groups Y.
 * @param[in] _numZ Number of groups Z.
 * @param[in] _flags Discard or preserve states. See `BGFX_DISCARD_*`.
 *
 */
BGFX_C_API void bgfx_dispatch(bgfx_view_id_t _id, bgfx_program_handle_t _program, uint32_t _numX, uint32_t _numY, uint32_t _numZ, uint8_t _flags);

/**
 * Dispatch compute indirect.
 *
 * @param[in] _id View id.
 * @param[in] _program Compute program.
 * @param[in] _indirectHandle Indirect buffer.
 * @param[in] _start First element in indirect buffer.
 * @param[in] _num Number of dispatches.
 * @param[in] _flags Discard or preserve states. See `BGFX_DISCARD_*`.
 *
 */
BGFX_C_API void bgfx_dispatch_indirect(bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, uint8_t _flags);

/**
 * Discard previously set state for draw or compute call.
 *
 * @param[in] _flags Draw/compute states to discard.
 *
 */
BGFX_C_API void bgfx_discard(uint8_t _flags);

/**
 * Blit 2D texture region between two 2D textures.
 * @attention Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
 * @attention Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
 *
 * @param[in] _id View id.
 * @param[in] _dst Destination texture handle.
 * @param[in] _dstMip Destination texture mip level.
 * @param[in] _dstX Destination texture X position.
 * @param[in] _dstY Destination texture Y position.
 * @param[in] _dstZ If texture is 2D this argument should be 0. If destination texture is cube
 *  this argument represents destination texture cube face. For 3D texture this argument
 *  represents destination texture Z position.
 * @param[in] _src Source texture handle.
 * @param[in] _srcMip Source texture mip level.
 * @param[in] _srcX Source texture X position.
 * @param[in] _srcY Source texture Y position.
 * @param[in] _srcZ If texture is 2D this argument should be 0. If source texture is cube
 *  this argument represents source texture cube face. For 3D texture this argument
 *  represents source texture Z position.
 * @param[in] _width Width of region.
 * @param[in] _height Height of region.
 * @param[in] _depth If texture is 3D this argument represents depth of region, otherwise it's
 *  unused.
 *
 */
BGFX_C_API void bgfx_blit(bgfx_view_id_t _id, bgfx_texture_handle_t _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, bgfx_texture_handle_t _src, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth);

/**/
typedef enum bgfx_function_id
{
    BGFX_FUNCTION_ID_ATTACHMENT_INIT,
    BGFX_FUNCTION_ID_VERTEX_LAYOUT_BEGIN,
    BGFX_FUNCTION_ID_VERTEX_LAYOUT_ADD,
    BGFX_FUNCTION_ID_VERTEX_LAYOUT_DECODE,
    BGFX_FUNCTION_ID_VERTEX_LAYOUT_HAS,
    BGFX_FUNCTION_ID_VERTEX_LAYOUT_SKIP,
    BGFX_FUNCTION_ID_VERTEX_LAYOUT_END,
    BGFX_FUNCTION_ID_VERTEX_PACK,
    BGFX_FUNCTION_ID_VERTEX_UNPACK,
    BGFX_FUNCTION_ID_VERTEX_CONVERT,
    BGFX_FUNCTION_ID_WELD_VERTICES,
    BGFX_FUNCTION_ID_TOPOLOGY_CONVERT,
    BGFX_FUNCTION_ID_TOPOLOGY_SORT_TRI_LIST,
    BGFX_FUNCTION_ID_GET_SUPPORTED_RENDERERS,
    BGFX_FUNCTION_ID_GET_RENDERER_NAME,
    BGFX_FUNCTION_ID_INIT_CTOR,
    BGFX_FUNCTION_ID_INIT,
    BGFX_FUNCTION_ID_SHUTDOWN,
    BGFX_FUNCTION_ID_RESET,
    BGFX_FUNCTION_ID_FRAME,
    BGFX_FUNCTION_ID_GET_RENDERER_TYPE,
    BGFX_FUNCTION_ID_GET_CAPS,
    BGFX_FUNCTION_ID_GET_STATS,
    BGFX_FUNCTION_ID_ALLOC,
    BGFX_FUNCTION_ID_COPY,
    BGFX_FUNCTION_ID_MAKE_REF,
    BGFX_FUNCTION_ID_MAKE_REF_RELEASE,
    BGFX_FUNCTION_ID_SET_DEBUG,
    BGFX_FUNCTION_ID_DBG_TEXT_CLEAR,
    BGFX_FUNCTION_ID_DBG_TEXT_PRINTF,
    BGFX_FUNCTION_ID_DBG_TEXT_VPRINTF,
    BGFX_FUNCTION_ID_DBG_TEXT_IMAGE,
    BGFX_FUNCTION_ID_CREATE_INDEX_BUFFER,
    BGFX_FUNCTION_ID_SET_INDEX_BUFFER_NAME,
    BGFX_FUNCTION_ID_DESTROY_INDEX_BUFFER,
    BGFX_FUNCTION_ID_CREATE_VERTEX_LAYOUT,
    BGFX_FUNCTION_ID_DESTROY_VERTEX_LAYOUT,
    BGFX_FUNCTION_ID_CREATE_VERTEX_BUFFER,
    BGFX_FUNCTION_ID_SET_VERTEX_BUFFER_NAME,
    BGFX_FUNCTION_ID_DESTROY_VERTEX_BUFFER,
    BGFX_FUNCTION_ID_CREATE_DYNAMIC_INDEX_BUFFER,
    BGFX_FUNCTION_ID_CREATE_DYNAMIC_INDEX_BUFFER_MEM,
    BGFX_FUNCTION_ID_UPDATE_DYNAMIC_INDEX_BUFFER,
    BGFX_FUNCTION_ID_DESTROY_DYNAMIC_INDEX_BUFFER,
    BGFX_FUNCTION_ID_CREATE_DYNAMIC_VERTEX_BUFFER,
    BGFX_FUNCTION_ID_CREATE_DYNAMIC_VERTEX_BUFFER_MEM,
    BGFX_FUNCTION_ID_UPDATE_DYNAMIC_VERTEX_BUFFER,
    BGFX_FUNCTION_ID_DESTROY_DYNAMIC_VERTEX_BUFFER,
    BGFX_FUNCTION_ID_GET_AVAIL_TRANSIENT_INDEX_BUFFER,
    BGFX_FUNCTION_ID_GET_AVAIL_TRANSIENT_VERTEX_BUFFER,
    BGFX_FUNCTION_ID_GET_AVAIL_INSTANCE_DATA_BUFFER,
    BGFX_FUNCTION_ID_ALLOC_TRANSIENT_INDEX_BUFFER,
    BGFX_FUNCTION_ID_ALLOC_TRANSIENT_VERTEX_BUFFER,
    BGFX_FUNCTION_ID_ALLOC_TRANSIENT_BUFFERS,
    BGFX_FUNCTION_ID_ALLOC_INSTANCE_DATA_BUFFER,
    BGFX_FUNCTION_ID_CREATE_INDIRECT_BUFFER,
    BGFX_FUNCTION_ID_DESTROY_INDIRECT_BUFFER,
    BGFX_FUNCTION_ID_CREATE_SHADER,
    BGFX_FUNCTION_ID_GET_SHADER_UNIFORMS,
    BGFX_FUNCTION_ID_SET_SHADER_NAME,
    BGFX_FUNCTION_ID_DESTROY_SHADER,
    BGFX_FUNCTION_ID_CREATE_PROGRAM,
    BGFX_FUNCTION_ID_CREATE_COMPUTE_PROGRAM,
    BGFX_FUNCTION_ID_DESTROY_PROGRAM,
    BGFX_FUNCTION_ID_IS_TEXTURE_VALID,
    BGFX_FUNCTION_ID_CALC_TEXTURE_SIZE,
    BGFX_FUNCTION_ID_CREATE_TEXTURE,
    BGFX_FUNCTION_ID_CREATE_TEXTURE_2D,
    BGFX_FUNCTION_ID_CREATE_TEXTURE_2D_SCALED,
    BGFX_FUNCTION_ID_CREATE_TEXTURE_3D,
    BGFX_FUNCTION_ID_CREATE_TEXTURE_CUBE,
    BGFX_FUNCTION_ID_UPDATE_TEXTURE_2D,
    BGFX_FUNCTION_ID_UPDATE_TEXTURE_3D,
    BGFX_FUNCTION_ID_UPDATE_TEXTURE_CUBE,
    BGFX_FUNCTION_ID_READ_TEXTURE,
    BGFX_FUNCTION_ID_SET_TEXTURE_NAME,
    BGFX_FUNCTION_ID_GET_DIRECT_ACCESS_PTR,
    BGFX_FUNCTION_ID_DESTROY_TEXTURE,
    BGFX_FUNCTION_ID_CREATE_FRAME_BUFFER,
    BGFX_FUNCTION_ID_CREATE_FRAME_BUFFER_SCALED,
    BGFX_FUNCTION_ID_CREATE_FRAME_BUFFER_FROM_HANDLES,
    BGFX_FUNCTION_ID_CREATE_FRAME_BUFFER_FROM_ATTACHMENT,
    BGFX_FUNCTION_ID_CREATE_FRAME_BUFFER_FROM_NWH,
    BGFX_FUNCTION_ID_SET_FRAME_BUFFER_NAME,
    BGFX_FUNCTION_ID_GET_TEXTURE,
    BGFX_FUNCTION_ID_DESTROY_FRAME_BUFFER,
    BGFX_FUNCTION_ID_CREATE_UNIFORM,
    BGFX_FUNCTION_ID_GET_UNIFORM_INFO,
    BGFX_FUNCTION_ID_DESTROY_UNIFORM,
    BGFX_FUNCTION_ID_CREATE_OCCLUSION_QUERY,
    BGFX_FUNCTION_ID_GET_RESULT,
    BGFX_FUNCTION_ID_DESTROY_OCCLUSION_QUERY,
    BGFX_FUNCTION_ID_SET_PALETTE_COLOR,
    BGFX_FUNCTION_ID_SET_PALETTE_COLOR_RGBA8,
    BGFX_FUNCTION_ID_SET_VIEW_NAME,
    BGFX_FUNCTION_ID_SET_VIEW_RECT,
    BGFX_FUNCTION_ID_SET_VIEW_RECT_RATIO,
    BGFX_FUNCTION_ID_SET_VIEW_SCISSOR,
    BGFX_FUNCTION_ID_SET_VIEW_CLEAR,
    BGFX_FUNCTION_ID_SET_VIEW_CLEAR_MRT,
    BGFX_FUNCTION_ID_SET_VIEW_MODE,
    BGFX_FUNCTION_ID_SET_VIEW_FRAME_BUFFER,
    BGFX_FUNCTION_ID_SET_VIEW_TRANSFORM,
    BGFX_FUNCTION_ID_SET_VIEW_ORDER,
    BGFX_FUNCTION_ID_RESET_VIEW,
    BGFX_FUNCTION_ID_ENCODER_BEGIN,
    BGFX_FUNCTION_ID_ENCODER_END,
    BGFX_FUNCTION_ID_ENCODER_SET_MARKER,
    BGFX_FUNCTION_ID_ENCODER_SET_STATE,
    BGFX_FUNCTION_ID_ENCODER_SET_CONDITION,
    BGFX_FUNCTION_ID_ENCODER_SET_STENCIL,
    BGFX_FUNCTION_ID_ENCODER_SET_SCISSOR,
    BGFX_FUNCTION_ID_ENCODER_SET_SCISSOR_CACHED,
    BGFX_FUNCTION_ID_ENCODER_SET_TRANSFORM,
    BGFX_FUNCTION_ID_ENCODER_SET_TRANSFORM_CACHED,
    BGFX_FUNCTION_ID_ENCODER_ALLOC_TRANSFORM,
    BGFX_FUNCTION_ID_ENCODER_SET_UNIFORM,
    BGFX_FUNCTION_ID_ENCODER_SET_INDEX_BUFFER,
    BGFX_FUNCTION_ID_ENCODER_SET_DYNAMIC_INDEX_BUFFER,
    BGFX_FUNCTION_ID_ENCODER_SET_TRANSIENT_INDEX_BUFFER,
    BGFX_FUNCTION_ID_ENCODER_SET_VERTEX_BUFFER,
    BGFX_FUNCTION_ID_ENCODER_SET_VERTEX_BUFFER_WITH_LAYOUT,
    BGFX_FUNCTION_ID_ENCODER_SET_DYNAMIC_VERTEX_BUFFER,
    BGFX_FUNCTION_ID_ENCODER_SET_DYNAMIC_VERTEX_BUFFER_WITH_LAYOUT,
    BGFX_FUNCTION_ID_ENCODER_SET_TRANSIENT_VERTEX_BUFFER,
    BGFX_FUNCTION_ID_ENCODER_SET_TRANSIENT_VERTEX_BUFFER_WITH_LAYOUT,
    BGFX_FUNCTION_ID_ENCODER_SET_VERTEX_COUNT,
    BGFX_FUNCTION_ID_ENCODER_SET_INSTANCE_DATA_BUFFER,
    BGFX_FUNCTION_ID_ENCODER_SET_INSTANCE_DATA_FROM_VERTEX_BUFFER,
    BGFX_FUNCTION_ID_ENCODER_SET_INSTANCE_DATA_FROM_DYNAMIC_VERTEX_BUFFER,
    BGFX_FUNCTION_ID_ENCODER_SET_INSTANCE_COUNT,
    BGFX_FUNCTION_ID_ENCODER_SET_TEXTURE,
    BGFX_FUNCTION_ID_ENCODER_TOUCH,
    BGFX_FUNCTION_ID_ENCODER_SUBMIT,
    BGFX_FUNCTION_ID_ENCODER_SUBMIT_OCCLUSION_QUERY,
    BGFX_FUNCTION_ID_ENCODER_SUBMIT_INDIRECT,
    BGFX_FUNCTION_ID_ENCODER_SET_COMPUTE_INDEX_BUFFER,
    BGFX_FUNCTION_ID_ENCODER_SET_COMPUTE_VERTEX_BUFFER,
    BGFX_FUNCTION_ID_ENCODER_SET_COMPUTE_DYNAMIC_INDEX_BUFFER,
    BGFX_FUNCTION_ID_ENCODER_SET_COMPUTE_DYNAMIC_VERTEX_BUFFER,
    BGFX_FUNCTION_ID_ENCODER_SET_COMPUTE_INDIRECT_BUFFER,
    BGFX_FUNCTION_ID_ENCODER_SET_IMAGE,
    BGFX_FUNCTION_ID_ENCODER_DISPATCH,
    BGFX_FUNCTION_ID_ENCODER_DISPATCH_INDIRECT,
    BGFX_FUNCTION_ID_ENCODER_DISCARD,
    BGFX_FUNCTION_ID_ENCODER_BLIT,
    BGFX_FUNCTION_ID_REQUEST_SCREEN_SHOT,
    BGFX_FUNCTION_ID_RENDER_FRAME,
    BGFX_FUNCTION_ID_SET_PLATFORM_DATA,
    BGFX_FUNCTION_ID_GET_INTERNAL_DATA,
    BGFX_FUNCTION_ID_OVERRIDE_INTERNAL_TEXTURE_PTR,
    BGFX_FUNCTION_ID_OVERRIDE_INTERNAL_TEXTURE,
    BGFX_FUNCTION_ID_SET_MARKER,
    BGFX_FUNCTION_ID_SET_STATE,
    BGFX_FUNCTION_ID_SET_CONDITION,
    BGFX_FUNCTION_ID_SET_STENCIL,
    BGFX_FUNCTION_ID_SET_SCISSOR,
    BGFX_FUNCTION_ID_SET_SCISSOR_CACHED,
    BGFX_FUNCTION_ID_SET_TRANSFORM,
    BGFX_FUNCTION_ID_SET_TRANSFORM_CACHED,
    BGFX_FUNCTION_ID_ALLOC_TRANSFORM,
    BGFX_FUNCTION_ID_SET_UNIFORM,
    BGFX_FUNCTION_ID_SET_INDEX_BUFFER,
    BGFX_FUNCTION_ID_SET_DYNAMIC_INDEX_BUFFER,
    BGFX_FUNCTION_ID_SET_TRANSIENT_INDEX_BUFFER,
    BGFX_FUNCTION_ID_SET_VERTEX_BUFFER,
    BGFX_FUNCTION_ID_SET_VERTEX_BUFFER_WITH_LAYOUT,
    BGFX_FUNCTION_ID_SET_DYNAMIC_VERTEX_BUFFER,
    BGFX_FUNCTION_ID_SET_DYNAMIC_VERTEX_BUFFER_WITH_LAYOUT,
    BGFX_FUNCTION_ID_SET_TRANSIENT_VERTEX_BUFFER,
    BGFX_FUNCTION_ID_SET_TRANSIENT_VERTEX_BUFFER_WITH_LAYOUT,
    BGFX_FUNCTION_ID_SET_VERTEX_COUNT,
    BGFX_FUNCTION_ID_SET_INSTANCE_DATA_BUFFER,
    BGFX_FUNCTION_ID_SET_INSTANCE_DATA_FROM_VERTEX_BUFFER,
    BGFX_FUNCTION_ID_SET_INSTANCE_DATA_FROM_DYNAMIC_VERTEX_BUFFER,
    BGFX_FUNCTION_ID_SET_INSTANCE_COUNT,
    BGFX_FUNCTION_ID_SET_TEXTURE,
    BGFX_FUNCTION_ID_TOUCH,
    BGFX_FUNCTION_ID_SUBMIT,
    BGFX_FUNCTION_ID_SUBMIT_OCCLUSION_QUERY,
    BGFX_FUNCTION_ID_SUBMIT_INDIRECT,
    BGFX_FUNCTION_ID_SET_COMPUTE_INDEX_BUFFER,
    BGFX_FUNCTION_ID_SET_COMPUTE_VERTEX_BUFFER,
    BGFX_FUNCTION_ID_SET_COMPUTE_DYNAMIC_INDEX_BUFFER,
    BGFX_FUNCTION_ID_SET_COMPUTE_DYNAMIC_VERTEX_BUFFER,
    BGFX_FUNCTION_ID_SET_COMPUTE_INDIRECT_BUFFER,
    BGFX_FUNCTION_ID_SET_IMAGE,
    BGFX_FUNCTION_ID_DISPATCH,
    BGFX_FUNCTION_ID_DISPATCH_INDIRECT,
    BGFX_FUNCTION_ID_DISCARD,
    BGFX_FUNCTION_ID_BLIT,

    BGFX_FUNCTION_ID_COUNT

} bgfx_function_id_t;

/**/
struct bgfx_interface_vtbl
{
    void (*attachment_init)(bgfx_attachment_t* _this, bgfx_texture_handle_t _handle, bgfx_access_t _access, uint16_t _layer, uint16_t _mip, uint8_t _resolve);
    bgfx_vertex_layout_t* (*vertex_layout_begin)(bgfx_vertex_layout_t* _this, bgfx_renderer_type_t _rendererType);
    bgfx_vertex_layout_t* (*vertex_layout_add)(bgfx_vertex_layout_t* _this, bgfx_attrib_t _attrib, uint8_t _num, bgfx_attrib_type_t _type, bool _normalized, bool _asInt);
    void (*vertex_layout_decode)(const bgfx_vertex_layout_t* _this, bgfx_attrib_t _attrib, uint8_t * _num, bgfx_attrib_type_t * _type, bool * _normalized, bool * _asInt);
    bool (*vertex_layout_has)(const bgfx_vertex_layout_t* _this, bgfx_attrib_t _attrib);
    bgfx_vertex_layout_t* (*vertex_layout_skip)(bgfx_vertex_layout_t* _this, uint8_t _num);
    void (*vertex_layout_end)(bgfx_vertex_layout_t* _this);
    void (*vertex_pack)(const float _input[4], bool _inputNormalized, bgfx_attrib_t _attr, const bgfx_vertex_layout_t * _layout, void* _data, uint32_t _index);
    void (*vertex_unpack)(float _output[4], bgfx_attrib_t _attr, const bgfx_vertex_layout_t * _layout, const void* _data, uint32_t _index);
    void (*vertex_convert)(const bgfx_vertex_layout_t * _dstLayout, void* _dstData, const bgfx_vertex_layout_t * _srcLayout, const void* _srcData, uint32_t _num);
    uint32_t (*weld_vertices)(void* _output, const bgfx_vertex_layout_t * _layout, const void* _data, uint32_t _num, bool _index32, float _epsilon);
    uint32_t (*topology_convert)(bgfx_topology_convert_t _conversion, void* _dst, uint32_t _dstSize, const void* _indices, uint32_t _numIndices, bool _index32);
    void (*topology_sort_tri_list)(bgfx_topology_sort_t _sort, void* _dst, uint32_t _dstSize, const float _dir[3], const float _pos[3], const void* _vertices, uint32_t _stride, const void* _indices, uint32_t _numIndices, bool _index32);
    uint8_t (*get_supported_renderers)(uint8_t _max, bgfx_renderer_type_t* _enum);
    const char* (*get_renderer_name)(bgfx_renderer_type_t _type);
    void (*init_ctor)(bgfx_init_t* _init);
    bool (*init)(const bgfx_init_t * _init);
    void (*shutdown)(void);
    void (*reset)(uint32_t _width, uint32_t _height, uint32_t _flags, bgfx_texture_format_t _format);
    uint32_t (*frame)(bool _capture);
    bgfx_renderer_type_t (*get_renderer_type)(void);
    const bgfx_caps_t* (*get_caps)(void);
    const bgfx_stats_t* (*get_stats)(void);
    const bgfx_memory_t* (*alloc)(uint32_t _size);
    const bgfx_memory_t* (*copy)(const void* _data, uint32_t _size);
    const bgfx_memory_t* (*make_ref)(const void* _data, uint32_t _size);
    const bgfx_memory_t* (*make_ref_release)(const void* _data, uint32_t _size, bgfx_release_fn_t _releaseFn, void* _userData);
    void (*set_debug)(uint32_t _debug);
    void (*dbg_text_clear)(uint8_t _attr, bool _small);
    void (*dbg_text_printf)(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, ... );
    void (*dbg_text_vprintf)(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, va_list _argList);
    void (*dbg_text_image)(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const void* _data, uint16_t _pitch);
    bgfx_index_buffer_handle_t (*create_index_buffer)(const bgfx_memory_t* _mem, uint16_t _flags);
    void (*set_index_buffer_name)(bgfx_index_buffer_handle_t _handle, const char* _name, int32_t _len);
    void (*destroy_index_buffer)(bgfx_index_buffer_handle_t _handle);
    bgfx_vertex_layout_handle_t (*create_vertex_layout)(const bgfx_vertex_layout_t * _layout);
    void (*destroy_vertex_layout)(bgfx_vertex_layout_handle_t _layoutHandle);
    bgfx_vertex_buffer_handle_t (*create_vertex_buffer)(const bgfx_memory_t* _mem, const bgfx_vertex_layout_t * _layout, uint16_t _flags);
    void (*set_vertex_buffer_name)(bgfx_vertex_buffer_handle_t _handle, const char* _name, int32_t _len);
    void (*destroy_vertex_buffer)(bgfx_vertex_buffer_handle_t _handle);
    bgfx_dynamic_index_buffer_handle_t (*create_dynamic_index_buffer)(uint32_t _num, uint16_t _flags);
    bgfx_dynamic_index_buffer_handle_t (*create_dynamic_index_buffer_mem)(const bgfx_memory_t* _mem, uint16_t _flags);
    void (*update_dynamic_index_buffer)(bgfx_dynamic_index_buffer_handle_t _handle, uint32_t _startIndex, const bgfx_memory_t* _mem);
    void (*destroy_dynamic_index_buffer)(bgfx_dynamic_index_buffer_handle_t _handle);
    bgfx_dynamic_vertex_buffer_handle_t (*create_dynamic_vertex_buffer)(uint32_t _num, const bgfx_vertex_layout_t* _layout, uint16_t _flags);
    bgfx_dynamic_vertex_buffer_handle_t (*create_dynamic_vertex_buffer_mem)(const bgfx_memory_t* _mem, const bgfx_vertex_layout_t* _layout, uint16_t _flags);
    void (*update_dynamic_vertex_buffer)(bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, const bgfx_memory_t* _mem);
    void (*destroy_dynamic_vertex_buffer)(bgfx_dynamic_vertex_buffer_handle_t _handle);
    uint32_t (*get_avail_transient_index_buffer)(uint32_t _num);
    uint32_t (*get_avail_transient_vertex_buffer)(uint32_t _num, const bgfx_vertex_layout_t * _layout);
    uint32_t (*get_avail_instance_data_buffer)(uint32_t _num, uint16_t _stride);
    void (*alloc_transient_index_buffer)(bgfx_transient_index_buffer_t* _tib, uint32_t _num);
    void (*alloc_transient_vertex_buffer)(bgfx_transient_vertex_buffer_t* _tvb, uint32_t _num, const bgfx_vertex_layout_t * _layout);
    bool (*alloc_transient_buffers)(bgfx_transient_vertex_buffer_t* _tvb, const bgfx_vertex_layout_t * _layout, uint32_t _numVertices, bgfx_transient_index_buffer_t* _tib, uint32_t _numIndices);
    void (*alloc_instance_data_buffer)(bgfx_instance_data_buffer_t* _idb, uint32_t _num, uint16_t _stride);
    bgfx_indirect_buffer_handle_t (*create_indirect_buffer)(uint32_t _num);
    void (*destroy_indirect_buffer)(bgfx_indirect_buffer_handle_t _handle);
    bgfx_shader_handle_t (*create_shader)(const bgfx_memory_t* _mem);
    uint16_t (*get_shader_uniforms)(bgfx_shader_handle_t _handle, bgfx_uniform_handle_t* _uniforms, uint16_t _max);
    void (*set_shader_name)(bgfx_shader_handle_t _handle, const char* _name, int32_t _len);
    void (*destroy_shader)(bgfx_shader_handle_t _handle);
    bgfx_program_handle_t (*create_program)(bgfx_shader_handle_t _vsh, bgfx_shader_handle_t _fsh, bool _destroyShaders);
    bgfx_program_handle_t (*create_compute_program)(bgfx_shader_handle_t _csh, bool _destroyShaders);
    void (*destroy_program)(bgfx_program_handle_t _handle);
    bool (*is_texture_valid)(uint16_t _depth, bool _cubeMap, uint16_t _numLayers, bgfx_texture_format_t _format, uint64_t _flags);
    void (*calc_texture_size)(bgfx_texture_info_t * _info, uint16_t _width, uint16_t _height, uint16_t _depth, bool _cubeMap, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format);
    bgfx_texture_handle_t (*create_texture)(const bgfx_memory_t* _mem, uint64_t _flags, uint8_t _skip, bgfx_texture_info_t* _info);
    bgfx_texture_handle_t (*create_texture_2d)(uint16_t _width, uint16_t _height, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format, uint64_t _flags, const bgfx_memory_t* _mem);
    bgfx_texture_handle_t (*create_texture_2d_scaled)(bgfx_backbuffer_ratio_t _ratio, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format, uint64_t _flags);
    bgfx_texture_handle_t (*create_texture_3d)(uint16_t _width, uint16_t _height, uint16_t _depth, bool _hasMips, bgfx_texture_format_t _format, uint64_t _flags, const bgfx_memory_t* _mem);
    bgfx_texture_handle_t (*create_texture_cube)(uint16_t _size, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format, uint64_t _flags, const bgfx_memory_t* _mem);
    void (*update_texture_2d)(bgfx_texture_handle_t _handle, uint16_t _layer, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const bgfx_memory_t* _mem, uint16_t _pitch);
    void (*update_texture_3d)(bgfx_texture_handle_t _handle, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _z, uint16_t _width, uint16_t _height, uint16_t _depth, const bgfx_memory_t* _mem);
    void (*update_texture_cube)(bgfx_texture_handle_t _handle, uint16_t _layer, uint8_t _side, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const bgfx_memory_t* _mem, uint16_t _pitch);
    uint32_t (*read_texture)(bgfx_texture_handle_t _handle, void* _data, uint8_t _mip);
    void (*set_texture_name)(bgfx_texture_handle_t _handle, const char* _name, int32_t _len);
    void* (*get_direct_access_ptr)(bgfx_texture_handle_t _handle);
    void (*destroy_texture)(bgfx_texture_handle_t _handle);
    bgfx_frame_buffer_handle_t (*create_frame_buffer)(uint16_t _width, uint16_t _height, bgfx_texture_format_t _format, uint64_t _textureFlags);
    bgfx_frame_buffer_handle_t (*create_frame_buffer_scaled)(bgfx_backbuffer_ratio_t _ratio, bgfx_texture_format_t _format, uint64_t _textureFlags);
    bgfx_frame_buffer_handle_t (*create_frame_buffer_from_handles)(uint8_t _num, const bgfx_texture_handle_t* _handles, bool _destroyTexture);
    bgfx_frame_buffer_handle_t (*create_frame_buffer_from_attachment)(uint8_t _num, const bgfx_attachment_t* _attachment, bool _destroyTexture);
    bgfx_frame_buffer_handle_t (*create_frame_buffer_from_nwh)(void* _nwh, uint16_t _width, uint16_t _height, bgfx_texture_format_t _format, bgfx_texture_format_t _depthFormat);
    void (*set_frame_buffer_name)(bgfx_frame_buffer_handle_t _handle, const char* _name, int32_t _len);
    bgfx_texture_handle_t (*get_texture)(bgfx_frame_buffer_handle_t _handle, uint8_t _attachment);
    void (*destroy_frame_buffer)(bgfx_frame_buffer_handle_t _handle);
    bgfx_uniform_handle_t (*create_uniform)(const char* _name, bgfx_uniform_type_t _type, uint16_t _num);
    void (*get_uniform_info)(bgfx_uniform_handle_t _handle, bgfx_uniform_info_t * _info);
    void (*destroy_uniform)(bgfx_uniform_handle_t _handle);
    bgfx_occlusion_query_handle_t (*create_occlusion_query)(void);
    bgfx_occlusion_query_result_t (*get_result)(bgfx_occlusion_query_handle_t _handle, int32_t* _result);
    void (*destroy_occlusion_query)(bgfx_occlusion_query_handle_t _handle);
    void (*set_palette_color)(uint8_t _index, const float _rgba[4]);
    void (*set_palette_color_rgba8)(uint8_t _index, uint32_t _rgba);
    void (*set_view_name)(bgfx_view_id_t _id, const char* _name);
    void (*set_view_rect)(bgfx_view_id_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);
    void (*set_view_rect_ratio)(bgfx_view_id_t _id, uint16_t _x, uint16_t _y, bgfx_backbuffer_ratio_t _ratio);
    void (*set_view_scissor)(bgfx_view_id_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);
    void (*set_view_clear)(bgfx_view_id_t _id, uint16_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil);
    void (*set_view_clear_mrt)(bgfx_view_id_t _id, uint16_t _flags, float _depth, uint8_t _stencil, uint8_t _c0, uint8_t _c1, uint8_t _c2, uint8_t _c3, uint8_t _c4, uint8_t _c5, uint8_t _c6, uint8_t _c7);
    void (*set_view_mode)(bgfx_view_id_t _id, bgfx_view_mode_t _mode);
    void (*set_view_frame_buffer)(bgfx_view_id_t _id, bgfx_frame_buffer_handle_t _handle);
    void (*set_view_transform)(bgfx_view_id_t _id, const void* _view, const void* _proj);
    void (*set_view_order)(bgfx_view_id_t _id, uint16_t _num, const bgfx_view_id_t* _order);
    void (*reset_view)(bgfx_view_id_t _id);
    bgfx_encoder_t* (*encoder_begin)(bool _forThread);
    void (*encoder_end)(bgfx_encoder_t* _encoder);
    void (*encoder_set_marker)(bgfx_encoder_t* _this, const char* _marker);
    void (*encoder_set_state)(bgfx_encoder_t* _this, uint64_t _state, uint32_t _rgba);
    void (*encoder_set_condition)(bgfx_encoder_t* _this, bgfx_occlusion_query_handle_t _handle, bool _visible);
    void (*encoder_set_stencil)(bgfx_encoder_t* _this, uint32_t _fstencil, uint32_t _bstencil);
    uint16_t (*encoder_set_scissor)(bgfx_encoder_t* _this, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);
    void (*encoder_set_scissor_cached)(bgfx_encoder_t* _this, uint16_t _cache);
    uint32_t (*encoder_set_transform)(bgfx_encoder_t* _this, const void* _mtx, uint16_t _num);
    void (*encoder_set_transform_cached)(bgfx_encoder_t* _this, uint32_t _cache, uint16_t _num);
    uint32_t (*encoder_alloc_transform)(bgfx_encoder_t* _this, bgfx_transform_t* _transform, uint16_t _num);
    void (*encoder_set_uniform)(bgfx_encoder_t* _this, bgfx_uniform_handle_t _handle, const void* _value, uint16_t _num);
    void (*encoder_set_index_buffer)(bgfx_encoder_t* _this, bgfx_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices);
    void (*encoder_set_dynamic_index_buffer)(bgfx_encoder_t* _this, bgfx_dynamic_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices);
    void (*encoder_set_transient_index_buffer)(bgfx_encoder_t* _this, const bgfx_transient_index_buffer_t* _tib, uint32_t _firstIndex, uint32_t _numIndices);
    void (*encoder_set_vertex_buffer)(bgfx_encoder_t* _this, uint8_t _stream, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices);
    void (*encoder_set_vertex_buffer_with_layout)(bgfx_encoder_t* _this, uint8_t _stream, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices, bgfx_vertex_layout_handle_t _layoutHandle);
    void (*encoder_set_dynamic_vertex_buffer)(bgfx_encoder_t* _this, uint8_t _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices);
    void (*encoder_set_dynamic_vertex_buffer_with_layout)(bgfx_encoder_t* _this, uint8_t _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices, bgfx_vertex_layout_handle_t _layoutHandle);
    void (*encoder_set_transient_vertex_buffer)(bgfx_encoder_t* _this, uint8_t _stream, const bgfx_transient_vertex_buffer_t* _tvb, uint32_t _startVertex, uint32_t _numVertices);
    void (*encoder_set_transient_vertex_buffer_with_layout)(bgfx_encoder_t* _this, uint8_t _stream, const bgfx_transient_vertex_buffer_t* _tvb, uint32_t _startVertex, uint32_t _numVertices, bgfx_vertex_layout_handle_t _layoutHandle);
    void (*encoder_set_vertex_count)(bgfx_encoder_t* _this, uint32_t _numVertices);
    void (*encoder_set_instance_data_buffer)(bgfx_encoder_t* _this, const bgfx_instance_data_buffer_t* _idb, uint32_t _start, uint32_t _num);
    void (*encoder_set_instance_data_from_vertex_buffer)(bgfx_encoder_t* _this, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num);
    void (*encoder_set_instance_data_from_dynamic_vertex_buffer)(bgfx_encoder_t* _this, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num);
    void (*encoder_set_instance_count)(bgfx_encoder_t* _this, uint32_t _numInstances);
    void (*encoder_set_texture)(bgfx_encoder_t* _this, uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint32_t _flags);
    void (*encoder_touch)(bgfx_encoder_t* _this, bgfx_view_id_t _id);
    void (*encoder_submit)(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, uint32_t _depth, uint8_t _flags);
    void (*encoder_submit_occlusion_query)(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_occlusion_query_handle_t _occlusionQuery, uint32_t _depth, uint8_t _flags);
    void (*encoder_submit_indirect)(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, uint32_t _depth, uint8_t _flags);
    void (*encoder_set_compute_index_buffer)(bgfx_encoder_t* _this, uint8_t _stage, bgfx_index_buffer_handle_t _handle, bgfx_access_t _access);
    void (*encoder_set_compute_vertex_buffer)(bgfx_encoder_t* _this, uint8_t _stage, bgfx_vertex_buffer_handle_t _handle, bgfx_access_t _access);
    void (*encoder_set_compute_dynamic_index_buffer)(bgfx_encoder_t* _this, uint8_t _stage, bgfx_dynamic_index_buffer_handle_t _handle, bgfx_access_t _access);
    void (*encoder_set_compute_dynamic_vertex_buffer)(bgfx_encoder_t* _this, uint8_t _stage, bgfx_dynamic_vertex_buffer_handle_t _handle, bgfx_access_t _access);
    void (*encoder_set_compute_indirect_buffer)(bgfx_encoder_t* _this, uint8_t _stage, bgfx_indirect_buffer_handle_t _handle, bgfx_access_t _access);
    void (*encoder_set_image)(bgfx_encoder_t* _this, uint8_t _stage, bgfx_texture_handle_t _handle, uint8_t _mip, bgfx_access_t _access, bgfx_texture_format_t _format);
    void (*encoder_dispatch)(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, uint32_t _numX, uint32_t _numY, uint32_t _numZ, uint8_t _flags);
    void (*encoder_dispatch_indirect)(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, uint8_t _flags);
    void (*encoder_discard)(bgfx_encoder_t* _this, uint8_t _flags);
    void (*encoder_blit)(bgfx_encoder_t* _this, bgfx_view_id_t _id, bgfx_texture_handle_t _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, bgfx_texture_handle_t _src, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth);
    void (*request_screen_shot)(bgfx_frame_buffer_handle_t _handle, const char* _filePath);
    bgfx_render_frame_t (*render_frame)(int32_t _msecs);
    void (*set_platform_data)(const bgfx_platform_data_t * _data);
    const bgfx_internal_data_t* (*get_internal_data)(void);
    uintptr_t (*override_internal_texture_ptr)(bgfx_texture_handle_t _handle, uintptr_t _ptr);
    uintptr_t (*override_internal_texture)(bgfx_texture_handle_t _handle, uint16_t _width, uint16_t _height, uint8_t _numMips, bgfx_texture_format_t _format, uint64_t _flags);
    void (*set_marker)(const char* _marker);
    void (*set_state)(uint64_t _state, uint32_t _rgba);
    void (*set_condition)(bgfx_occlusion_query_handle_t _handle, bool _visible);
    void (*set_stencil)(uint32_t _fstencil, uint32_t _bstencil);
    uint16_t (*set_scissor)(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);
    void (*set_scissor_cached)(uint16_t _cache);
    uint32_t (*set_transform)(const void* _mtx, uint16_t _num);
    void (*set_transform_cached)(uint32_t _cache, uint16_t _num);
    uint32_t (*alloc_transform)(bgfx_transform_t* _transform, uint16_t _num);
    void (*set_uniform)(bgfx_uniform_handle_t _handle, const void* _value, uint16_t _num);
    void (*set_index_buffer)(bgfx_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices);
    void (*set_dynamic_index_buffer)(bgfx_dynamic_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices);
    void (*set_transient_index_buffer)(const bgfx_transient_index_buffer_t* _tib, uint32_t _firstIndex, uint32_t _numIndices);
    void (*set_vertex_buffer)(uint8_t _stream, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices);
    void (*set_vertex_buffer_with_layout)(uint8_t _stream, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices, bgfx_vertex_layout_handle_t _layoutHandle);
    void (*set_dynamic_vertex_buffer)(uint8_t _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices);
    void (*set_dynamic_vertex_buffer_with_layout)(uint8_t _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices, bgfx_vertex_layout_handle_t _layoutHandle);
    void (*set_transient_vertex_buffer)(uint8_t _stream, const bgfx_transient_vertex_buffer_t* _tvb, uint32_t _startVertex, uint32_t _numVertices);
    void (*set_transient_vertex_buffer_with_layout)(uint8_t _stream, const bgfx_transient_vertex_buffer_t* _tvb, uint32_t _startVertex, uint32_t _numVertices, bgfx_vertex_layout_handle_t _layoutHandle);
    void (*set_vertex_count)(uint32_t _numVertices);
    void (*set_instance_data_buffer)(const bgfx_instance_data_buffer_t* _idb, uint32_t _start, uint32_t _num);
    void (*set_instance_data_from_vertex_buffer)(bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num);
    void (*set_instance_data_from_dynamic_vertex_buffer)(bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num);
    void (*set_instance_count)(uint32_t _numInstances);
    void (*set_texture)(uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint32_t _flags);
    void (*touch)(bgfx_view_id_t _id);
    void (*submit)(bgfx_view_id_t _id, bgfx_program_handle_t _program, uint32_t _depth, uint8_t _flags);
    void (*submit_occlusion_query)(bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_occlusion_query_handle_t _occlusionQuery, uint32_t _depth, uint8_t _flags);
    void (*submit_indirect)(bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, uint32_t _depth, uint8_t _flags);
    void (*set_compute_index_buffer)(uint8_t _stage, bgfx_index_buffer_handle_t _handle, bgfx_access_t _access);
    void (*set_compute_vertex_buffer)(uint8_t _stage, bgfx_vertex_buffer_handle_t _handle, bgfx_access_t _access);
    void (*set_compute_dynamic_index_buffer)(uint8_t _stage, bgfx_dynamic_index_buffer_handle_t _handle, bgfx_access_t _access);
    void (*set_compute_dynamic_vertex_buffer)(uint8_t _stage, bgfx_dynamic_vertex_buffer_handle_t _handle, bgfx_access_t _access);
    void (*set_compute_indirect_buffer)(uint8_t _stage, bgfx_indirect_buffer_handle_t _handle, bgfx_access_t _access);
    void (*set_image)(uint8_t _stage, bgfx_texture_handle_t _handle, uint8_t _mip, bgfx_access_t _access, bgfx_texture_format_t _format);
    void (*dispatch)(bgfx_view_id_t _id, bgfx_program_handle_t _program, uint32_t _numX, uint32_t _numY, uint32_t _numZ, uint8_t _flags);
    void (*dispatch_indirect)(bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, uint8_t _flags);
    void (*discard)(uint8_t _flags);
    void (*blit)(bgfx_view_id_t _id, bgfx_texture_handle_t _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, bgfx_texture_handle_t _src, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth);
};

/**/
typedef bgfx_interface_vtbl_t* (*PFN_BGFX_GET_INTERFACE)(uint32_t _version);

/**/
BGFX_C_API bgfx_interface_vtbl_t* bgfx_get_interface(uint32_t _version);

#endif // BGFX_C99_H_HEADER_GUARD
