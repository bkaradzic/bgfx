/**
    This code is based on the glslang_c_interface implementation by Viktor Latypov
**/

/**
BSD 2-Clause License

Copyright (c) 2019, Viktor Latypov
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/

#ifndef GLSLANG_C_IFACE_H_INCLUDED
#define GLSLANG_C_IFACE_H_INCLUDED

#include <stdlib.h>

#include "glslang_c_shader_types.h"

typedef struct glslang_shader_s glslang_shader_t;
typedef struct glslang_program_s glslang_program_t;

typedef struct glslang_input_s {
    glslang_source_t language;
    glslang_stage_t stage;
    glslang_client_t client;
    glslang_target_client_version_t client_version;
    glslang_target_language_t target_language;
    glslang_target_language_version_t target_language_version;
    /** Shader source code */
    const char* code;
    int default_version;
    glslang_profile_t default_profile;
    int force_default_version_and_profile;
    int forward_compatible;
    glslang_messages_t messages;
} glslang_input_t;

/* Inclusion result structure allocated by C include_local/include_system callbacks */
typedef struct glsl_include_result_s {
    /* Header file name or NULL if inclusion failed */
    const char* header_name;

    /* Header contents or NULL */
    const char* header_data;
    size_t header_length;

} glsl_include_result_t;

/* Callback for local file inclusion */
typedef glsl_include_result_t* (*glsl_include_local_func)(void* ctx, const char* header_name, const char* includer_name,
                                                          size_t include_depth);

/* Callback for system file inclusion */
typedef glsl_include_result_t* (*glsl_include_system_func)(void* ctx, const char* header_name,
                                                           const char* includer_name, size_t include_depth);

/* Callback for include result destruction */
typedef int (*glsl_free_include_result_func)(void* ctx, glsl_include_result_t* result);

/* Collection of callbacks for GLSL preprocessor */
typedef struct glsl_include_callbacks_s {
    glsl_include_system_func include_system;
    glsl_include_local_func include_local;
    glsl_free_include_result_func free_include_result;
} glsl_include_callbacks_t;

#ifdef __cplusplus
extern "C" {
#endif

int glslang_initialize_process();
void glslang_finalize_process();

glslang_shader_t* glslang_shader_create(const glslang_input_t* input);
void glslang_shader_delete(glslang_shader_t* shader);
int glslang_shader_preprocess(glslang_shader_t* shader, const glslang_input_t* input);
int glslang_shader_parse(glslang_shader_t* shader, const glslang_input_t* input);
const char* glslang_shader_get_preprocessed_code(glslang_shader_t* shader);
const char* glslang_shader_get_info_log(glslang_shader_t* shader);
const char* glslang_shader_get_info_debug_log(glslang_shader_t* shader);

glslang_program_t* glslang_program_create();
void glslang_program_delete(glslang_program_t* program);
void glslang_program_add_shader(glslang_program_t* program, glslang_shader_t* shader);
int glslang_program_link(glslang_program_t* program, int messages); // glslang_messages_t
void glslang_program_SPIRV_generate(glslang_program_t* program, glslang_stage_t stage);
size_t glslang_program_SPIRV_get_size(glslang_program_t* program);
void glslang_program_SPIRV_get(glslang_program_t* program, unsigned int*);
unsigned int* glslang_program_SPIRV_get_ptr(glslang_program_t* program);
const char* glslang_program_SPIRV_get_messages(glslang_program_t* program);
const char* glslang_program_get_info_log(glslang_program_t* program);
const char* glslang_program_get_info_debug_log(glslang_program_t* program);

#ifdef __cplusplus
}
#endif

#endif /* #ifdef GLSLANG_C_IFACE_INCLUDED */
