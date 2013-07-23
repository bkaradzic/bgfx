/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "common.h"

#include <bgfx.h>
#include <bx/countof.h>
#include <bx/timer.h>
#include <bx/readerwriter.h>
#include "entry.h"
#include "dbg.h"
#include "fpumath.h"
#include "processevents.h"
#include "imgui/imgui.h"

#include <string.h>
#include <vector>
#include <string>

static const char* s_shaderPath = NULL;

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

static bgfx::ProgramHandle loadProgram(const char* _vshName, const char* _fshName)
{
	const bgfx::Memory* mem;

	mem = loadShader(_vshName);
	bgfx::VertexShaderHandle vsh = bgfx::createVertexShader(mem);
	mem = loadShader(_fshName);
	bgfx::FragmentShaderHandle fsh = bgfx::createFragmentShader(mem);
	bgfx::ProgramHandle program = bgfx::createProgram(vsh, fsh);
	bgfx::destroyVertexShader(vsh);
	bgfx::destroyFragmentShader(fsh);

	return program;
}

static const bgfx::Memory* loadTexture(const char* _name)
{
	char filePath[512];
	strcpy(filePath, "textures/");
	strcat(filePath, _name);
	return load(filePath);
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

struct Mesh
{
	void load(const char* _filePath)
	{
#define BGFX_CHUNK_MAGIC_VB BX_MAKEFOURCC('V', 'B', ' ', 0x0)
#define BGFX_CHUNK_MAGIC_IB BX_MAKEFOURCC('I', 'B', ' ', 0x0)
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

					bx::read(&reader, m_decl);
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

			if (bgfx::invalidHandle != group.m_ibh.idx)
			{
				bgfx::destroyIndexBuffer(group.m_ibh);
			}
		}
		m_groups.clear();
	}

	void submit(uint8_t _view, bgfx::ProgramHandle _program, float* _mtx)
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

			// Submit primitive for rendering to view 0.
			bgfx::submit(_view);
		}
	}

	bgfx::VertexDecl m_decl;
	typedef std::vector<Group> GroupArray;
	GroupArray m_groups;
};

static bool s_flipV = false;
static float s_texelHalf = 0.0f;

struct PosColorTexCoord0Vertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_rgba;
	float m_u;
	float m_v;

	static void init()
	{
		ms_decl.begin();
		ms_decl.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);
		ms_decl.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true);
		ms_decl.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float);
		ms_decl.end();
	}

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosColorTexCoord0Vertex::ms_decl;

void screenSpaceQuad(float _textureWidth, float _textureHeight, bool _originBottomLeft = false, float _width = 1.0f, float _height = 1.0f)
{
	if (bgfx::checkAvailTransientVertexBuffer(3, PosColorTexCoord0Vertex::ms_decl) )
	{
		bgfx::TransientVertexBuffer vb;
		bgfx::allocTransientVertexBuffer(&vb, 3, PosColorTexCoord0Vertex::ms_decl);
		PosColorTexCoord0Vertex* vertex = (PosColorTexCoord0Vertex*)vb.data;

		const float zz = 0.0f;

		const float minx = -_width;
		const float maxx =  _width;
		const float miny = 0.0f;
		const float maxy = _height*2.0f;

		const float texelHalfW = s_texelHalf/_textureWidth;
		const float texelHalfH = s_texelHalf/_textureHeight;
		const float minu = -1.0f + texelHalfW;
		const float maxu =  1.0f + texelHalfW;

		float minv = texelHalfH;
		float maxv = 2.0f + texelHalfH;

		if (_originBottomLeft)
		{
			std::swap(minv, maxv);
			minv -= 1.0f;
			maxv -= 1.0f;
		}

		vertex[0].m_x = minx;
		vertex[0].m_y = miny;
		vertex[0].m_z = zz;
		vertex[0].m_rgba = 0xffffffff;
		vertex[0].m_u = minu;
		vertex[0].m_v = minv;

		vertex[1].m_x = maxx;
		vertex[1].m_y = miny;
		vertex[1].m_z = zz;
		vertex[1].m_rgba = 0xffffffff;
		vertex[1].m_u = maxu;
		vertex[1].m_v = minv;

		vertex[2].m_x = maxx;
		vertex[2].m_y = maxy;
		vertex[2].m_z = zz;
		vertex[2].m_rgba = 0xffffffff;
		vertex[2].m_u = maxu;
		vertex[2].m_v = maxv;

		bgfx::setVertexBuffer(&vb);
	}
}

void setOffsets2x2Lum(bgfx::UniformHandle _handle, uint32_t _width, uint32_t _height)
{
	float offsets[16][4];

	float du = 1.0f/_width;
	float dv = 1.0f/_height;

	uint32_t num = 0;
	for (uint32_t yy = 0; yy < 3; ++yy)
	{
		for (uint32_t xx = 0; xx < 3; ++xx)
		{
			offsets[num][0] = (xx - s_texelHalf) * du;
			offsets[num][1] = (yy - s_texelHalf) * dv;
			++num;
		}
	}

	bgfx::setUniform(_handle, offsets, num);
}

void setOffsets4x4Lum(bgfx::UniformHandle _handle, uint32_t _width, uint32_t _height)
{
	float offsets[16][4];

	float du = 1.0f/_width;
	float dv = 1.0f/_height;

	uint32_t num = 0;
	for (uint32_t yy = 0; yy < 4; ++yy)
	{
		for (uint32_t xx = 0; xx < 4; ++xx)
		{
			offsets[num][0] = (xx - 1.0f - s_texelHalf) * du;
			offsets[num][1] = (yy - 1.0f - s_texelHalf) * dv;
			++num;
		}
	}

	bgfx::setUniform(_handle, offsets, num);
}

inline float square(float _x)
{
	return _x*_x;
}

int _main_(int /*_argc*/, char** /*_argv*/)
{
	PosColorTexCoord0Vertex::init();

	uint32_t width = 1280;
	uint32_t height = 720;
	uint32_t debug = BGFX_DEBUG_TEXT;
	uint32_t reset = BGFX_RESET_VSYNC;

	bgfx::init();
	bgfx::reset(width, height, reset);

	// Enable debug text.
	bgfx::setDebug(debug);

	// Set view 0 clear state.
	bgfx::setViewClear(0
		, BGFX_CLEAR_COLOR_BIT|BGFX_CLEAR_DEPTH_BIT
		, 0x303030ff
		, 1.0f
		, 0
		);

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

	case bgfx::RendererType::OpenGLES2:
	case bgfx::RendererType::OpenGLES3:
		s_shaderPath = "shaders/gles/";
		s_flipV = true;
		break;
	}

	const bgfx::Memory* mem;

	mem = loadTexture("uffizi.dds");
	bgfx::TextureHandle uffizi = bgfx::createTexture(mem, BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP|BGFX_TEXTURE_W_CLAMP);

	bgfx::UniformHandle u_time      = bgfx::createUniform("u_time",     bgfx::UniformType::Uniform1f);
	bgfx::UniformHandle u_texCube   = bgfx::createUniform("u_texCube",  bgfx::UniformType::Uniform1i);
	bgfx::UniformHandle u_texColor  = bgfx::createUniform("u_texColor", bgfx::UniformType::Uniform1i);
	bgfx::UniformHandle u_texLum    = bgfx::createUniform("u_texLum",   bgfx::UniformType::Uniform1i);
	bgfx::UniformHandle u_texBlur   = bgfx::createUniform("u_texBlur",  bgfx::UniformType::Uniform1i);
	bgfx::UniformHandle u_mtx       = bgfx::createUniform("u_mtx",      bgfx::UniformType::Uniform4x4fv);
	bgfx::UniformHandle u_tonemap   = bgfx::createUniform("u_tonemap",  bgfx::UniformType::Uniform4fv);
	bgfx::UniformHandle u_offset    = bgfx::createUniform("u_offset",   bgfx::UniformType::Uniform4fv, 16);
	bgfx::UniformHandle u_weight    = bgfx::createUniform("u_weight",   bgfx::UniformType::Uniform4fv, 16);

	bgfx::ProgramHandle skyProgram     = loadProgram("vs_hdr_skybox",  "fs_hdr_skybox");
	bgfx::ProgramHandle lumProgram     = loadProgram("vs_hdr_lum",     "fs_hdr_lum");
	bgfx::ProgramHandle lumAvgProgram  = loadProgram("vs_hdr_lumavg",  "fs_hdr_lumavg");
	bgfx::ProgramHandle blurProgram    = loadProgram("vs_hdr_blur",    "fs_hdr_blur");
	bgfx::ProgramHandle brightProgram  = loadProgram("vs_hdr_bright",  "fs_hdr_bright");
	bgfx::ProgramHandle meshProgram    = loadProgram("vs_hdr_mesh",    "fs_hdr_mesh");
	bgfx::ProgramHandle tonemapProgram = loadProgram("vs_hdr_tonemap", "fs_hdr_tonemap");

	Mesh mesh;
	mesh.load("meshes/bunny.bin");

	bgfx::RenderTargetHandle rt = bgfx::createRenderTarget(width, height, BGFX_RENDER_TARGET_COLOR_RGBA8|BGFX_RENDER_TARGET_DEPTH);

	bgfx::RenderTargetHandle lum[5];
	lum[0] = bgfx::createRenderTarget(128, 128, BGFX_RENDER_TARGET_COLOR_RGBA8);
	lum[1] = bgfx::createRenderTarget( 64,  64, BGFX_RENDER_TARGET_COLOR_RGBA8);
	lum[2] = bgfx::createRenderTarget( 16,  16, BGFX_RENDER_TARGET_COLOR_RGBA8);
	lum[3] = bgfx::createRenderTarget(  4,   4, BGFX_RENDER_TARGET_COLOR_RGBA8);
	lum[4] = bgfx::createRenderTarget(  1,   1, BGFX_RENDER_TARGET_COLOR_RGBA8);

	bgfx::RenderTargetHandle bright;
	bright = bgfx::createRenderTarget(width/2, height/2, BGFX_RENDER_TARGET_COLOR_RGBA8);

	bgfx::RenderTargetHandle blur;
	blur = bgfx::createRenderTarget(width/8, height/8, BGFX_RENDER_TARGET_COLOR_RGBA8);

	FILE* file = fopen("font/droidsans.ttf", "rb");
	uint32_t size = (uint32_t)fsize(file);
	void* data = malloc(size);
	size_t ignore = fread(data, 1, size, file);
	BX_UNUSED(ignore);
	fclose(file);

	imguiCreate(data, size);

	free(data);

	float speed      = 0.37f;
	float middleGray = 0.18f;
	float white      = 1.1f;
	float treshold   = 1.5f;

	int32_t scrollArea = 0;

	uint32_t oldWidth = 0;
	uint32_t oldHeight = 0;

	MouseState mouseState;

	float time = 0.0f;

	while (!processEvents(width, height, debug, reset, &mouseState) )
	{
		if (oldWidth != width
		||  oldHeight != height)
		{
			// Recreate variable size render targets when resolution changes.
			oldWidth = width;
			oldHeight = height;
			bgfx::destroyRenderTarget(rt);
			bgfx::destroyRenderTarget(bright);
			bgfx::destroyRenderTarget(blur);

			rt = bgfx::createRenderTarget(width, height, BGFX_RENDER_TARGET_COLOR_RGBA8|BGFX_RENDER_TARGET_DEPTH);
			bright = bgfx::createRenderTarget(width/2, height/2, BGFX_RENDER_TARGET_COLOR_RGBA8);
			blur = bgfx::createRenderTarget(width/8, height/8, BGFX_RENDER_TARGET_COLOR_RGBA8);
		}

		imguiBeginFrame(mouseState.m_mx
			, mouseState.m_my
			, (mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT  : 0)
			| (mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT : 0)
			, 0
			, width
			, height
			);

		imguiBeginScrollArea("Settings", width - width / 5 - 10, 10, width / 5, height / 3, &scrollArea);
		imguiSeparatorLine();

		imguiSlider("Speed", &speed, 0.0f, 1.0f, 0.01f);
		imguiSeparator();

		imguiSlider("Middle gray", &middleGray, 0.1f, 1.0f, 0.01f);
		imguiSlider("White point", &white, 0.1f, 2.0f, 0.01f);
		imguiSlider("Treshold", &treshold, 0.1f, 2.0f, 0.01f);

		imguiEndScrollArea();
		imguiEndFrame();

		// This dummy draw call is here to make sure that view 0 is cleared
		// if no other draw calls are submitted to view 0.
		bgfx::submit(0);

		int64_t now = bx::getHPCounter();
		static int64_t last = now;
		const int64_t frameTime = now - last;
		last = now;
		const double freq = double(bx::getHPFrequency() );
		const double toMs = 1000.0/freq;

		time += (float)(frameTime*speed/freq);

		bgfx::setUniform(u_time, &time);

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/09-hdr");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Using multiple views and render targets.");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

		// Set views.
		bgfx::setViewRectMask(0x1f, 0, 0, width, height);
		bgfx::setViewRenderTargetMask(0x3, rt);

		bgfx::setViewRect(2, 0, 0, 128, 128);
		bgfx::setViewRenderTarget(2, lum[0]);

		bgfx::setViewRect(3, 0, 0, 64, 64);
		bgfx::setViewRenderTarget(3, lum[1]);

		bgfx::setViewRect(4, 0, 0, 16, 16);
		bgfx::setViewRenderTarget(4, lum[2]);

		bgfx::setViewRect(5, 0, 0, 4, 4);
		bgfx::setViewRenderTarget(5, lum[3]);

		bgfx::setViewRect(6, 0, 0, 1, 1);
		bgfx::setViewRenderTarget(6, lum[4]);

		bgfx::setViewRect(7, 0, 0, width/2, height/2);
		bgfx::setViewRenderTarget(7, bright);

		bgfx::setViewRect(8, 0, 0, width/8, height/8);
		bgfx::setViewRenderTarget(8, blur);

		bgfx::setViewRect(9, 0, 0, width, height);

		float view[16];
		float proj[16];

		mtxIdentity(view);
		mtxOrtho(proj, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 100.0f);

		// Set view and projection matrix for view 0.
		bgfx::setViewTransformMask(0
				|(1<<0)
				|(1<<2)
				|(1<<3)
				|(1<<4)
				|(1<<5)
				|(1<<6)
				|(1<<7)
				|(1<<8)
				|(1<<9)
				, view
				, proj
				);

		float at[3] = { 0.0f, 1.0f, 0.0f };
		float eye[3] = { 0.0f, 1.0f, -2.5f };

		float mtx[16];
		mtxRotateXY(mtx
			, 0.0f
			, time
			); 

		float temp[4];
		vec3MulMtx(temp, eye, mtx);

		mtxLookAt(view, temp, at);
		mtxProj(proj, 60.0f, float(width)/float(height), 0.1f, 100.0f);

		// Set view and projection matrix for view 1.
		bgfx::setViewTransformMask(1<<1, view, proj);

		bgfx::setUniform(u_mtx, mtx);

		// Render skybox into view 0.
		bgfx::setTexture(0, u_texCube, uffizi);
		bgfx::setProgram(skyProgram);
		bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
		screenSpaceQuad( (float)width, (float)height, true);
		bgfx::submit(0);

		// Render mesh into view 1
		bgfx::setTexture(0, u_texCube, uffizi);
		mesh.submit(1, meshProgram, NULL);

		// Calculate luminance.
		setOffsets2x2Lum(u_offset, 128, 128);
		bgfx::setTexture(0, u_texColor, rt);
		bgfx::setProgram(lumProgram);
		bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
		screenSpaceQuad(128.0f, 128.0f, s_flipV);
		bgfx::submit(2);

		// Downscale luminance 0.
		setOffsets4x4Lum(u_offset, 128, 128);
		bgfx::setTexture(0, u_texColor, lum[0]);
		bgfx::setProgram(lumAvgProgram);
		bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
		screenSpaceQuad(64.0f, 64.0f, s_flipV);
		bgfx::submit(3);

		// Downscale luminance 1.
		setOffsets4x4Lum(u_offset, 64, 64);
		bgfx::setTexture(0, u_texColor, lum[1]);
		bgfx::setProgram(lumAvgProgram);
		bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
		screenSpaceQuad(16.0f, 16.0f, s_flipV);
		bgfx::submit(4);

		// Downscale luminance 2.
		setOffsets4x4Lum(u_offset, 16, 16);
		bgfx::setTexture(0, u_texColor, lum[2]);
		bgfx::setProgram(lumAvgProgram);
		bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
		screenSpaceQuad(4.0f, 4.0f, s_flipV);
		bgfx::submit(5);

		// Downscale luminance 3.
		setOffsets4x4Lum(u_offset, 4, 4);
		bgfx::setTexture(0, u_texColor, lum[3]);
		bgfx::setProgram(lumAvgProgram);
		bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
		screenSpaceQuad(1.0f, 1.0f, s_flipV);
		bgfx::submit(6);

		float tonemap[4] = { middleGray, square(white), treshold, 0.0f };
		bgfx::setUniform(u_tonemap, tonemap);

		// Bright pass treshold is tonemap[3].
		setOffsets4x4Lum(u_offset, width/2, height/2);
		bgfx::setTexture(0, u_texColor, rt);
		bgfx::setTexture(1, u_texLum, lum[4]);
		bgfx::setProgram(brightProgram);
		bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
		screenSpaceQuad( (float)width/2.0f, (float)height/2.0f, s_flipV);
		bgfx::submit(7);

		// Blur bright pass vertically.
		bgfx::setTexture(0, u_texColor, bright);
		bgfx::setProgram(blurProgram);
		bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
		screenSpaceQuad( (float)width/8.0f, (float)height/8.0f, s_flipV);
		bgfx::submit(8);

		// Blur bright pass horizontally, do tonemaping and combine.
		bgfx::setTexture(0, u_texColor, rt);
		bgfx::setTexture(1, u_texLum, lum[4]);
		bgfx::setTexture(2, u_texBlur, blur);
		bgfx::setProgram(tonemapProgram);
		bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
		screenSpaceQuad( (float)width, (float)height, s_flipV);
		bgfx::submit(9);

		// Advance to next frame. Rendering thread will be kicked to 
		// process submitted rendering primitives.
		bgfx::frame();
	}

	imguiDestroy();

	// Cleanup.
	mesh.unload();

	bgfx::destroyRenderTarget(lum[0]);
	bgfx::destroyRenderTarget(lum[1]);
	bgfx::destroyRenderTarget(lum[2]);
	bgfx::destroyRenderTarget(lum[3]);
	bgfx::destroyRenderTarget(lum[4]);
	bgfx::destroyRenderTarget(bright);
	bgfx::destroyRenderTarget(blur);
	bgfx::destroyRenderTarget(rt);

	bgfx::destroyProgram(meshProgram);
	bgfx::destroyProgram(skyProgram);
	bgfx::destroyProgram(tonemapProgram);
	bgfx::destroyProgram(lumProgram);
	bgfx::destroyProgram(lumAvgProgram);
	bgfx::destroyProgram(blurProgram);
	bgfx::destroyProgram(brightProgram);
	bgfx::destroyTexture(uffizi);

	bgfx::destroyUniform(u_time);
	bgfx::destroyUniform(u_texCube);
	bgfx::destroyUniform(u_texColor);
	bgfx::destroyUniform(u_texLum);
	bgfx::destroyUniform(u_texBlur);
	bgfx::destroyUniform(u_mtx);
	bgfx::destroyUniform(u_tonemap);
	bgfx::destroyUniform(u_offset);
	bgfx::destroyUniform(u_weight);

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
