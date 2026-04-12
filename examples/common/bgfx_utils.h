/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_UTILS_H_HEADER_GUARD
#define BGFX_UTILS_H_HEADER_GUARD

#include <bx/bounds.h>
#include <bx/pixelformat.h>
#include <bx/filepath.h>
#include <bgfx/bgfx.h>
#include <bimg/bimg.h>

#include <tinystl/allocator.h>
#include <tinystl/vector.h>
namespace stl = tinystl;

#include "args.h"

/// Load file contents into memory.
///
/// @param[in] _filePath File path to load.
/// @param[out] _size If non-NULL, will be set to the size of the loaded data.
///
/// @returns Pointer to loaded data. Must be freed with `unload`.
///
void* load(const bx::FilePath& _filePath, uint32_t* _size = NULL);

/// Free memory allocated by `load`.
///
/// @param[in] _ptr Pointer to data returned by `load`.
///
void unload(void* _ptr);

/// Load shader from file.
///
/// @param[in] _name Shader name.
///
/// @returns Shader handle.
///
bgfx::ShaderHandle loadShader(const bx::StringView& _name);

/// Load shader program from vertex and fragment shader files.
///
/// @param[in] _vsName Vertex shader name.
/// @param[in] _fsName Fragment shader name.
///
/// @returns Program handle.
///
bgfx::ProgramHandle loadProgram(const bx::StringView& _vsName, const bx::StringView& _fsName);

/// Load texture from file.
///
/// @param[in] _filePath File path to texture.
/// @param[in] _flags Texture creation flags.
/// @param[in] _skip Number of top-level mip levels to skip.
/// @param[out] _info If non-NULL, will be filled with texture info.
/// @param[out] _orientation If non-NULL, will be filled with image orientation.
///
/// @returns Texture handle.
///
bgfx::TextureHandle loadTexture(const bx::FilePath& _filePath, uint64_t _flags = BGFX_TEXTURE_NONE|BGFX_SAMPLER_NONE, uint8_t _skip = 0, bgfx::TextureInfo* _info = NULL, bimg::Orientation::Enum* _orientation = NULL);

/// Load image container from file.
///
/// @param[in] _filePath File path to image.
/// @param[in] _dstFormat Destination texture format.
///
/// @returns Pointer to image container.
///
bimg::ImageContainer* imageLoad(const bx::FilePath& _filePath, bgfx::TextureFormat::Enum _dstFormat);

/// Calculate tangent vectors for a vertex/index buffer pair.
///
/// @param[in,out] _vertices Vertex stream (tangent attribute will be written).
/// @param[in] _numVertices Number of vertices.
/// @param[in] _layout Vertex stream layout.
/// @param[in] _indices Index buffer.
/// @param[in] _numIndices Number of indices.
///
void calcTangents(void* _vertices, uint16_t _numVertices, bgfx::VertexLayout _layout, const uint16_t* _indices, uint32_t _numIndices);

/// Weld vertices by position. Generates a remap table that maps each vertex
/// to the first vertex with the same position. Returns number of unique vertices.
///
/// @param[out] _output Welded vertices remapping table. The size of buffer
///   must be the same as number of vertices.
/// @param[in] _layout Vertex stream layout.
/// @param[in] _data Vertex stream.
/// @param[in] _num Number of vertices in vertex stream.
/// @param[in] _index32 Set to `true` if input indices are 32-bit.
///
/// @returns Number of unique vertices after vertex welding.
///
uint32_t weldVertices(void* _output, const bgfx::VertexLayout& _layout, const void* _data, uint32_t _num, bool _index32);

/// Returns true if both internal transient index and vertex buffer have
/// enough space.
///
/// @param[in] _numVertices Number of vertices.
/// @param[in] _layout Vertex layout.
/// @param[in] _numIndices Number of indices.
///
inline bool checkAvailTransientBuffers(uint32_t _numVertices, const bgfx::VertexLayout& _layout, uint32_t _numIndices)
{
	return _numVertices == bgfx::getAvailTransientVertexBuffer(_numVertices, _layout)
		&& (0 == _numIndices || _numIndices == bgfx::getAvailTransientIndexBuffer(_numIndices) )
		;
}

/// Encode normal vector as RGBA8 color value.
///
/// @param[in] _x X component of the normal.
/// @param[in] _y Y component of the normal.
/// @param[in] _z Z component of the normal.
/// @param[in] _w W component.
///
/// @returns Packed RGBA8 value.
///
inline uint32_t encodeNormalRgba8(float _x, float _y = 0.0f, float _z = 0.0f, float _w = 0.0f)
{
	const float src[] =
	{
		_x * 0.5f + 0.5f,
		_y * 0.5f + 0.5f,
		_z * 0.5f + 0.5f,
		_w * 0.5f + 0.5f,
	};
	uint32_t dst;
	bx::packRgba8(&dst, src);
	return dst;
}

/// Rendering state for a mesh pass.
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
	bgfx::ViewId        m_viewId;
};

struct Primitive
{
	uint32_t m_startIndex;
	uint32_t m_numIndices;
	uint32_t m_startVertex;
	uint32_t m_numVertices;

	bx::Sphere m_sphere;
	bx::Aabb   m_aabb;
	bx::Obb    m_obb;
};

typedef stl::vector<Primitive> PrimitiveArray;

struct Group
{
	Group();
	void reset();

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle m_ibh;
	uint16_t m_numVertices;
	uint8_t* m_vertices;
	uint32_t m_numIndices;
	uint16_t* m_indices;
	bx::Sphere m_sphere;
	bx::Aabb   m_aabb;
	bx::Obb    m_obb;
	PrimitiveArray m_prims;
};
typedef stl::vector<Group> GroupArray;

struct Mesh
{
	void load(bx::ReaderSeekerI* _reader, bool _ramcopy);
	void unload();
	void submit(bgfx::ViewId _id, bgfx::ProgramHandle _program, const float* _mtx, uint64_t _state) const;
	void submit(const MeshState*const* _state, uint8_t _numPasses, const float* _mtx, uint16_t _numMatrices) const;

	bgfx::VertexLayout m_layout;
	GroupArray m_groups;
};

/// Load mesh from file.
///
/// @param[in] _filePath File path to mesh.
/// @param[in] _ramcopy If `true`, keep a RAM copy of vertex/index data.
///
/// @returns Pointer to loaded mesh.
///
Mesh* meshLoad(const bx::FilePath& _filePath, bool _ramcopy = false);

/// Unload mesh and free resources.
///
/// @param[in] _mesh Pointer to mesh to unload.
///
void meshUnload(Mesh* _mesh);

/// Create mesh state for multi-pass rendering.
///
/// @returns Pointer to new mesh state.
///
MeshState* meshStateCreate();

/// Destroy mesh state.
///
/// @param[in] _meshState Pointer to mesh state to destroy.
///
void meshStateDestroy(MeshState* _meshState);

/// Submit mesh for rendering with a single program.
///
/// @param[in] _mesh Pointer to mesh.
/// @param[in] _id View ID.
/// @param[in] _program Program handle.
/// @param[in] _mtx Model transform matrix.
/// @param[in] _state Render state flags.
///
void meshSubmit(const Mesh* _mesh, bgfx::ViewId _id, bgfx::ProgramHandle _program, const float* _mtx, uint64_t _state = BGFX_STATE_MASK);

/// Submit mesh for multi-pass rendering.
///
/// @param[in] _mesh Pointer to mesh.
/// @param[in] _state Array of mesh state pointers, one per pass.
/// @param[in] _numPasses Number of rendering passes.
/// @param[in] _mtx Model transform matrix.
/// @param[in] _numMatrices Number of matrices.
///
void meshSubmit(const Mesh* _mesh, const MeshState*const* _state, uint8_t _numPasses, const float* _mtx, uint16_t _numMatrices = 1);

/// Get renderer type name.
///
/// @param[in] _type Renderer type enum.
///
/// @returns Renderer name string.
///
bx::StringView getName(bgfx::RendererType::Enum _type);

/// Get renderer type from name.
///
/// @param[in] _name Renderer type name.
///
/// @returns Renderer type enum.
///
bgfx::RendererType::Enum getType(const bx::StringView& _name);

#endif // BGFX_UTILS_H_HEADER_GUARD
