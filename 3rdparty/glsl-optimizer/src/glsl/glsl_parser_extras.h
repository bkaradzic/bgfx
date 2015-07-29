/*
 * Copyright © 2010 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#pragma once
#ifndef GLSL_PARSER_EXTRAS_H
#define GLSL_PARSER_EXTRAS_H

/*
 * Most of the definitions here only apply to C++
 */
#ifdef __cplusplus


#include <stdlib.h>
#include "glsl_symbol_table.h"

struct gl_context;

struct glsl_switch_state {
   /** Temporary variables needed for switch statement. */
   ir_variable *test_var;
   ir_variable *is_fallthru_var;
   ir_variable *is_break_var;
   class ast_switch_statement *switch_nesting_ast;

   /** Used to set condition if 'default' label should be chosen. */
   ir_variable *run_default;

   /** Table of constant values already used in case labels */
   struct hash_table *labels_ht;
   class ast_case_label *previous_default;

   bool is_switch_innermost; // if switch stmt is closest to break, ...
};

const char *
glsl_compute_version_string(void *mem_ctx, bool is_es, unsigned version);

typedef struct YYLTYPE {
   int first_line;
   int first_column;
   int last_line;
   int last_column;
   unsigned source;
} YYLTYPE;
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1

extern void _mesa_glsl_error(YYLTYPE *locp, _mesa_glsl_parse_state *state,
			     const char *fmt, ...);


struct _mesa_glsl_parse_state {
   _mesa_glsl_parse_state(struct gl_context *_ctx, gl_shader_stage stage,
			  void *mem_ctx);

   DECLARE_RALLOC_CXX_OPERATORS(_mesa_glsl_parse_state);

   /**
    * Generate a string representing the GLSL version currently being compiled
    * (useful for error messages).
    */
   const char *get_version_string()
   {
      return glsl_compute_version_string(this, this->es_shader,
                                         this->language_version);
   }

   /**
    * Determine whether the current GLSL version is sufficiently high to
    * support a certain feature.
    *
    * \param required_glsl_version is the desktop GLSL version that is
    * required to support the feature, or 0 if no version of desktop GLSL
    * supports the feature.
    *
    * \param required_glsl_es_version is the GLSL ES version that is required
    * to support the feature, or 0 if no version of GLSL ES suports the
    * feature.
    */
   bool is_version(unsigned required_glsl_version,
                   unsigned required_glsl_es_version) const
   {
      unsigned required_version = this->es_shader ?
         required_glsl_es_version : required_glsl_version;
      return required_version != 0
         && this->language_version >= required_version;
   }

   bool check_version(unsigned required_glsl_version,
                      unsigned required_glsl_es_version,
                      YYLTYPE *locp, const char *fmt, ...) PRINTFLIKE(5, 6);

   bool check_precision_qualifiers_allowed(YYLTYPE *locp)
   {
      return check_version(130, 100, locp,
                           "precision qualifiers are forbidden");
   }

   bool check_bitwise_operations_allowed(YYLTYPE *locp)
   {
      return check_version(130, 300, locp, "bit-wise operations are forbidden");
   }

   bool check_explicit_attrib_stream_allowed(YYLTYPE *locp)
   {
      if (!this->has_explicit_attrib_stream()) {
         const char *const requirement = "GL_ARB_gpu_shader5 extension or GLSL 400";

         _mesa_glsl_error(locp, this, "explicit stream requires %s",
                          requirement);
         return false;
      }

      return true;
   }

   bool check_explicit_attrib_location_allowed(YYLTYPE *locp,
                                               const ir_variable *var)
   {
      if (!this->has_explicit_attrib_location()) {
         const char *const requirement = this->es_shader
            ? "GLSL ES 300"
            : "GL_ARB_explicit_attrib_location extension or GLSL 330";

         _mesa_glsl_error(locp, this, "%s explicit location requires %s",
                          mode_string(var), requirement);
         return false;
      }

      return true;
   }

   bool check_separate_shader_objects_allowed(YYLTYPE *locp,
                                              const ir_variable *var)
   {
      if (!this->has_separate_shader_objects()) {
         const char *const requirement = this->es_shader
            ? "GL_EXT_separate_shader_objects extension"
            : "GL_ARB_separate_shader_objects extension or GLSL 420";

         _mesa_glsl_error(locp, this, "%s explicit location requires %s",
                          mode_string(var), requirement);
         return false;
      }

      return true;
   }

   bool check_explicit_uniform_location_allowed(YYLTYPE *locp,
                                                const ir_variable *)
   {
      if (!this->has_explicit_attrib_location() ||
          !this->ARB_explicit_uniform_location_enable) {
         _mesa_glsl_error(locp, this,
                          "uniform explicit location requires "
                          "GL_ARB_explicit_uniform_location and either "
                          "GL_ARB_explicit_attrib_location or GLSL 330.");
         return false;
      }

      return true;
   }

   bool has_explicit_attrib_stream() const
   {
      return ARB_gpu_shader5_enable || is_version(400, 0);
   }

   bool has_explicit_attrib_location() const
   {
      return ARB_explicit_attrib_location_enable || is_version(330, 300);
   }

   bool has_uniform_buffer_objects() const
   {
      return ARB_uniform_buffer_object_enable || is_version(140, 300);
   }

   bool has_separate_shader_objects() const
   {
      return ARB_separate_shader_objects_enable || is_version(410, 0)
         || EXT_separate_shader_objects_enable;
   }

   void process_version_directive(YYLTYPE *locp, int version,
                                  const char *ident);

   struct gl_context *const ctx;
   void *scanner;
   exec_list translation_unit;
   glsl_symbol_table *symbols;

   unsigned num_supported_versions;
   struct {
      unsigned ver;
      bool es;
   } supported_versions[12];

   bool es_shader;
   bool metal_target;
   unsigned language_version;
   bool had_version_string;
   bool had_float_precision;
   gl_shader_stage stage;

   /**
    * Number of nested struct_specifier levels
    *
    * Outside a struct_specifier, this is zero.
    */
   unsigned struct_specifier_depth;

   /**
    * Default uniform layout qualifiers tracked during parsing.
    * Currently affects uniform blocks and uniform buffer variables in
    * those blocks.
    */
   struct ast_type_qualifier *default_uniform_qualifier;

   /**
    * Variables to track different cases if a fragment shader redeclares
    * built-in variable gl_FragCoord.
    *
    * Note: These values are computed at ast_to_hir time rather than at parse
    * time.
    */
   bool fs_redeclares_gl_fragcoord;
   bool fs_origin_upper_left;
   bool fs_pixel_center_integer;
   bool fs_redeclares_gl_fragcoord_with_no_layout_qualifiers;

   /**
    * True if a geometry shader input primitive type was specified using a
    * layout directive.
    *
    * Note: this value is computed at ast_to_hir time rather than at parse
    * time.
    */
   bool gs_input_prim_type_specified;

   /** Input layout qualifiers from GLSL 1.50. (geometry shader controls)*/
   struct ast_type_qualifier *in_qualifier;

   /**
    * True if a compute shader input local size was specified using a layout
    * directive.
    *
    * Note: this value is computed at ast_to_hir time rather than at parse
    * time.
    */
   bool cs_input_local_size_specified;

   /**
    * If cs_input_local_size_specified is true, the local size that was
    * specified.  Otherwise ignored.
    */
   unsigned cs_input_local_size[3];

   /** Output layout qualifiers from GLSL 1.50. (geometry shader controls)*/
   struct ast_type_qualifier *out_qualifier;

   /**
    * Printable list of GLSL versions supported by the current context
    *
    * \note
    * This string should probably be generated per-context instead of per
    * invokation of the compiler.  This should be changed when the method of
    * tracking supported GLSL versions changes.
    */
   const char *supported_version_string;

   /**
    * Implementation defined limits that affect built-in variables, etc.
    *
    * \sa struct gl_constants (in mtypes.h)
    */
   struct {
      /* 1.10 */
      unsigned MaxLights;
      unsigned MaxClipPlanes;
      unsigned MaxTextureUnits;
      unsigned MaxTextureCoords;
      unsigned MaxVertexAttribs;
      unsigned MaxVertexUniformComponents;
      unsigned MaxVertexTextureImageUnits;
      unsigned MaxCombinedTextureImageUnits;
      unsigned MaxTextureImageUnits;
      unsigned MaxFragmentUniformComponents;

      /* ARB_draw_buffers */
      unsigned MaxDrawBuffers;

      /* 3.00 ES */
      int MinProgramTexelOffset;
      int MaxProgramTexelOffset;

      /* 1.50 */
      unsigned MaxVertexOutputComponents;
      unsigned MaxGeometryInputComponents;
      unsigned MaxGeometryOutputComponents;
      unsigned MaxFragmentInputComponents;
      unsigned MaxGeometryTextureImageUnits;
      unsigned MaxGeometryOutputVertices;
      unsigned MaxGeometryTotalOutputComponents;
      unsigned MaxGeometryUniformComponents;

      /* ARB_shader_atomic_counters */
      unsigned MaxVertexAtomicCounters;
      unsigned MaxGeometryAtomicCounters;
      unsigned MaxFragmentAtomicCounters;
      unsigned MaxCombinedAtomicCounters;
      unsigned MaxAtomicBufferBindings;

      /* ARB_compute_shader */
      unsigned MaxComputeWorkGroupCount[3];
      unsigned MaxComputeWorkGroupSize[3];

      /* ARB_shader_image_load_store */
      unsigned MaxImageUnits;
      unsigned MaxCombinedImageUnitsAndFragmentOutputs;
      unsigned MaxImageSamples;
      unsigned MaxVertexImageUniforms;
      unsigned MaxGeometryImageUniforms;
      unsigned MaxFragmentImageUniforms;
      unsigned MaxCombinedImageUniforms;
   } Const;

   /**
    * During AST to IR conversion, pointer to current IR function
    *
    * Will be \c NULL whenever the AST to IR conversion is not inside a
    * function definition.
    */
   class ir_function_signature *current_function;

   /**
    * During AST to IR conversion, pointer to the toplevel IR
    * instruction list being generated.
    */
   exec_list *toplevel_ir;

   /** Have we found a return statement in this function? */
   bool found_return;

   /** Was there an error during compilation? */
   bool error;

   /**
    * Are all shader inputs / outputs invariant?
    *
    * This is set when the 'STDGL invariant(all)' pragma is used.
    */
   bool all_invariant;

   /** Loop or switch statement containing the current instructions. */
   class ast_iteration_statement *loop_nesting_ast;

   struct glsl_switch_state switch_state;

   /** List of structures defined in user code. */
   const glsl_type **user_structures;
   unsigned num_user_structures;

   char *info_log;

   /**
    * \name Enable bits for GLSL extensions
    */
   /*@{*/
   /* ARB extensions go here, sorted alphabetically.
    */
   bool ARB_arrays_of_arrays_enable;
   bool ARB_arrays_of_arrays_warn;
   bool ARB_compute_shader_enable;
   bool ARB_compute_shader_warn;
   bool ARB_conservative_depth_enable;
   bool ARB_conservative_depth_warn;
   bool ARB_derivative_control_enable;
   bool ARB_derivative_control_warn;
   bool ARB_draw_buffers_enable;
   bool ARB_draw_buffers_warn;
   bool ARB_draw_instanced_enable;
   bool ARB_draw_instanced_warn;
   bool ARB_explicit_attrib_location_enable;
   bool ARB_explicit_attrib_location_warn;
   bool ARB_explicit_uniform_location_enable;
   bool ARB_explicit_uniform_location_warn;
   bool ARB_fragment_coord_conventions_enable;
   bool ARB_fragment_coord_conventions_warn;
   bool ARB_fragment_layer_viewport_enable;
   bool ARB_fragment_layer_viewport_warn;
   bool ARB_gpu_shader5_enable;
   bool ARB_gpu_shader5_warn;
   bool ARB_sample_shading_enable;
   bool ARB_sample_shading_warn;
   bool ARB_separate_shader_objects_enable;
   bool ARB_separate_shader_objects_warn;
   bool ARB_shader_atomic_counters_enable;
   bool ARB_shader_atomic_counters_warn;
   bool ARB_shader_bit_encoding_enable;
   bool ARB_shader_bit_encoding_warn;
   bool ARB_shader_image_load_store_enable;
   bool ARB_shader_image_load_store_warn;
   bool ARB_shader_stencil_export_enable;
   bool ARB_shader_stencil_export_warn;
   bool ARB_shader_texture_lod_enable;
   bool ARB_shader_texture_lod_warn;
   bool ARB_shading_language_420pack_enable;
   bool ARB_shading_language_420pack_warn;
   bool ARB_shading_language_packing_enable;
   bool ARB_shading_language_packing_warn;
   bool ARB_texture_cube_map_array_enable;
   bool ARB_texture_cube_map_array_warn;
   bool ARB_texture_gather_enable;
   bool ARB_texture_gather_warn;
   bool ARB_texture_multisample_enable;
   bool ARB_texture_multisample_warn;
   bool ARB_texture_query_levels_enable;
   bool ARB_texture_query_levels_warn;
   bool ARB_texture_query_lod_enable;
   bool ARB_texture_query_lod_warn;
   bool ARB_texture_rectangle_enable;
   bool ARB_texture_rectangle_warn;
   bool ARB_uniform_buffer_object_enable;
   bool ARB_uniform_buffer_object_warn;
   bool ARB_viewport_array_enable;
   bool ARB_viewport_array_warn;

   /* KHR extensions go here, sorted alphabetically.
    */

   /* OES extensions go here, sorted alphabetically.
    */
   bool OES_EGL_image_external_enable;
   bool OES_EGL_image_external_warn;
   bool OES_standard_derivatives_enable;
   bool OES_standard_derivatives_warn;
   bool OES_texture_3D_enable;
   bool OES_texture_3D_warn;

   /* All other extensions go here, sorted alphabetically.
    */
   bool AMD_conservative_depth_enable;
   bool AMD_conservative_depth_warn;
   bool AMD_shader_stencil_export_enable;
   bool AMD_shader_stencil_export_warn;
   bool AMD_shader_trinary_minmax_enable;
   bool AMD_shader_trinary_minmax_warn;
   bool AMD_vertex_shader_layer_enable;
   bool AMD_vertex_shader_layer_warn;
   bool AMD_vertex_shader_viewport_index_enable;
   bool AMD_vertex_shader_viewport_index_warn;
   bool EXT_draw_buffers_enable;
   bool EXT_draw_buffers_warn;
   bool EXT_draw_instanced_enable;
   bool EXT_draw_instanced_warn;
   bool EXT_frag_depth_enable;
   bool EXT_frag_depth_warn;
   bool EXT_gpu_shader4_enable;
   bool EXT_gpu_shader4_warn;
   bool EXT_separate_shader_objects_enable;
   bool EXT_separate_shader_objects_warn;
   bool EXT_shader_framebuffer_fetch_enable;
   bool EXT_shader_framebuffer_fetch_warn;
   bool EXT_shader_integer_mix_enable;
   bool EXT_shader_integer_mix_warn;
   bool EXT_shader_texture_lod_enable;
   bool EXT_shader_texture_lod_warn;
   bool EXT_shadow_samplers_enable;
   bool EXT_shadow_samplers_warn;
   bool EXT_texture_array_enable;
   bool EXT_texture_array_warn;

   /*@}*/

   /** Extensions supported by the OpenGL implementation. */
   const struct gl_extensions *extensions;

   bool uses_builtin_functions;
   bool fs_uses_gl_fragcoord;

   /**
    * For geometry shaders, size of the most recently seen input declaration
    * that was a sized array, or 0 if no sized input array declarations have
    * been seen.
    *
    * Unused for other shader types.
    */
   unsigned gs_input_size;

   bool early_fragment_tests;

   /** Atomic counter offsets by binding */
   unsigned atomic_counter_offsets[MAX_COMBINED_ATOMIC_BUFFERS];

   bool allow_extension_directive_midshader;
};

# define YYLLOC_DEFAULT(Current, Rhs, N)			\
do {								\
   if (N)							\
   {								\
      (Current).first_line   = YYRHSLOC(Rhs, 1).first_line;	\
      (Current).first_column = YYRHSLOC(Rhs, 1).first_column;	\
      (Current).last_line    = YYRHSLOC(Rhs, N).last_line;	\
      (Current).last_column  = YYRHSLOC(Rhs, N).last_column;	\
   }								\
   else								\
   {								\
      (Current).first_line   = (Current).last_line =		\
	 YYRHSLOC(Rhs, 0).last_line;				\
      (Current).first_column = (Current).last_column =		\
	 YYRHSLOC(Rhs, 0).last_column;				\
   }								\
   (Current).source = 0;					\
} while (0)

/**
 * Emit a warning to the shader log
 *
 * \sa _mesa_glsl_error
 */
extern void _mesa_glsl_warning(const YYLTYPE *locp,
			       _mesa_glsl_parse_state *state,
			       const char *fmt, ...);

extern void _mesa_glsl_lexer_ctor(struct _mesa_glsl_parse_state *state,
				  const char *string);

extern void _mesa_glsl_lexer_dtor(struct _mesa_glsl_parse_state *state);

union YYSTYPE;
extern int _mesa_glsl_lexer_lex(union YYSTYPE *yylval, YYLTYPE *yylloc,
                                void *scanner);

extern int _mesa_glsl_parse(struct _mesa_glsl_parse_state *);

/**
 * Process elements of the #extension directive
 *
 * \return
 * If \c name and \c behavior are valid, \c true is returned.  Otherwise
 * \c false is returned.
 */
extern bool _mesa_glsl_process_extension(const char *name, YYLTYPE *name_locp,
					 const char *behavior,
					 YYLTYPE *behavior_locp,
					 _mesa_glsl_parse_state *state);

#endif /* __cplusplus */


/*
 * These definitions apply to C and C++
 */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get the textual name of the specified shader stage (which is a
 * gl_shader_stage).
 */
extern const char *
_mesa_shader_stage_to_string(unsigned stage);

extern int glcpp_preprocess(void *ctx, const char **shader, char **info_log,
                      const struct gl_extensions *extensions, struct gl_context *gl_ctx);

extern void _mesa_destroy_shader_compiler(void);
extern void _mesa_destroy_shader_compiler_caches(void);

#ifdef __cplusplus
}
#endif


#endif /* GLSL_PARSER_EXTRAS_H */
