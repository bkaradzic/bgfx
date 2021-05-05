/*
 * Copyright © 2008, 2009 Intel Corporation
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
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

extern "C" {
#include "main/core.h" /* for struct gl_context */
#include "main/context.h"
}

#include "util/ralloc.h"
#include "ast.h"
#include "glsl_parser_extras.h"
#include "glsl_parser.h"
#include "ir_optimization.h"
#include "loop_analysis.h"
#include "standalone_scaffolding.h"

/**
 * Format a short human-readable description of the given GLSL version.
 */
const char *
glsl_compute_version_string(void *mem_ctx, bool is_es, unsigned version)
{
   return ralloc_asprintf(mem_ctx, "GLSL%s %d.%02d", is_es ? " ES" : "",
                          version / 100, version % 100);
}


static const unsigned known_desktop_glsl_versions[] =
   { 110, 120, 130, 140, 150, 330, 400, 410, 420, 430, 440 };


_mesa_glsl_parse_state::_mesa_glsl_parse_state(struct gl_context *_ctx,
					       gl_shader_stage stage,
                                               void *mem_ctx)
   : ctx(_ctx), cs_input_local_size_specified(false), cs_input_local_size(),
     switch_state()
{
   assert(stage < MESA_SHADER_STAGES);
   this->stage = stage;

   this->scanner = NULL;
   this->translation_unit.make_empty();
   this->symbols = new(mem_ctx) glsl_symbol_table;

   this->info_log = ralloc_strdup(mem_ctx, "");
   this->error = false;
   this->loop_nesting_ast = NULL;

   this->struct_specifier_depth = 0;

   this->uses_builtin_functions = false;

   /* Set default language version and extensions */
   this->language_version = ctx->Const.ForceGLSLVersion ?
                            ctx->Const.ForceGLSLVersion : 110;
   this->es_shader = false;
   this->metal_target = false;
   this->had_version_string = false;
   this->had_float_precision = false;
   this->ARB_texture_rectangle_enable = true;

   /* OpenGL ES 2.0 has different defaults from desktop GL. */
   if (ctx->API == API_OPENGLES2) {
      this->language_version = 100;
      this->es_shader = true;
      this->ARB_texture_rectangle_enable = false;
   }

   this->extensions = &ctx->Extensions;

   this->Const.MaxLights = ctx->Const.MaxLights;
   this->Const.MaxClipPlanes = ctx->Const.MaxClipPlanes;
   this->Const.MaxTextureUnits = ctx->Const.MaxTextureUnits;
   this->Const.MaxTextureCoords = ctx->Const.MaxTextureCoordUnits;
   this->Const.MaxVertexAttribs = ctx->Const.Program[MESA_SHADER_VERTEX].MaxAttribs;
   this->Const.MaxVertexUniformComponents = ctx->Const.Program[MESA_SHADER_VERTEX].MaxUniformComponents;
   this->Const.MaxVertexTextureImageUnits = ctx->Const.Program[MESA_SHADER_VERTEX].MaxTextureImageUnits;
   this->Const.MaxCombinedTextureImageUnits = ctx->Const.MaxCombinedTextureImageUnits;
   this->Const.MaxTextureImageUnits = ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxTextureImageUnits;
   this->Const.MaxFragmentUniformComponents = ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxUniformComponents;
   this->Const.MinProgramTexelOffset = ctx->Const.MinProgramTexelOffset;
   this->Const.MaxProgramTexelOffset = ctx->Const.MaxProgramTexelOffset;

   this->Const.MaxDrawBuffers = ctx->Const.MaxDrawBuffers;

   /* 1.50 constants */
   this->Const.MaxVertexOutputComponents = ctx->Const.Program[MESA_SHADER_VERTEX].MaxOutputComponents;
   this->Const.MaxGeometryInputComponents = ctx->Const.Program[MESA_SHADER_GEOMETRY].MaxInputComponents;
   this->Const.MaxGeometryOutputComponents = ctx->Const.Program[MESA_SHADER_GEOMETRY].MaxOutputComponents;
   this->Const.MaxFragmentInputComponents = ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxInputComponents;
   this->Const.MaxGeometryTextureImageUnits = ctx->Const.Program[MESA_SHADER_GEOMETRY].MaxTextureImageUnits;
   this->Const.MaxGeometryOutputVertices = ctx->Const.MaxGeometryOutputVertices;
   this->Const.MaxGeometryTotalOutputComponents = ctx->Const.MaxGeometryTotalOutputComponents;
   this->Const.MaxGeometryUniformComponents = ctx->Const.Program[MESA_SHADER_GEOMETRY].MaxUniformComponents;

   this->Const.MaxVertexAtomicCounters = ctx->Const.Program[MESA_SHADER_VERTEX].MaxAtomicCounters;
   this->Const.MaxGeometryAtomicCounters = ctx->Const.Program[MESA_SHADER_GEOMETRY].MaxAtomicCounters;
   this->Const.MaxFragmentAtomicCounters = ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxAtomicCounters;
   this->Const.MaxCombinedAtomicCounters = ctx->Const.MaxCombinedAtomicCounters;
   this->Const.MaxAtomicBufferBindings = ctx->Const.MaxAtomicBufferBindings;

   /* Compute shader constants */
   for (unsigned i = 0; i < Elements(this->Const.MaxComputeWorkGroupCount); i++)
      this->Const.MaxComputeWorkGroupCount[i] = ctx->Const.MaxComputeWorkGroupCount[i];
   for (unsigned i = 0; i < Elements(this->Const.MaxComputeWorkGroupSize); i++)
      this->Const.MaxComputeWorkGroupSize[i] = ctx->Const.MaxComputeWorkGroupSize[i];

   this->Const.MaxImageUnits = ctx->Const.MaxImageUnits;
   this->Const.MaxCombinedImageUnitsAndFragmentOutputs = ctx->Const.MaxCombinedImageUnitsAndFragmentOutputs;
   this->Const.MaxImageSamples = ctx->Const.MaxImageSamples;
   this->Const.MaxVertexImageUniforms = ctx->Const.Program[MESA_SHADER_VERTEX].MaxImageUniforms;
   this->Const.MaxGeometryImageUniforms = ctx->Const.Program[MESA_SHADER_GEOMETRY].MaxImageUniforms;
   this->Const.MaxFragmentImageUniforms = ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxImageUniforms;
   this->Const.MaxCombinedImageUniforms = ctx->Const.MaxCombinedImageUniforms;

   this->current_function = NULL;
   this->toplevel_ir = NULL;
   this->found_return = false;
   this->all_invariant = false;
   this->user_structures = NULL;
   this->num_user_structures = 0;

   /* Populate the list of supported GLSL versions */
   /* FINISHME: Once the OpenGL 3.0 'forward compatible' context or
    * the OpenGL 3.2 Core context is supported, this logic will need
    * change.  Older versions of GLSL are no longer supported
    * outside the compatibility contexts of 3.x.
    */
   this->num_supported_versions = 0;
   if (_mesa_is_desktop_gl(ctx)) {
      for (unsigned i = 0; i < ARRAY_SIZE(known_desktop_glsl_versions); i++) {
         if (known_desktop_glsl_versions[i] <= ctx->Const.GLSLVersion) {
            this->supported_versions[this->num_supported_versions].ver
               = known_desktop_glsl_versions[i];
            this->supported_versions[this->num_supported_versions].es = false;
            this->num_supported_versions++;
         }
      }
   }
   if (ctx->API == API_OPENGLES2 || ctx->Extensions.ARB_ES2_compatibility) {
      this->supported_versions[this->num_supported_versions].ver = 100;
      this->supported_versions[this->num_supported_versions].es = true;
      this->num_supported_versions++;
   }
   if (_mesa_is_gles3(ctx) || ctx->Extensions.ARB_ES3_compatibility) {
      this->supported_versions[this->num_supported_versions].ver = 300;
      this->supported_versions[this->num_supported_versions].es = true;
      this->num_supported_versions++;
   }
   assert(this->num_supported_versions
          <= ARRAY_SIZE(this->supported_versions));

   /* Create a string for use in error messages to tell the user which GLSL
    * versions are supported.
    */
   char *supported = ralloc_strdup(this, "");
   for (unsigned i = 0; i < this->num_supported_versions; i++) {
      unsigned ver = this->supported_versions[i].ver;
      const char *const prefix = (i == 0)
	 ? ""
	 : ((i == this->num_supported_versions - 1) ? ", and " : ", ");
      const char *const suffix = (this->supported_versions[i].es) ? " ES" : "";

      ralloc_asprintf_append(& supported, "%s%u.%02u%s",
			     prefix,
			     ver / 100, ver % 100,
			     suffix);
   }

   this->supported_version_string = supported;

   if (ctx->Const.ForceGLSLExtensionsWarn)
      _mesa_glsl_process_extension("all", NULL, "warn", NULL, this);

   this->default_uniform_qualifier = new(this) ast_type_qualifier;
   this->default_uniform_qualifier->flags.q.shared = 1;
   this->default_uniform_qualifier->flags.q.column_major = 1;

   this->fs_uses_gl_fragcoord = false;
   this->fs_redeclares_gl_fragcoord = false;
   this->fs_origin_upper_left = false;
   this->fs_pixel_center_integer = false;
   this->fs_redeclares_gl_fragcoord_with_no_layout_qualifiers = false;

   this->gs_input_prim_type_specified = false;
   this->gs_input_size = 0;
   this->in_qualifier = new(this) ast_type_qualifier();
   this->out_qualifier = new(this) ast_type_qualifier();
   this->early_fragment_tests = false;
   memset(this->atomic_counter_offsets, 0,
          sizeof(this->atomic_counter_offsets));
   this->allow_extension_directive_midshader =
      ctx->Const.AllowGLSLExtensionDirectiveMidShader;
}

/**
 * Determine whether the current GLSL version is sufficiently high to support
 * a certain feature, and generate an error message if it isn't.
 *
 * \param required_glsl_version and \c required_glsl_es_version are
 * interpreted as they are in _mesa_glsl_parse_state::is_version().
 *
 * \param locp is the parser location where the error should be reported.
 *
 * \param fmt (and additional arguments) constitute a printf-style error
 * message to report if the version check fails.  Information about the
 * current and required GLSL versions will be appended.  So, for example, if
 * the GLSL version being compiled is 1.20, and check_version(130, 300, locp,
 * "foo unsupported") is called, the error message will be "foo unsupported in
 * GLSL 1.20 (GLSL 1.30 or GLSL 3.00 ES required)".
 */
bool
_mesa_glsl_parse_state::check_version(unsigned required_glsl_version,
                                      unsigned required_glsl_es_version,
                                      YYLTYPE *locp, const char *fmt, ...)
{
   if (this->is_version(required_glsl_version, required_glsl_es_version))
      return true;

   va_list args;
   va_start(args, fmt);
   char *problem = ralloc_vasprintf(this, fmt, args);
   va_end(args);
   const char *glsl_version_string
      = glsl_compute_version_string(this, false, required_glsl_version);
   const char *glsl_es_version_string
      = glsl_compute_version_string(this, true, required_glsl_es_version);
   const char *requirement_string = "";
   if (required_glsl_version && required_glsl_es_version) {
      requirement_string = ralloc_asprintf(this, " (%s or %s required)",
                                           glsl_version_string,
                                           glsl_es_version_string);
   } else if (required_glsl_version) {
      requirement_string = ralloc_asprintf(this, " (%s required)",
                                           glsl_version_string);
   } else if (required_glsl_es_version) {
      requirement_string = ralloc_asprintf(this, " (%s required)",
                                           glsl_es_version_string);
   }
   _mesa_glsl_error(locp, this, "%s in %s%s",
                    problem, this->get_version_string(),
                    requirement_string);

   return false;
}

/**
 * Process a GLSL #version directive.
 *
 * \param version is the integer that follows the #version token.
 *
 * \param ident is a string identifier that follows the integer, if any is
 * present.  Otherwise NULL.
 */
void
_mesa_glsl_parse_state::process_version_directive(YYLTYPE *locp, int version,
                                                  const char *ident)
{
   bool es_token_present = false;
   if (ident) {
      if (strcmp(ident, "es") == 0) {
         es_token_present = true;
      } else if (version >= 150) {
         if (strcmp(ident, "core") == 0) {
            /* Accept the token.  There's no need to record that this is
             * a core profile shader since that's the only profile we support.
             */
         } else if (strcmp(ident, "compatibility") == 0) {
            _mesa_glsl_error(locp, this,
                             "the compatibility profile is not supported");
         } else {
            _mesa_glsl_error(locp, this,
                             "\"%s\" is not a valid shading language profile; "
                             "if present, it must be \"core\"", ident);
         }
      } else {
         _mesa_glsl_error(locp, this,
                          "illegal text following version number");
      }
   }

   this->es_shader = es_token_present;
   if (version == 100) {
      if (es_token_present) {
         _mesa_glsl_error(locp, this,
                          "GLSL 1.00 ES should be selected using "
                          "`#version 100'");
      } else {
         this->es_shader = true;
      }
   }

   if (this->es_shader) {
      this->ARB_texture_rectangle_enable = false;
   }

   this->language_version = version;
   this->had_version_string = true;

   bool supported = false;
   for (unsigned i = 0; i < this->num_supported_versions; i++) {
      if (this->supported_versions[i].ver == (unsigned) version
          && this->supported_versions[i].es == this->es_shader) {
         supported = true;
         break;
      }
   }

   if (!supported) {
      _mesa_glsl_error(locp, this, "%s is not supported. "
                       "Supported versions are: %s",
                       this->get_version_string(),
                       this->supported_version_string);

      /* On exit, the language_version must be set to a valid value.
       * Later calls to _mesa_glsl_initialize_types will misbehave if
       * the version is invalid.
       */
      switch (this->ctx->API) {
      case API_OPENGL_COMPAT:
      case API_OPENGL_CORE:
	 this->language_version = this->ctx->Const.GLSLVersion;
	 break;

      case API_OPENGLES:
	 assert(!"Should not get here.");
	 /* FALLTHROUGH */

      case API_OPENGLES2:
	 this->language_version = 100;
	 break;
      }
   }
}


/**
 * Translate a gl_shader_stage to a short shader stage name for debug
 * printouts and error messages.
 */
const char *
_mesa_shader_stage_to_string(unsigned stage)
{
   switch (stage) {
   case MESA_SHADER_VERTEX:   return "vertex";
   case MESA_SHADER_FRAGMENT: return "fragment";
   case MESA_SHADER_GEOMETRY: return "geometry";
   }

   assert(!"Should not get here.");
   return "unknown";
}

/* This helper function will append the given message to the shader's
   info log and report it via GL_ARB_debug_output. Per that extension,
   'type' is one of the enum values classifying the message, and
   'id' is the implementation-defined ID of the given message. */
static void
_mesa_glsl_msg(const YYLTYPE *locp, _mesa_glsl_parse_state *state,
               GLenum type, const char *fmt, va_list ap)
{
   bool error = (type == MESA_DEBUG_TYPE_ERROR);
   GLuint msg_id = 0;

   assert(state->info_log != NULL);

   /* Get the offset that the new message will be written to. */
   int msg_offset = strlen(state->info_log);

	// format:
	// (line,col): type: message
   ralloc_asprintf_append(&state->info_log, "(%u,%u): %s: ",
					    locp->first_line,
					    locp->first_column,
					    error ? "error" : "warning");
   ralloc_vasprintf_append(&state->info_log, fmt, ap);

   const char *const msg = &state->info_log[msg_offset];
   struct gl_context *ctx = state->ctx;

   /* Report the error via GL_ARB_debug_output. */
   _mesa_shader_debug(ctx, type, &msg_id, msg, strlen(msg));

   ralloc_strcat(&state->info_log, "\n");
}

void
_mesa_glsl_error(YYLTYPE *locp, _mesa_glsl_parse_state *state,
		 const char *fmt, ...)
{
   va_list ap;

   state->error = true;

   va_start(ap, fmt);
   _mesa_glsl_msg(locp, state, MESA_DEBUG_TYPE_ERROR, fmt, ap);
   va_end(ap);
}


void
_mesa_glsl_warning(const YYLTYPE *locp, _mesa_glsl_parse_state *state,
		   const char *fmt, ...)
{
   va_list ap;

   va_start(ap, fmt);
   _mesa_glsl_msg(locp, state, MESA_DEBUG_TYPE_OTHER, fmt, ap);
   va_end(ap);
}


/**
 * Enum representing the possible behaviors that can be specified in
 * an #extension directive.
 */
enum ext_behavior {
   extension_disable,
   extension_enable,
   extension_require,
   extension_warn
};

/**
 * Element type for _mesa_glsl_supported_extensions
 */
struct _mesa_glsl_extension {
   /**
    * Name of the extension when referred to in a GLSL extension
    * statement
    */
   const char *name;

   /** True if this extension is available to desktop GL shaders */
   bool avail_in_GL;

   /** True if this extension is available to GLES shaders */
   bool avail_in_ES;

   /**
    * Flag in the gl_extensions struct indicating whether this
    * extension is supported by the driver, or
    * &gl_extensions::dummy_true if supported by all drivers.
    *
    * Note: the type (GLboolean gl_extensions::*) is a "pointer to
    * member" type, the type-safe alternative to the "offsetof" macro.
    * In a nutshell:
    *
    * - foo bar::* p declares p to be an "offset" to a field of type
    *   foo that exists within struct bar
    * - &bar::baz computes the "offset" of field baz within struct bar
    * - x.*p accesses the field of x that exists at "offset" p
    * - x->*p is equivalent to (*x).*p
    */
   const GLboolean gl_extensions::* supported_flag;

   /**
    * Flag in the _mesa_glsl_parse_state struct that should be set
    * when this extension is enabled.
    *
    * See note in _mesa_glsl_extension::supported_flag about "pointer
    * to member" types.
    */
   bool _mesa_glsl_parse_state::* enable_flag;

   /**
    * Flag in the _mesa_glsl_parse_state struct that should be set
    * when the shader requests "warn" behavior for this extension.
    *
    * See note in _mesa_glsl_extension::supported_flag about "pointer
    * to member" types.
    */
   bool _mesa_glsl_parse_state::* warn_flag;


   bool compatible_with_state(const _mesa_glsl_parse_state *state) const;
   void set_flags(_mesa_glsl_parse_state *state, ext_behavior behavior) const;
};

#define EXT(NAME, GL, ES, SUPPORTED_FLAG)                   \
   { "GL_" #NAME, GL, ES, &gl_extensions::SUPPORTED_FLAG,   \
         &_mesa_glsl_parse_state::NAME##_enable,            \
         &_mesa_glsl_parse_state::NAME##_warn }

/**
 * Table of extensions that can be enabled/disabled within a shader,
 * and the conditions under which they are supported.
 */
static const _mesa_glsl_extension _mesa_glsl_supported_extensions[] = {
   /*                                  API availability */
   /* name                             GL     ES         supported flag */

   /* ARB extensions go here, sorted alphabetically.
    */
   EXT(ARB_arrays_of_arrays,            true,  false,     ARB_arrays_of_arrays),
   EXT(ARB_compute_shader,              true,  false,     ARB_compute_shader),
   EXT(ARB_conservative_depth,          true,  false,     ARB_conservative_depth),
   EXT(ARB_derivative_control,          true,  false,     ARB_derivative_control),
   EXT(ARB_draw_buffers,                true,  false,     dummy_true),
   EXT(ARB_draw_instanced,              true,  false,     ARB_draw_instanced),
   EXT(ARB_explicit_attrib_location,    true,  false,     ARB_explicit_attrib_location),
   EXT(ARB_explicit_uniform_location,   true,  false,     ARB_explicit_uniform_location),
   EXT(ARB_fragment_coord_conventions,  true,  false,     ARB_fragment_coord_conventions),
   EXT(ARB_fragment_layer_viewport,     true,  false,     ARB_fragment_layer_viewport),
   EXT(ARB_gpu_shader5,                 true,  false,     ARB_gpu_shader5),
   EXT(ARB_sample_shading,              true,  false,     ARB_sample_shading),
   EXT(ARB_separate_shader_objects,     true,  false,     dummy_true),
   EXT(ARB_shader_atomic_counters,      true,  false,     ARB_shader_atomic_counters),
   EXT(ARB_shader_bit_encoding,         true,  false,     ARB_shader_bit_encoding),
   EXT(ARB_shader_image_load_store,     true,  false,     ARB_shader_image_load_store),
   EXT(ARB_shader_stencil_export,       true,  false,     ARB_shader_stencil_export),
   EXT(ARB_shader_texture_lod,          true,  false,     ARB_shader_texture_lod),
   EXT(ARB_shader_viewport_layer_array, true,  false,     ARB_shader_viewport_layer_array),
   EXT(ARB_shading_language_420pack,    true,  false,     ARB_shading_language_420pack),
   EXT(ARB_shading_language_packing,    true,  false,     ARB_shading_language_packing),
   EXT(ARB_texture_cube_map_array,      true,  false,     ARB_texture_cube_map_array),
   EXT(ARB_texture_gather,              true,  false,     ARB_texture_gather),
   EXT(ARB_texture_multisample,         true,  false,     ARB_texture_multisample),
   EXT(ARB_texture_query_levels,        true,  false,     ARB_texture_query_levels),
   EXT(ARB_texture_query_lod,           true,  false,     ARB_texture_query_lod),
   EXT(ARB_texture_rectangle,           true,  false,     dummy_true),
   EXT(ARB_uniform_buffer_object,       true,  false,     ARB_uniform_buffer_object),
   EXT(ARB_viewport_array,              true,  false,     ARB_viewport_array),

   /* KHR extensions go here, sorted alphabetically.
    */

   /* OES extensions go here, sorted alphabetically.
    */
   EXT(OES_EGL_image_external,         false, true,      OES_EGL_image_external),
   EXT(OES_standard_derivatives,       false, true,      OES_standard_derivatives),
   EXT(OES_texture_3D,                 false, true,      EXT_texture3D),

   /* All other extensions go here, sorted alphabetically.
    */
   EXT(AMD_conservative_depth,         true,  false,     ARB_conservative_depth),
   EXT(AMD_shader_stencil_export,      true,  false,     ARB_shader_stencil_export),
   EXT(AMD_shader_trinary_minmax,      true,  false,     dummy_true),
   EXT(AMD_vertex_shader_layer,        true,  false,     AMD_vertex_shader_layer),
   EXT(AMD_vertex_shader_viewport_index, true,  false,   AMD_vertex_shader_viewport_index),
   EXT(EXT_draw_buffers,               false,  true,     EXT_draw_buffers),
   EXT(EXT_draw_instanced,             false,  true,     EXT_draw_instanced),
   EXT(EXT_frag_depth,                 false,  true,     EXT_frag_depth),
   EXT(EXT_gpu_shader4,				   true,  false,     EXT_gpu_shader4),
   EXT(EXT_separate_shader_objects,    false, true,      dummy_true),
   EXT(EXT_shader_framebuffer_fetch,   false, true,      EXT_shader_framebuffer_fetch),
   EXT(EXT_shader_integer_mix,         true,  true,      EXT_shader_integer_mix),
   EXT(EXT_shader_texture_lod,         true,  true,      ARB_shader_texture_lod), // BK - made it available in GLSL
   EXT(EXT_shadow_samplers,            false, true,      EXT_shadow_samplers),
   EXT(EXT_texture_array,              true,  true,      EXT_texture_array), // BK - made it available in ESSL
};

#undef EXT


/**
 * Determine whether a given extension is compatible with the target,
 * API, and extension information in the current parser state.
 */
bool _mesa_glsl_extension::compatible_with_state(const _mesa_glsl_parse_state *
                                                 state) const
{
   /* Check that this extension matches whether we are compiling
    * for desktop GL or GLES.
    */
   if (state->es_shader) {
      if (!this->avail_in_ES) return false;
   } else {
      if (!this->avail_in_GL) return false;
   }

   /* Check that this extension is supported by the OpenGL
    * implementation.
    *
    * Note: the ->* operator indexes into state->extensions by the
    * offset this->supported_flag.  See
    * _mesa_glsl_extension::supported_flag for more info.
    */
   return !!(state->extensions->*(this->supported_flag));
}

/**
 * Set the appropriate flags in the parser state to establish the
 * given behavior for this extension.
 */
void _mesa_glsl_extension::set_flags(_mesa_glsl_parse_state *state,
                                     ext_behavior behavior) const
{
   /* Note: the ->* operator indexes into state by the
    * offsets this->enable_flag and this->warn_flag.  See
    * _mesa_glsl_extension::supported_flag for more info.
    */
   state->*(this->enable_flag) = (behavior != extension_disable);
   state->*(this->warn_flag)   = (behavior == extension_warn);
}

/**
 * Find an extension by name in _mesa_glsl_supported_extensions.  If
 * the name is not found, return NULL.
 */
static const _mesa_glsl_extension *find_extension(const char *name)
{
   for (unsigned i = 0; i < Elements(_mesa_glsl_supported_extensions); ++i) {
      if (strcmp(name, _mesa_glsl_supported_extensions[i].name) == 0) {
         return &_mesa_glsl_supported_extensions[i];
      }
   }
   return NULL;
}


bool
_mesa_glsl_process_extension(const char *name, YYLTYPE *name_locp,
			     const char *behavior_string, YYLTYPE *behavior_locp,
			     _mesa_glsl_parse_state *state)
{
   ext_behavior behavior;
   if (strcmp(behavior_string, "warn") == 0) {
      behavior = extension_warn;
   } else if (strcmp(behavior_string, "require") == 0) {
      behavior = extension_require;
   } else if (strcmp(behavior_string, "enable") == 0) {
      behavior = extension_enable;
   } else if (strcmp(behavior_string, "disable") == 0) {
      behavior = extension_disable;
   } else {
      _mesa_glsl_error(behavior_locp, state,
		       "unknown extension behavior `%s'",
		       behavior_string);
      return false;
   }

   if (strcmp(name, "all") == 0) {
      if ((behavior == extension_enable) || (behavior == extension_require)) {
	 _mesa_glsl_error(name_locp, state, "cannot %s all extensions",
			  (behavior == extension_enable)
			  ? "enable" : "require");
	 return false;
      } else {
         for (unsigned i = 0;
              i < Elements(_mesa_glsl_supported_extensions); ++i) {
            const _mesa_glsl_extension *extension
               = &_mesa_glsl_supported_extensions[i];
            if (extension->compatible_with_state(state)) {
               _mesa_glsl_supported_extensions[i].set_flags(state, behavior);
            }
         }
      }
   } else {
      const _mesa_glsl_extension *extension = find_extension(name);
      if (extension && extension->compatible_with_state(state)) {
         extension->set_flags(state, behavior);
      } else {
         static const char fmt[] = "extension `%s' unsupported in %s shader";

         if (behavior == extension_require) {
            _mesa_glsl_error(name_locp, state, fmt,
                             name, _mesa_shader_stage_to_string(state->stage));
            return false;
         } else {
            _mesa_glsl_warning(name_locp, state, fmt,
                               name, _mesa_shader_stage_to_string(state->stage));
         }
      }
   }

   return true;
}


/**
 * Recurses through <type> and <expr> if <expr> is an aggregate initializer
 * and sets <expr>'s <constructor_type> field to <type>. Gives later functions
 * (process_array_constructor, et al) sufficient information to do type
 * checking.
 *
 * Operates on assignments involving an aggregate initializer. E.g.,
 *
 * vec4 pos = {1.0, -1.0, 0.0, 1.0};
 *
 * or more ridiculously,
 *
 * struct S {
 *     vec4 v[2];
 * };
 *
 * struct {
 *     S a[2], b;
 *     int c;
 * } aggregate = {
 *     {
 *         {
 *             {
 *                 {1.0, 2.0, 3.0, 4.0}, // a[0].v[0]
 *                 {5.0, 6.0, 7.0, 8.0}  // a[0].v[1]
 *             } // a[0].v
 *         }, // a[0]
 *         {
 *             {
 *                 {1.0, 2.0, 3.0, 4.0}, // a[1].v[0]
 *                 {5.0, 6.0, 7.0, 8.0}  // a[1].v[1]
 *             } // a[1].v
 *         } // a[1]
 *     }, // a
 *     {
 *         {
 *             {1.0, 2.0, 3.0, 4.0}, // b.v[0]
 *             {5.0, 6.0, 7.0, 8.0}  // b.v[1]
 *         } // b.v
 *     }, // b
 *     4 // c
 * };
 *
 * This pass is necessary because the right-hand side of <type> e = { ... }
 * doesn't contain sufficient information to determine if the types match.
 */
void
_mesa_ast_set_aggregate_type(const glsl_type *type,
                             ast_expression *expr)
{
   ast_aggregate_initializer *ai = (ast_aggregate_initializer *)expr;
   ai->constructor_type = type;

   /* If the aggregate is an array, recursively set its elements' types. */
   if (type->is_array()) {
      /* Each array element has the type type->element_type().
       *
       * E.g., if <type> if struct S[2] we want to set each element's type to
       * struct S.
       */
      for (exec_node *expr_node = ai->expressions.head;
           !expr_node->is_tail_sentinel();
           expr_node = expr_node->next) {
         ast_expression *expr = exec_node_data(ast_expression, expr_node,
                                               link);

         if (expr->oper == ast_aggregate)
            _mesa_ast_set_aggregate_type(type->element_type(), expr);
      }

   /* If the aggregate is a struct, recursively set its fields' types. */
   } else if (type->is_record()) {
      exec_node *expr_node = ai->expressions.head;

      /* Iterate through the struct's fields. */
      for (unsigned i = 0; !expr_node->is_tail_sentinel() && i < type->length;
           i++, expr_node = expr_node->next) {
         ast_expression *expr = exec_node_data(ast_expression, expr_node,
                                               link);

         if (expr->oper == ast_aggregate) {
            _mesa_ast_set_aggregate_type(type->fields.structure[i].type, expr);
         }
      }
   /* If the aggregate is a matrix, set its columns' types. */
   } else if (type->is_matrix()) {
      for (exec_node *expr_node = ai->expressions.head;
           !expr_node->is_tail_sentinel();
           expr_node = expr_node->next) {
         ast_expression *expr = exec_node_data(ast_expression, expr_node,
                                               link);

         if (expr->oper == ast_aggregate)
            _mesa_ast_set_aggregate_type(type->column_type(), expr);
      }
   }
}


void
_mesa_ast_type_qualifier_print(const struct ast_type_qualifier *q)
{
   if (q->flags.q.constant)
      printf("const ");

   if (q->flags.q.invariant)
      printf("invariant ");

   if (q->flags.q.attribute)
      printf("attribute ");

   if (q->flags.q.varying)
      printf("varying ");

   if (q->flags.q.in && q->flags.q.out)
      printf("inout ");
   else {
      if (q->flags.q.in)
	 printf("in ");

      if (q->flags.q.out)
	 printf("out ");
   }

   if (q->flags.q.centroid)
      printf("centroid ");
   if (q->flags.q.sample)
      printf("sample ");
   if (q->flags.q.uniform)
      printf("uniform ");
   if (q->flags.q.smooth)
      printf("smooth ");
   if (q->flags.q.flat)
      printf("flat ");
   if (q->flags.q.noperspective)
      printf("noperspective ");
}


void
ast_node::print(void) const
{
   printf("unhandled node ");
}


ast_node::ast_node(void)
{
   this->location.source = 0;
   this->location.first_line = 0;
   this->location.first_column = 0;
   this->location.last_line = 0;
   this->location.last_column = 0;
}


static void
ast_opt_array_dimensions_print(const ast_array_specifier *array_specifier)
{
   if (array_specifier)
      array_specifier->print();
}


void
ast_compound_statement::print(void) const
{
   printf("{\n");
   
   foreach_list_typed(ast_node, ast, link, &this->statements) {
      ast->print();
   }

   printf("}\n");
}


ast_compound_statement::ast_compound_statement(int new_scope,
					       ast_node *statements)
{
   this->new_scope = new_scope;

   if (statements != NULL) {
      this->statements.push_degenerate_list_at_head(&statements->link);
   }
}


void
ast_expression::print(void) const
{
   switch (oper) {
   case ast_assign:
   case ast_mul_assign:
   case ast_div_assign:
   case ast_mod_assign:
   case ast_add_assign:
   case ast_sub_assign:
   case ast_ls_assign:
   case ast_rs_assign:
   case ast_and_assign:
   case ast_xor_assign:
   case ast_or_assign:
      subexpressions[0]->print();
      printf("%s ", operator_string(oper));
      subexpressions[1]->print();
      break;

   case ast_field_selection:
      subexpressions[0]->print();
      printf(". %s ", primary_expression.identifier);
      break;

   case ast_plus:
   case ast_neg:
   case ast_bit_not:
   case ast_logic_not:
   case ast_pre_inc:
   case ast_pre_dec:
      printf("%s ", operator_string(oper));
      subexpressions[0]->print();
      break;

   case ast_post_inc:
   case ast_post_dec:
      subexpressions[0]->print();
      printf("%s ", operator_string(oper));
      break;

   case ast_conditional:
      subexpressions[0]->print();
      printf("? ");
      subexpressions[1]->print();
      printf(": ");
      subexpressions[2]->print();
      break;

   case ast_array_index:
      subexpressions[0]->print();
      printf("[ ");
      subexpressions[1]->print();
      printf("] ");
      break;

   case ast_function_call: {
      subexpressions[0]->print();
      printf("( ");

      foreach_list_typed (ast_node, ast, link, &this->expressions) {
	 if (&ast->link != this->expressions.get_head())
	    printf(", ");

	 ast->print();
      }

      printf(") ");
      break;
   }

   case ast_identifier:
      printf("%s ", primary_expression.identifier);
      break;

   case ast_int_constant:
      printf("%d ", primary_expression.int_constant);
      break;

   case ast_uint_constant:
      printf("%u ", primary_expression.uint_constant);
      break;

   case ast_float_constant:
      printf("%f ", primary_expression.float_constant);
      break;

   case ast_bool_constant:
      printf("%s ",
	     primary_expression.bool_constant
	     ? "true" : "false");
      break;

   case ast_sequence: {
      printf("( ");
      foreach_list_typed (ast_node, ast, link, & this->expressions) {
	 if (&ast->link != this->expressions.get_head())
	    printf(", ");

	 ast->print();
      }
      printf(") ");
      break;
   }

   case ast_aggregate: {
      printf("{ ");
      foreach_list_typed (ast_node, ast, link, & this->expressions) {
	 if (&ast->link != this->expressions.get_head())
	    printf(", ");

	 ast->print();
      }
      printf("} ");
      break;
   }

   default:
      assert(0);
      break;
   }
}

ast_expression::ast_expression(int oper,
			       ast_expression *ex0,
			       ast_expression *ex1,
			       ast_expression *ex2) :
   primary_expression()
{
   this->oper = ast_operators(oper);
   this->subexpressions[0] = ex0;
   this->subexpressions[1] = ex1;
   this->subexpressions[2] = ex2;
   this->non_lvalue_description = NULL;
}


void
ast_expression_statement::print(void) const
{
   if (expression)
      expression->print();

   printf("; ");
}


ast_expression_statement::ast_expression_statement(ast_expression *ex) :
   expression(ex)
{
   /* empty */
}


void
ast_function::print(void) const
{
   return_type->print();
   printf(" %s (", identifier);

   foreach_list_typed(ast_node, ast, link, & this->parameters) {
      ast->print();
   }

   printf(")");
}


ast_function::ast_function(void)
   : return_type(NULL), identifier(NULL), is_definition(false),
     signature(NULL)
{
   /* empty */
}


void
ast_fully_specified_type::print(void) const
{
   _mesa_ast_type_qualifier_print(& qualifier);
   specifier->print();
}


void
ast_parameter_declarator::print(void) const
{
   type->print();
   if (identifier)
      printf("%s ", identifier);
   ast_opt_array_dimensions_print(array_specifier);
}


void
ast_function_definition::print(void) const
{
   prototype->print();
   body->print();
}


void
ast_declaration::print(void) const
{
   printf("%s ", identifier);
   ast_opt_array_dimensions_print(array_specifier);

   if (initializer) {
      printf("= ");
      initializer->print();
   }
}


ast_declaration::ast_declaration(const char *identifier,
				 ast_array_specifier *array_specifier,
				 ast_expression *initializer)
{
   this->identifier = identifier;
   this->array_specifier = array_specifier;
   this->initializer = initializer;
}


void
ast_declarator_list::print(void) const
{
   assert(type || invariant);

   if (type)
      type->print();
   else if (invariant)
      printf("invariant ");
   else
      printf("precise ");

   foreach_list_typed (ast_node, ast, link, & this->declarations) {
      if (&ast->link != this->declarations.get_head())
	 printf(", ");

      ast->print();
   }

   printf("; ");
}


ast_declarator_list::ast_declarator_list(ast_fully_specified_type *type)
{
   this->type = type;
   this->invariant = false;
   this->precise = false;
}

void
ast_jump_statement::print(void) const
{
   switch (mode) {
   case ast_continue:
      printf("continue; ");
      break;
   case ast_break:
      printf("break; ");
      break;
   case ast_return:
      printf("return ");
      if (opt_return_value)
	 opt_return_value->print();

      printf("; ");
      break;
   case ast_discard:
      printf("discard; ");
      break;
   }
}


ast_jump_statement::ast_jump_statement(int mode, ast_expression *return_value)
   : opt_return_value(NULL)
{
   this->mode = ast_jump_modes(mode);

   if (mode == ast_return)
      opt_return_value = return_value;
}


void
ast_selection_statement::print(void) const
{
   printf("if ( ");
   condition->print();
   printf(") ");

   then_statement->print();

   if (else_statement) {
      printf("else ");
      else_statement->print();
   }
   
}


ast_selection_statement::ast_selection_statement(ast_expression *condition,
						 ast_node *then_statement,
						 ast_node *else_statement)
{
   this->condition = condition;
   this->then_statement = then_statement;
   this->else_statement = else_statement;
}


void
ast_switch_statement::print(void) const
{
   printf("switch ( ");
   test_expression->print();
   printf(") ");

   body->print();
}


ast_switch_statement::ast_switch_statement(ast_expression *test_expression,
					   ast_node *body)
{
   this->test_expression = test_expression;
   this->body = body;
}


void
ast_switch_body::print(void) const
{
   printf("{\n");
   if (stmts != NULL) {
      stmts->print();
   }
   printf("}\n");
}


ast_switch_body::ast_switch_body(ast_case_statement_list *stmts)
{
   this->stmts = stmts;
}


void ast_case_label::print(void) const
{
   if (test_value != NULL) {
      printf("case ");
      test_value->print();
      printf(": ");
   } else {
      printf("default: ");
   }
}


ast_case_label::ast_case_label(ast_expression *test_value)
{
   this->test_value = test_value;
}


void ast_case_label_list::print(void) const
{
   foreach_list_typed(ast_node, ast, link, & this->labels) {
      ast->print();
   }
   printf("\n");
}


ast_case_label_list::ast_case_label_list(void)
{
}


void ast_case_statement::print(void) const
{
   labels->print();
   foreach_list_typed(ast_node, ast, link, & this->stmts) {
      ast->print();
      printf("\n");
   }
}


ast_case_statement::ast_case_statement(ast_case_label_list *labels)
{
   this->labels = labels;
}


void ast_case_statement_list::print(void) const
{
   foreach_list_typed(ast_node, ast, link, & this->cases) {
      ast->print();
   }
}


ast_case_statement_list::ast_case_statement_list(void)
{
}


void
ast_iteration_statement::print(void) const
{
   switch (mode) {
   case ast_for:
      printf("for( ");
      if (init_statement)
	 init_statement->print();
      printf("; ");

      if (condition)
	 condition->print();
      printf("; ");

      if (rest_expression)
	 rest_expression->print();
      printf(") ");

      body->print();
      break;

   case ast_while:
      printf("while ( ");
      if (condition)
	 condition->print();
      printf(") ");
      body->print();
      break;

   case ast_do_while:
      printf("do ");
      body->print();
      printf("while ( ");
      if (condition)
	 condition->print();
      printf("); ");
      break;
   }
}


ast_iteration_statement::ast_iteration_statement(int mode,
						 ast_node *init,
						 ast_node *condition,
						 ast_expression *rest_expression,
						 ast_node *body)
{
   this->mode = ast_iteration_modes(mode);
   this->init_statement = init;
   this->condition = condition;
   this->rest_expression = rest_expression;
   this->body = body;
}


void
ast_struct_specifier::print(void) const
{
   printf("struct %s { ", name);
   foreach_list_typed(ast_node, ast, link, &this->declarations) {
      ast->print();
   }
   printf("} ");
}


ast_struct_specifier::ast_struct_specifier(const char *identifier,
					   ast_declarator_list *declarator_list)
{
   if (identifier == NULL) {
      static unsigned anon_count = 1;
      identifier = ralloc_asprintf(this, "#anon_struct_%04x", anon_count);
      anon_count++;
   }
   name = identifier;
   this->declarations.push_degenerate_list_at_head(&declarator_list->link);
   is_declaration = true;
}

static void
set_shader_inout_layout(struct gl_shader *shader,
		     struct _mesa_glsl_parse_state *state)
{
   if (shader->Stage != MESA_SHADER_GEOMETRY) {
      /* Should have been prevented by the parser. */
      assert(!state->in_qualifier->flags.i);
      assert(!state->out_qualifier->flags.i);
   }

   if (shader->Stage != MESA_SHADER_COMPUTE) {
      /* Should have been prevented by the parser. */
      assert(!state->cs_input_local_size_specified);
   }

   if (shader->Stage != MESA_SHADER_FRAGMENT) {
      /* Should have been prevented by the parser. */
      assert(!state->fs_uses_gl_fragcoord);
      assert(!state->fs_redeclares_gl_fragcoord);
      assert(!state->fs_pixel_center_integer);
      assert(!state->fs_origin_upper_left);
   }

   switch (shader->Stage) {
   case MESA_SHADER_GEOMETRY:
      shader->Geom.VerticesOut = 0;
      if (state->out_qualifier->flags.q.max_vertices)
         shader->Geom.VerticesOut = state->out_qualifier->max_vertices;

      if (state->gs_input_prim_type_specified) {
         shader->Geom.InputType = state->in_qualifier->prim_type;
      } else {
         shader->Geom.InputType = PRIM_UNKNOWN;
      }

      if (state->out_qualifier->flags.q.prim_type) {
         shader->Geom.OutputType = state->out_qualifier->prim_type;
      } else {
         shader->Geom.OutputType = PRIM_UNKNOWN;
      }

      shader->Geom.Invocations = 0;
      if (state->in_qualifier->flags.q.invocations)
         shader->Geom.Invocations = state->in_qualifier->invocations;
      break;

   case MESA_SHADER_COMPUTE:
      if (state->cs_input_local_size_specified) {
         for (int i = 0; i < 3; i++)
            shader->Comp.LocalSize[i] = state->cs_input_local_size[i];
      } else {
         for (int i = 0; i < 3; i++)
            shader->Comp.LocalSize[i] = 0;
      }
      break;

   case MESA_SHADER_FRAGMENT:
      shader->redeclares_gl_fragcoord = state->fs_redeclares_gl_fragcoord;
      shader->uses_gl_fragcoord = state->fs_uses_gl_fragcoord;
      shader->pixel_center_integer = state->fs_pixel_center_integer;
      shader->origin_upper_left = state->fs_origin_upper_left;
      shader->ARB_fragment_coord_conventions_enable =
         state->ARB_fragment_coord_conventions_enable;
      break;

   default:
      /* Nothing to do. */
      break;
   }
}

extern "C" {

void
_mesa_glsl_compile_shader(struct gl_context *ctx, struct gl_shader *shader,
                          bool dump_ast, bool dump_hir)
{
   struct _mesa_glsl_parse_state *state =
      new(shader) _mesa_glsl_parse_state(ctx, shader->Stage, shader);
   const char *source = shader->Source;

   if (ctx->Const.GenerateTemporaryNames)
      ir_variable::temporaries_allocate_names = true;

   state->error = !!glcpp_preprocess(state, &source, &state->info_log,
                             &ctx->Extensions, ctx);

   if (!state->error) {
     _mesa_glsl_lexer_ctor(state, source);
     _mesa_glsl_parse(state);
     _mesa_glsl_lexer_dtor(state);
   }

   if (dump_ast) {
      foreach_list_typed(ast_node, ast, link, &state->translation_unit) {
         ast->print();
      }
      printf("\n\n");
   }

   ralloc_free(shader->ir);
   shader->ir = new(shader) exec_list;
   if (!state->error && !state->translation_unit.is_empty())
      _mesa_ast_to_hir(shader->ir, state);

   if (!state->error) {
      validate_ir_tree(shader->ir);

      /* Print out the unoptimized IR. */
      if (dump_hir) {
         _mesa_print_ir(stdout, shader->ir, state);
      }
   }


   if (!state->error && !shader->ir->is_empty()) {
      struct gl_shader_compiler_options *options =
         &ctx->Const.ShaderCompilerOptions[shader->Stage];

      /* Do some optimization at compile time to reduce shader IR size
       * and reduce later work if the same shader is linked multiple times
       */
      while (do_common_optimization(shader->ir, false, false, options,
                                    ctx->Const.NativeIntegers))
         ;

      validate_ir_tree(shader->ir);

      enum ir_variable_mode other;
      switch (shader->Stage) {
      case MESA_SHADER_VERTEX:
         other = ir_var_shader_in;
         break;
      case MESA_SHADER_FRAGMENT:
         other = ir_var_shader_out;
         break;
      default:
         /* Something invalid to ensure optimize_dead_builtin_uniforms
          * doesn't remove anything other than uniforms or constants.
          */
         other = ir_var_mode_count;
         break;
      }

      optimize_dead_builtin_variables(shader->ir, other);

      validate_ir_tree(shader->ir);
   }

   if (shader->InfoLog)
      ralloc_free(shader->InfoLog);

   shader->symbols = new(shader->ir) glsl_symbol_table;
   shader->CompileStatus = !state->error;
   shader->InfoLog = state->info_log;
   shader->Version = state->language_version;
   shader->IsES = state->es_shader;
   shader->uses_builtin_functions = state->uses_builtin_functions;

   if (!state->error)
      set_shader_inout_layout(shader, state);

   /* Retain any live IR, but trash the rest. */
   reparent_ir(shader->ir, shader->ir);

   /* Destroy the symbol table.  Create a new symbol table that contains only
    * the variables and functions that still exist in the IR.  The symbol
    * table will be used later during linking.
    *
    * There must NOT be any freed objects still referenced by the symbol
    * table.  That could cause the linker to dereference freed memory.
    *
    * We don't have to worry about types or interface-types here because those
    * are fly-weights that are looked up by glsl_type.
    */
   foreach_in_list (ir_instruction, ir, shader->ir) {
      switch (ir->ir_type) {
      case ir_type_function:
         shader->symbols->add_function((ir_function *) ir);
         break;
      case ir_type_variable: {
         ir_variable *const var = (ir_variable *) ir;

         if (var->data.mode != ir_var_temporary)
            shader->symbols->add_variable(var);
         break;
      }
      default:
         break;
      }
   }

   delete state->symbols;
   ralloc_free(state);
}

} /* extern "C" */
/**
 * Do the set of common optimizations passes
 *
 * \param ir                          List of instructions to be optimized
 * \param linked                      Is the shader linked?  This enables
 *                                    optimizations passes that remove code at
 *                                    global scope and could cause linking to
 *                                    fail.
 * \param uniform_locations_assigned  Have locations already been assigned for
 *                                    uniforms?  This prevents the declarations
 *                                    of unused uniforms from being removed.
 *                                    The setting of this flag only matters if
 *                                    \c linked is \c true.
 * \param max_unroll_iterations       Maximum number of loop iterations to be
 *                                    unrolled.  Setting to 0 disables loop
 *                                    unrolling.
 * \param options                     The driver's preferred shader options.
 */
bool
do_common_optimization(exec_list *ir, bool linked,
		       bool uniform_locations_assigned,
                       const struct gl_shader_compiler_options *options,
                       bool native_integers)
{
   GLboolean progress = GL_FALSE;

   progress = lower_instructions(ir, SUB_TO_ADD_NEG) || progress;

   if (linked) {
      progress = do_function_inlining(ir) || progress;
      progress = do_dead_functions(ir) || progress;
      progress = do_structure_splitting(ir) || progress;
   }
   progress = do_if_simplification(ir) || progress;
   progress = opt_flatten_nested_if_blocks(ir) || progress;
   progress = do_copy_propagation(ir) || progress;
   progress = do_copy_propagation_elements(ir) || progress;

   if (options->OptimizeForAOS && !linked)
      progress = opt_flip_matrices(ir) || progress;

   if (linked && options->OptimizeForAOS) {
      progress = do_vectorize(ir) || progress;
   }

   if (linked)
      progress = do_dead_code(ir, uniform_locations_assigned) || progress;
   else
      progress = do_dead_code_unlinked(ir) || progress;
   progress = do_dead_code_local(ir) || progress;
   progress = do_tree_grafting(ir) || progress;
   progress = do_constant_propagation(ir) || progress;
   if (linked)
      progress = do_constant_variable(ir) || progress;
   else
      progress = do_constant_variable_unlinked(ir) || progress;
   progress = do_constant_folding(ir) || progress;
   progress = do_minmax_prune(ir) || progress;
   progress = do_cse(ir) || progress;
   progress = do_rebalance_tree(ir) || progress;
   progress = do_algebraic(ir, native_integers, options) || progress;
   progress = do_lower_jumps(ir) || progress;
   progress = do_vec_index_to_swizzle(ir) || progress;
   progress = lower_vector_insert(ir, false) || progress;
   progress = do_swizzle_swizzle(ir) || progress;
   progress = do_noop_swizzle(ir) || progress;

   progress = optimize_split_arrays(ir, linked, false) || progress;
   progress = optimize_redundant_jumps(ir) || progress;

   loop_state *ls = analyze_loop_variables(ir);
   if (ls->loop_found) {
      progress = set_loop_controls(ir, ls) || progress;
      progress = unroll_loops(ir, ls, options) || progress;
   }
   delete ls;

   return !!progress;
}

extern "C" {

/**
 * To be called at GL teardown time, this frees compiler datastructures.
 *
 * After calling this, any previously compiled shaders and shader
 * programs would be invalid.  So this should happen at approximately
 * program exit.
 */
void
_mesa_destroy_shader_compiler(void)
{
   _mesa_destroy_shader_compiler_caches();

   _mesa_glsl_release_types();
}

/**
 * Releases compiler caches to trade off performance for memory.
 *
 * Intended to be used with glReleaseShaderCompiler().
 */
void
_mesa_destroy_shader_compiler_caches(void)
{
   _mesa_glsl_release_builtin_functions();
}

}
