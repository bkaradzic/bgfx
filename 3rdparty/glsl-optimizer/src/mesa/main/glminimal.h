/*
 * Mesa 3-D graphics library
 * Version:  7.6
 *
 * Copyright (C) 1999-2006  Brian Paul   All Rights Reserved.
 * Copyright (C) 2009  VMware, Inc.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 Minimized version of gl.h with only things that the GLSL compiler needs.
*/

#ifndef __gl_minimal_h_
#define __gl_minimal_h_

#include "stdint.h"


/**********************************************************************
 * Begin system-specific stuff. Do not do any of this when building
 * for SciTech SNAP, as this is all done before this header file is
 * included. 
 */
#if !defined(__SCITECH_SNAP__)

#if defined(__BEOS__)
#include <stdlib.h>     /* to get some BeOS-isms */
#endif

#if !defined(OPENSTEP) && (defined(NeXT) || defined(NeXT_PDO))
#define OPENSTEP
#endif

#if defined(_WIN32) && !defined(__WIN32__) && !defined(__CYGWIN__)
#define __WIN32__
#endif

#if (defined(__BEOS__) && defined(__POWERPC__)) || defined(__QUICKDRAW__)
#  define PRAGMA_EXPORT_SUPPORTED		1
#endif

#if defined(macintosh) && PRAGMA_IMPORT_SUPPORTED
#pragma import on
#endif

#ifdef CENTERLINE_CLPP
#define signed
#endif

#if defined(PRAGMA_EXPORT_SUPPORTED)
#pragma export on
#endif

#endif /* !__SCITECH_SNAP__ */
/*
 * End system-specific stuff.
 **********************************************************************/




#define GL_VERSION_1_1   1
#define GL_VERSION_1_2   1
#define GL_VERSION_1_3   1
#define GL_ARB_imaging   1


/*
 * Datatypes
 */
typedef unsigned int	GLenum;
typedef unsigned char	GLboolean;
typedef unsigned int	GLbitfield;
typedef void		GLvoid;
typedef signed char	GLbyte;		/* 1-byte signed */
typedef short		GLshort;	/* 2-byte signed */
typedef int		GLint;		/* 4-byte signed */
typedef unsigned char	GLubyte;	/* 1-byte unsigned */
typedef unsigned short	GLushort;	/* 2-byte unsigned */
typedef unsigned int	GLuint;		/* 4-byte unsigned */
typedef int		GLsizei;	/* 4-byte signed */
typedef float		GLfloat;	/* single precision float */
typedef float		GLclampf;	/* single precision float in [0,1] */
typedef double		GLdouble;	/* double precision float */
typedef double		GLclampd;	/* double precision float in [0,1] */
typedef char GLchar;
typedef char GLcharARB;
typedef int64_t GLint64;
typedef uint64_t GLuint64;




/*
 * Constants
 */

/* Boolean values */
#define GL_FALSE				0x0
#define GL_TRUE					0x1

/* Data types */
#define GL_BYTE					0x1400
#define GL_UNSIGNED_BYTE			0x1401
#define GL_SHORT				0x1402
#define GL_UNSIGNED_SHORT			0x1403
#define GL_INT					0x1404
#define GL_UNSIGNED_INT				0x1405
#define GL_FLOAT				0x1406
#define GL_2_BYTES				0x1407
#define GL_3_BYTES				0x1408
#define GL_4_BYTES				0x1409
#define GL_DOUBLE				0x140A

/* Primitives */
#define GL_POINTS				0x0000
#define GL_LINES				0x0001
#define GL_LINE_LOOP				0x0002
#define GL_LINE_STRIP				0x0003
#define GL_TRIANGLES				0x0004
#define GL_TRIANGLE_STRIP			0x0005
#define GL_TRIANGLE_FAN				0x0006
#define GL_QUADS				0x0007
#define GL_QUAD_STRIP				0x0008
#define GL_POLYGON				0x0009
#define GL_LINES_ADJACENCY                0x000A
#define GL_LINE_STRIP_ADJACENCY           0x000B
#define GL_TRIANGLES_ADJACENCY            0x000C
#define GL_TRIANGLE_STRIP_ADJACENCY       0x000D


/* Matrix Mode */
#define GL_MATRIX_MODE				0x0BA0
#define GL_MODELVIEW				0x1700
#define GL_PROJECTION				0x1701
#define GL_TEXTURE				0x1702

/* Points */
#define GL_POINT_SMOOTH				0x0B10
#define GL_POINT_SIZE				0x0B11
#define GL_POINT_SIZE_GRANULARITY 		0x0B13
#define GL_POINT_SIZE_RANGE			0x0B12


/* Polygons */
#define GL_POINT				0x1B00
#define GL_LINE					0x1B01
#define GL_FILL					0x1B02
#define GL_CW					0x0900
#define GL_CCW					0x0901
#define GL_FRONT				0x0404
#define GL_BACK					0x0405
#define GL_POLYGON_MODE				0x0B40
#define GL_POLYGON_SMOOTH			0x0B41
#define GL_POLYGON_STIPPLE			0x0B42
#define GL_EDGE_FLAG				0x0B43
#define GL_CULL_FACE				0x0B44
#define GL_CULL_FACE_MODE			0x0B45
#define GL_FRONT_FACE				0x0B46
#define GL_POLYGON_OFFSET_FACTOR		0x8038
#define GL_POLYGON_OFFSET_UNITS			0x2A00
#define GL_POLYGON_OFFSET_POINT			0x2A01
#define GL_POLYGON_OFFSET_LINE			0x2A02
#define GL_POLYGON_OFFSET_FILL			0x8037

/* Display Lists */
#define GL_COMPILE				0x1300
#define GL_COMPILE_AND_EXECUTE			0x1301
#define GL_LIST_BASE				0x0B32
#define GL_LIST_INDEX				0x0B33
#define GL_LIST_MODE				0x0B30

/* Depth buffer */
#define GL_NEVER				0x0200
#define GL_LESS					0x0201
#define GL_EQUAL				0x0202
#define GL_LEQUAL				0x0203
#define GL_GREATER				0x0204
#define GL_NOTEQUAL				0x0205
#define GL_GEQUAL				0x0206
#define GL_ALWAYS				0x0207
#define GL_DEPTH_TEST				0x0B71
#define GL_DEPTH_BITS				0x0D56
#define GL_DEPTH_CLEAR_VALUE			0x0B73
#define GL_DEPTH_FUNC				0x0B74
#define GL_DEPTH_RANGE				0x0B70
#define GL_DEPTH_WRITEMASK			0x0B72
#define GL_DEPTH_COMPONENT			0x1902


/* Blending */
#define GL_BLEND				0x0BE2
#define GL_BLEND_SRC				0x0BE1
#define GL_BLEND_DST				0x0BE0
#define GL_ZERO					0x0
#define GL_ONE					0x1
#define GL_SRC_COLOR				0x0300
#define GL_ONE_MINUS_SRC_COLOR			0x0301
#define GL_SRC_ALPHA				0x0302
#define GL_ONE_MINUS_SRC_ALPHA			0x0303
#define GL_DST_ALPHA				0x0304
#define GL_ONE_MINUS_DST_ALPHA			0x0305
#define GL_DST_COLOR				0x0306
#define GL_ONE_MINUS_DST_COLOR			0x0307
#define GL_SRC_ALPHA_SATURATE			0x0308

/* Render Mode */
#define GL_FEEDBACK				0x1C01
#define GL_RENDER				0x1C00
#define GL_SELECT				0x1C02


/* Buffers, Pixel Drawing/Reading */
#define GL_NONE					0x0
#define GL_LEFT					0x0406
#define GL_RIGHT				0x0407
/*GL_FRONT					0x0404 */
/*GL_BACK					0x0405 */
/*GL_FRONT_AND_BACK				0x0408 */
#define GL_FRONT_LEFT				0x0400
#define GL_FRONT_RIGHT				0x0401
#define GL_BACK_LEFT				0x0402
#define GL_BACK_RIGHT				0x0403
#define GL_COLOR_INDEX				0x1900
#define GL_INDEX_BITS				0x0D51
#define GL_SUBPIXEL_BITS			0x0D50
#define GL_READ_BUFFER				0x0C02
#define GL_DRAW_BUFFER				0x0C01
#define GL_DOUBLEBUFFER				0x0C32
#define GL_BITMAP				0x1A00
#define GL_COLOR				0x1800
#define GL_DEPTH				0x1801
#define GL_DITHER				0x0BD0

/* Implementation limits */
#define GL_MAX_LIST_NESTING			0x0B31
#define GL_MAX_EVAL_ORDER			0x0D30
#define GL_MAX_LIGHTS				0x0D31
#define GL_MAX_CLIP_PLANES			0x0D32
#define GL_MAX_TEXTURE_SIZE			0x0D33
#define GL_MAX_PIXEL_MAP_TABLE			0x0D34
#define GL_MAX_ATTRIB_STACK_DEPTH		0x0D35
#define GL_MAX_MODELVIEW_STACK_DEPTH		0x0D36
#define GL_MAX_NAME_STACK_DEPTH			0x0D37
#define GL_MAX_PROJECTION_STACK_DEPTH		0x0D38
#define GL_MAX_TEXTURE_STACK_DEPTH		0x0D39
#define GL_MAX_VIEWPORT_DIMS			0x0D3A
#define GL_MAX_CLIENT_ATTRIB_STACK_DEPTH	0x0D3B

/* Gets */
#define GL_ATTRIB_STACK_DEPTH			0x0BB0
#define GL_COLOR_CLEAR_VALUE			0x0C22
#define GL_COLOR_WRITEMASK			0x0C23
#define GL_CURRENT_INDEX			0x0B01
#define GL_CURRENT_COLOR			0x0B00
#define GL_CURRENT_NORMAL			0x0B02
#define GL_CURRENT_RASTER_COLOR			0x0B04
#define GL_CURRENT_RASTER_DISTANCE		0x0B09
#define GL_CURRENT_RASTER_INDEX			0x0B05
#define GL_CURRENT_RASTER_POSITION		0x0B07
#define GL_CURRENT_RASTER_TEXTURE_COORDS	0x0B06
#define GL_CURRENT_RASTER_POSITION_VALID	0x0B08
#define GL_CURRENT_TEXTURE_COORDS		0x0B03
#define GL_INDEX_CLEAR_VALUE			0x0C20
#define GL_INDEX_MODE				0x0C30
#define GL_INDEX_WRITEMASK			0x0C21
#define GL_MODELVIEW_MATRIX			0x0BA6
#define GL_MODELVIEW_STACK_DEPTH		0x0BA3
#define GL_NAME_STACK_DEPTH			0x0D70
#define GL_PROJECTION_MATRIX			0x0BA7
#define GL_PROJECTION_STACK_DEPTH		0x0BA4
#define GL_RENDER_MODE				0x0C40
#define GL_TEXTURE_MATRIX			0x0BA8
#define GL_TEXTURE_STACK_DEPTH			0x0BA5
#define GL_VIEWPORT				0x0BA2


/* Scissor box */
#define GL_SCISSOR_BOX				0x0C10
#define GL_SCISSOR_TEST				0x0C11

/* Pixel Mode / Transfer */
#define GL_MAP_COLOR				0x0D10
#define GL_MAP_STENCIL				0x0D11
#define GL_INDEX_SHIFT				0x0D12
#define GL_INDEX_OFFSET				0x0D13
#define GL_DEPTH_SCALE				0x0D1E
#define GL_DEPTH_BIAS				0x0D1F
#define GL_PACK_ALIGNMENT			0x0D05
#define GL_PACK_LSB_FIRST			0x0D01
#define GL_PACK_ROW_LENGTH			0x0D02
#define GL_PACK_SKIP_PIXELS			0x0D04
#define GL_PACK_SKIP_ROWS			0x0D03
#define GL_PACK_SWAP_BYTES			0x0D00
#define GL_UNPACK_ALIGNMENT			0x0CF5
#define GL_UNPACK_LSB_FIRST			0x0CF1
#define GL_UNPACK_ROW_LENGTH			0x0CF2
#define GL_UNPACK_SKIP_PIXELS			0x0CF4
#define GL_UNPACK_SKIP_ROWS			0x0CF3
#define GL_UNPACK_SWAP_BYTES			0x0CF0
#define GL_ZOOM_X				0x0D16
#define GL_ZOOM_Y				0x0D17

/* Texture mapping */
#define GL_TEXTURE_ENV				0x2300
#define GL_TEXTURE_ENV_MODE			0x2200
#define GL_TEXTURE_1D				0x0DE0
#define GL_TEXTURE_2D				0x0DE1
#define GL_TEXTURE_WRAP_S			0x2802
#define GL_TEXTURE_WRAP_T			0x2803
#define GL_TEXTURE_MAG_FILTER			0x2800
#define GL_TEXTURE_MIN_FILTER			0x2801
#define GL_TEXTURE_ENV_COLOR			0x2201
#define GL_TEXTURE_GEN_S			0x0C60
#define GL_TEXTURE_GEN_T			0x0C61
#define GL_TEXTURE_GEN_R			0x0C62
#define GL_TEXTURE_GEN_Q			0x0C63
#define GL_TEXTURE_GEN_MODE			0x2500
#define GL_TEXTURE_BORDER_COLOR			0x1004
#define GL_TEXTURE_WIDTH			0x1000
#define GL_TEXTURE_HEIGHT			0x1001
#define GL_TEXTURE_BORDER			0x1005
#define GL_TEXTURE_COMPONENTS			0x1003
#define GL_TEXTURE_RED_SIZE			0x805C
#define GL_TEXTURE_GREEN_SIZE			0x805D
#define GL_TEXTURE_BLUE_SIZE			0x805E
#define GL_TEXTURE_ALPHA_SIZE			0x805F
#define GL_TEXTURE_LUMINANCE_SIZE		0x8060
#define GL_TEXTURE_INTENSITY_SIZE		0x8061
#define GL_NEAREST_MIPMAP_NEAREST		0x2700
#define GL_NEAREST_MIPMAP_LINEAR		0x2702
#define GL_LINEAR_MIPMAP_NEAREST		0x2701
#define GL_LINEAR_MIPMAP_LINEAR			0x2703
#define GL_OBJECT_LINEAR			0x2401
#define GL_OBJECT_PLANE				0x2501
#define GL_EYE_LINEAR				0x2400
#define GL_EYE_PLANE				0x2502
#define GL_SPHERE_MAP				0x2402
#define GL_DECAL				0x2101
#define GL_MODULATE				0x2100
#define GL_NEAREST				0x2600
#define GL_REPEAT				0x2901
#define GL_CLAMP				0x2900
#define GL_S					0x2000
#define GL_T					0x2001
#define GL_R					0x2002
#define GL_Q					0x2003

/* Utility */
#define GL_VENDOR				0x1F00
#define GL_RENDERER				0x1F01
#define GL_VERSION				0x1F02
#define GL_EXTENSIONS				0x1F03

/* Errors */
#define GL_NO_ERROR 				0x0
#define GL_INVALID_ENUM				0x0500
#define GL_INVALID_VALUE			0x0501
#define GL_INVALID_OPERATION			0x0502
#define GL_STACK_OVERFLOW			0x0503
#define GL_STACK_UNDERFLOW			0x0504
#define GL_OUT_OF_MEMORY			0x0505

/* glPush/PopAttrib bits */
#define GL_CURRENT_BIT				0x00000001
#define GL_POINT_BIT				0x00000002
#define GL_LINE_BIT				0x00000004
#define GL_POLYGON_BIT				0x00000008
#define GL_POLYGON_STIPPLE_BIT			0x00000010
#define GL_PIXEL_MODE_BIT			0x00000020
#define GL_LIGHTING_BIT				0x00000040
#define GL_FOG_BIT				0x00000080
#define GL_VIEWPORT_BIT				0x00000800
#define GL_TRANSFORM_BIT			0x00001000
#define GL_ENABLE_BIT				0x00002000
#define GL_HINT_BIT				0x00008000
#define GL_EVAL_BIT				0x00010000
#define GL_LIST_BIT				0x00020000
#define GL_TEXTURE_BIT				0x00040000
#define GL_SCISSOR_BIT				0x00080000
#define GL_ALL_ATTRIB_BITS			0x000FFFFF


/* OpenGL 1.1 */
#define GL_TEXTURE_PRIORITY			0x8066
#define GL_TEXTURE_RESIDENT			0x8067
#define GL_TEXTURE_BINDING_1D			0x8068
#define GL_TEXTURE_BINDING_2D			0x8069
#define GL_TEXTURE_INTERNAL_FORMAT		0x1003


#define GL_TEXTURE_CUBE_MAP_ARRAY         0x9009
#define GL_TEXTURE_BINDING_CUBE_MAP_ARRAY 0x900A
#define GL_PROXY_TEXTURE_CUBE_MAP_ARRAY   0x900B
#define GL_SAMPLER_CUBE_MAP_ARRAY         0x900C
#define GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW  0x900D
#define GL_INT_SAMPLER_CUBE_MAP_ARRAY     0x900E
#define GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY 0x900F

#define GL_SAMPLER_2D_MULTISAMPLE         0x9108
#define GL_INT_SAMPLER_2D_MULTISAMPLE     0x9109
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE 0x910A
#define GL_SAMPLER_2D_MULTISAMPLE_ARRAY   0x910B
#define GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910C
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910D

/* Texture formats */
#define GL_RGBA32F                        0x8814
#define GL_RGB32F                         0x8815
#define GL_RGBA16F                        0x881A
#define GL_RGB16F                         0x881B
#define GL_R8                             0x8229
#define GL_R16                            0x822A
#define GL_RG8                            0x822B
#define GL_RG16                           0x822C
#define GL_R16F                           0x822D
#define GL_R32F                           0x822E
#define GL_RG16F                          0x822F
#define GL_RG32F                          0x8230
#define GL_R8I                            0x8231
#define GL_R8UI                           0x8232
#define GL_R16I                           0x8233
#define GL_R16UI                          0x8234
#define GL_R32I                           0x8235
#define GL_R32UI                          0x8236
#define GL_RG8I                           0x8237
#define GL_RG8UI                          0x8238
#define GL_RG16I                          0x8239
#define GL_RG16UI                         0x823A
#define GL_RG32I                          0x823B
#define GL_RG32UI                         0x823C
#define GL_RGBA32UI                       0x8D70
#define GL_RGB32UI                        0x8D71
#define GL_RGBA16UI                       0x8D76
#define GL_RGB16UI                        0x8D77
#define GL_RGBA8UI                        0x8D7C
#define GL_RGB8UI                         0x8D7D
#define GL_RGBA32I                        0x8D82
#define GL_RGB32I                         0x8D83
#define GL_RGBA16I                        0x8D88
#define GL_RGB16I                         0x8D89
#define GL_RGBA8I                         0x8D8E
#define GL_RGB8I                          0x8D8F
#define GL_RGBA8                          0x8058
#define GL_RGB10_A2                       0x8059
#define GL_R11F_G11F_B10F                 0x8C3A
#define GL_R8_SNORM                       0x8F94
#define GL_RG8_SNORM                      0x8F95
#define GL_RGB8_SNORM                     0x8F96
#define GL_RGBA8_SNORM                    0x8F97
#define GL_R16_SNORM                      0x8F98
#define GL_RG16_SNORM                     0x8F99
#define GL_RGB16_SNORM                    0x8F9A
#define GL_RGBA16_SNORM                   0x8F9B
#define GL_RGB10_A2UI                     0x906F
#define GL_RGBA16                         0x805B


#define GL_INVALID_INDEX                  0xFFFFFFFF


#endif /* __gl_h_ */
