/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef BGFX_UTILS_H_HEADER_GUARD
#define BGFX_UTILS_H_HEADER_GUARD

#include <bgfx.h>

void* load(const char* _filePath);
bgfx::ShaderHandle loadShader(const char* _name);
bgfx::ProgramHandle loadProgram(const char* _vsName, const char* _fsName);
bgfx::TextureHandle loadTexture(const char* _name, uint32_t _flags = BGFX_TEXTURE_NONE, uint8_t _skip = 0, bgfx::TextureInfo* _info = NULL);
void calcTangents(void* _vertices, uint16_t _numVertices, bgfx::VertexDecl _decl, const uint16_t* _indices, uint32_t _numIndices);

struct Mesh;
Mesh* meshLoad(const char* _filePath);
void meshUnload(Mesh* _mesh);
void meshSubmit(Mesh* _mesh, uint8_t _id, bgfx::ProgramHandle _program, float* _mtx, uint64_t _state = BGFX_STATE_MASK);

#endif // BGFX_UTILS_H_HEADER_GUARD
