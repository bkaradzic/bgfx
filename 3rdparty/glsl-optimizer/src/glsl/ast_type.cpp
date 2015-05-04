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

#include "ast.h"

void
ast_type_specifier::print(void) const
{
   if (structure) {
      structure->print();
   } else {
      printf("%s ", type_name);
   }

   if (array_specifier) {
      array_specifier->print();
   }
}

bool
ast_fully_specified_type::has_qualifiers() const
{
   return this->qualifier.flags.i != 0;
}

bool ast_type_qualifier::has_interpolation() const
{
   return this->flags.q.smooth
          || this->flags.q.flat
          || this->flags.q.noperspective;
}

bool
ast_type_qualifier::has_layout() const
{
   return this->flags.q.origin_upper_left
          || this->flags.q.pixel_center_integer
          || this->flags.q.depth_any
          || this->flags.q.depth_greater
          || this->flags.q.depth_less
          || this->flags.q.depth_unchanged
          || this->flags.q.std140
          || this->flags.q.shared
          || this->flags.q.column_major
          || this->flags.q.row_major
          || this->flags.q.packed
          || this->flags.q.explicit_location
          || this->flags.q.explicit_index
          || this->flags.q.explicit_binding
          || this->flags.q.explicit_offset;
}

bool
ast_type_qualifier::has_storage() const
{
   return this->flags.q.constant
          || this->flags.q.attribute
          || this->flags.q.varying
          || this->flags.q.in
          || this->flags.q.out
          || this->flags.q.uniform;
}

bool
ast_type_qualifier::has_auxiliary_storage() const
{
   return this->flags.q.centroid
          || this->flags.q.sample;
}

const char*
ast_type_qualifier::interpolation_string() const
{
   if (this->flags.q.smooth)
      return "smooth";
   else if (this->flags.q.flat)
      return "flat";
   else if (this->flags.q.noperspective)
      return "noperspective";
   else
      return NULL;
}

bool
ast_type_qualifier::merge_qualifier(YYLTYPE *loc,
				    _mesa_glsl_parse_state *state,
				    ast_type_qualifier q)
{
   ast_type_qualifier ubo_mat_mask;
   ubo_mat_mask.flags.i = 0;
   ubo_mat_mask.flags.q.row_major = 1;
   ubo_mat_mask.flags.q.column_major = 1;

   ast_type_qualifier ubo_layout_mask;
   ubo_layout_mask.flags.i = 0;
   ubo_layout_mask.flags.q.std140 = 1;
   ubo_layout_mask.flags.q.packed = 1;
   ubo_layout_mask.flags.q.shared = 1;

   ast_type_qualifier ubo_binding_mask;
   ubo_binding_mask.flags.i = 0;
   ubo_binding_mask.flags.q.explicit_binding = 1;
   ubo_binding_mask.flags.q.explicit_offset = 1;

   ast_type_qualifier stream_layout_mask;
   stream_layout_mask.flags.i = 0;
   stream_layout_mask.flags.q.stream = 1;

   /* Uniform block layout qualifiers get to overwrite each
    * other (rightmost having priority), while all other
    * qualifiers currently don't allow duplicates.
    */
   ast_type_qualifier allowed_duplicates_mask;
   allowed_duplicates_mask.flags.i =
      ubo_mat_mask.flags.i |
      ubo_layout_mask.flags.i |
      ubo_binding_mask.flags.i;

   /* Geometry shaders can have several layout qualifiers
    * assigning different stream values.
    */
   if (state->stage == MESA_SHADER_GEOMETRY)
      allowed_duplicates_mask.flags.i |=
         stream_layout_mask.flags.i;

   if ((this->flags.i & q.flags.i & ~allowed_duplicates_mask.flags.i) != 0) {
      _mesa_glsl_error(loc, state,
		       "duplicate layout qualifiers used");
      return false;
   }

   if (q.flags.q.prim_type) {
      if (this->flags.q.prim_type && this->prim_type != q.prim_type) {
	 _mesa_glsl_error(loc, state,
			  "conflicting primitive type qualifiers used");
	 return false;
      }
      this->prim_type = q.prim_type;
   }

   if (q.flags.q.max_vertices) {
      if (this->flags.q.max_vertices && this->max_vertices != q.max_vertices) {
	 _mesa_glsl_error(loc, state,
			  "geometry shader set conflicting max_vertices "
			  "(%d and %d)", this->max_vertices, q.max_vertices);
	 return false;
      }
      this->max_vertices = q.max_vertices;
   }

   if (q.flags.q.invocations) {
      if (this->flags.q.invocations && this->invocations != q.invocations) {
         _mesa_glsl_error(loc, state,
                          "geometry shader set conflicting invocations "
                          "(%d and %d)", this->invocations, q.invocations);
         return false;
      }
      this->invocations = q.invocations;
   }

   if (state->stage == MESA_SHADER_GEOMETRY &&
       state->has_explicit_attrib_stream()) {
      if (q.flags.q.stream && q.stream >= state->ctx->Const.MaxVertexStreams) {
         _mesa_glsl_error(loc, state,
                          "`stream' value is larger than MAX_VERTEX_STREAMS - 1 "
                          "(%d > %d)",
                          q.stream, state->ctx->Const.MaxVertexStreams - 1);
      }
      if (this->flags.q.explicit_stream &&
          this->stream >= state->ctx->Const.MaxVertexStreams) {
         _mesa_glsl_error(loc, state,
                          "`stream' value is larger than MAX_VERTEX_STREAMS - 1 "
                          "(%d > %d)",
                          this->stream, state->ctx->Const.MaxVertexStreams - 1);
      }

      if (!this->flags.q.explicit_stream) {
         if (q.flags.q.stream) {
            this->flags.q.stream = 1;
            this->stream = q.stream;
         } else if (!this->flags.q.stream && this->flags.q.out) {
            /* Assign default global stream value */
            this->flags.q.stream = 1;
            this->stream = state->out_qualifier->stream;
         }
      } else {
         if (q.flags.q.explicit_stream) {
            _mesa_glsl_error(loc, state,
                             "duplicate layout `stream' qualifier");
         }
      }
   }

   if ((q.flags.i & ubo_mat_mask.flags.i) != 0)
      this->flags.i &= ~ubo_mat_mask.flags.i;
   if ((q.flags.i & ubo_layout_mask.flags.i) != 0)
      this->flags.i &= ~ubo_layout_mask.flags.i;

   for (int i = 0; i < 3; i++) {
      if (q.flags.q.local_size & (1 << i)) {
         if ((this->flags.q.local_size & (1 << i)) &&
             this->local_size[i] != q.local_size[i]) {
            _mesa_glsl_error(loc, state,
                             "compute shader set conflicting values for "
                             "local_size_%c (%d and %d)", 'x' + i,
                             this->local_size[i], q.local_size[i]);
            return false;
         }
         this->local_size[i] = q.local_size[i];
      }
   }

   this->flags.i |= q.flags.i;

   if (q.flags.q.explicit_location)
      this->location = q.location;

   if (q.flags.q.explicit_index)
      this->index = q.index;

   if (q.flags.q.explicit_binding)
      this->binding = q.binding;

   if (q.flags.q.explicit_offset)
      this->offset = q.offset;

   if (q.precision != ast_precision_none)
      this->precision = q.precision;

   if (q.flags.q.explicit_image_format) {
      this->image_format = q.image_format;
      this->image_base_type = q.image_base_type;
   }

   return true;
}

bool
ast_type_qualifier::merge_in_qualifier(YYLTYPE *loc,
                                       _mesa_glsl_parse_state *state,
                                       ast_type_qualifier q,
                                       ast_node* &node)
{
   void *mem_ctx = state;
   bool create_gs_ast = false;
   bool create_cs_ast = false;
   ast_type_qualifier valid_in_mask;
   valid_in_mask.flags.i = 0;

   switch (state->stage) {
   case MESA_SHADER_GEOMETRY:
      if (q.flags.q.prim_type) {
         /* Make sure this is a valid input primitive type. */
         switch (q.prim_type) {
         case GL_POINTS:
         case GL_LINES:
         case GL_LINES_ADJACENCY:
         case GL_TRIANGLES:
         case GL_TRIANGLES_ADJACENCY:
            break;
         default:
            _mesa_glsl_error(loc, state,
                             "invalid geometry shader input primitive type");
            break;
         }
      }

      create_gs_ast |=
         q.flags.q.prim_type &&
         !state->in_qualifier->flags.q.prim_type;

      valid_in_mask.flags.q.prim_type = 1;
      valid_in_mask.flags.q.invocations = 1;
      break;
   case MESA_SHADER_FRAGMENT:
      if (q.flags.q.early_fragment_tests) {
         state->early_fragment_tests = true;
      } else {
         _mesa_glsl_error(loc, state, "invalid input layout qualifier");
      }
      break;
   case MESA_SHADER_COMPUTE:
      create_cs_ast |=
         q.flags.q.local_size != 0 &&
         state->in_qualifier->flags.q.local_size == 0;

      valid_in_mask.flags.q.local_size = 7;
      break;
   default:
      _mesa_glsl_error(loc, state,
                       "input layout qualifiers only valid in "
                       "geometry, fragment and compute shaders");
      break;
   }

   /* Generate an error when invalid input layout qualifiers are used. */
   if ((q.flags.i & ~valid_in_mask.flags.i) != 0) {
      _mesa_glsl_error(loc, state,
		       "invalid input layout qualifiers used");
      return false;
   }

   /* Input layout qualifiers can be specified multiple
    * times in separate declarations, as long as they match.
    */
   if (this->flags.q.prim_type) {
      if (q.flags.q.prim_type &&
          this->prim_type != q.prim_type) {
         _mesa_glsl_error(loc, state,
                          "conflicting input primitive types specified");
      }
   } else if (q.flags.q.prim_type) {
      state->in_qualifier->flags.q.prim_type = 1;
      state->in_qualifier->prim_type = q.prim_type;
   }

   if (this->flags.q.invocations &&
       q.flags.q.invocations &&
       this->invocations != q.invocations) {
      _mesa_glsl_error(loc, state,
                       "conflicting invocations counts specified");
      return false;
   } else if (q.flags.q.invocations) {
      this->flags.q.invocations = 1;
      this->invocations = q.invocations;
   }

   if (create_gs_ast) {
      node = new(mem_ctx) ast_gs_input_layout(*loc, q.prim_type);
   } else if (create_cs_ast) {
      /* Infer a local_size of 1 for every unspecified dimension */
      unsigned local_size[3];
      for (int i = 0; i < 3; i++) {
         if (q.flags.q.local_size & (1 << i))
            local_size[i] = q.local_size[i];
         else
            local_size[i] = 1;
      }
      node = new(mem_ctx) ast_cs_input_layout(*loc, local_size);
   }

   return true;
}
