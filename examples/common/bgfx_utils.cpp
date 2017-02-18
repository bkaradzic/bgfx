/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"

#include <tinystl/allocator.h>
#include <tinystl/vector.h>
#include <tinystl/string.h>
namespace stl = tinystl;

#include <bgfx/bgfx.h>
#include <bx/commandline.h>
#include <bx/endian.h>
#include <bx/fpumath.h>
#include <bx/readerwriter.h>
#include <bx/string.h>
#include "entry/entry.h"
#include <ib-compress/indexbufferdecompression.h>

BX_PRAGMA_DIAGNOSTIC_PUSH()
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wtype-limits")
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wunused-parameter")
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wunused-value")
BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4100) // error C4100: '' : unreferenced formal parameter
#if BX_PLATFORM_EMSCRIPTEN
#	include <compat/ctype.h>
#endif // BX_PLATFORM_EMSCRIPTEN
#define MINIZ_NO_STDIO
#define TINYEXR_IMPLEMENTATION
#include <tinyexr/tinyexr.h>
BX_PRAGMA_DIAGNOSTIC_POP()

#define LODEPNG_NO_COMPILE_ENCODER
#define LODEPNG_NO_COMPILE_DISK
#define LODEPNG_NO_COMPILE_ANCILLARY_CHUNKS
#define LODEPNG_NO_COMPILE_ERROR_TEXT
#define LODEPNG_NO_COMPILE_ALLOCATORS
#define LODEPNG_NO_COMPILE_CPP
#include <lodepng/lodepng.h>

#include "bgfx_utils.h"

void* load(bx::FileReaderI* _reader, bx::AllocatorI* _allocator, const char* _filePath, uint32_t* _size)
{
	if (bx::open(_reader, _filePath) )
	{
		uint32_t size = (uint32_t)bx::getSize(_reader);
		void* data = BX_ALLOC(_allocator, size);
		bx::read(_reader, data, size);
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
		bx::read(_reader, mem->data, size);
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
		bx::read(_reader, data, size);
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
	case bgfx::RendererType::Gnm:        shaderPath = "shaders/pssl/";  break;
	case bgfx::RendererType::Metal:      shaderPath = "shaders/metal/"; break;
	case bgfx::RendererType::OpenGL:     shaderPath = "shaders/glsl/";  break;
	case bgfx::RendererType::OpenGLES:   shaderPath = "shaders/essl/";  break;
	case bgfx::RendererType::Vulkan:     shaderPath = "shaders/spirv/"; break;

	case bgfx::RendererType::Count:
		BX_CHECK(false, "You should not be here!");
		break;
	}

	bx::strlncpy(filePath, BX_COUNTOF(filePath), shaderPath);
	bx::strlncat(filePath, BX_COUNTOF(filePath), _name);
	bx::strlncat(filePath, BX_COUNTOF(filePath), ".bin");

	return bgfx::createShader(loadMem(_reader, filePath) );
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

typedef unsigned char stbi_uc;
extern "C" stbi_uc* stbi_load_from_memory(stbi_uc const* _buffer, int _len, int* _x, int* _y, int* _comp, int _req_comp);
extern "C" void stbi_image_free(void* _ptr);
extern void lodepng_free(void* _ptr);

static void exrRelease(void* _ptr)
{
	BX_FREE(entry::getAllocator(), _ptr);
}

bgfx::TextureHandle loadTexture(bx::FileReaderI* _reader, const char* _filePath, uint32_t _flags, uint8_t _skip, bgfx::TextureInfo* _info)
{
	if (NULL != bx::stristr(_filePath, ".dds")
	||  NULL != bx::stristr(_filePath, ".pvr")
	||  NULL != bx::stristr(_filePath, ".ktx") )
	{
		const bgfx::Memory* mem = loadMem(_reader, _filePath);
		if (NULL != mem)
		{
			return bgfx::createTexture(mem, _flags, _skip, _info);
		}

		bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;
		DBG("Failed to load %s.", _filePath);
		return handle;
	}

	bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;
	bx::AllocatorI* allocator = entry::getAllocator();

	uint32_t size = 0;
	void* data = loadMem(_reader, allocator, _filePath, &size);
	if (NULL != data)
	{
		bgfx::TextureFormat::Enum format = bgfx::TextureFormat::RGBA8;
		uint32_t bpp = 32;

		uint32_t width  = 0;
		uint32_t height = 0;

		typedef void (*ReleaseFn)(void* _ptr);
		ReleaseFn release = stbi_image_free;

		uint8_t* out = NULL;
		static uint8_t pngMagic[] = { 0x89, 0x50, 0x4E, 0x47, 0x0d, 0x0a };

		if (0 == bx::memCmp(data, pngMagic, sizeof(pngMagic) ) )
		{
			release = lodepng_free;

			unsigned error;
			LodePNGState state;
			lodepng_state_init(&state);
			state.decoder.color_convert = 0;
			error = lodepng_decode(&out, &width, &height, &state, (uint8_t*)data, size);

			if (0 == error)
			{
				switch (state.info_raw.bitdepth)
				{
				case 8:
					switch (state.info_raw.colortype)
					{
					case LCT_GREY:
						format = bgfx::TextureFormat::R8;
						bpp    = 8;
						break;

					case LCT_GREY_ALPHA:
						format = bgfx::TextureFormat::RG8;
						bpp    = 16;
						break;

					case LCT_RGB:
						format = bgfx::TextureFormat::RGB8;
						bpp    = 24;
						break;

					case LCT_RGBA:
						format = bgfx::TextureFormat::RGBA8;
						bpp    = 32;
						break;

					case LCT_PALETTE:
						format = bgfx::TextureFormat::R8;
						bpp    = 8;
						break;
					}
					break;

				case 16:
					switch (state.info_raw.colortype)
					{
					case LCT_GREY:
						for (uint32_t ii = 0, num = width*height; ii < num; ++ii)
						{
							uint16_t* rgba = (uint16_t*)out + ii*4;
							rgba[0] = bx::toHostEndian(rgba[0], false);
						}
						format = bgfx::TextureFormat::R16;
						bpp    = 16;
						break;

					case LCT_GREY_ALPHA:
						for (uint32_t ii = 0, num = width*height; ii < num; ++ii)
						{
							uint16_t* rgba = (uint16_t*)out + ii*4;
							rgba[0] = bx::toHostEndian(rgba[0], false);
							rgba[1] = bx::toHostEndian(rgba[1], false);
						}
						format = bgfx::TextureFormat::R16;
						bpp    = 16;
						break;

					case LCT_RGBA:
						for (uint32_t ii = 0, num = width*height; ii < num; ++ii)
						{
							uint16_t* rgba = (uint16_t*)out + ii*4;
							rgba[0] = bx::toHostEndian(rgba[0], false);
							rgba[1] = bx::toHostEndian(rgba[1], false);
							rgba[2] = bx::toHostEndian(rgba[2], false);
							rgba[3] = bx::toHostEndian(rgba[3], false);
						}
						format = bgfx::TextureFormat::RGBA16;
						bpp    = 64;
						break;

					case LCT_RGB:
					case LCT_PALETTE:
						break;
					}
					break;

				default:
					break;
				}
			}

			lodepng_state_cleanup(&state);
		}
		else
		{
			EXRVersion exrVersion;
			int result = ParseEXRVersionFromMemory(&exrVersion, (uint8_t*)data, size);
			if (TINYEXR_SUCCESS == result)
			{
				const char* err = NULL;
				EXRHeader exrHeader;
				result = ParseEXRHeaderFromMemory(&exrHeader, &exrVersion, (uint8_t*)data, size, &err);
				if (TINYEXR_SUCCESS == result)
				{
					EXRImage exrImage;
					InitEXRImage(&exrImage);

					result = LoadEXRImageFromMemory(&exrImage, &exrHeader, (uint8_t*)data, size, &err);
					if (TINYEXR_SUCCESS == result)
					{
						uint8_t idxR = UINT8_MAX;
						uint8_t idxG = UINT8_MAX;
						uint8_t idxB = UINT8_MAX;
						uint8_t idxA = UINT8_MAX;
						for (uint8_t ii = 0, num = uint8_t(exrHeader.num_channels); ii < num; ++ii)
						{
							const EXRChannelInfo& channel = exrHeader.channels[ii];
							if (UINT8_MAX == idxR
							&&  0 == bx::strncmp(channel.name, "R") )
							{
								idxR = ii;
							}
							else if (UINT8_MAX == idxG
								 &&  0 == bx::strncmp(channel.name, "G") )
							{
								idxG = ii;
							}
							else if (UINT8_MAX == idxB
								 &&  0 == bx::strncmp(channel.name, "B") )
							{
								idxB = ii;
							}
							else if (UINT8_MAX == idxA
								 &&  0 == bx::strncmp(channel.name, "A") )
							{
								idxA = ii;
							}
						}

						if (UINT8_MAX != idxR)
						{
							const bool asFloat = exrHeader.pixel_types[idxR] == TINYEXR_PIXELTYPE_FLOAT;

							uint32_t srcBpp = 32;
							uint32_t dstBpp = asFloat ? 32 : 16;
							format = asFloat ? bgfx::TextureFormat::R32F : bgfx::TextureFormat::R16F;
							uint32_t stepR = 1;
							uint32_t stepG = 0;
							uint32_t stepB = 0;
							uint32_t stepA = 0;

							if (UINT8_MAX != idxG)
							{
								srcBpp += 32;
								dstBpp = asFloat ? 64 : 32;
								format = asFloat ? bgfx::TextureFormat::RG32F : bgfx::TextureFormat::RG16F;
								stepG  = 1;
							}

							if (UINT8_MAX != idxB)
							{
								srcBpp += 32;
								dstBpp = asFloat ? 128 : 64;
								format = asFloat ? bgfx::TextureFormat::RGBA32F : bgfx::TextureFormat::RGBA16F;
								stepB  = 1;
							}

							if (UINT8_MAX != idxA)
							{
								srcBpp += 32;
								dstBpp = asFloat ? 128 : 64;
								format = asFloat ? bgfx::TextureFormat::RGBA32F : bgfx::TextureFormat::RGBA16F;
								stepA  = 1;
							}

							release = exrRelease;
							out = (uint8_t*)BX_ALLOC(allocator, exrImage.width * exrImage.height * dstBpp/8);

							const float zero = 0.0f;
							const float* srcR = UINT8_MAX == idxR ? &zero : (const float*)(exrImage.images)[idxR];
							const float* srcG = UINT8_MAX == idxG ? &zero : (const float*)(exrImage.images)[idxG];
							const float* srcB = UINT8_MAX == idxB ? &zero : (const float*)(exrImage.images)[idxB];
							const float* srcA = UINT8_MAX == idxA ? &zero : (const float*)(exrImage.images)[idxA];

							const uint32_t bytesPerPixel = dstBpp/8;
							for (uint32_t ii = 0, num = exrImage.width * exrImage.height; ii < num; ++ii)
							{
								float rgba[4] =
								{
									*srcR,
									*srcG,
									*srcB,
									*srcA,
								};
								bx::memCopy(&out[ii * bytesPerPixel], rgba, bytesPerPixel);

								srcR += stepR;
								srcG += stepG;
								srcB += stepB;
								srcA += stepA;
							}
						}

						FreeEXRImage(&exrImage);
					}

					FreeEXRHeader(&exrHeader);
				}
			}
			else
			{
				int comp = 0;
				out = stbi_load_from_memory( (uint8_t*)data, size, (int*)&width, (int*)&height, &comp, 4);
			}
		}

		BX_FREE(allocator, data);

		if (NULL != out)
		{
			handle = bgfx::createTexture2D(
				  uint16_t(width)
				, uint16_t(height)
				, false
				, 1
				, format
				, _flags
				, bgfx::copy(out, width*height*bpp/8)
				);
			release(out);

			if (NULL != _info)
			{
				bgfx::calcTextureSize(
					  *_info
					, uint16_t(width)
					, uint16_t(height)
					, 0
					, false
					, false
					, 1
					, format
					);
			}
		}
	}
	else
	{
		DBG("Failed to load %s.", _filePath);
	}

	return handle;
}

bgfx::TextureHandle loadTexture(const char* _name, uint32_t _flags, uint8_t _skip, bgfx::TextureInfo* _info)
{
	return loadTexture(entry::getFileReader(), _name, _flags, _skip, _info);
}

void calcTangents(void* _vertices, uint16_t _numVertices, bgfx::VertexDecl _decl, const uint16_t* _indices, uint32_t _numIndices)
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

		bgfx::vertexUnpack(&v0.m_x, bgfx::Attrib::Position,  _decl, _vertices, i0);
		bgfx::vertexUnpack(&v0.m_u, bgfx::Attrib::TexCoord0, _decl, _vertices, i0);

		bgfx::vertexUnpack(&v1.m_x, bgfx::Attrib::Position,  _decl, _vertices, i1);
		bgfx::vertexUnpack(&v1.m_u, bgfx::Attrib::TexCoord0, _decl, _vertices, i1);

		bgfx::vertexUnpack(&v2.m_x, bgfx::Attrib::Position,  _decl, _vertices, i2);
		bgfx::vertexUnpack(&v2.m_u, bgfx::Attrib::TexCoord0, _decl, _vertices, i2);

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
		const float* tanu = &tangents[ii*6];
		const float* tanv = &tangents[ii*6 + 3];

		float normal[4];
		bgfx::vertexUnpack(normal, bgfx::Attrib::Normal, _decl, _vertices, ii);
		float ndt = bx::vec3Dot(normal, tanu);

		float nxt[3];
		bx::vec3Cross(nxt, normal, tanu);

		float tmp[3];
		tmp[0] = tanu[0] - normal[0] * ndt;
		tmp[1] = tanu[1] - normal[1] * ndt;
		tmp[2] = tanu[2] - normal[2] * ndt;

		float tangent[4];
		bx::vec3Norm(tangent, tmp);

		tangent[3] = bx::vec3Dot(nxt, tanv) < 0.0f ? -1.0f : 1.0f;
		bgfx::vertexPack(tangent, true, bgfx::Attrib::Tangent, _decl, _vertices, ii);
	}

	delete [] tangents;
}

struct Aabb
{
	float m_min[3];
	float m_max[3];
};

struct Obb
{
	float m_mtx[16];
};

struct Sphere
{
	float m_center[3];
	float m_radius;
};

struct Primitive
{
	uint32_t m_startIndex;
	uint32_t m_numIndices;
	uint32_t m_startVertex;
	uint32_t m_numVertices;

	Sphere m_sphere;
	Aabb m_aabb;
	Obb m_obb;
};

typedef stl::vector<Primitive> PrimitiveArray;

struct Group
{
	Group()
	{
		reset();
	}

	void reset()
	{
		m_vbh.idx = bgfx::invalidHandle;
		m_ibh.idx = bgfx::invalidHandle;
		m_prims.clear();
	}

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle m_ibh;
	Sphere m_sphere;
	Aabb m_aabb;
	Obb m_obb;
	PrimitiveArray m_prims;
};

namespace bgfx
{
	int32_t read(bx::ReaderI* _reader, bgfx::VertexDecl& _decl, bx::Error* _err = NULL);
}

struct Mesh
{
	void load(bx::ReaderSeekerI* _reader)
	{
#define BGFX_CHUNK_MAGIC_VB  BX_MAKEFOURCC('V', 'B', ' ', 0x1)
#define BGFX_CHUNK_MAGIC_IB  BX_MAKEFOURCC('I', 'B', ' ', 0x0)
#define BGFX_CHUNK_MAGIC_IBC BX_MAKEFOURCC('I', 'B', 'C', 0x0)
#define BGFX_CHUNK_MAGIC_PRI BX_MAKEFOURCC('P', 'R', 'I', 0x0)

		using namespace bx;
		using namespace bgfx;

		Group group;

		bx::AllocatorI* allocator = entry::getAllocator();

		uint32_t chunk;
		bx::Error err;
		while (4 == bx::read(_reader, chunk, &err)
		&&     err.isOk() )
		{
			switch (chunk)
			{
			case BGFX_CHUNK_MAGIC_VB:
				{
					read(_reader, group.m_sphere);
					read(_reader, group.m_aabb);
					read(_reader, group.m_obb);

					read(_reader, m_decl);

					uint16_t stride = m_decl.getStride();

					uint16_t numVertices;
					read(_reader, numVertices);
					const bgfx::Memory* mem = bgfx::alloc(numVertices*stride);
					read(_reader, mem->data, mem->size);

					group.m_vbh = bgfx::createVertexBuffer(mem, m_decl);
				}
				break;

			case BGFX_CHUNK_MAGIC_IB:
				{
					uint32_t numIndices;
					read(_reader, numIndices);
					const bgfx::Memory* mem = bgfx::alloc(numIndices*2);
					read(_reader, mem->data, mem->size);
					group.m_ibh = bgfx::createIndexBuffer(mem);
				}
				break;

			case BGFX_CHUNK_MAGIC_IBC:
				{
					uint32_t numIndices;
					bx::read(_reader, numIndices);

					const bgfx::Memory* mem = bgfx::alloc(numIndices*2);

					uint32_t compressedSize;
					bx::read(_reader, compressedSize);

					void* compressedIndices = BX_ALLOC(allocator, compressedSize);

					bx::read(_reader, compressedIndices, compressedSize);

					ReadBitstream rbs( (const uint8_t*)compressedIndices, compressedSize);
					DecompressIndexBuffer( (uint16_t*)mem->data, numIndices / 3, rbs);

					BX_FREE(allocator, compressedIndices);

					group.m_ibh = bgfx::createIndexBuffer(mem);
				}
				break;

			case BGFX_CHUNK_MAGIC_PRI:
				{
					uint16_t len;
					read(_reader, len);

					stl::string material;
					material.resize(len);
					read(_reader, const_cast<char*>(material.c_str() ), len);

					uint16_t num;
					read(_reader, num);

					for (uint32_t ii = 0; ii < num; ++ii)
					{
						read(_reader, len);

						stl::string name;
						name.resize(len);
						read(_reader, const_cast<char*>(name.c_str() ), len);

						Primitive prim;
						read(_reader, prim.m_startIndex);
						read(_reader, prim.m_numIndices);
						read(_reader, prim.m_startVertex);
						read(_reader, prim.m_numVertices);
						read(_reader, prim.m_sphere);
						read(_reader, prim.m_aabb);
						read(_reader, prim.m_obb);

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

	void unload()
	{
		for (GroupArray::const_iterator it = m_groups.begin(), itEnd = m_groups.end(); it != itEnd; ++it)
		{
			const Group& group = *it;
			bgfx::destroyVertexBuffer(group.m_vbh);

			if (bgfx::isValid(group.m_ibh) )
			{
				bgfx::destroyIndexBuffer(group.m_ibh);
			}
		}
		m_groups.clear();
	}

	void submit(uint8_t _id, bgfx::ProgramHandle _program, const float* _mtx, uint64_t _state) const
	{
		if (BGFX_STATE_MASK == _state)
		{
			_state = 0
				| BGFX_STATE_RGB_WRITE
				| BGFX_STATE_ALPHA_WRITE
				| BGFX_STATE_DEPTH_WRITE
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
			bgfx::setVertexBuffer(group.m_vbh);
			bgfx::submit(_id, _program, 0, it != itEnd-1);
		}
	}

	void submit(const MeshState*const* _state, uint8_t _numPasses, const float* _mtx, uint16_t _numMatrices) const
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
				bgfx::setTexture(texture.m_stage
						, texture.m_sampler
						, texture.m_texture
						, texture.m_flags
						);
			}

			for (GroupArray::const_iterator it = m_groups.begin(), itEnd = m_groups.end(); it != itEnd; ++it)
			{
				const Group& group = *it;

				bgfx::setIndexBuffer(group.m_ibh);
				bgfx::setVertexBuffer(group.m_vbh);
				bgfx::submit(state.m_viewId, state.m_program, 0, it != itEnd-1);
			}
		}
	}

	bgfx::VertexDecl m_decl;
	typedef stl::vector<Group> GroupArray;
	GroupArray m_groups;
};

Mesh* meshLoad(bx::ReaderSeekerI* _reader)
{
	Mesh* mesh = new Mesh;
	mesh->load(_reader);
	return mesh;
}

Mesh* meshLoad(const char* _filePath)
{
	bx::FileReaderI* reader = entry::getFileReader();
	if (bx::open(reader, _filePath) )
	{
		Mesh* mesh = meshLoad(reader);
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

void meshSubmit(const Mesh* _mesh, uint8_t _id, bgfx::ProgramHandle _program, const float* _mtx, uint64_t _state)
{
	_mesh->submit(_id, _program, _mtx, _state);
}

void meshSubmit(const Mesh* _mesh, const MeshState*const* _state, uint8_t _numPasses, const float* _mtx, uint16_t _numMatrices)
{
	_mesh->submit(_state, _numPasses, _mtx, _numMatrices);
}

Args::Args(int _argc, char** _argv)
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
	else if (BX_ENABLED(BX_PLATFORM_WINDOWS) )
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
