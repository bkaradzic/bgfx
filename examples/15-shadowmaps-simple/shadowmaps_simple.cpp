/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <string>
#include <vector>
#include <algorithm>

#include "common.h"

#include <bgfx.h>
#include <bx/timer.h>
#include <bx/readerwriter.h>
#include <bx/fpumath.h>
#include "entry/entry.h"

#define RENDER_SHADOW_PASS_ID 0
#define RENDER_SCENE_PASS_ID  1

uint32_t packUint32(uint8_t _x, uint8_t _y, uint8_t _z, uint8_t _w)
{
	union
	{
		uint32_t ui32;
		uint8_t arr[4];
	} un;

	un.arr[0] = _x;
	un.arr[1] = _y;
	un.arr[2] = _z;
	un.arr[3] = _w;

	return un.ui32;
}

uint32_t packF4u(float _x, float _y = 0.0f, float _z = 0.0f, float _w = 0.0f)
{
	const uint8_t xx = uint8_t(_x*127.0f + 128.0f);
	const uint8_t yy = uint8_t(_y*127.0f + 128.0f);
	const uint8_t zz = uint8_t(_z*127.0f + 128.0f);
	const uint8_t ww = uint8_t(_w*127.0f + 128.0f);
	return packUint32(xx, yy, zz, ww);
}

struct PosNormalVertex
{
	float    m_x;
	float    m_y;
	float    m_z;
	uint32_t m_normal;
};

static PosNormalVertex s_hplaneVertices[] =
{
	{ -1.0f, 0.0f,  1.0f, packF4u(0.0f, 1.0f, 0.0f) },
	{  1.0f, 0.0f,  1.0f, packF4u(0.0f, 1.0f, 0.0f) },
	{ -1.0f, 0.0f, -1.0f, packF4u(0.0f, 1.0f, 0.0f) },
	{  1.0f, 0.0f, -1.0f, packF4u(0.0f, 1.0f, 0.0f) },
};

static const uint16_t s_planeIndices[] =
{
	0, 1, 2,
	1, 3, 2,
};

static const char* s_shaderPath = NULL;
static bool s_flipV = false;
static float s_texelHalf = 0.0f;
bgfx::FrameBufferHandle s_shadowMapFB;
static bgfx::UniformHandle u_shadowMap;

inline void mtxProj(float* _result, float _fovy, float _aspect, float _near, float _far)
{
	bx::mtxProj(_result, _fovy, _aspect, _near, _far, s_flipV);
}

static void shaderFilePath(char* _out, const char* _name)
{
	strcpy(_out, s_shaderPath);
	strcat(_out, _name);
	strcat(_out, ".bin");
}

long int fsize(FILE* _file)
{
	long int pos = ftell(_file);
	fseek(_file, 0L, SEEK_END);
	long int size = ftell(_file);
	fseek(_file, pos, SEEK_SET);
	return size;
}

static const bgfx::Memory* load(const char* _filePath)
{
	FILE* file = fopen(_filePath, "rb");
	if (NULL != file)
	{
		uint32_t size = (uint32_t)fsize(file);
		const bgfx::Memory* mem = bgfx::alloc(size+1);
		size_t ignore = fread(mem->data, 1, size, file);
		BX_UNUSED(ignore);
		fclose(file);
		mem->data[mem->size-1] = '\0';
		return mem;
	}

	return NULL;
}

static const bgfx::Memory* loadShader(const char* _name)
{
	char filePath[512];
	shaderFilePath(filePath, _name);
	return load(filePath);
}

static bgfx::ProgramHandle loadProgram(const char* _vsName, const char* _fsName)
{
	const bgfx::Memory* mem;

	// Load vertex shader.
	mem = loadShader(_vsName);
	bgfx::ShaderHandle vsh = bgfx::createShader(mem);

	// Load fragment shader.
	mem = loadShader(_fsName);
	bgfx::ShaderHandle fsh = bgfx::createShader(mem);

	// Create program from shaders.
	return bgfx::createProgram(vsh, fsh, true /* destroy shaders when program is destroyed */);
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

typedef std::vector<Primitive> PrimitiveArray;

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
	int32_t read(bx::ReaderI* _reader, bgfx::VertexDecl& _decl);
}

struct Mesh
{
	void load(const void* _vertices, uint32_t _numVertices, const bgfx::VertexDecl _decl, const uint16_t* _indices, uint32_t _numIndices)
	{
		Group group;
		const bgfx::Memory* mem;
		uint32_t size;

		size = _numVertices*_decl.getStride();
		mem = bgfx::makeRef(_vertices, size);
		group.m_vbh = bgfx::createVertexBuffer(mem, _decl);

		size = _numIndices*2;
		mem = bgfx::makeRef(_indices, size);
		group.m_ibh = bgfx::createIndexBuffer(mem);

		//TODO:
		// group.m_sphere = ...
		// group.m_aabb = ...
		// group.m_obb = ...
		// group.m_prims = ...

		m_groups.push_back(group);
	}

	void load(const char* _filePath)
	{
#define BGFX_CHUNK_MAGIC_VB  BX_MAKEFOURCC('V', 'B', ' ', 0x1)
#define BGFX_CHUNK_MAGIC_IB  BX_MAKEFOURCC('I', 'B', ' ', 0x0)
#define BGFX_CHUNK_MAGIC_PRI BX_MAKEFOURCC('P', 'R', 'I', 0x0)

		bx::CrtFileReader reader;
		reader.open(_filePath);

		Group group;

		uint32_t chunk;
		while (4 == bx::read(&reader, chunk) )
		{
			switch (chunk)
			{
			case BGFX_CHUNK_MAGIC_VB:
				{
					bx::read(&reader, group.m_sphere);
					bx::read(&reader, group.m_aabb);
					bx::read(&reader, group.m_obb);

					bgfx::read(&reader, m_decl);
					uint16_t stride = m_decl.getStride();

					uint16_t numVertices;
					bx::read(&reader, numVertices);
					const bgfx::Memory* mem = bgfx::alloc(numVertices*stride);
					bx::read(&reader, mem->data, mem->size);

					group.m_vbh = bgfx::createVertexBuffer(mem, m_decl);
				}
				break;

			case BGFX_CHUNK_MAGIC_IB:
				{
					uint32_t numIndices;
					bx::read(&reader, numIndices);
					const bgfx::Memory* mem = bgfx::alloc(numIndices*2);
					bx::read(&reader, mem->data, mem->size);
					group.m_ibh = bgfx::createIndexBuffer(mem);
				}
				break;

			case BGFX_CHUNK_MAGIC_PRI:
				{
					uint16_t len;
					bx::read(&reader, len);

					std::string material;
					material.resize(len);
					bx::read(&reader, const_cast<char*>(material.c_str() ), len);

					uint16_t num;
					bx::read(&reader, num);

					for (uint32_t ii = 0; ii < num; ++ii)
					{
						bx::read(&reader, len);

						std::string name;
						name.resize(len);
						bx::read(&reader, const_cast<char*>(name.c_str() ), len);

						Primitive prim;
						bx::read(&reader, prim.m_startIndex);
						bx::read(&reader, prim.m_numIndices);
						bx::read(&reader, prim.m_startVertex);
						bx::read(&reader, prim.m_numVertices);
						bx::read(&reader, prim.m_sphere);
						bx::read(&reader, prim.m_aabb);
						bx::read(&reader, prim.m_obb);

						group.m_prims.push_back(prim);
					}

					m_groups.push_back(group);
					group.reset();
				}
				break;

			default:
				DBG("%08x at %d", chunk, reader.seek() );
				break;
			}
		}

		reader.close();
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

	void submit(uint8_t _view, float* _mtx, bgfx::ProgramHandle _program)
	{
		for (GroupArray::const_iterator it = m_groups.begin(), itEnd = m_groups.end(); it != itEnd; ++it)
		{
			const Group& group = *it;

			// Set model matrix for rendering.
			bgfx::setTransform(_mtx);
			bgfx::setProgram(_program);
			bgfx::setIndexBuffer(group.m_ibh);
			bgfx::setVertexBuffer(group.m_vbh);

			// Set shadow map.
			bgfx::setTexture(4, u_shadowMap, s_shadowMapFB);

			// Set render states.
			bgfx::setState(0
				| BGFX_STATE_RGB_WRITE
				| BGFX_STATE_ALPHA_WRITE
				| BGFX_STATE_DEPTH_WRITE
				| BGFX_STATE_DEPTH_TEST_LESS
				| BGFX_STATE_CULL_CCW
				| BGFX_STATE_MSAA
				);

			// Submit primitive for rendering.
			bgfx::submit(_view);
		}
	}

	void submitShadow(uint8_t _view, float* _mtx, bgfx::ProgramHandle _program)
	{
		for (GroupArray::const_iterator it = m_groups.begin(), itEnd = m_groups.end(); it != itEnd; ++it)
		{
			const Group& group = *it;

			// Set model matrix for rendering.
			bgfx::setTransform(_mtx);
			bgfx::setProgram(_program);
			bgfx::setIndexBuffer(group.m_ibh);
			bgfx::setVertexBuffer(group.m_vbh);

			// Set render states.
			bgfx::setState(0
				| BGFX_STATE_RGB_WRITE
				| BGFX_STATE_ALPHA_WRITE
				| BGFX_STATE_DEPTH_WRITE
				| BGFX_STATE_DEPTH_TEST_LESS
				| BGFX_STATE_CULL_CCW
				| BGFX_STATE_MSAA
				);

			// Submit primitive for rendering.
			bgfx::submit(_view);
		}
	}

	bgfx::VertexDecl m_decl;
	typedef std::vector<Group> GroupArray;
	GroupArray m_groups;
};

int _main_(int /*_argc*/, char** /*_argv*/)
{
	uint32_t width = 1280;
	uint32_t height = 720;
	uint32_t debug = BGFX_DEBUG_TEXT;
	uint32_t reset = BGFX_RESET_VSYNC;

	bgfx::init();
	bgfx::reset(width, height, reset);

	// Enable debug text.
	bgfx::setDebug(debug);

	// Setup root path for binary shaders. Shader binaries are different
	// for each renderer.
	switch (bgfx::getRendererType() )
	{
	default:
	case bgfx::RendererType::Direct3D9:
		s_shaderPath = "shaders/dx9/";
		s_texelHalf = 0.5f;
		break;

	case bgfx::RendererType::Direct3D11:
		s_shaderPath = "shaders/dx11/";
		break;

	case bgfx::RendererType::OpenGL:
		s_shaderPath = "shaders/glsl/";
		s_flipV = true;
		break;

	case bgfx::RendererType::OpenGLES:
		s_shaderPath = "shaders/gles/";
		s_flipV = true;
		break;
	}

	// Uniforms.
	u_shadowMap = bgfx::createUniform("u_shadowMap", bgfx::UniformType::Uniform1iv);

	bgfx::UniformHandle u_lightPos = bgfx::createUniform("u_lightPos", bgfx::UniformType::Uniform4fv);
	bgfx::UniformHandle u_lightMtx = bgfx::createUniform("u_lightMtx", bgfx::UniformType::Uniform4x4fv);

	// Vertex declarations.
	bgfx::VertexDecl PosNormalDecl;
	PosNormalDecl.begin()
		.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Normal,    4, bgfx::AttribType::Uint8, true, true)
		.end();

	// Meshes.
	Mesh bunnyMesh;
	Mesh cubeMesh;
	Mesh hollowcubeMesh;
	Mesh hplaneMesh;
	bunnyMesh.load("meshes/bunny.bin");
	cubeMesh.load("meshes/cube.bin");
	hollowcubeMesh.load("meshes/hollowcube.bin");
	hplaneMesh.load(s_hplaneVertices, BX_COUNTOF(s_hplaneVertices), PosNormalDecl, s_planeIndices, BX_COUNTOF(s_planeIndices) );

	// Render targets.
	uint16_t shadowMapSize = 512;

	// Get renderer capabilities info.
	const bgfx::Caps* caps = bgfx::getCaps();
	// Shadow samplers are supported at least partially supported if texture
	// compare less equal feature is supported.
	bool shadowSamplerSupported = 0 != (caps->supported & BGFX_CAPS_TEXTURE_COMPARE_LEQUAL);

	bgfx::ProgramHandle progShadow;
	bgfx::ProgramHandle progMesh;

	if (shadowSamplerSupported)
	{
		// Depth textures and shadow samplers are supported.
		progShadow = loadProgram("vs_sms_shadow", "fs_sms_shadow");
		progMesh   = loadProgram("vs_sms_mesh",   "fs_sms_mesh");

		bgfx::TextureHandle fbtextures[] =
		{
			bgfx::createTexture2D(shadowMapSize, shadowMapSize, 1, bgfx::TextureFormat::D16, BGFX_TEXTURE_COMPARE_LEQUAL),
		};
		s_shadowMapFB = bgfx::createFrameBuffer(BX_COUNTOF(fbtextures), fbtextures, true);
	}
	else
	{
		// Depth textures and shadow samplers are not supported. Use float
		// depth packing into color buffer instead.
		progShadow = loadProgram("vs_sms_shadow_pd", "fs_sms_shadow_pd");
		progMesh   = loadProgram("vs_sms_mesh",      "fs_sms_mesh_pd");

		bgfx::TextureHandle fbtextures[] =
		{
			bgfx::createTexture2D(shadowMapSize, shadowMapSize, 1, bgfx::TextureFormat::BGRA8, BGFX_TEXTURE_RT),
			bgfx::createTexture2D(shadowMapSize, shadowMapSize, 1, bgfx::TextureFormat::D16, BGFX_TEXTURE_RT_BUFFER_ONLY),
		};
		s_shadowMapFB = bgfx::createFrameBuffer(BX_COUNTOF(fbtextures), fbtextures, true);
	}

	// Set view and projection matrices.
	float view[16];
	float proj[16];

	const float eye[3] = { 0.0f, 30.0f, -60.0f };
	const float at[3]  = { 0.0f, 5.0f, 0.0f };
	bx::mtxLookAt(view, eye, at);

	const float aspect = float(int32_t(width) ) / float(int32_t(height) );
	mtxProj(proj, 60.0f, aspect, 0.1f, 1000.0f);

	// Time acumulators.
	float timeAccumulatorLight = 0.0f;
	float timeAccumulatorScene = 0.0f;

	entry::MouseState mouseState;
	while (!entry::processEvents(width, height, debug, reset, &mouseState) )
	{
		// Time.
		int64_t now = bx::getHPCounter();
		static int64_t last = now;
		const int64_t frameTime = now - last;
		last = now;
		const double freq = double(bx::getHPFrequency() );
		const double toMs = 1000.0/freq;
		const float deltaTime = float(frameTime/freq);

		// Update time accumulators.
		timeAccumulatorLight += deltaTime;
		timeAccumulatorScene += deltaTime;

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/15-shadowmaps-simple");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Shadow maps example (technique: %s).", shadowSamplerSupported ? "depth texture and shadow samplers" : "shadow depth packed into color texture");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

		// Setup lights.
		float lightPos[4];
		lightPos[0] = -cos(timeAccumulatorLight);
		lightPos[1] = -1.0f;
		lightPos[2] = -sin(timeAccumulatorLight);
		lightPos[3] = 0.0f;

		bgfx::setUniform(u_lightPos, lightPos);

		// Setup instance matrices.
		float mtxFloor[16];
		bx::mtxSRT(mtxFloor
			, 30.0f, 30.0f, 30.0f
			, 0.0f, 0.0f, 0.0f
			, 0.0f, 0.0f, 0.0f
			);

		float mtxBunny[16];
		bx::mtxSRT(mtxBunny
			, 5.0f, 5.0f, 5.0f
			, 0.0f, bx::pi - timeAccumulatorScene, 0.0f
			, 15.0f, 5.0f, 0.0f
			);

		float mtxHollowcube[16];
		bx::mtxSRT(mtxHollowcube
			, 2.5f, 2.5f, 2.5f
			, 0.0f, 1.56f - timeAccumulatorScene, 0.0f
			, 0.0f, 10.0f, 0.0f
			);

		float mtxCube[16];
		bx::mtxSRT(mtxCube
			, 2.5f, 2.5f, 2.5f
			, 0.0f, 1.56f - timeAccumulatorScene, 0.0f
			, -15.0f, 5.0f, 0.0f
			);

		// Define matrices.
		float lightView[16];
		float lightProj[16];

		const float eye[3] =
		{
			-lightPos[0],
			-lightPos[1],
			-lightPos[2],
		};
		const float at[3] = { 0.0f, 0.0f, 0.0f };
		bx::mtxLookAt(lightView, eye, at);

		const float area = 30.0f;
		bx::mtxOrtho(lightProj, -area, area, -area, area, -100.0f, 100.0f);

		bgfx::setViewRect(RENDER_SHADOW_PASS_ID, 0, 0, shadowMapSize, shadowMapSize);
		bgfx::setViewFrameBuffer(RENDER_SHADOW_PASS_ID, s_shadowMapFB);
		bgfx::setViewTransform(RENDER_SHADOW_PASS_ID, lightView, lightProj);

		bgfx::setViewRect(RENDER_SCENE_PASS_ID, 0, 0, width, height);
		bgfx::setViewTransform(RENDER_SCENE_PASS_ID, view, proj);

		// Clear backbuffer and shadowmap framebuffer at beginning.
		bgfx::setViewClear(RENDER_SHADOW_PASS_ID
			, BGFX_CLEAR_COLOR_BIT | BGFX_CLEAR_DEPTH_BIT
			, 0x303030ff, 1.0f, 0
			);

		bgfx::setViewClear(RENDER_SCENE_PASS_ID
			, BGFX_CLEAR_COLOR_BIT | BGFX_CLEAR_DEPTH_BIT
			, 0x303030ff, 1.0f, 0
			);

		// Render.
		float mtxShadow[16];
		float lightMtx[16];

		const float sy = s_flipV ? 0.5f : -0.5f;
		const float mtxCrop[16] =
		{
			0.5f, 0.0f, 0.0f, 0.0f,
			0.0f,   sy, 0.0f, 0.0f,
			0.0f, 0.0f, 0.5f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f,
		};

		float mtxTmp[16];
		bx::mtxMul(mtxTmp, lightProj, mtxCrop);
		bx::mtxMul(mtxShadow, lightView, mtxTmp);

		// Floor.
		bx::mtxMul(lightMtx, mtxFloor, mtxShadow);
		bgfx::setUniform(u_lightMtx, lightMtx);
		hplaneMesh.submit(RENDER_SCENE_PASS_ID, mtxFloor, progMesh);
		hplaneMesh.submitShadow(RENDER_SHADOW_PASS_ID, mtxFloor, progShadow);

		// Bunny.
		bx::mtxMul(lightMtx, mtxBunny, mtxShadow);
		bgfx::setUniform(u_lightMtx, lightMtx);
		bunnyMesh.submit(RENDER_SCENE_PASS_ID, mtxBunny, progMesh);
		bunnyMesh.submitShadow(RENDER_SHADOW_PASS_ID, mtxBunny, progShadow);

		// Hollow cube.
		bx::mtxMul(lightMtx, mtxHollowcube, mtxShadow);
		bgfx::setUniform(u_lightMtx, lightMtx);
		hollowcubeMesh.submit(RENDER_SCENE_PASS_ID, mtxHollowcube, progMesh);
		hollowcubeMesh.submitShadow(RENDER_SHADOW_PASS_ID, mtxHollowcube, progShadow);

		// Cube.
		bx::mtxMul(lightMtx, mtxCube, mtxShadow);
		bgfx::setUniform(u_lightMtx, lightMtx);
		cubeMesh.submit(RENDER_SCENE_PASS_ID, mtxCube, progMesh);
		cubeMesh.submitShadow(RENDER_SHADOW_PASS_ID, mtxCube, progShadow);

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx::frame();
	}

	bunnyMesh.unload();
	cubeMesh.unload();
	hollowcubeMesh.unload();
	hplaneMesh.unload();

	bgfx::destroyProgram(progShadow);
	bgfx::destroyProgram(progMesh);

	bgfx::destroyFrameBuffer(s_shadowMapFB);

	bgfx::destroyUniform(u_shadowMap);
	bgfx::destroyUniform(u_lightPos);
	bgfx::destroyUniform(u_lightMtx);

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
