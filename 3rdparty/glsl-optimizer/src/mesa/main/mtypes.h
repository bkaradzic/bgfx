/*
 * Mesa 3-D graphics library
 * Version:  7.7
 *
 * Copyright (C) 1999-2008  Brian Paul   All Rights Reserved.
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

/**
 * \file mtypes.h
 * Main Mesa data structures.
 *
 * Please try to mark derived values with a leading underscore ('_').
 */

#ifndef MTYPES_H
#define MTYPES_H


#include "main/glheader.h"
#include "main/config.h"


#ifdef __cplusplus
extern "C" {
#endif



/**
 * \name Some forward type declarations
 */
/*@{*/
struct gl_context;
struct gl_uniform_storage;
/*@}*/


/** Extra draw modes beyond GL_POINTS, GL_TRIANGLE_FAN, etc */
#define PRIM_OUTSIDE_BEGIN_END   (GL_POLYGON+1)
#define PRIM_INSIDE_UNKNOWN_PRIM (GL_POLYGON+2)
#define PRIM_UNKNOWN             (GL_POLYGON+3)



/**
 * Indexes for vertex program attributes.
 * GL_NV_vertex_program aliases generic attributes over the conventional
 * attributes.  In GL_ARB_vertex_program shader the aliasing is optional.
 * In GL_ARB_vertex_shader / OpenGL 2.0 the aliasing is disallowed (the
 * generic attributes are distinct/separate).
 */
typedef enum
{
   VERT_ATTRIB_POS = 0,
   VERT_ATTRIB_WEIGHT = 1,
   VERT_ATTRIB_NORMAL = 2,
   VERT_ATTRIB_COLOR0 = 3,
   VERT_ATTRIB_COLOR1 = 4,
   VERT_ATTRIB_FOG = 5,
   VERT_ATTRIB_COLOR_INDEX = 6,
   VERT_ATTRIB_EDGEFLAG = 7,
   VERT_ATTRIB_TEX0 = 8,
   VERT_ATTRIB_TEX1 = 9,
   VERT_ATTRIB_TEX2 = 10,
   VERT_ATTRIB_TEX3 = 11,
   VERT_ATTRIB_TEX4 = 12,
   VERT_ATTRIB_TEX5 = 13,
   VERT_ATTRIB_TEX6 = 14,
   VERT_ATTRIB_TEX7 = 15,
   VERT_ATTRIB_POINT_SIZE = 16,
   VERT_ATTRIB_GENERIC0 = 17,
   VERT_ATTRIB_GENERIC1 = 18,
   VERT_ATTRIB_GENERIC2 = 19,
   VERT_ATTRIB_GENERIC3 = 20,
   VERT_ATTRIB_GENERIC4 = 21,
   VERT_ATTRIB_GENERIC5 = 22,
   VERT_ATTRIB_GENERIC6 = 23,
   VERT_ATTRIB_GENERIC7 = 24,
   VERT_ATTRIB_GENERIC8 = 25,
   VERT_ATTRIB_GENERIC9 = 26,
   VERT_ATTRIB_GENERIC10 = 27,
   VERT_ATTRIB_GENERIC11 = 28,
   VERT_ATTRIB_GENERIC12 = 29,
   VERT_ATTRIB_GENERIC13 = 30,
   VERT_ATTRIB_GENERIC14 = 31,
   VERT_ATTRIB_GENERIC15 = 32,
   VERT_ATTRIB_MAX = 33
} gl_vert_attrib;

/**
 * Symbolic constats to help iterating over
 * specific blocks of vertex attributes.
 *
 * VERT_ATTRIB_FF
 *   includes all fixed function attributes as well as
 *   the aliased GL_NV_vertex_program shader attributes.
 * VERT_ATTRIB_TEX
 *   include the classic texture coordinate attributes.
 *   Is a subset of VERT_ATTRIB_FF.
 * VERT_ATTRIB_GENERIC_NV
 *   include the NV shader attributes.
 *   Is a subset of VERT_ATTRIB_FF.
 * VERT_ATTRIB_GENERIC
 *   include the OpenGL 2.0+ GLSL generic shader attributes.
 *   These alias the generic GL_ARB_vertex_shader attributes.
 */
#define VERT_ATTRIB_FF(i)           (VERT_ATTRIB_POS + (i))
#define VERT_ATTRIB_FF_MAX          VERT_ATTRIB_GENERIC0

#define VERT_ATTRIB_TEX(i)          (VERT_ATTRIB_TEX0 + (i))
#define VERT_ATTRIB_TEX_MAX         MAX_TEXTURE_COORD_UNITS

#define VERT_ATTRIB_GENERIC_NV(i)   (VERT_ATTRIB_POS + (i))
#define VERT_ATTRIB_GENERIC_NV_MAX  MAX_VERTEX_GENERIC_ATTRIBS

#define VERT_ATTRIB_GENERIC(i)      (VERT_ATTRIB_GENERIC0 + (i))
#define VERT_ATTRIB_GENERIC_MAX     MAX_VERTEX_GENERIC_ATTRIBS



/**
 * Indexes for vertex program result attributes.  Note that
 * _mesa_vert_result_to_frag_attrib() and _mesa_frag_attrib_to_vert_result() make
 * assumptions about the layout of this enum.
 */
typedef enum
{
   VERT_RESULT_HPOS = 0,
   VERT_RESULT_COL0 = 1,
   VERT_RESULT_COL1 = 2,
   VERT_RESULT_FOGC = 3,
   VERT_RESULT_TEX0 = 4,
   VERT_RESULT_TEX1 = 5,
   VERT_RESULT_TEX2 = 6,
   VERT_RESULT_TEX3 = 7,
   VERT_RESULT_TEX4 = 8,
   VERT_RESULT_TEX5 = 9,
   VERT_RESULT_TEX6 = 10,
   VERT_RESULT_TEX7 = 11,
   VERT_RESULT_PSIZ = 12,
   VERT_RESULT_BFC0 = 13,
   VERT_RESULT_BFC1 = 14,
   VERT_RESULT_EDGE = 15,
   VERT_RESULT_CLIP_VERTEX = 16,
   VERT_RESULT_CLIP_DIST0 = 17,
   VERT_RESULT_CLIP_DIST1 = 18,
   VERT_RESULT_VAR0 = 19,  /**< shader varying */
   VERT_RESULT_MAX = (VERT_RESULT_VAR0 + MAX_VARYING)
} gl_vert_result;


/*********************************************/

/**
 * Indexes for geometry program attributes.
 */
typedef enum
{
   GEOM_ATTRIB_POSITION = 0,
   GEOM_ATTRIB_COLOR0 = 1,
   GEOM_ATTRIB_COLOR1 = 2,
   GEOM_ATTRIB_SECONDARY_COLOR0 = 3,
   GEOM_ATTRIB_SECONDARY_COLOR1 = 4,
   GEOM_ATTRIB_FOG_FRAG_COORD = 5,
   GEOM_ATTRIB_POINT_SIZE = 6,
   GEOM_ATTRIB_CLIP_VERTEX = 7,
   GEOM_ATTRIB_PRIMITIVE_ID = 8,
   GEOM_ATTRIB_TEX_COORD = 9,

   GEOM_ATTRIB_VAR0 = 16,
   GEOM_ATTRIB_MAX = (GEOM_ATTRIB_VAR0 + MAX_VARYING)
} gl_geom_attrib;



/**
 * Indexes for geometry program result attributes
 */
typedef enum
{
   GEOM_RESULT_POS  = 0,
   GEOM_RESULT_COL0  = 1,
   GEOM_RESULT_COL1  = 2,
   GEOM_RESULT_SCOL0 = 3,
   GEOM_RESULT_SCOL1 = 4,
   GEOM_RESULT_FOGC = 5,
   GEOM_RESULT_TEX0 = 6,
   GEOM_RESULT_TEX1 = 7,
   GEOM_RESULT_TEX2 = 8,
   GEOM_RESULT_TEX3 = 9,
   GEOM_RESULT_TEX4 = 10,
   GEOM_RESULT_TEX5 = 11,
   GEOM_RESULT_TEX6 = 12,
   GEOM_RESULT_TEX7 = 13,
   GEOM_RESULT_PSIZ = 14,
   GEOM_RESULT_CLPV = 15,
   GEOM_RESULT_PRID = 16,
   GEOM_RESULT_LAYR = 17,
   GEOM_RESULT_VAR0 = 18,  /**< shader varying, should really be 16 */
   /* ### we need to -2 because var0 is 18 instead 16 like in the others */
   GEOM_RESULT_MAX  =  (GEOM_RESULT_VAR0 + MAX_VARYING - 2)
} gl_geom_result;


/**
 * Indexes for fragment program input attributes.  Note that
 * _mesa_vert_result_to_frag_attrib() and frag_attrib_to_vert_result() make
 * assumptions about the layout of this enum.
 */
typedef enum
{
   FRAG_ATTRIB_WPOS = 0,
   FRAG_ATTRIB_COL0 = 1,
   FRAG_ATTRIB_COL1 = 2,
   FRAG_ATTRIB_FOGC = 3,
   FRAG_ATTRIB_TEX0 = 4,
   FRAG_ATTRIB_TEX1 = 5,
   FRAG_ATTRIB_TEX2 = 6,
   FRAG_ATTRIB_TEX3 = 7,
   FRAG_ATTRIB_TEX4 = 8,
   FRAG_ATTRIB_TEX5 = 9,
   FRAG_ATTRIB_TEX6 = 10,
   FRAG_ATTRIB_TEX7 = 11,
   FRAG_ATTRIB_FACE = 12,  /**< front/back face */
   FRAG_ATTRIB_PNTC = 13,  /**< sprite/point coord */
   FRAG_ATTRIB_CLIP_DIST0 = 14,
   FRAG_ATTRIB_CLIP_DIST1 = 15,
   FRAG_ATTRIB_VAR0 = 16,  /**< shader varying */
   FRAG_ATTRIB_MAX = (FRAG_ATTRIB_VAR0 + MAX_VARYING)
} gl_frag_attrib;


/**
 * Convert from a gl_vert_result value to the corresponding gl_frag_attrib.
 *
 * VERT_RESULT_HPOS is converted to FRAG_ATTRIB_WPOS.
 *
 * gl_vert_result values which have no corresponding gl_frag_attrib
 * (VERT_RESULT_PSIZ, VERT_RESULT_BFC0, VERT_RESULT_BFC1, and
 * VERT_RESULT_EDGE) are converted to a value of -1.
 */
static inline int
_mesa_vert_result_to_frag_attrib(gl_vert_result vert_result)
{
   if (vert_result >= VERT_RESULT_CLIP_DIST0)
      return vert_result - VERT_RESULT_CLIP_DIST0 + FRAG_ATTRIB_CLIP_DIST0;
   else if (vert_result <= VERT_RESULT_TEX7)
      return vert_result;
   else
      return -1;
}


/**
 * Convert from a gl_frag_attrib value to the corresponding gl_vert_result.
 *
 * FRAG_ATTRIB_WPOS is converted to VERT_RESULT_HPOS.
 *
 * gl_frag_attrib values which have no corresponding gl_vert_result
 * (FRAG_ATTRIB_FACE and FRAG_ATTRIB_PNTC) are converted to a value of -1.
 */
static inline int
_mesa_frag_attrib_to_vert_result(gl_frag_attrib frag_attrib)
{
   if (frag_attrib <= FRAG_ATTRIB_TEX7)
      return frag_attrib;
   else if (frag_attrib >= FRAG_ATTRIB_CLIP_DIST0)
      return frag_attrib - FRAG_ATTRIB_CLIP_DIST0 + VERT_RESULT_CLIP_DIST0;
   else
      return -1;
}


/**
 * Fragment program results
 */
typedef enum
{
   FRAG_RESULT_DEPTH = 0,
   FRAG_RESULT_STENCIL = 1,
   /* If a single color should be written to all render targets, this
    * register is written.  No FRAG_RESULT_DATAn will be written.
    */
   FRAG_RESULT_COLOR = 2,

   /* FRAG_RESULT_DATAn are the per-render-target (GLSL gl_FragData[n]
    * or ARB_fragment_program fragment.color[n]) color results.  If
    * any are written, FRAG_RESULT_COLOR will not be written.
    */
   FRAG_RESULT_DATA0 = 3,
   FRAG_RESULT_MAX = (FRAG_RESULT_DATA0 + MAX_DRAW_BUFFERS)
} gl_frag_result;



struct gl_config;
	


/**
 * An index for each type of texture object.  These correspond to the GL
 * texture target enums, such as GL_TEXTURE_2D, GL_TEXTURE_CUBE_MAP, etc.
 * Note: the order is from highest priority to lowest priority.
 */
typedef enum
{
   TEXTURE_BUFFER_INDEX,
   TEXTURE_2D_ARRAY_INDEX,
   TEXTURE_1D_ARRAY_INDEX,
   TEXTURE_EXTERNAL_INDEX,
   TEXTURE_CUBE_INDEX,
   TEXTURE_3D_INDEX,
   TEXTURE_RECT_INDEX,
   TEXTURE_2D_INDEX,
   TEXTURE_1D_INDEX,
   NUM_TEXTURE_TARGETS
} gl_texture_index;





struct gl_transform_feedback_varying_info
{
   char *Name;
   GLenum Type;
   GLint Size;
};


/**
 * Per-output info vertex shaders for transform feedback.
 */
struct gl_transform_feedback_output
{
   unsigned OutputRegister;
   unsigned OutputBuffer;
   unsigned NumComponents;

   /** offset (in DWORDs) of this output within the interleaved structure */
   unsigned DstOffset;

   /**
    * Offset into the output register of the data to output.  For example,
    * if NumComponents is 2 and ComponentOffset is 1, then the data to
    * offset is in the y and z components of the output register.
    */
   unsigned ComponentOffset;
};


/** Post-link transform feedback info. */
struct gl_transform_feedback_info
{
   unsigned NumOutputs;

   /**
    * Number of transform feedback buffers in use by this program.
    */
   unsigned NumBuffers;

   struct gl_transform_feedback_output *Outputs;

   /** Transform feedback varyings used for the linking of this shader program.
    *
    * Use for glGetTransformFeedbackVarying().
    */
   struct gl_transform_feedback_varying_info *Varyings;
   GLint NumVarying;

   /**
    * Total number of components stored in each buffer.  This may be used by
    * hardware back-ends to determine the correct stride when interleaving
    * multiple transform feedback outputs in the same buffer.
    */
   unsigned BufferStride[MAX_FEEDBACK_BUFFERS];
};





/**
 * Names of the various vertex/fragment program register files, etc.
 *
 * NOTE: first four tokens must fit into 2 bits (see t_vb_arbprogram.c)
 * All values should fit in a 4-bit field.
 *
 * NOTE: PROGRAM_ENV_PARAM, PROGRAM_STATE_VAR, PROGRAM_NAMED_PARAM,
 * PROGRAM_CONSTANT, and PROGRAM_UNIFORM can all be considered to
 * be "uniform" variables since they can only be set outside glBegin/End.
 * They're also all stored in the same Parameters array.
 */
typedef enum
{
   PROGRAM_TEMPORARY,   /**< machine->Temporary[] */
   PROGRAM_INPUT,       /**< machine->Inputs[] */
   PROGRAM_OUTPUT,      /**< machine->Outputs[] */
   PROGRAM_VARYING,     /**< machine->Inputs[]/Outputs[] */
   PROGRAM_LOCAL_PARAM, /**< gl_program->LocalParams[] */
   PROGRAM_ENV_PARAM,   /**< gl_program->Parameters[] */
   PROGRAM_STATE_VAR,   /**< gl_program->Parameters[] */
   PROGRAM_NAMED_PARAM, /**< gl_program->Parameters[] */
   PROGRAM_CONSTANT,    /**< gl_program->Parameters[] */
   PROGRAM_UNIFORM,     /**< gl_program->Parameters[] */
   PROGRAM_WRITE_ONLY,  /**< A dummy, write-only register */
   PROGRAM_ADDRESS,     /**< machine->AddressReg */
   PROGRAM_SAMPLER,     /**< for shader samplers, compile-time only */
   PROGRAM_SYSTEM_VALUE,/**< InstanceId, PrimitiveID, etc. */
   PROGRAM_UNDEFINED,   /**< Invalid/TBD value */
   PROGRAM_FILE_MAX
} gl_register_file;


/**
 * If the register file is PROGRAM_SYSTEM_VALUE, the register index will be
 * one of these values.
 */
typedef enum
{
   SYSTEM_VALUE_FRONT_FACE,  /**< Fragment shader only (not done yet) */
   SYSTEM_VALUE_VERTEX_ID,   /**< Vertex shader only */
   SYSTEM_VALUE_INSTANCE_ID, /**< Vertex shader only */
   SYSTEM_VALUE_MAX          /**< Number of values */
} gl_system_value;


/**
 * The possible interpolation qualifiers that can be applied to a fragment
 * shader input in GLSL.
 *
 * Note: INTERP_QUALIFIER_NONE must be 0 so that memsetting the
 * gl_fragment_program data structure to 0 causes the default behavior.
 */
enum glsl_interp_qualifier
{
   INTERP_QUALIFIER_NONE = 0,
   INTERP_QUALIFIER_SMOOTH,
   INTERP_QUALIFIER_FLAT,
   INTERP_QUALIFIER_NOPERSPECTIVE
};


/**
 * \brief Layout qualifiers for gl_FragDepth.
 *
 * Extension AMD_conservative_depth allows gl_FragDepth to be redeclared with
 * a layout qualifier.
 *
 * \see enum ir_depth_layout
 */
enum gl_frag_depth_layout
{
   FRAG_DEPTH_LAYOUT_NONE, /**< No layout is specified. */
   FRAG_DEPTH_LAYOUT_ANY,
   FRAG_DEPTH_LAYOUT_GREATER,
   FRAG_DEPTH_LAYOUT_LESS,
   FRAG_DEPTH_LAYOUT_UNCHANGED
};


/**
 * Base class for any kind of program object
 */
struct gl_program
{
   GLuint Id;
   GLubyte *String;  /**< Null-terminated program text */
   GLint RefCount;
   GLenum Target;    /**< GL_VERTEX/FRAGMENT_PROGRAM_ARB, GL_FRAGMENT_PROGRAM_NV */
   GLenum Format;    /**< String encoding format */
   GLboolean Resident;

   /** Numbered local parameters */
   GLfloat LocalParams[MAX_PROGRAM_LOCAL_PARAMS][4];

   /** Map from sampler unit to texture unit (set by glUniform1i()) */
   GLubyte SamplerUnits[MAX_SAMPLERS];

   /** Bitmask of which register files are read/written with indirect
    * addressing.  Mask of (1 << PROGRAM_x) bits.
    */
   GLbitfield IndirectRegisterFiles;

   /** Logical counts */
   /*@{*/
   GLuint NumInstructions;
   GLuint NumTemporaries;
   GLuint NumParameters;
   GLuint NumAttributes;
   GLuint NumAddressRegs;
   GLuint NumAluInstructions;
   GLuint NumTexInstructions;
   GLuint NumTexIndirections;
   /*@}*/
   /** Native, actual h/w counts */
   /*@{*/
   GLuint NumNativeInstructions;
   GLuint NumNativeTemporaries;
   GLuint NumNativeParameters;
   GLuint NumNativeAttributes;
   GLuint NumNativeAddressRegs;
   GLuint NumNativeAluInstructions;
   GLuint NumNativeTexInstructions;
   GLuint NumNativeTexIndirections;
   /*@}*/
};


/** Vertex program object */
struct gl_vertex_program
{
   struct gl_program Base;   /**< base class */
   GLboolean IsNVProgram;    /**< is this a GL_NV_vertex_program program? */
   GLboolean IsPositionInvariant;
   GLboolean UsesClipDistance;
};


/** Geometry program object */
struct gl_geometry_program
{
   struct gl_program Base;   /**< base class */

   GLint VerticesOut;
   GLenum InputType;  /**< GL_POINTS, GL_LINES, GL_LINES_ADJACENCY_ARB,
                           GL_TRIANGLES, or GL_TRIANGLES_ADJACENCY_ARB */
   GLenum OutputType; /**< GL_POINTS, GL_LINE_STRIP or GL_TRIANGLE_STRIP */
};




/** Set by #pragma directives */
struct gl_sl_pragmas
{
   GLboolean IgnoreOptimize;  /**< ignore #pragma optimize(on/off) ? */
   GLboolean IgnoreDebug;     /**< ignore #pragma debug(on/off) ? */
   GLboolean Optimize;  /**< defaults on */
   GLboolean Debug;     /**< defaults off */
};


/**
 * A GLSL vertex or fragment shader object.
 */
struct gl_shader
{
   GLenum Type;  /**< GL_FRAGMENT_SHADER || GL_VERTEX_SHADER || GL_GEOMETRY_SHADER_ARB (first field!) */
   GLuint Name;  /**< AKA the handle */
   GLint RefCount;  /**< Reference count */
   GLboolean DeletePending;
   GLboolean CompileStatus;
   const char *Source;  /**< Source code string */
   GLuint SourceChecksum;       /**< for debug/logging purposes */
   struct gl_program *Program;  /**< Post-compile assembly code */
   char *InfoLog;
   struct gl_sl_pragmas Pragmas;

   unsigned Version;       /**< GLSL version used for linking */

   /**
    * \name Sampler tracking
    *
    * \note Each of these fields is only set post-linking.
    */
   /*@{*/
   unsigned num_samplers;	/**< Number of samplers used by this shader. */
   GLbitfield active_samplers;	/**< Bitfield of which samplers are used */
   GLbitfield shadow_samplers;	/**< Samplers used for shadow sampling. */
   /*@}*/

   /**
    * Number of uniform components used by this shader.
    *
    * This field is only set post-linking.
    */
   unsigned num_uniform_components;

   /**
    * This shader's uniform block information.
    *
    * The offsets of the variables are assigned only for shaders in a program's
    * _LinkedShaders[].
    */
   struct gl_uniform_block *UniformBlocks;
   unsigned NumUniformBlocks;

   struct exec_list *ir;
   struct glsl_symbol_table *symbols;

   /** Shaders containing built-in functions that are used for linking. */
   struct gl_shader *builtins_to_link[16];
   unsigned num_builtins_to_link;
};


/**
 * Shader stages. Note that these will become 5 with tessellation.
 * These MUST have the same values as gallium's PIPE_SHADER_*
 */
typedef enum
{
   MESA_SHADER_VERTEX = 0,
   MESA_SHADER_FRAGMENT = 1,
   MESA_SHADER_GEOMETRY = 2,
   MESA_SHADER_TYPES = 3
} gl_shader_type;

struct gl_uniform_buffer_variable
{
   char *Name;
   const struct glsl_type *Type;
   unsigned int Buffer;
   unsigned int Offset;
   GLboolean RowMajor;
};

struct gl_uniform_block
{
   /** Declared name of the uniform block */
   char *Name;

   /** Array of supplemental information about UBO ir_variables. */
   struct gl_uniform_buffer_variable *Uniforms;
   GLuint NumUniforms;

   /**
    * Index (GL_UNIFORM_BLOCK_BINDING) into ctx->UniformBufferBindings[] to use
    * with glBindBufferBase to bind a buffer object to this uniform block.  When
    * updated in the program, _NEW_BUFFER_OBJECT will be set.
    */
   GLuint Binding;

   /**
    * Minimum size of a buffer object to back this uniform buffer
    * (GL_UNIFORM_BLOCK_DATA_SIZE).
    */
   GLuint UniformBufferSize;
};

/**
 * A GLSL program object.
 * Basically a linked collection of vertex and fragment shaders.
 */
struct gl_shader_program
{
   GLenum Type;  /**< Always GL_SHADER_PROGRAM (internal token) */
   GLuint Name;  /**< aka handle or ID */
   GLint RefCount;  /**< Reference count */
   GLboolean DeletePending;

   /**
    * Flags that the linker should not reject the program if it lacks
    * a vertex or fragment shader.  GLES2 doesn't allow separate
    * shader objects, and would reject them.  However, we internally
    * build separate shader objects for fixed function programs, which
    * we use for drivers/common/meta.c and for handling
    * _mesa_update_state with no program bound (for example in
    * glClear()).
    */
   GLboolean InternalSeparateShader;

   GLuint NumShaders;          /**< number of attached shaders */
   struct gl_shader **Shaders; /**< List of attached the shaders */

   /**
    * User-defined attribute bindings
    *
    * These are set via \c glBindAttribLocation and are used to direct the
    * GLSL linker.  These are \b not the values used in the compiled shader,
    * and they are \b not the values returned by \c glGetAttribLocation.
    */
   struct string_to_uint_map *AttributeBindings;

   /**
    * User-defined fragment data bindings
    *
    * These are set via \c glBindFragDataLocation and are used to direct the
    * GLSL linker.  These are \b not the values used in the compiled shader,
    * and they are \b not the values returned by \c glGetFragDataLocation.
    */
   struct string_to_uint_map *FragDataBindings;
   struct string_to_uint_map *FragDataIndexBindings;

   /**
    * Transform feedback varyings last specified by
    * glTransformFeedbackVaryings().
    *
    * For the current set of transform feeedback varyings used for transform
    * feedback output, see LinkedTransformFeedback.
    */
   struct {
      GLenum BufferMode;
      GLuint NumVarying;
      char **VaryingNames;  /**< Array [NumVarying] of char * */
   } TransformFeedback;

   /** Post-link transform feedback info. */
   struct gl_transform_feedback_info LinkedTransformFeedback;

   /** Post-link gl_FragDepth layout for ARB_conservative_depth. */
   enum gl_frag_depth_layout FragDepthLayout;

   /** Geometry shader state - copied into gl_geometry_program at link time */
   struct {
      GLint VerticesOut;
      GLenum InputType;  /**< GL_POINTS, GL_LINES, GL_LINES_ADJACENCY_ARB,
                              GL_TRIANGLES, or GL_TRIANGLES_ADJACENCY_ARB */
      GLenum OutputType; /**< GL_POINTS, GL_LINE_STRIP or GL_TRIANGLE_STRIP */
   } Geom;

   /** Vertex shader state - copied into gl_vertex_program at link time */
   struct {
      GLboolean UsesClipDistance; /**< True if gl_ClipDistance is written to. */
      GLuint ClipDistanceArraySize; /**< Size of the gl_ClipDistance array, or
                                         0 if not present. */
   } Vert;

   /* post-link info: */
   unsigned NumUserUniformStorage;
   struct gl_uniform_storage *UniformStorage;

   struct gl_uniform_block *UniformBlocks;
   unsigned NumUniformBlocks;

   /**
    * Indices into the _LinkedShaders's UniformBlocks[] array for each stage
    * they're used in, or -1.
    *
    * This is used to maintain the Binding values of the stage's UniformBlocks[]
    * and to answer the GL_UNIFORM_BLOCK_REFERENCED_BY_*_SHADER queries.
    */
   int *UniformBlockStageIndex[MESA_SHADER_TYPES];

   /**
    * Map of active uniform names to locations
    *
    * Maps any active uniform that is not an array element to a location.
    * Each active uniform, including individual structure members will appear
    * in this map.  This roughly corresponds to the set of names that would be
    * enumerated by \c glGetActiveUniform.
    */
   struct string_to_uint_map *UniformHash;

   /**
    * Map from sampler unit to texture unit (set by glUniform1i())
    *
    * A sampler unit is associated with each sampler uniform by the linker.
    * The sampler unit associated with each uniform is stored in the
    * \c gl_uniform_storage::sampler field.
    */
   GLubyte SamplerUnits[MAX_SAMPLERS];
   /** Which texture target is being sampled (TEXTURE_1D/2D/3D/etc_INDEX) */
   gl_texture_index SamplerTargets[MAX_SAMPLERS];

   GLboolean LinkStatus;   /**< GL_LINK_STATUS */
   GLboolean Validated;
   GLboolean _Used;        /**< Ever used for drawing? */
   char *InfoLog;

   unsigned Version;       /**< GLSL version used for linking */

   /**
    * Per-stage shaders resulting from the first stage of linking.
    *
    * Set of linked shaders for this program.  The array is accessed using the
    * \c MESA_SHADER_* defines.  Entries for non-existent stages will be
    * \c NULL.
    */
   struct gl_shader *_LinkedShaders[MESA_SHADER_TYPES];
};   


#define GLSL_DUMP      0x1  /**< Dump shaders to stdout */
#define GLSL_LOG       0x2  /**< Write shaders to files */
#define GLSL_OPT       0x4  /**< Force optimizations (override pragmas) */
#define GLSL_NO_OPT    0x8  /**< Force no optimizations (override pragmas) */
#define GLSL_UNIFORMS 0x10  /**< Print glUniform calls */
#define GLSL_NOP_VERT 0x20  /**< Force no-op vertex shaders */
#define GLSL_NOP_FRAG 0x40  /**< Force no-op fragment shaders */
#define GLSL_REPORT_ERRORS 0x100  /**< Print compilation errors */



/**
 * Compiler options for a single GLSL shaders type
 */
struct gl_shader_compiler_options
{
   /** Driver-selectable options: */
   GLboolean EmitCondCodes;             /**< Use condition codes? */
   GLboolean EmitNVTempInitialization;  /**< 0-fill NV temp registers */
   GLboolean EmitNoLoops;
   GLboolean EmitNoFunctions;
   GLboolean EmitNoCont;                  /**< Emit CONT opcode? */
   GLboolean EmitNoMainReturn;            /**< Emit CONT/RET opcodes? */
   GLboolean EmitNoNoise;                 /**< Emit NOISE opcodes? */
   GLboolean EmitNoPow;                   /**< Emit POW opcodes? */
   GLboolean LowerClipDistance; /**< Lower gl_ClipDistance from float[8] to vec4[2]? */

   /**
    * \name Forms of indirect addressing the driver cannot do.
    */
   /*@{*/
   GLboolean EmitNoIndirectInput;   /**< No indirect addressing of inputs */
   GLboolean EmitNoIndirectOutput;  /**< No indirect addressing of outputs */
   GLboolean EmitNoIndirectTemp;    /**< No indirect addressing of temps */
   GLboolean EmitNoIndirectUniform; /**< No indirect addressing of constants */
   /*@}*/

   GLuint MaxIfDepth;               /**< Maximum nested IF blocks */
   GLuint MaxUnrollIterations;

   struct gl_sl_pragmas DefaultPragmas; /**< Default #pragma settings */
};






/**
 * Limits for vertex, geometry and fragment programs/shaders.
 */
struct gl_program_constants
{
   /* logical limits */
   GLuint MaxInstructions;
   GLuint MaxAluInstructions;
   GLuint MaxTexInstructions;
   GLuint MaxTexIndirections;
   GLuint MaxAttribs;
   GLuint MaxTemps;
   GLuint MaxAddressRegs;
   GLuint MaxAddressOffset;  /**< [-MaxAddressOffset, MaxAddressOffset-1] */
   GLuint MaxParameters;
   GLuint MaxLocalParams;
   GLuint MaxEnvParams;
   /* native/hardware limits */
   GLuint MaxNativeInstructions;
   GLuint MaxNativeAluInstructions;
   GLuint MaxNativeTexInstructions;
   GLuint MaxNativeTexIndirections;
   GLuint MaxNativeAttribs;
   GLuint MaxNativeTemps;
   GLuint MaxNativeAddressRegs;
   GLuint MaxNativeParameters;
   /* For shaders */
   GLuint MaxUniformComponents;  /**< Usually == MaxParameters * 4 */
   /* GL_ARB_uniform_buffer_object */
   GLuint MaxUniformBlocks;
   GLuint MaxCombinedUniformComponents;
};


/**
 * Constants which may be overridden by device driver during context creation
 * but are never changed after that.
 */
struct gl_constants
{
   GLint MaxTextureMbytes;      /**< Max memory per image, in MB */
   GLint MaxTextureLevels;      /**< Max mipmap levels. */ 
   GLint Max3DTextureLevels;    /**< Max mipmap levels for 3D textures */
   GLint MaxCubeTextureLevels;  /**< Max mipmap levels for cube textures */
   GLint MaxArrayTextureLayers; /**< Max layers in array textures */
   GLint MaxTextureRectSize;    /**< Max rectangle texture size, in pixes */
   GLuint MaxTextureCoordUnits;
   GLuint MaxTextureImageUnits;
   GLuint MaxVertexTextureImageUnits;
   GLuint MaxCombinedTextureImageUnits;
   GLuint MaxGeometryTextureImageUnits;
   GLuint MaxTextureUnits;           /**< = MIN(CoordUnits, ImageUnits) */
   GLfloat MaxTextureMaxAnisotropy;  /**< GL_EXT_texture_filter_anisotropic */
   GLfloat MaxTextureLodBias;        /**< GL_EXT_texture_lod_bias */
   GLuint MaxTextureBufferSize;      /**< GL_ARB_texture_buffer_object */

   GLuint MaxArrayLockSize;

   GLint SubPixelBits;

   GLfloat MinPointSize, MaxPointSize;	     /**< aliased */
   GLfloat MinPointSizeAA, MaxPointSizeAA;   /**< antialiased */
   GLfloat PointSizeGranularity;
   GLfloat MinLineWidth, MaxLineWidth;       /**< aliased */
   GLfloat MinLineWidthAA, MaxLineWidthAA;   /**< antialiased */
   GLfloat LineWidthGranularity;

   GLuint MaxColorTableSize;

   GLuint MaxClipPlanes;
   GLuint MaxLights;
   GLfloat MaxShininess;                     /**< GL_NV_light_max_exponent */
   GLfloat MaxSpotExponent;                  /**< GL_NV_light_max_exponent */

   GLuint MaxViewportWidth, MaxViewportHeight;

   struct gl_program_constants VertexProgram;   /**< GL_ARB_vertex_program */
   struct gl_program_constants FragmentProgram; /**< GL_ARB_fragment_program */
   struct gl_program_constants GeometryProgram;  /**< GL_ARB_geometry_shader4 */
   GLuint MaxProgramMatrices;
   GLuint MaxProgramMatrixStackDepth;

   struct {
      GLuint SamplesPassed;
      GLuint TimeElapsed;
      GLuint Timestamp;
      GLuint PrimitivesGenerated;
      GLuint PrimitivesWritten;
   } QueryCounterBits;

   /** vertex array / buffer object bounds checking */
   GLboolean CheckArrayBounds;

   GLuint MaxDrawBuffers;    /**< GL_ARB_draw_buffers */

   GLuint MaxColorAttachments;   /**< GL_EXT_framebuffer_object */
   GLuint MaxRenderbufferSize;   /**< GL_EXT_framebuffer_object */
   GLuint MaxSamples;            /**< GL_ARB_framebuffer_object */

   /** Number of varying vectors between vertex and fragment shaders */
   GLuint MaxVarying;
   GLuint MaxVertexVaryingComponents;   /**< Between vert and geom shader */
   GLuint MaxGeometryVaryingComponents; /**< Between geom and frag shader */

   /** @{
    * GL_ARB_uniform_buffer_object
    */
   GLuint MaxCombinedUniformBlocks;
   GLuint MaxUniformBufferBindings;
   GLuint MaxUniformBlockSize;
   GLuint UniformBufferOffsetAlignment;
   /** @} */

   /** GL_ARB_geometry_shader4 */
   GLuint MaxGeometryOutputVertices;
   GLuint MaxGeometryTotalOutputComponents;

   GLuint GLSLVersion;  /**< GLSL version supported (ex: 120 = 1.20) */

   /**
    * Changes default GLSL extension behavior from "error" to "warn".  It's out
    * of spec, but it can make some apps work that otherwise wouldn't.
    */
   GLboolean ForceGLSLExtensionsWarn;

   /**
    * Does the driver support real 32-bit integers?  (Otherwise, integers are
    * simulated via floats.)
    */
   GLboolean NativeIntegers;

   /**
    * If the driver supports real 32-bit integers, what integer value should be
    * used for boolean true in uniform uploads?  (Usually 1 or ~0.)
    */
   GLuint UniformBooleanTrue;

   /** Which texture units support GL_ATI_envmap_bumpmap as targets */
   GLbitfield SupportedBumpUnits;

   /** GL_EXT_provoking_vertex */
   GLboolean QuadsFollowProvokingVertexConvention;

   /** OpenGL version 3.0 */
   GLbitfield ContextFlags;  /**< Ex: GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT */

   /** OpenGL version 3.2 */
   GLbitfield ProfileMask;   /**< Mask of CONTEXT_x_PROFILE_BIT */

   /** GL_EXT_transform_feedback */
   GLuint MaxTransformFeedbackBuffers;
   GLuint MaxTransformFeedbackSeparateComponents;
   GLuint MaxTransformFeedbackInterleavedComponents;
   GLuint MaxVertexStreams;

   /** GL_EXT_gpu_shader4 */
   GLint MinProgramTexelOffset, MaxProgramTexelOffset;

   /* GL_ARB_robustness */
   GLenum ResetStrategy;

   /* GL_ARB_blend_func_extended */
   GLuint MaxDualSourceDrawBuffers;

   /**
    * Whether the implementation strips out and ignores texture borders.
    *
    * Many GPU hardware implementations don't support rendering with texture
    * borders and mipmapped textures.  (Note: not static border color, but the
    * old 1-pixel border around each edge).  Implementations then have to do
    * slow fallbacks to be correct, or just ignore the border and be fast but
    * wrong.  Setting the flag strips the border off of TexImage calls,
    * providing "fast but wrong" at significantly reduced driver complexity.
    *
    * Texture borders are deprecated in GL 3.0.
    **/
   GLboolean StripTextureBorder;

   /**
    * For drivers which can do a better job at eliminating unused varyings
    * and uniforms than the GLSL compiler.
    *
    * XXX Remove these as soon as a better solution is available.
    */
   GLboolean GLSLSkipStrictMaxVaryingLimitCheck;
   GLboolean GLSLSkipStrictMaxUniformLimitCheck;

   /**
    * Force software support for primitive restart in the VBO module.
    */
   GLboolean PrimitiveRestartInSoftware;
};


/**
 * Enable flag for each OpenGL extension.  Different device drivers will
 * enable different extensions at runtime.
 */
struct gl_extensions
{
   GLboolean dummy;  /* don't remove this! */
   GLboolean dummy_true;  /* Set true by _mesa_init_extensions(). */
   GLboolean dummy_false; /* Set false by _mesa_init_extensions(). */
   GLboolean ANGLE_texture_compression_dxt;
   GLboolean ARB_ES2_compatibility;
   GLboolean ARB_base_instance;
   GLboolean ARB_blend_func_extended;
   GLboolean ARB_color_buffer_float;
   GLboolean ARB_conservative_depth;
   GLboolean ARB_copy_buffer;
   GLboolean ARB_depth_buffer_float;
   GLboolean ARB_depth_clamp;
   GLboolean ARB_depth_texture;
   GLboolean ARB_draw_buffers_blend;
   GLboolean ARB_draw_elements_base_vertex;
   GLboolean ARB_draw_instanced;
   GLboolean ARB_fragment_coord_conventions;
   GLboolean ARB_fragment_program;
   GLboolean ARB_fragment_program_shadow;
   GLboolean ARB_fragment_shader;
   GLboolean ARB_framebuffer_object;
   GLboolean ARB_explicit_attrib_location;
   GLboolean ARB_geometry_shader4;
   GLboolean ARB_half_float_pixel;
   GLboolean ARB_half_float_vertex;
   GLboolean ARB_instanced_arrays;
   GLboolean ARB_map_buffer_range;
   GLboolean ARB_occlusion_query;
   GLboolean ARB_occlusion_query2;
   GLboolean ARB_point_sprite;
   GLboolean ARB_seamless_cube_map;
   GLboolean ARB_shader_bit_encoding;
   GLboolean ARB_shader_objects;
   GLboolean ARB_shader_stencil_export;
   GLboolean ARB_shader_texture_lod;
   GLboolean ARB_shading_language_100;
   GLboolean ARB_shadow;
   GLboolean ARB_sync;
   GLboolean ARB_texture_border_clamp;
   GLboolean ARB_texture_buffer_object;
   GLboolean ARB_texture_compression_rgtc;
   GLboolean ARB_texture_cube_map;
   GLboolean ARB_texture_env_combine;
   GLboolean ARB_texture_env_crossbar;
   GLboolean ARB_texture_env_dot3;
   GLboolean ARB_texture_float;
   GLboolean ARB_texture_multisample;
   GLboolean ARB_texture_non_power_of_two;
   GLboolean ARB_texture_rg;
   GLboolean ARB_texture_rgb10_a2ui;
   GLboolean ARB_texture_storage;
   GLboolean ARB_timer_query;
   GLboolean ARB_transform_feedback2;
   GLboolean ARB_transform_feedback3;
   GLboolean ARB_transform_feedback_instanced;
   GLboolean ARB_transpose_matrix;
   GLboolean ARB_uniform_buffer_object;
   GLboolean ARB_vertex_program;
   GLboolean ARB_vertex_shader;
   GLboolean ARB_vertex_type_2_10_10_10_rev;
   GLboolean ARB_window_pos;
   GLboolean EXT_blend_color;
   GLboolean EXT_blend_equation_separate;
   GLboolean EXT_blend_func_separate;
   GLboolean EXT_blend_minmax;
   GLboolean EXT_clip_volume_hint;
   GLboolean EXT_compiled_vertex_array;
   GLboolean EXT_depth_bounds_test;
   GLboolean EXT_draw_buffers2;
   GLboolean EXT_draw_range_elements;
   GLboolean EXT_fog_coord;
   GLboolean EXT_framebuffer_blit;
   GLboolean EXT_framebuffer_multisample;
   GLboolean EXT_framebuffer_object;
   GLboolean EXT_framebuffer_sRGB;
   GLboolean EXT_gpu_program_parameters;
   GLboolean EXT_gpu_shader4;
   GLboolean EXT_packed_depth_stencil;
   GLboolean EXT_packed_float;
   GLboolean EXT_packed_pixels;
   GLboolean EXT_pixel_buffer_object;
   GLboolean EXT_point_parameters;
   GLboolean EXT_provoking_vertex;
   GLboolean EXT_rescale_normal;
   GLboolean EXT_shadow_funcs;
   GLboolean EXT_secondary_color;
   GLboolean EXT_separate_shader_objects;
   GLboolean EXT_separate_specular_color;
   GLboolean EXT_stencil_two_side;
   GLboolean EXT_texture3D;
   GLboolean EXT_texture_array;
   GLboolean EXT_texture_compression_latc;
   GLboolean EXT_texture_compression_s3tc;
   GLboolean EXT_texture_env_dot3;
   GLboolean EXT_texture_filter_anisotropic;
   GLboolean EXT_texture_integer;
   GLboolean EXT_texture_mirror_clamp;
   GLboolean EXT_texture_shared_exponent;
   GLboolean EXT_texture_snorm;
   GLboolean EXT_texture_sRGB;
   GLboolean EXT_texture_sRGB_decode;
   GLboolean EXT_texture_swizzle;
   GLboolean EXT_transform_feedback;
   GLboolean EXT_timer_query;
   GLboolean EXT_vertex_array_bgra;
   GLboolean OES_standard_derivatives;
   GLboolean EXT_shadow_samplers;
   GLboolean EXT_frag_depth;
   /* vendor extensions */
   GLboolean AMD_seamless_cubemap_per_texture;
   GLboolean APPLE_packed_pixels;
   GLboolean APPLE_object_purgeable;
   GLboolean ATI_envmap_bumpmap;
   GLboolean ATI_texture_compression_3dc;
   GLboolean ATI_texture_mirror_once;
   GLboolean ATI_texture_env_combine3;
   GLboolean ATI_fragment_shader;
   GLboolean ATI_separate_stencil;
   GLboolean IBM_rasterpos_clip;
   GLboolean IBM_multimode_draw_arrays;
   GLboolean MESA_pack_invert;
   GLboolean MESA_resize_buffers;
   GLboolean MESA_ycbcr_texture;
   GLboolean MESA_texture_array;
   GLboolean NV_blend_square;
   GLboolean NV_conditional_render;
   GLboolean NV_fog_distance;
   GLboolean NV_fragment_program;
   GLboolean NV_fragment_program_option;
   GLboolean NV_light_max_exponent;
   GLboolean NV_point_sprite;
   GLboolean NV_primitive_restart;
   GLboolean NV_read_buffer;
   GLboolean NV_texture_barrier;
   GLboolean NV_texgen_reflection;
   GLboolean NV_texture_env_combine4;
   GLboolean NV_texture_rectangle;
   GLboolean NV_vertex_program;
   GLboolean NV_vertex_program1_1;
   GLboolean SGIS_texture_lod;
   GLboolean TDFX_texture_compression_FXT1;
   GLboolean S3_s3tc;
   GLboolean OES_EGL_image;
   GLboolean OES_draw_texture;
   GLboolean OES_EGL_image_external;
   GLboolean OES_compressed_ETC1_RGB8_texture;
   GLboolean extension_sentinel;
   /** The extension string */
   const GLubyte *String;
   /** Number of supported extensions */
   GLuint Count;
};





/* This has to be included here. */
#include "dd.h"





typedef enum {
   SHADER_ERROR_UNKNOWN,
   SHADER_ERROR_COUNT
} gl_shader_error;
	
/**
 * Enum for the OpenGL APIs we know about and may support.
 */
typedef enum
{
   API_OPENGL,      /* legacy / compatibility contexts */
   API_OPENGLES,
   API_OPENGLES2,
   API_OPENGL_CORE,
} gl_api;



/**
 * Mesa rendering context.
 *
 * This is the central context data structure for Mesa.  Almost all
 * OpenGL state is contained in this structure.
 * Think of this as a base class from which device drivers will derive
 * sub classes.
 *
 * The struct gl_context typedef names this structure.
 */
struct gl_context
{
   gl_api API;

   /**
    * Device driver function pointer table
    */
   struct dd_function_table Driver;

   /** Core/Driver constants */
   struct gl_constants Const;

   /** Extension information */
   struct gl_extensions Extensions;

   /** GL version integer, for example 31 for GL 3.1, or 20 for GLES 2.0. */
   GLuint Version;
   char *VersionString;


   struct gl_shader_compiler_options ShaderCompilerOptions[MESA_SHADER_TYPES];

   GLenum ErrorValue;        /**< Last error code */
};


#ifdef DEBUG
extern int MESA_VERBOSE;
extern int MESA_DEBUG_FLAGS;
# define MESA_FUNCTION __FUNCTION__
#else
# define MESA_VERBOSE 0
# define MESA_DEBUG_FLAGS 0
# define MESA_FUNCTION "a function"
# ifndef NDEBUG
#  define NDEBUG
# endif
#endif


/** The MESA_VERBOSE var is a bitmask of these flags */
enum _verbose
{
   VERBOSE_VARRAY		= 0x0001,
   VERBOSE_TEXTURE		= 0x0002,
   VERBOSE_MATERIAL		= 0x0004,
   VERBOSE_PIPELINE		= 0x0008,
   VERBOSE_DRIVER		= 0x0010,
   VERBOSE_STATE		= 0x0020,
   VERBOSE_API			= 0x0040,
   VERBOSE_DISPLAY_LIST		= 0x0100,
   VERBOSE_LIGHTING		= 0x0200,
   VERBOSE_PRIMS		= 0x0400,
   VERBOSE_VERTS		= 0x0800,
   VERBOSE_DISASSEM		= 0x1000,
   VERBOSE_DRAW                 = 0x2000,
   VERBOSE_SWAPBUFFERS          = 0x4000
};


/** The MESA_DEBUG_FLAGS var is a bitmask of these flags */
enum _debug
{
   DEBUG_SILENT                 = (1 << 0),
   DEBUG_ALWAYS_FLUSH		= (1 << 1),
   DEBUG_INCOMPLETE_TEXTURE     = (1 << 2),
   DEBUG_INCOMPLETE_FBO         = (1 << 3)
};



#ifdef __cplusplus
}
#endif

#endif /* MTYPES_H */
