/*
 * Copyright 2011-2022 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "common.h"

#include <tinystl/allocator.h>
#include <tinystl/vector.h>
#include <tinystl/string.h>
namespace stl = tinystl;

#include <bgfx/bgfx.h>
#include <bx/commandline.h>
#include <bx/endian.h>
#include <bx/math.h>
#include <bx/readerwriter.h>
#include <bx/string.h>
#include "entry/entry.h"
#include <meshoptimizer/src/meshoptimizer.h>

#include "bgfx_utils.h"

#include <bimg/decode.h>

void* load(bx::FileReaderI* _reader, bx::AllocatorI* _allocator, const char* _filePath, uint32_t* _size)
{
	if (bx::open(_reader, _filePath) )
	{
		uint32_t size = (uint32_t)bx::getSize(_reader);
		void* data = BX_ALLOC(_allocator, size);
		bx::read(_reader, data, size, bx::ErrorAssert{});
		bx::close(_reader);
		if (NULL != _size)
		{
			*_size = size;
		}
		return data;
	}
	else
	{
		DBG("Failed to open: %s.", _filePath);
	}

	if (NULL != _size)
	{
		*_size = 0;
	}

	return NULL;
}

void* load(const char* _filePath, uint32_t* _size)
{
	return load(entry::getFileReader(), entry::getAllocator(), _filePath, _size);
}

void unload(void* _ptr)
{
	BX_FREE(entry::getAllocator(), _ptr);
}

static const bgfx::Memory* loadMem(bx::FileReaderI* _reader, const char* _filePath)
{
	if (bx::open(_reader, _filePath) )
	{
		uint32_t size = (uint32_t)bx::getSize(_reader);
		const bgfx::Memory* mem = bgfx::alloc(size+1);
		bx::read(_reader, mem->data, size, bx::ErrorAssert{});
		bx::close(_reader);
		mem->data[mem->size-1] = '\0';
		return mem;
	}

	DBG("Failed to load %s.", _filePath);
	return NULL;
}

static void* loadMem(bx::FileReaderI* _reader, bx::AllocatorI* _allocator, const char* _filePath, uint32_t* _size)
{
	if (bx::open(_reader, _filePath) )
	{
		uint32_t size = (uint32_t)bx::getSize(_reader);
		void* data = BX_ALLOC(_allocator, size);
		bx::read(_reader, data, size, bx::ErrorAssert{});
		bx::close(_reader);

		if (NULL != _size)
		{
			*_size = size;
		}
		return data;
	}

	DBG("Failed to load %s.", _filePath);
	return NULL;
}

static bgfx::ShaderHandle loadShader(bx::FileReaderI* _reader, const char* _name)
{
	char filePath[512];

	const char* shaderPath = "???";

	switch (bgfx::getRendererType() )
	{
	case bgfx::RendererType::Noop:
	case bgfx::RendererType::Direct3D9:  shaderPath = "shaders/dx9/";   break;
	case bgfx::RendererType::Direct3D11:
	case bgfx::RendererType::Direct3D12: shaderPath = "shaders/dx11/";  break;
	case bgfx::RendererType::Agc:
	case bgfx::RendererType::Gnm:        shaderPath = "shaders/pssl/";  break;
	case bgfx::RendererType::Metal:      shaderPath = "shaders/metal/"; break;
	case bgfx::RendererType::Nvn:        shaderPath = "shaders/nvn/";   break;
	case bgfx::RendererType::OpenGL:     shaderPath = "shaders/glsl/";  break;
	case bgfx::RendererType::OpenGLES:   shaderPath = "shaders/essl/";  break;
	case bgfx::RendererType::Vulkan:     shaderPath = "shaders/spirv/"; break;
	case bgfx::RendererType::WebGPU:     shaderPath = "shaders/spirv/"; break;

	case bgfx::RendererType::Count:
		BX_ASSERT(false, "You should not be here!");
		break;
	}

	bx::strCopy(filePath, BX_COUNTOF(filePath), shaderPath);
	bx::strCat(filePath, BX_COUNTOF(filePath), _name);
	bx::strCat(filePath, BX_COUNTOF(filePath), ".bin");

	bgfx::ShaderHandle handle = bgfx::createShader(loadMem(_reader, filePath) );
	bgfx::setName(handle, _name);

	return handle;
}

bgfx::ShaderHandle loadShader(const char* _name)
{
	return loadShader(entry::getFileReader(), _name);
}

bgfx::ProgramHandle loadProgram(bx::FileReaderI* _reader, const char* _vsName, const char* _fsName)
{
	bgfx::ShaderHandle vsh = loadShader(_reader, _vsName);
	bgfx::ShaderHandle fsh = BGFX_INVALID_HANDLE;
	if (NULL != _fsName)
	{
		fsh = loadShader(_reader, _fsName);
	}

	return bgfx::createProgram(vsh, fsh, true /* destroy shaders when program is destroyed */);
}

bgfx::ProgramHandle loadProgram(const char* _vsName, const char* _fsName)
{
	return loadProgram(entry::getFileReader(), _vsName, _fsName);
}

static void imageReleaseCb(void* _ptr, void* _userData)
{
	BX_UNUSED(_ptr);
	bimg::ImageContainer* imageContainer = (bimg::ImageContainer*)_userData;
	bimg::imageFree(imageContainer);
}

bgfx::TextureHandle loadTexture(bx::FileReaderI* _reader, const char* _filePath, uint64_t _flags, uint8_t _skip, bgfx::TextureInfo* _info, bimg::Orientation::Enum* _orientation)
{
	BX_UNUSED(_skip);
	bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;

	uint32_t size;
	void* data = load(_reader, entry::getAllocator(), _filePath, &size);
	if (NULL != data)
	{
		bimg::ImageContainer* imageContainer = bimg::imageParse(entry::getAllocator(), data, size);

		if (NULL != imageContainer)
		{
			if (NULL != _orientation)
			{
				*_orientation = imageContainer->m_orientation;
			}

			const bgfx::Memory* mem = bgfx::makeRef(
					  imageContainer->m_data
					, imageContainer->m_size
					, imageReleaseCb
					, imageContainer
					);
			unload(data);

			if (imageContainer->m_cubeMap)
			{
				handle = bgfx::createTextureCube(
					  uint16_t(imageContainer->m_width)
					, 1 < imageContainer->m_numMips
					, imageContainer->m_numLayers
					, bgfx::TextureFormat::Enum(imageContainer->m_format)
					, _flags
					, mem
					);
			}
			else if (1 < imageContainer->m_depth)
			{
				handle = bgfx::createTexture3D(
					  uint16_t(imageContainer->m_width)
					, uint16_t(imageContainer->m_height)
					, uint16_t(imageContainer->m_depth)
					, 1 < imageContainer->m_numMips
					, bgfx::TextureFormat::Enum(imageContainer->m_format)
					, _flags
					, mem
					);
			}
			else if (bgfx::isTextureValid(0, false, imageContainer->m_numLayers, bgfx::TextureFormat::Enum(imageContainer->m_format), _flags) )
			{
				handle = bgfx::createTexture2D(
					  uint16_t(imageContainer->m_width)
					, uint16_t(imageContainer->m_height)
					, 1 < imageContainer->m_numMips
					, imageContainer->m_numLayers
					, bgfx::TextureFormat::Enum(imageContainer->m_format)
					, _flags
					, mem
					);
			}

			if (bgfx::isValid(handle) )
			{
				bgfx::setName(handle, _filePath);
			}

			if (NULL != _info)
			{
				bgfx::calcTextureSize(
					  *_info
					, uint16_t(imageContainer->m_width)
					, uint16_t(imageContainer->m_height)
					, uint16_t(imageContainer->m_depth)
					, imageContainer->m_cubeMap
					, 1 < imageContainer->m_numMips
					, imageContainer->m_numLayers
					, bgfx::TextureFormat::Enum(imageContainer->m_format)
					);
			}
		}
	}

	return handle;
}

bgfx::TextureHandle loadTexture(const char* _name, uint64_t _flags, uint8_t _skip, bgfx::TextureInfo* _info, bimg::Orientation::Enum* _orientation)
{
	return loadTexture(entry::getFileReader(), _name, _flags, _skip, _info, _orientation);
}

bimg::ImageContainer* imageLoad(const char* _filePath, bgfx::TextureFormat::Enum _dstFormat)
{
	uint32_t size = 0;
	void* data = loadMem(entry::getFileReader(), entry::getAllocator(), _filePath, &size);

	return bimg::imageParse(entry::getAllocator(), data, size, bimg::TextureFormat::Enum(_dstFormat) );
}

void calcTangents(void* _vertices, uint16_t _numVertices, bgfx::VertexLayout _layout, const uint16_t* _indices, uint32_t _numIndices)
{
	struct PosTexcoord
	{
		float m_x;
		float m_y;
		float m_z;
		float m_pad0;
		float m_u;
		float m_v;
		float m_pad1;
		float m_pad2;
	};

	float* tangents = new float[6*_numVertices];
	bx::memSet(tangents, 0, 6*_numVertices*sizeof(float) );

	PosTexcoord v0;
	PosTexcoord v1;
	PosTexcoord v2;

	for (uint32_t ii = 0, num = _numIndices/3; ii < num; ++ii)
	{
		const uint16_t* indices = &_indices[ii*3];
		uint32_t i0 = indices[0];
		uint32_t i1 = indices[1];
		uint32_t i2 = indices[2];

		bgfx::vertexUnpack(&v0.m_x, bgfx::Attrib::Position, _layout, _vertices, i0);
		bgfx::vertexUnpack(&v0.m_u, bgfx::Attrib::TexCoord0, _layout, _vertices, i0);

		bgfx::vertexUnpack(&v1.m_x, bgfx::Attrib::Position, _layout, _vertices, i1);
		bgfx::vertexUnpack(&v1.m_u, bgfx::Attrib::TexCoord0, _layout, _vertices, i1);

		bgfx::vertexUnpack(&v2.m_x, bgfx::Attrib::Position, _layout, _vertices, i2);
		bgfx::vertexUnpack(&v2.m_u, bgfx::Attrib::TexCoord0, _layout, _vertices, i2);

		const float bax = v1.m_x - v0.m_x;
		const float bay = v1.m_y - v0.m_y;
		const float baz = v1.m_z - v0.m_z;
		const float bau = v1.m_u - v0.m_u;
		const float bav = v1.m_v - v0.m_v;

		const float cax = v2.m_x - v0.m_x;
		const float cay = v2.m_y - v0.m_y;
		const float caz = v2.m_z - v0.m_z;
		const float cau = v2.m_u - v0.m_u;
		const float cav = v2.m_v - v0.m_v;

		const float det = (bau * cav - bav * cau);
		const float invDet = 1.0f / det;

		const float tx = (bax * cav - cax * bav) * invDet;
		const float ty = (bay * cav - cay * bav) * invDet;
		const float tz = (baz * cav - caz * bav) * invDet;

		const float bx = (cax * bau - bax * cau) * invDet;
		const float by = (cay * bau - bay * cau) * invDet;
		const float bz = (caz * bau - baz * cau) * invDet;

		for (uint32_t jj = 0; jj < 3; ++jj)
		{
			float* tanu = &tangents[indices[jj]*6];
			float* tanv = &tanu[3];
			tanu[0] += tx;
			tanu[1] += ty;
			tanu[2] += tz;

			tanv[0] += bx;
			tanv[1] += by;
			tanv[2] += bz;
		}
	}

	for (uint32_t ii = 0; ii < _numVertices; ++ii)
	{
		const bx::Vec3 tanu = bx::load<bx::Vec3>(&tangents[ii*6]);
		const bx::Vec3 tanv = bx::load<bx::Vec3>(&tangents[ii*6 + 3]);

		float nxyzw[4];
		bgfx::vertexUnpack(nxyzw, bgfx::Attrib::Normal, _layout, _vertices, ii);

		const bx::Vec3 normal  = bx::load<bx::Vec3>(nxyzw);
		const float    ndt     = bx::dot(normal, tanu);
		const bx::Vec3 nxt     = bx::cross(normal, tanu);
		const bx::Vec3 tmp     = bx::sub(tanu, bx::mul(normal, ndt) );

		float tangent[4];
		bx::store(tangent, bx::normalize(tmp) );
		tangent[3] = bx::dot(nxt, tanv) < 0.0f ? -1.0f : 1.0f;

		bgfx::vertexPack(tangent, true, bgfx::Attrib::Tangent, _layout, _vertices, ii);
	}

	delete [] tangents;
}

Group::Group()
{
	reset();
}

void Group::reset()
{
	m_vbh.idx = bgfx::kInvalidHandle;
	m_ibh.idx = bgfx::kInvalidHandle;
	m_numVertices = 0;
	m_vertices = NULL;
	m_numIndices = 0;
	m_indices = NULL;
	m_prims.clear();
}

namespace bgfx
{
	int32_t read(bx::ReaderI* _reader, bgfx::VertexLayout& _layout, bx::Error* _err);
}

void Mesh::load(bx::ReaderSeekerI* _reader, bool _ramcopy)
{
	constexpr uint32_t kChunkVertexBuffer           = BX_MAKEFOURCC('V', 'B', ' ', 0x1);
	constexpr uint32_t kChunkVertexBufferCompressed = BX_MAKEFOURCC('V', 'B', 'C', 0x0);
	constexpr uint32_t kChunkIndexBuffer            = BX_MAKEFOURCC('I', 'B', ' ', 0x0);
	constexpr uint32_t kChunkIndexBufferCompressed  = BX_MAKEFOURCC('I', 'B', 'C', 0x1);
	constexpr uint32_t kChunkPrimitive              = BX_MAKEFOURCC('P', 'R', 'I', 0x0);

	using namespace bx;
	using namespace bgfx;

	Group group;

	bx::AllocatorI* allocator = entry::getAllocator();

	uint32_t chunk;
	bx::Error err;
	while (4 == bx::read(_reader, chunk, &err)
	   &&  err.isOk() )
	{
		switch (chunk)
		{
			case kChunkVertexBuffer:
			{
				read(_reader, group.m_sphere, &err);
				read(_reader, group.m_aabb, &err);
				read(_reader, group.m_obb, &err);

				read(_reader, m_layout, &err);

				uint16_t stride = m_layout.getStride();

				read(_reader, group.m_numVertices, &err);
				const bgfx::Memory* mem = bgfx::alloc(group.m_numVertices*stride);
				read(_reader, mem->data, mem->size, &err);

				if (_ramcopy)
				{
					group.m_vertices = (uint8_t*)BX_ALLOC(allocator, group.m_numVertices*stride);
					bx::memCopy(group.m_vertices, mem->data, mem->size);
				}

				group.m_vbh = bgfx::createVertexBuffer(mem, m_layout);
			}
				break;

			case kChunkVertexBufferCompressed:
			{
				read(_reader, group.m_sphere, &err);
				read(_reader, group.m_aabb, &err);
				read(_reader, group.m_obb, &err);

				read(_reader, m_layout, &err);

				uint16_t stride = m_layout.getStride();

				read(_reader, group.m_numVertices, &err);

				const bgfx::Memory* mem = bgfx::alloc(group.m_numVertices*stride);

				uint32_t compressedSize;
				bx::read(_reader, compressedSize, &err);

				void* compressedVertices = BX_ALLOC(allocator, compressedSize);
				bx::read(_reader, compressedVertices, compressedSize, &err);

				meshopt_decodeVertexBuffer(mem->data, group.m_numVertices, stride, (uint8_t*)compressedVertices, compressedSize);

				BX_FREE(allocator, compressedVertices);

				if (_ramcopy)
				{
					group.m_vertices = (uint8_t*)BX_ALLOC(allocator, group.m_numVertices*stride);
					bx::memCopy(group.m_vertices, mem->data, mem->size);
				}

				group.m_vbh = bgfx::createVertexBuffer(mem, m_layout);
			}
				break;

			case kChunkIndexBuffer:
			{
				read(_reader, group.m_numIndices, &err);

				const bgfx::Memory* mem = bgfx::alloc(group.m_numIndices*2);
				read(_reader, mem->data, mem->size, &err);

				if (_ramcopy)
				{
					group.m_indices = (uint16_t*)BX_ALLOC(allocator, group.m_numIndices*2);
					bx::memCopy(group.m_indices, mem->data, mem->size);
				}

				group.m_ibh = bgfx::createIndexBuffer(mem);
			}
				break;

			case kChunkIndexBufferCompressed:
			{
				bx::read(_reader, group.m_numIndices, &err);

				const bgfx::Memory* mem = bgfx::alloc(group.m_numIndices*2);

				uint32_t compressedSize;
				bx::read(_reader, compressedSize, &err);

				void* compressedIndices = BX_ALLOC(allocator, compressedSize);

				bx::read(_reader, compressedIndices, compressedSize, &err);

				meshopt_decodeIndexBuffer(mem->data, group.m_numIndices, 2, (uint8_t*)compressedIndices, compressedSize);

				BX_FREE(allocator, compressedIndices);

				if (_ramcopy)
				{
					group.m_indices = (uint16_t*)BX_ALLOC(allocator, group.m_numIndices*2);
					bx::memCopy(group.m_indices, mem->data, mem->size);
				}

				group.m_ibh = bgfx::createIndexBuffer(mem);
			}
				break;

			case kChunkPrimitive:
			{
				uint16_t len;
				read(_reader, len, &err);

				stl::string material;
				material.resize(len);
				read(_reader, const_cast<char*>(material.c_str() ), len, &err);

				uint16_t num;
				read(_reader, num, &err);

				for (uint32_t ii = 0; ii < num; ++ii)
				{
					read(_reader, len, &err);

					stl::string name;
					name.resize(len);
					read(_reader, const_cast<char*>(name.c_str() ), len, &err);

					Primitive prim;
					read(_reader, prim.m_startIndex, &err);
					read(_reader, prim.m_numIndices, &err);
					read(_reader, prim.m_startVertex, &err);
					read(_reader, prim.m_numVertices, &err);
					read(_reader, prim.m_sphere, &err);
					read(_reader, prim.m_aabb, &err);
					read(_reader, prim.m_obb, &err);

					group.m_prims.push_back(prim);
				}

				m_groups.push_back(group);
				group.reset();
			}
				break;

			default:
				DBG("%08x at %d", chunk, bx::skip(_reader, 0) );
				break;
		}
	}
}

void Mesh::unload()
{
	bx::AllocatorI* allocator = entry::getAllocator();

	for (GroupArray::const_iterator it = m_groups.begin(), itEnd = m_groups.end(); it != itEnd; ++it)
	{
		const Group& group = *it;
		bgfx::destroy(group.m_vbh);

		if (bgfx::isValid(group.m_ibh) )
		{
			bgfx::destroy(group.m_ibh);
		}

		if (NULL != group.m_vertices)
		{
			BX_FREE(allocator, group.m_vertices);
		}

		if (NULL != group.m_indices)
		{
			BX_FREE(allocator, group.m_indices);
		}
	}
	m_groups.clear();
}

void Mesh::submit(bgfx::ViewId _id, bgfx::ProgramHandle _program, const float* _mtx, uint64_t _state) const
{
	if (BGFX_STATE_MASK == _state)
	{
		_state = 0
			| BGFX_STATE_WRITE_RGB
			| BGFX_STATE_WRITE_A
			| BGFX_STATE_WRITE_Z
			| BGFX_STATE_DEPTH_TEST_LESS
			| BGFX_STATE_CULL_CCW
			| BGFX_STATE_MSAA
			;
	}

	bgfx::setTransform(_mtx);
	bgfx::setState(_state);

	for (GroupArray::const_iterator it = m_groups.begin(), itEnd = m_groups.end(); it != itEnd; ++it)
	{
		const Group& group = *it;

		bgfx::setIndexBuffer(group.m_ibh);
		bgfx::setVertexBuffer(0, group.m_vbh);
		bgfx::submit(
			  _id
			, _program
			, 0
			, BGFX_DISCARD_INDEX_BUFFER
			| BGFX_DISCARD_VERTEX_STREAMS
			);
	}

	bgfx::discard();
}

void Mesh::submit(const MeshState*const* _state, uint8_t _numPasses, const float* _mtx, uint16_t _numMatrices) const
{
	uint32_t cached = bgfx::setTransform(_mtx, _numMatrices);

	for (uint32_t pass = 0; pass < _numPasses; ++pass)
	{
		bgfx::setTransform(cached, _numMatrices);

		const MeshState& state = *_state[pass];
		bgfx::setState(state.m_state);

		for (uint8_t tex = 0; tex < state.m_numTextures; ++tex)
		{
			const MeshState::Texture& texture = state.m_textures[tex];
			bgfx::setTexture(
				  texture.m_stage
				, texture.m_sampler
				, texture.m_texture
				, texture.m_flags
				);
		}

		for (GroupArray::const_iterator it = m_groups.begin(), itEnd = m_groups.end(); it != itEnd; ++it)
		{
			const Group& group = *it;

			bgfx::setIndexBuffer(group.m_ibh);
			bgfx::setVertexBuffer(0, group.m_vbh);
			bgfx::submit(
				  state.m_viewId
				, state.m_program
				, 0
				, BGFX_DISCARD_INDEX_BUFFER
				| BGFX_DISCARD_VERTEX_STREAMS
				);
		}

		bgfx::discard(0
			| BGFX_DISCARD_BINDINGS
			| BGFX_DISCARD_STATE
			| BGFX_DISCARD_TRANSFORM
			);
	}

	bgfx::discard();
}

Mesh* meshLoad(bx::ReaderSeekerI* _reader, bool _ramcopy)
{
	Mesh* mesh = new Mesh;
	mesh->load(_reader, _ramcopy);
	return mesh;
}

Mesh* meshLoad(const char* _filePath, bool _ramcopy)
{
	bx::FileReaderI* reader = entry::getFileReader();
	if (bx::open(reader, _filePath) )
	{
		Mesh* mesh = meshLoad(reader, _ramcopy);
		bx::close(reader);
		return mesh;
	}

	return NULL;
}

void meshUnload(Mesh* _mesh)
{
	_mesh->unload();
	delete _mesh;
}

MeshState* meshStateCreate()
{
	MeshState* state = (MeshState*)BX_ALLOC(entry::getAllocator(), sizeof(MeshState) );
	return state;
}

void meshStateDestroy(MeshState* _meshState)
{
	BX_FREE(entry::getAllocator(), _meshState);
}

void meshSubmit(const Mesh* _mesh, bgfx::ViewId _id, bgfx::ProgramHandle _program, const float* _mtx, uint64_t _state)
{
	_mesh->submit(_id, _program, _mtx, _state);
}

void meshSubmit(const Mesh* _mesh, const MeshState*const* _state, uint8_t _numPasses, const float* _mtx, uint16_t _numMatrices)
{
	_mesh->submit(_state, _numPasses, _mtx, _numMatrices);
}

struct RendererTypeRemap
{
	bx::StringView           name;
	bgfx::RendererType::Enum type;
};

static RendererTypeRemap s_rendererTypeRemap[] =
{
	{ "d3d11", bgfx::RendererType::Direct3D11 },
	{ "d3d12", bgfx::RendererType::Direct3D12 },
	{ "d3d9",  bgfx::RendererType::Direct3D9  },
	{ "gl",    bgfx::RendererType::OpenGL     },
	{ "mtl",   bgfx::RendererType::Metal      },
	{ "noop",  bgfx::RendererType::Noop       },
	{ "vk",    bgfx::RendererType::Vulkan     },
};

bx::StringView getName(bgfx::RendererType::Enum _type)
{
	for (uint32_t ii = 0; ii < BX_COUNTOF(s_rendererTypeRemap); ++ii)
	{
		const RendererTypeRemap& remap = s_rendererTypeRemap[ii];

		if (_type == remap.type)
		{
			return remap.name;
		}
	}

	return "";
}

bgfx::RendererType::Enum getType(const bx::StringView& _name)
{
	for (uint32_t ii = 0; ii < BX_COUNTOF(s_rendererTypeRemap); ++ii)
	{
		const RendererTypeRemap& remap = s_rendererTypeRemap[ii];

		if (0 == bx::strCmpI(_name, remap.name) )
		{
			return remap.type;
		}
	}

	return bgfx::RendererType::Count;
}

Args::Args(int _argc, const char* const* _argv)
	: m_type(bgfx::RendererType::Count)
	, m_pciId(BGFX_PCI_ID_NONE)
{
	bx::CommandLine cmdLine(_argc, (const char**)_argv);

	if (cmdLine.hasArg("gl") )
	{
		m_type = bgfx::RendererType::OpenGL;
	}
	else if (cmdLine.hasArg("vk") )
	{
		m_type = bgfx::RendererType::Vulkan;
	}
	else if (cmdLine.hasArg("noop") )
	{
		m_type = bgfx::RendererType::Noop;
	}
	else if (BX_ENABLED(BX_PLATFORM_WINDOWS|BX_PLATFORM_WINRT|BX_PLATFORM_XBOXONE) )
	{
		if (cmdLine.hasArg("d3d9") )
		{
			m_type = bgfx::RendererType::Direct3D9;
		}
		else if (cmdLine.hasArg("d3d11") )
		{
			m_type = bgfx::RendererType::Direct3D11;
		}
		else if (cmdLine.hasArg("d3d12") )
		{
			m_type = bgfx::RendererType::Direct3D12;
		}
	}
	else if (BX_ENABLED(BX_PLATFORM_OSX) )
	{
		if (cmdLine.hasArg("mtl") )
		{
			m_type = bgfx::RendererType::Metal;
		}
	}

	if (cmdLine.hasArg("amd") )
	{
		m_pciId = BGFX_PCI_ID_AMD;
	}
	else if (cmdLine.hasArg("nvidia") )
	{
		m_pciId = BGFX_PCI_ID_NVIDIA;
	}
	else if (cmdLine.hasArg("intel") )
	{
		m_pciId = BGFX_PCI_ID_INTEL;
	}
	else if (cmdLine.hasArg("sw") )
	{
		m_pciId = BGFX_PCI_ID_SOFTWARE_RASTERIZER;
	}
}
