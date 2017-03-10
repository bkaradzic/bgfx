/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_UTILS_H_HEADER_GUARD
#define BGFX_UTILS_H_HEADER_GUARD

#include <bgfx/bgfx.h>
#include "image.h"

///
void* load(const char* _filePath, uint32_t* _size = NULL);

///
void unload(void* _ptr);

///
bgfx::ShaderHandle loadShader(const char* _name);

///
bgfx::ProgramHandle loadProgram(const char* _vsName, const char* _fsName);

///
bgfx::TextureHandle loadTexture(const char* _name, uint32_t _flags = BGFX_TEXTURE_NONE, uint8_t _skip = 0, bgfx::TextureInfo* _info = NULL);

///
bgfx::ImageContainer* imageLoad(const char* _filePath, bgfx::TextureFormat::Enum _dstFormat);

///
void calcTangents(void* _vertices, uint16_t _numVertices, bgfx::VertexDecl _decl, const uint16_t* _indices, uint32_t _numIndices);

/// Returns true if both internal transient index and vertex buffer have
/// enough space.
///
/// @param[in] _numVertices Number of vertices.
/// @param[in] _decl Vertex declaration.
/// @param[in] _numIndices Number of indices.
///
inline bool checkAvailTransientBuffers(uint32_t _numVertices, const bgfx::VertexDecl& _decl, uint32_t _numIndices)
{
	return _numVertices == bgfx::getAvailTransientVertexBuffer(_numVertices, _decl)
		&& _numIndices  == bgfx::getAvailTransientIndexBuffer(_numIndices)
		;
}

///
struct MeshState
{
	struct Texture
	{
		uint32_t            m_flags;
		bgfx::UniformHandle m_sampler;
		bgfx::TextureHandle m_texture;
		uint8_t             m_stage;
	};

	Texture             m_textures[4];
	uint64_t            m_state;
	bgfx::ProgramHandle m_program;
	uint8_t             m_numTextures;
	uint8_t             m_viewId;
};

struct Mesh;

///
Mesh* meshLoad(const char* _filePath);

///
void meshUnload(Mesh* _mesh);

///
MeshState* meshStateCreate();

///
void meshStateDestroy(MeshState* _meshState);

///
void meshSubmit(const Mesh* _mesh, uint8_t _id, bgfx::ProgramHandle _program, const float* _mtx, uint64_t _state = BGFX_STATE_MASK);

///
void meshSubmit(const Mesh* _mesh, const MeshState*const* _state, uint8_t _numPasses, const float* _mtx, uint16_t _numMatrices = 1);

///
struct Args
{
	Args(int _argc, char** _argv);

	bgfx::RendererType::Enum m_type;
	uint16_t m_pciId;
};

#endif // BGFX_UTILS_H_HEADER_GUARD
