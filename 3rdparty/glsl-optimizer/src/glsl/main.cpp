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
#include <getopt.h>

/** @file main.cpp
 *
 * This file is the main() routine and scaffolding for producing
 * builtin_compiler (which doesn't include builtins itself and is used
 * to generate the profile information for builtin_function.cpp), and
 * for glsl_compiler (which does include builtins and can be used to
 * offline compile GLSL code and examine the resulting GLSL IR.
 */

#include "ast.h"
#include "glsl_parser_extras.h"
#include "ir_optimization.h"
#include "program.h"
#include "loop_analysis.h"
#include "standalone_scaffolding.h"

static int glsl_version = 330;

static void
initialize_context(struct gl_context *ctx, gl_api api)
{
   initialize_context_to_defaults(ctx, api);

   /* The standalone compiler needs to claim support for almost
    * everything in order to compile the built-in functions.
    */
   ctx->Const.GLSLVersion = glsl_version;
   ctx->Extensions.ARB_ES3_compatibility = true;
   ctx->Const.MaxComputeWorkGroupCount[0] = 65535;
   ctx->Const.MaxComputeWorkGroupCount[1] = 65535;
   ctx->Const.MaxComputeWorkGroupCount[2] = 65535;
   ctx->Const.MaxComputeWorkGroupSize[0] = 1024;
   ctx->Const.MaxComputeWorkGroupSize[1] = 1024;
   ctx->Const.MaxComputeWorkGroupSize[2] = 64;
   ctx->Const.MaxComputeWorkGroupInvocations = 1024;
   ctx->Const.Program[MESA_SHADER_COMPUTE].MaxTextureImageUnits = 16;
   ctx->Const.Program[MESA_SHADER_COMPUTE].MaxUniformComponents = 1024;
   ctx->Const.Program[MESA_SHADER_COMPUTE].MaxInputComponents = 0; /* not used */
   ctx->Const.Program[MESA_SHADER_COMPUTE].MaxOutputComponents = 0; /* not used */

   switch (ctx->Const.GLSLVersion) {
   case 100:
      ctx->Const.MaxClipPlanes = 0;
      ctx->Const.MaxCombinedTextureImageUnits = 8;
      ctx->Const.MaxDrawBuffers = 2;
      ctx->Const.MinProgramTexelOffset = 0;
      ctx->Const.MaxProgramTexelOffset = 0;
      ctx->Const.MaxLights = 0;
      ctx->Const.MaxTextureCoordUnits = 0;
      ctx->Const.MaxTextureUnits = 8;

      ctx->Const.Program[MESA_SHADER_VERTEX].MaxAttribs = 8;
      ctx->Const.Program[MESA_SHADER_VERTEX].MaxTextureImageUnits = 0;
      ctx->Const.Program[MESA_SHADER_VERTEX].MaxUniformComponents = 128 * 4;
      ctx->Const.Program[MESA_SHADER_VERTEX].MaxInputComponents = 0; /* not used */
      ctx->Const.Program[MESA_SHADER_VERTEX].MaxOutputComponents = 32;

      ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxTextureImageUnits =
         ctx->Const.MaxCombinedTextureImageUnits;
      ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxUniformComponents = 16 * 4;
      ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxInputComponents =
         ctx->Const.Program[MESA_SHADER_VERTEX].MaxOutputComponents;
      ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxOutputComponents = 0; /* not used */

      ctx->Const.MaxVarying = ctx->Const.Program[MESA_SHADER_VERTEX].MaxOutputComponents / 4;
      break;
   case 110:
   case 120:
      ctx->Const.MaxClipPlanes = 6;
      ctx->Const.MaxCombinedTextureImageUnits = 2;
      ctx->Const.MaxDrawBuffers = 1;
      ctx->Const.MinProgramTexelOffset = 0;
      ctx->Const.MaxProgramTexelOffset = 0;
      ctx->Const.MaxLights = 8;
      ctx->Const.MaxTextureCoordUnits = 2;
      ctx->Const.MaxTextureUnits = 2;

      ctx->Const.Program[MESA_SHADER_VERTEX].MaxAttribs = 16;
      ctx->Const.Program[MESA_SHADER_VERTEX].MaxTextureImageUnits = 0;
      ctx->Const.Program[MESA_SHADER_VERTEX].MaxUniformComponents = 512;
      ctx->Const.Program[MESA_SHADER_VERTEX].MaxInputComponents = 0; /* not used */
      ctx->Const.Program[MESA_SHADER_VERTEX].MaxOutputComponents = 32;

      ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxTextureImageUnits =
         ctx->Const.MaxCombinedTextureImageUnits;
      ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxUniformComponents = 64;
      ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxInputComponents =
         ctx->Const.Program[MESA_SHADER_VERTEX].MaxOutputComponents;
      ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxOutputComponents = 0; /* not used */

      ctx->Const.MaxVarying = ctx->Const.Program[MESA_SHADER_VERTEX].MaxOutputComponents / 4;
      break;
   case 130:
   case 140:
      ctx->Const.MaxClipPlanes = 8;
      ctx->Const.MaxCombinedTextureImageUnits = 16;
      ctx->Const.MaxDrawBuffers = 8;
      ctx->Const.MinProgramTexelOffset = -8;
      ctx->Const.MaxProgramTexelOffset = 7;
      ctx->Const.MaxLights = 8;
      ctx->Const.MaxTextureCoordUnits = 8;
      ctx->Const.MaxTextureUnits = 2;

      ctx->Const.Program[MESA_SHADER_VERTEX].MaxAttribs = 16;
      ctx->Const.Program[MESA_SHADER_VERTEX].MaxTextureImageUnits = 16;
      ctx->Const.Program[MESA_SHADER_VERTEX].MaxUniformComponents = 1024;
      ctx->Const.Program[MESA_SHADER_VERTEX].MaxInputComponents = 0; /* not used */
      ctx->Const.Program[MESA_SHADER_VERTEX].MaxOutputComponents = 64;

      ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxTextureImageUnits = 16;
      ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxUniformComponents = 1024;
      ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxInputComponents =
         ctx->Const.Program[MESA_SHADER_VERTEX].MaxOutputComponents;
      ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxOutputComponents = 0; /* not used */

      ctx->Const.MaxVarying = ctx->Const.Program[MESA_SHADER_VERTEX].MaxOutputComponents / 4;
      break;
   case 150:
   case 330:
      ctx->Const.MaxClipPlanes = 8;
      ctx->Const.MaxDrawBuffers = 8;
      ctx->Const.MinProgramTexelOffset = -8;
      ctx->Const.MaxProgramTexelOffset = 7;
      ctx->Const.MaxLights = 8;
      ctx->Const.MaxTextureCoordUnits = 8;
      ctx->Const.MaxTextureUnits = 2;

      ctx->Const.Program[MESA_SHADER_VERTEX].MaxAttribs = 16;
      ctx->Const.Program[MESA_SHADER_VERTEX].MaxTextureImageUnits = 16;
      ctx->Const.Program[MESA_SHADER_VERTEX].MaxUniformComponents = 1024;
      ctx->Const.Program[MESA_SHADER_VERTEX].MaxInputComponents = 0; /* not used */
      ctx->Const.Program[MESA_SHADER_VERTEX].MaxOutputComponents = 64;

      ctx->Const.Program[MESA_SHADER_GEOMETRY].MaxTextureImageUnits = 16;
      ctx->Const.Program[MESA_SHADER_GEOMETRY].MaxUniformComponents = 1024;
      ctx->Const.Program[MESA_SHADER_GEOMETRY].MaxInputComponents =
         ctx->Const.Program[MESA_SHADER_VERTEX].MaxOutputComponents;
      ctx->Const.Program[MESA_SHADER_GEOMETRY].MaxOutputComponents = 128;

      ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxTextureImageUnits = 16;
      ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxUniformComponents = 1024;
      ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxInputComponents =
         ctx->Const.Program[MESA_SHADER_GEOMETRY].MaxOutputComponents;
      ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxOutputComponents = 0; /* not used */

      ctx->Const.MaxCombinedTextureImageUnits =
         ctx->Const.Program[MESA_SHADER_VERTEX].MaxTextureImageUnits
         + ctx->Const.Program[MESA_SHADER_GEOMETRY].MaxTextureImageUnits
         + ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxTextureImageUnits;

      ctx->Const.MaxGeometryOutputVertices = 256;
      ctx->Const.MaxGeometryTotalOutputComponents = 1024;

//      ctx->Const.MaxGeometryVaryingComponents = 64;

      ctx->Const.MaxVarying = 60 / 4;
      break;
   case 300:
      ctx->Const.MaxClipPlanes = 8;
      ctx->Const.MaxCombinedTextureImageUnits = 32;
      ctx->Const.MaxDrawBuffers = 4;
      ctx->Const.MinProgramTexelOffset = -8;
      ctx->Const.MaxProgramTexelOffset = 7;
      ctx->Const.MaxLights = 0;
      ctx->Const.MaxTextureCoordUnits = 0;
      ctx->Const.MaxTextureUnits = 0;

      ctx->Const.Program[MESA_SHADER_VERTEX].MaxAttribs = 16;
      ctx->Const.Program[MESA_SHADER_VERTEX].MaxTextureImageUnits = 16;
      ctx->Const.Program[MESA_SHADER_VERTEX].MaxUniformComponents = 1024;
      ctx->Const.Program[MESA_SHADER_VERTEX].MaxInputComponents = 0; /* not used */
      ctx->Const.Program[MESA_SHADER_VERTEX].MaxOutputComponents = 16 * 4;

      ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxTextureImageUnits = 16;
      ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxUniformComponents = 224;
      ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxInputComponents = 15 * 4;
      ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxOutputComponents = 0; /* not used */

      ctx->Const.MaxVarying = ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxInputComponents / 4;
      break;
   }

   ctx->Driver.NewShader = _mesa_new_shader;
}

/* Returned string will have 'ctx' as its ralloc owner. */
static char *
load_text_file(void *ctx, const char *file_name)
{
	char *text = NULL;
	size_t size;
	size_t total_read = 0;
	FILE *fp = fopen(file_name, "rb");

	if (!fp) {
		return NULL;
	}

	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	text = (char *) ralloc_size(ctx, size + 1);
	if (text != NULL) {
		do {
			size_t bytes = fread(text + total_read,
					     1, size - total_read, fp);
			if (bytes < size - total_read) {
				free(text);
				text = NULL;
				goto error;
			}

			if (bytes == 0) {
				break;
			}

			total_read += bytes;
		} while (total_read < size);

		text[total_read] = '\0';
error:;
	}

	fclose(fp);

	return text;
}

int dump_ast = 0;
int dump_hir = 0;
int dump_lir = 0;
int do_link = 0;

const struct option compiler_opts[] = {
   { "dump-ast", no_argument, &dump_ast, 1 },
   { "dump-hir", no_argument, &dump_hir, 1 },
   { "dump-lir", no_argument, &dump_lir, 1 },
   { "link",     no_argument, &do_link,  1 },
   { "version",  required_argument, NULL, 'v' },
   { NULL, 0, NULL, 0 }
};

/**
 * \brief Print proper usage and exit with failure.
 */
void
usage_fail(const char *name)
{

   const char *header =
      "usage: %s [options] <file.vert | file.geom | file.frag>\n"
      "\n"
      "Possible options are:\n";
   printf(header, name, name);
   for (const struct option *o = compiler_opts; o->name != 0; ++o) {
      printf("    --%s\n", o->name);
   }
   exit(EXIT_FAILURE);
}


void
compile_shader(struct gl_context *ctx, struct gl_shader *shader)
{
   struct _mesa_glsl_parse_state *state =
      new(shader) _mesa_glsl_parse_state(ctx, shader->Stage, shader);

   _mesa_glsl_compile_shader(ctx, shader, dump_ast, dump_hir);

   /* Print out the resulting IR */
   if (!state->error && dump_lir) {
      _mesa_print_ir(shader->ir, state);
   }

   return;
}

int
main(int argc, char **argv)
{
   int status = EXIT_SUCCESS;
   struct gl_context local_ctx;
   struct gl_context *ctx = &local_ctx;
   bool glsl_es = false;

   int c;
   int idx = 0;
   while ((c = getopt_long(argc, argv, "", compiler_opts, &idx)) != -1) {
      switch (c) {
      case 'v':
         glsl_version = strtol(optarg, NULL, 10);
         switch (glsl_version) {
         case 100:
         case 300:
            glsl_es = true;
            break;
         case 110:
         case 120:
         case 130:
         case 140:
         case 150:
         case 330:
            glsl_es = false;
            break;
         default:
            fprintf(stderr, "Unrecognized GLSL version `%s'\n", optarg);
            usage_fail(argv[0]);
            break;
         }
         break;
      default:
         break;
      }
   }


   if (argc <= optind)
      usage_fail(argv[0]);

   initialize_context(ctx, (glsl_es) ? API_OPENGLES2 : API_OPENGL_COMPAT);

   struct gl_shader_program *whole_program;

   whole_program = rzalloc (NULL, struct gl_shader_program);
   assert(whole_program != NULL);
   whole_program->InfoLog = ralloc_strdup(whole_program, "");

   for (/* empty */; argc > optind; optind++) {
      whole_program->Shaders =
	 reralloc(whole_program, whole_program->Shaders,
		  struct gl_shader *, whole_program->NumShaders + 1);
      assert(whole_program->Shaders != NULL);

      struct gl_shader *shader = rzalloc(whole_program, gl_shader);

      whole_program->Shaders[whole_program->NumShaders] = shader;
      whole_program->NumShaders++;

      const unsigned len = strlen(argv[optind]);
      if (len < 6)
	 usage_fail(argv[0]);

      const char *const ext = & argv[optind][len - 5];
      if (strncmp(".vert", ext, 5) == 0 || strncmp(".glsl", ext, 5) == 0)
	 shader->Type = GL_VERTEX_SHADER;
      else if (strncmp(".geom", ext, 5) == 0)
	 shader->Type = GL_GEOMETRY_SHADER;
      else if (strncmp(".frag", ext, 5) == 0)
	 shader->Type = GL_FRAGMENT_SHADER;
      else if (strncmp(".comp", ext, 5) == 0)
         shader->Type = GL_COMPUTE_SHADER;
      else
	 usage_fail(argv[0]);
      shader->Stage = _mesa_shader_enum_to_shader_stage(shader->Type);

      shader->Source = load_text_file(whole_program, argv[optind]);
      if (shader->Source == NULL) {
	 printf("File \"%s\" does not exist.\n", argv[optind]);
	 exit(EXIT_FAILURE);
      }

      compile_shader(ctx, shader);

      if (strlen(shader->InfoLog) > 0)
	 printf("Info log for %s:\n%s\n", argv[optind], shader->InfoLog);

      if (!shader->CompileStatus) {
	 status = EXIT_FAILURE;
	 break;
      }
   }

   if ((status == EXIT_SUCCESS) && do_link)  {
      link_shaders(ctx, whole_program);
      status = (whole_program->LinkStatus) ? EXIT_SUCCESS : EXIT_FAILURE;

      if (strlen(whole_program->InfoLog) > 0)
	 printf("Info log for linking:\n%s\n", whole_program->InfoLog);
   }

   for (unsigned i = 0; i < MESA_SHADER_STAGES; i++)
      ralloc_free(whole_program->_LinkedShaders[i]);

   ralloc_free(whole_program);
   _mesa_glsl_release_types();
   _mesa_glsl_release_builtin_functions();

   return status;
}
