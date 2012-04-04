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

#include "main/core.h" /* for slot numbers */

struct builtin_variable {
   enum ir_variable_mode mode;
   int slot;
   const char *type;
   const char *name;
};

static const builtin_variable builtin_core_vs_variables[] = {
   { ir_var_out, VERT_RESULT_HPOS, "vec4",  "gl_Position" },
   { ir_var_out, VERT_RESULT_PSIZ, "float", "gl_PointSize" },
};

static const builtin_variable builtin_core_fs_variables[] = {
   { ir_var_in,  FRAG_ATTRIB_WPOS,  "vec4",  "gl_FragCoord" },
   { ir_var_in,  FRAG_ATTRIB_FACE,  "bool",  "gl_FrontFacing" },
   { ir_var_out, FRAG_RESULT_COLOR, "vec4",  "gl_FragColor" },
};

static const builtin_variable builtin_100ES_fs_variables[] = {
   { ir_var_in,  FRAG_ATTRIB_PNTC,   "vec2",   "gl_PointCoord" },
};

static const builtin_variable builtin_110_fs_variables[] = {
   { ir_var_out, FRAG_RESULT_DEPTH, "float", "gl_FragDepth" },
};

static const builtin_variable builtin_110_deprecated_fs_variables[] = {
   { ir_var_in,  FRAG_ATTRIB_COL0,  "vec4",  "gl_Color" },
   { ir_var_in,  FRAG_ATTRIB_COL1,  "vec4",  "gl_SecondaryColor" },
   { ir_var_in,  FRAG_ATTRIB_FOGC,  "float", "gl_FogFragCoord" },
};

static const builtin_variable builtin_110_deprecated_vs_variables[] = {
   { ir_var_in,  VERT_ATTRIB_POS,    "vec4",  "gl_Vertex" },
   { ir_var_in,  VERT_ATTRIB_NORMAL, "vec3",  "gl_Normal" },
   { ir_var_in,  VERT_ATTRIB_COLOR0, "vec4",  "gl_Color" },
   { ir_var_in,  VERT_ATTRIB_COLOR1, "vec4",  "gl_SecondaryColor" },
   { ir_var_in,  VERT_ATTRIB_TEX0,   "vec4",  "gl_MultiTexCoord0" },
   { ir_var_in,  VERT_ATTRIB_TEX1,   "vec4",  "gl_MultiTexCoord1" },
   { ir_var_in,  VERT_ATTRIB_TEX2,   "vec4",  "gl_MultiTexCoord2" },
   { ir_var_in,  VERT_ATTRIB_TEX3,   "vec4",  "gl_MultiTexCoord3" },
   { ir_var_in,  VERT_ATTRIB_TEX4,   "vec4",  "gl_MultiTexCoord4" },
   { ir_var_in,  VERT_ATTRIB_TEX5,   "vec4",  "gl_MultiTexCoord5" },
   { ir_var_in,  VERT_ATTRIB_TEX6,   "vec4",  "gl_MultiTexCoord6" },
   { ir_var_in,  VERT_ATTRIB_TEX7,   "vec4",  "gl_MultiTexCoord7" },
   { ir_var_in,  VERT_ATTRIB_FOG,    "float", "gl_FogCoord" },
   { ir_var_out, VERT_RESULT_HPOS,   "vec4",  "gl_ClipVertex" },
   { ir_var_out, VERT_RESULT_COL0,   "vec4",  "gl_FrontColor" },
   { ir_var_out, VERT_RESULT_BFC0,   "vec4",  "gl_BackColor" },
   { ir_var_out, VERT_RESULT_COL1,   "vec4",  "gl_FrontSecondaryColor" },
   { ir_var_out, VERT_RESULT_BFC1,   "vec4",  "gl_BackSecondaryColor" },
   { ir_var_out, VERT_RESULT_FOGC,   "float", "gl_FogFragCoord" },
};

static const builtin_variable builtin_120_fs_variables[] = {
   { ir_var_in,  FRAG_ATTRIB_PNTC,   "vec2",   "gl_PointCoord" },
};

static const builtin_variable builtin_130_vs_variables[] = {
   { ir_var_in,  -1,                 "int",   "gl_VertexID" },
};

static const builtin_variable builtin_110_deprecated_uniforms[] = {
   { ir_var_uniform, -1, "mat4", "gl_ModelViewMatrix" },
   { ir_var_uniform, -1, "mat4", "gl_ProjectionMatrix" },
   { ir_var_uniform, -1, "mat4", "gl_ModelViewProjectionMatrix" },
   { ir_var_uniform, -1, "mat3", "gl_NormalMatrix" },
   { ir_var_uniform, -1, "mat4", "gl_ModelViewMatrixInverse" },
   { ir_var_uniform, -1, "mat4", "gl_ProjectionMatrixInverse" },
   { ir_var_uniform, -1, "mat4", "gl_ModelViewProjectionMatrixInverse" },
   { ir_var_uniform, -1, "mat4", "gl_ModelViewMatrixTranspose" },
   { ir_var_uniform, -1, "mat4", "gl_ProjectionMatrixTranspose" },
   { ir_var_uniform, -1, "mat4", "gl_ModelViewProjectionMatrixTranspose" },
   { ir_var_uniform, -1, "mat4", "gl_ModelViewMatrixInverseTranspose" },
   { ir_var_uniform, -1, "mat4", "gl_ProjectionMatrixInverseTranspose" },
   { ir_var_uniform, -1, "mat4", "gl_ModelViewProjectionMatrixInverseTranspose" },
   { ir_var_uniform, -1, "float", "gl_NormalScale" },
   { ir_var_uniform, -1, "gl_LightModelParameters", "gl_LightModel"},

   /* Mesa-internal ATI_envmap_bumpmap state. */
   { ir_var_uniform, -1, "vec2", "gl_MESABumpRotMatrix0"},
   { ir_var_uniform, -1, "vec2", "gl_MESABumpRotMatrix1"},
   { ir_var_uniform, -1, "vec4", "gl_MESAFogParamsOptimized"},
};

