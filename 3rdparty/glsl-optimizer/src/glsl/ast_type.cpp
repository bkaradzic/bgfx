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
extern "C" {
#include "program/symbol_table.h"
}

void
ast_type_specifier::print(void) const
{
   if (structure) {
      structure->print();
   } else {
      printf("%s ", type_name);
   }

   if (is_array) {
      printf("[ ");

      if (array_size) {
	 array_size->print();
      }

      printf("] ");
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

   /* Uniform block layout qualifiers get to overwrite each
    * other (rightmost having priority), while all other
    * qualifiers currently don't allow duplicates.
    */

   if ((this->flags.i & q.flags.i & ~(ubo_mat_mask.flags.i |
				      ubo_layout_mask.flags.i)) != 0) {
      _mesa_glsl_error(loc, state,
		       "duplicate layout qualifiers used\n");
      return false;
   }

   if ((q.flags.i & ubo_mat_mask.flags.i) != 0)
      this->flags.i &= ~ubo_mat_mask.flags.i;
   if ((q.flags.i & ubo_layout_mask.flags.i) != 0)
      this->flags.i &= ~ubo_layout_mask.flags.i;

   this->flags.i |= q.flags.i;

   if (q.flags.q.explicit_location)
      this->location = q.location;

   if (q.flags.q.explicit_index)
      this->index = q.index;

   return true;
}

