/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bgfx/bgfx.h>
#include <bgfx/embedded_shader.h>
#include "debugdraw.h"
#include "../bgfx_utils.h"
#include "../packrect.h"

#include <bx/fpumath.h>
#include <bx/radixsort.h>
#include <bx/uint32_t.h>
#include <bx/crtimpl.h>
#include <bx/handlealloc.h>

struct DebugVertex
{
	float m_x;
	float m_y;
	float m_z;
	float m_len;
	uint32_t m_abgr;

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 1, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0,    4, bgfx::AttribType::Uint8, true)
			.end();
	}

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl DebugVertex::ms_decl;

struct DebugUvVertex
{
	float m_x;
	float m_y;
	float m_z;
	float m_u;
	float m_v;
	uint32_t m_abgr;

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0,    4, bgfx::AttribType::Uint8, true)
			.end();
	}

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl DebugUvVertex::ms_decl;

struct DebugShapeVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint8_t m_indices[4];

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Indices,  4, bgfx::AttribType::Uint8)
			.end();
	}

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl DebugShapeVertex::ms_decl;

static DebugShapeVertex s_cubeVertices[8] =
{
	{-1.0f,  1.0f,  1.0f, { 0, 0, 0, 0 } },
	{ 1.0f,  1.0f,  1.0f, { 0, 0, 0, 0 } },
	{-1.0f, -1.0f,  1.0f, { 0, 0, 0, 0 } },
	{ 1.0f, -1.0f,  1.0f, { 0, 0, 0, 0 } },
	{-1.0f,  1.0f, -1.0f, { 0, 0, 0, 0 } },
	{ 1.0f,  1.0f, -1.0f, { 0, 0, 0, 0 } },
	{-1.0f, -1.0f, -1.0f, { 0, 0, 0, 0 } },
	{ 1.0f, -1.0f, -1.0f, { 0, 0, 0, 0 } },
};

static const uint16_t s_cubeIndices[36] =
{
	0, 1, 2, // 0
	1, 3, 2,
	4, 6, 5, // 2
	5, 6, 7,
	0, 2, 4, // 4
	4, 2, 6,
	1, 5, 3, // 6
	5, 7, 3,
	0, 4, 1, // 8
	4, 5, 1,
	2, 3, 6, // 10
	6, 3, 7,
};

static const uint8_t s_circleLod[] =
{
	37,
	29,
	23,
	17,
	11,
};

static uint8_t getCircleLod(uint8_t _lod)
{
	_lod = _lod > BX_COUNTOF(s_circleLod)-1 ? BX_COUNTOF(s_circleLod)-1 : _lod;
	return s_circleLod[_lod];
}

static void circle(float* _out, float _angle)
{
	float sa = bx::fsin(_angle);
	float ca = bx::fcos(_angle);
	_out[0] = sa;
	_out[1] = ca;
}

static void squircle(float* _out, float _angle)
{
	float sa = bx::fsin(_angle);
	float ca = bx::fcos(_angle);
	_out[0] = bx::fsqrt(bx::fabsolute(sa) ) * bx::fsign(sa);
	_out[1] = bx::fsqrt(bx::fabsolute(ca) ) * bx::fsign(ca);
}

uint32_t genSphere(uint8_t _subdiv0, void* _pos0 = NULL, uint16_t _posStride0 = 0, void* _normals0 = NULL, uint16_t _normalStride0 = 0)
{
	if (NULL != _pos0)
	{
		struct Gen
		{
			Gen(void* _pos, uint16_t _posStride, void* _normals, uint16_t _normalStride, uint8_t _subdiv)
				: m_pos( (uint8_t*)_pos)
				, m_normals( (uint8_t*)_normals)
				, m_posStride(_posStride)
				, m_normalStride(_normalStride)
			{
				static const float scale = 1.0f;
				static const float golden = 1.6180339887f;
				static const float len = bx::fsqrt(golden*golden + 1.0f);
				static const float ss = 1.0f/len * scale;
				static const float ll = ss*golden;

				static const float vv[12][4] =
				{
					{ -ll, 0.0f, -ss, 0.0f },
					{  ll, 0.0f, -ss, 0.0f },
					{  ll, 0.0f,  ss, 0.0f },
					{ -ll, 0.0f,  ss, 0.0f },

					{ -ss,  ll, 0.0f, 0.0f },
					{  ss,  ll, 0.0f, 0.0f },
					{  ss, -ll, 0.0f, 0.0f },
					{ -ss, -ll, 0.0f, 0.0f },

					{ 0.0f, -ss,  ll, 0.0f },
					{ 0.0f,  ss,  ll, 0.0f },
					{ 0.0f,  ss, -ll, 0.0f },
					{ 0.0f, -ss, -ll, 0.0f },
				};

				m_numVertices = 0;

				triangle(vv[ 0], vv[ 4], vv[ 3], scale, _subdiv);
				triangle(vv[ 0], vv[10], vv[ 4], scale, _subdiv);
				triangle(vv[ 4], vv[10], vv[ 5], scale, _subdiv);
				triangle(vv[ 5], vv[10], vv[ 1], scale, _subdiv);
				triangle(vv[ 5], vv[ 1], vv[ 2], scale, _subdiv);
				triangle(vv[ 5], vv[ 2], vv[ 9], scale, _subdiv);
				triangle(vv[ 5], vv[ 9], vv[ 4], scale, _subdiv);
				triangle(vv[ 3], vv[ 4], vv[ 9], scale, _subdiv);

				triangle(vv[ 0], vv[ 3], vv[ 7], scale, _subdiv);
				triangle(vv[ 0], vv[ 7], vv[11], scale, _subdiv);
				triangle(vv[11], vv[ 7], vv[ 6], scale, _subdiv);
				triangle(vv[11], vv[ 6], vv[ 1], scale, _subdiv);
				triangle(vv[ 1], vv[ 6], vv[ 2], scale, _subdiv);
				triangle(vv[ 2], vv[ 6], vv[ 8], scale, _subdiv);
				triangle(vv[ 8], vv[ 6], vv[ 7], scale, _subdiv);
				triangle(vv[ 8], vv[ 7], vv[ 3], scale, _subdiv);

				triangle(vv[ 0], vv[11], vv[10], scale, _subdiv);
				triangle(vv[ 1], vv[10], vv[11], scale, _subdiv);
				triangle(vv[ 2], vv[ 8], vv[ 9], scale, _subdiv);
				triangle(vv[ 3], vv[ 9], vv[ 8], scale, _subdiv);
			}

			void addVert(const float* _v)
			{
				float* verts = (float*)m_pos;
				verts[0] = _v[0];
				verts[1] = _v[1];
				verts[2] = _v[2];
				m_pos += m_posStride;

				if (NULL != m_normals)
				{
					float* normals = (float*)m_normals;
					bx::vec3Norm(normals, _v);
					m_normals += m_normalStride;
				}

				m_numVertices++;
			}

			void triangle(const float* _v0, const float* _v1, const float* _v2, float _scale, uint8_t _subdiv)
			{
				if (0 == _subdiv)
				{
					addVert(_v0);
					addVert(_v1);
					addVert(_v2);
				}
				else
				{
					float tmp0[4];
					float tmp1[4];

					float v01[4];
					bx::vec3Add(tmp0, _v0, _v1);
					bx::vec3Norm(tmp1, tmp0);
					bx::vec3Mul(v01, tmp1, _scale);

					float v12[4];
					bx::vec3Add(tmp0, _v1, _v2);
					bx::vec3Norm(tmp1, tmp0);
					bx::vec3Mul(v12, tmp1, _scale);

					float v20[4];
					bx::vec3Add(tmp0, _v2, _v0);
					bx::vec3Norm(tmp1, tmp0);
					bx::vec3Mul(v20, tmp1, _scale);

					--_subdiv;
					triangle(_v0, v01, v20, _scale, _subdiv);
					triangle(_v1, v12, v01, _scale, _subdiv);
					triangle(_v2, v20, v12, _scale, _subdiv);
					triangle(v01, v12, v20, _scale, _subdiv);
				}
			}

			uint8_t* m_pos;
			uint8_t* m_normals;
			uint16_t m_posStride;
			uint16_t m_normalStride;
			uint32_t m_numVertices;

		} gen(_pos0, _posStride0, _normals0, _normalStride0, _subdiv0);
	}

	uint32_t numVertices = 20*3*bx::uint32_max(1, (uint32_t)bx::fpow(4.0f, _subdiv0) );
	return numVertices;
}

void getPoint(float* _result, Axis::Enum _axis, float _x, float _y)
{
	switch (_axis)
	{
		case Axis::X:
			_result[0] = 0.0f;
			_result[1] = _x;
			_result[2] = _y;
			break;

		case Axis::Y:
			_result[0] = _y;
			_result[1] = 0.0f;
			_result[2] = _x;
			break;

		default:
			_result[0] = _x;
			_result[1] = _y;
			_result[2] = 0.0f;
			break;
	}
}


#include "vs_debugdraw_lines.bin.h"
#include "fs_debugdraw_lines.bin.h"
#include "vs_debugdraw_lines_stipple.bin.h"
#include "fs_debugdraw_lines_stipple.bin.h"
#include "vs_debugdraw_fill.bin.h"
#include "fs_debugdraw_fill.bin.h"
#include "vs_debugdraw_fill_lit.bin.h"
#include "fs_debugdraw_fill_lit.bin.h"
#include "vs_debugdraw_fill_texture.bin.h"
#include "fs_debugdraw_fill_texture.bin.h"

static const bgfx::EmbeddedShader s_embeddedShaders[] =
{
	BGFX_EMBEDDED_SHADER(vs_debugdraw_lines),
	BGFX_EMBEDDED_SHADER(fs_debugdraw_lines),
	BGFX_EMBEDDED_SHADER(vs_debugdraw_lines_stipple),
	BGFX_EMBEDDED_SHADER(fs_debugdraw_lines_stipple),
	BGFX_EMBEDDED_SHADER(vs_debugdraw_fill),
	BGFX_EMBEDDED_SHADER(fs_debugdraw_fill),
	BGFX_EMBEDDED_SHADER(vs_debugdraw_fill_lit),
	BGFX_EMBEDDED_SHADER(fs_debugdraw_fill_lit),
	BGFX_EMBEDDED_SHADER(vs_debugdraw_fill_texture),
	BGFX_EMBEDDED_SHADER(fs_debugdraw_fill_texture),

	BGFX_EMBEDDED_SHADER_END()
};

#define SPRITE_TEXTURE_SIZE 1024

template<uint16_t MaxHandlesT = 256, uint16_t TextureSizeT = 1024>
struct SpriteT
{
	SpriteT()
		: m_ra(TextureSizeT, TextureSizeT)
	{
	}

	SpriteHandle create(uint16_t _width, uint16_t _height)
	{
		SpriteHandle handle = { bx::HandleAlloc::invalid };

		if (m_handleAlloc.getNumHandles() < m_handleAlloc.getMaxHandles() )
		{
			Pack2D pack;
			if (m_ra.find(_width, _height, pack) )
			{
				handle.idx = m_handleAlloc.alloc();
				m_pack[handle.idx] = pack;
			}
		}

		return handle;
	}

	void destroy(SpriteHandle _sprite)
	{
		const Pack2D& pack = m_pack[_sprite.idx];
		m_ra.clear(pack);
		m_handleAlloc.free(_sprite.idx);
	}

	const Pack2D& get(SpriteHandle _sprite) const
	{
		return m_pack[_sprite.idx];
	}

	bx::HandleAllocT<MaxHandlesT> m_handleAlloc;
	Pack2D                        m_pack[MaxHandlesT];
	RectPack2DT<256>              m_ra;
};

struct DebugDraw
{
	DebugDraw()
		: m_depthTestLess(true)
		, m_state(State::Count)
	{
	}

	void init(bool _depthTestLess, bx::AllocatorI* _allocator)
	{
		m_allocator = _allocator;
		m_depthTestLess = _depthTestLess;

#if BX_CONFIG_ALLOCATOR_CRT
		if (NULL == _allocator)
		{
			static bx::CrtAllocator allocator;
			m_allocator = &allocator;
		}
#endif // BX_CONFIG_ALLOCATOR_CRT

		DebugVertex::init();
		DebugUvVertex::init();
		DebugShapeVertex::init();

		bgfx::RendererType::Enum type = bgfx::getRendererType();

		m_program[Program::Lines] =
			bgfx::createProgram(
				  bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_debugdraw_lines")
				, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_debugdraw_lines")
				, true
				);

		m_program[Program::LinesStipple] =
			bgfx::createProgram(
				  bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_debugdraw_lines_stipple")
				, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_debugdraw_lines_stipple")
				, true
				);

		m_program[Program::Fill] =
			bgfx::createProgram(
				  bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_debugdraw_fill")
				, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_debugdraw_fill")
				, true
				);

		m_program[Program::FillLit] =
			bgfx::createProgram(
				  bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_debugdraw_fill_lit")
				, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_debugdraw_fill_lit")
				, true
				);

		m_program[Program::FillTexture] =
			bgfx::createProgram(
				  bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_debugdraw_fill_texture")
				, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_debugdraw_fill_texture")
				, true
				);

		u_params   = bgfx::createUniform("u_params", bgfx::UniformType::Vec4, 4);
		s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Int1);
		m_texture  = bgfx::createTexture2D(SPRITE_TEXTURE_SIZE, SPRITE_TEXTURE_SIZE, false, 1, bgfx::TextureFormat::BGRA8);

		void* vertices[Mesh::Count] = {};
		uint16_t* indices[Mesh::Count] = {};
		uint16_t stride = DebugShapeVertex::ms_decl.getStride();

		uint32_t startVertex = 0;
		uint32_t startIndex  = 0;

		for (uint32_t mesh = 0; mesh < 4; ++mesh)
		{
			Mesh::Enum id = Mesh::Enum(Mesh::Sphere0+mesh);

			const uint8_t  tess = uint8_t(3-mesh);
			const uint32_t numVertices = genSphere(tess);
			const uint32_t numIndices  = numVertices;

			vertices[id] = BX_ALLOC(m_allocator, numVertices*stride);
			memset(vertices[id], 0, numVertices*stride);
			genSphere(tess, vertices[id], stride);

			uint16_t* trilist = (uint16_t*)BX_ALLOC(m_allocator, numIndices*sizeof(uint16_t) );
			for (uint32_t ii = 0; ii < numIndices; ++ii)
			{
				trilist[ii] = uint16_t(ii);
			}

			uint32_t numLineListIndices = bgfx::topologyConvert(bgfx::TopologyConvert::TriListToLineList
							, NULL
							, 0
							, trilist
							, numIndices
							, false
							);
			indices[id] = (uint16_t*)BX_ALLOC(m_allocator, (numIndices + numLineListIndices)*sizeof(uint16_t) );
			uint16_t* indicesOut = indices[id];
			memcpy(indicesOut, trilist, numIndices*sizeof(uint16_t) );

			bgfx::topologyConvert(bgfx::TopologyConvert::TriListToLineList
							, &indicesOut[numIndices]
							, numLineListIndices*sizeof(uint16_t)
							, trilist
							, numIndices
							, false
							);

			m_mesh[id].m_startVertex = startVertex;
			m_mesh[id].m_numVertices = numVertices;
			m_mesh[id].m_startIndex[0] = startIndex;
			m_mesh[id].m_numIndices[0] = numIndices;
			m_mesh[id].m_startIndex[1] = startIndex+numIndices;
			m_mesh[id].m_numIndices[1] = numLineListIndices;

			startVertex += numVertices;
			startIndex  += numIndices + numLineListIndices;

			BX_FREE(m_allocator, trilist);
		}

		for (uint32_t mesh = 0; mesh < 4; ++mesh)
		{
			Mesh::Enum id = Mesh::Enum(Mesh::Cone0+mesh);

			const uint32_t num = getCircleLod(uint8_t(mesh) );
			const float step = bx::pi * 2.0f / num;

			const uint32_t numVertices = num+1;
			const uint32_t numIndices  = num*6;
			const uint32_t numLineListIndices = num*4;

			vertices[id] = BX_ALLOC(m_allocator, numVertices*stride);
			indices[id]  = (uint16_t*)BX_ALLOC(m_allocator, (numIndices + numLineListIndices)*sizeof(uint16_t) );
			memset(indices[id], 0, (numIndices + numLineListIndices)*sizeof(uint16_t) );

			DebugShapeVertex* vertex = (DebugShapeVertex*)vertices[id];
			uint16_t* index = indices[id];

			vertex[num].m_x = 0.0f;
			vertex[num].m_y = 0.0f;
			vertex[num].m_z = 0.0f;
			vertex[num].m_indices[0] = 1;

			for (uint32_t ii = 0; ii < num; ++ii)
			{
				const float angle = step * ii;

				float xy[2];
				circle(xy, angle);

				vertex[ii].m_x = xy[1];
				vertex[ii].m_y = 0.0f;
				vertex[ii].m_z = xy[0];
				vertex[ii].m_indices[0] = 0;

				index[ii*3+0] = uint16_t(num);
				index[ii*3+1] = uint16_t( (ii+1)%num);
				index[ii*3+2] = uint16_t(ii);

				index[num*3+ii*3+0] = 0;
				index[num*3+ii*3+1] = uint16_t(ii);
				index[num*3+ii*3+2] = uint16_t( (ii+1)%num);

				index[numIndices+ii*2+0] = uint16_t(ii);
				index[numIndices+ii*2+1] = uint16_t(num);

				index[numIndices+num*2+ii*2+0] = uint16_t(ii);
				index[numIndices+num*2+ii*2+1] = uint16_t( (ii+1)%num);
			}

			m_mesh[id].m_startVertex = startVertex;
			m_mesh[id].m_numVertices = numVertices;
			m_mesh[id].m_startIndex[0] = startIndex;
			m_mesh[id].m_numIndices[0] = numIndices;
			m_mesh[id].m_startIndex[1] = startIndex+numIndices;
			m_mesh[id].m_numIndices[1] = numLineListIndices;

			startVertex += numVertices;
			startIndex  += numIndices + numLineListIndices;
		}

		for (uint32_t mesh = 0; mesh < 4; ++mesh)
		{
			Mesh::Enum id = Mesh::Enum(Mesh::Cylinder0+mesh);

			const uint32_t num = getCircleLod(uint8_t(mesh) );
			const float step = bx::pi * 2.0f / num;

			const uint32_t numVertices = num*2;
			const uint32_t numIndices  = num*12;
			const uint32_t numLineListIndices = num*6;

			vertices[id] = BX_ALLOC(m_allocator, numVertices*stride);
			indices[id]  = (uint16_t*)BX_ALLOC(m_allocator, (numIndices + numLineListIndices)*sizeof(uint16_t) );
			memset(indices[id], 0, (numIndices + numLineListIndices)*sizeof(uint16_t) );

			DebugShapeVertex* vertex = (DebugShapeVertex*)vertices[id];
			uint16_t* index = indices[id];

			for (uint32_t ii = 0; ii < num; ++ii)
			{
				const float angle = step * ii;

				float xy[2];
				circle(xy, angle);

				vertex[ii].m_x = xy[1];
				vertex[ii].m_y = 0.0f;
				vertex[ii].m_z = xy[0];
				vertex[ii].m_indices[0] = 0;

				vertex[ii+num].m_x = xy[1];
				vertex[ii+num].m_y = 0.0f;
				vertex[ii+num].m_z = xy[0];
				vertex[ii+num].m_indices[0] = 1;

				index[ii*6+0] = uint16_t(ii+num);
				index[ii*6+1] = uint16_t( (ii+1)%num);
				index[ii*6+2] = uint16_t(ii);
				index[ii*6+3] = uint16_t(ii+num);
				index[ii*6+4] = uint16_t( (ii+1)%num+num);
				index[ii*6+5] = uint16_t( (ii+1)%num);

				index[num*6+ii*6+0] = uint16_t(0);
				index[num*6+ii*6+1] = uint16_t(ii);
				index[num*6+ii*6+2] = uint16_t( (ii+1)%num);
				index[num*6+ii*6+3] = uint16_t(num);
				index[num*6+ii*6+4] = uint16_t( (ii+1)%num+num);
				index[num*6+ii*6+5] = uint16_t(ii+num);

				index[numIndices+ii*2+0] = uint16_t(ii);
				index[numIndices+ii*2+1] = uint16_t(ii+num);

				index[numIndices+num*2+ii*2+0] = uint16_t(ii);
				index[numIndices+num*2+ii*2+1] = uint16_t( (ii+1)%num);

				index[numIndices+num*4+ii*2+0] = uint16_t(num + ii);
				index[numIndices+num*4+ii*2+1] = uint16_t(num + (ii+1)%num);
			}

			m_mesh[id].m_startVertex = startVertex;
			m_mesh[id].m_numVertices = numVertices;
			m_mesh[id].m_startIndex[0] = startIndex;
			m_mesh[id].m_numIndices[0] = numIndices;
			m_mesh[id].m_startIndex[1] = startIndex+numIndices;
			m_mesh[id].m_numIndices[1] = numLineListIndices;

			startVertex += numVertices;
			startIndex  += numIndices + numLineListIndices;
		}

		for (uint32_t mesh = 0; mesh < 4; ++mesh)
		{
			Mesh::Enum id = Mesh::Enum(Mesh::Capsule0+mesh);

			const uint32_t num = getCircleLod(uint8_t(mesh) );
			const float step = bx::pi * 2.0f / num;

			const uint32_t numVertices = num*2;
			const uint32_t numIndices  = num*6;
			const uint32_t numLineListIndices = num*6;

			vertices[id] = BX_ALLOC(m_allocator, numVertices*stride);
			indices[id]  = (uint16_t*)BX_ALLOC(m_allocator, (numIndices + numLineListIndices)*sizeof(uint16_t) );
			memset(indices[id], 0, (numIndices + numLineListIndices)*sizeof(uint16_t) );

			DebugShapeVertex* vertex = (DebugShapeVertex*)vertices[id];
			uint16_t* index = indices[id];

			for (uint32_t ii = 0; ii < num; ++ii)
			{
				const float angle = step * ii;

				float xy[2];
				circle(xy, angle);

				vertex[ii].m_x = xy[1];
				vertex[ii].m_y = 0.0f;
				vertex[ii].m_z = xy[0];
				vertex[ii].m_indices[0] = 0;

				vertex[ii+num].m_x = xy[1];
				vertex[ii+num].m_y = 0.0f;
				vertex[ii+num].m_z = xy[0];
				vertex[ii+num].m_indices[0] = 1;

				index[ii*6+0] = uint16_t(ii+num);
				index[ii*6+1] = uint16_t( (ii+1)%num);
				index[ii*6+2] = uint16_t(ii);
				index[ii*6+3] = uint16_t(ii+num);
				index[ii*6+4] = uint16_t( (ii+1)%num+num);
				index[ii*6+5] = uint16_t( (ii+1)%num);

//				index[num*6+ii*6+0] = uint16_t(0);
//				index[num*6+ii*6+1] = uint16_t(ii);
//				index[num*6+ii*6+2] = uint16_t( (ii+1)%num);
//				index[num*6+ii*6+3] = uint16_t(num);
//				index[num*6+ii*6+4] = uint16_t( (ii+1)%num+num);
//				index[num*6+ii*6+5] = uint16_t(ii+num);

				index[numIndices+ii*2+0] = uint16_t(ii);
				index[numIndices+ii*2+1] = uint16_t(ii+num);

				index[numIndices+num*2+ii*2+0] = uint16_t(ii);
				index[numIndices+num*2+ii*2+1] = uint16_t( (ii+1)%num);

				index[numIndices+num*4+ii*2+0] = uint16_t(num + ii);
				index[numIndices+num*4+ii*2+1] = uint16_t(num + (ii+1)%num);
			}

			m_mesh[id].m_startVertex = startVertex;
			m_mesh[id].m_numVertices = numVertices;
			m_mesh[id].m_startIndex[0] = startIndex;
			m_mesh[id].m_numIndices[0] = numIndices;
			m_mesh[id].m_startIndex[1] = startIndex+numIndices;
			m_mesh[id].m_numIndices[1] = numLineListIndices;

			startVertex += numVertices;
			startIndex  += numIndices + numLineListIndices;
		}

		m_mesh[Mesh::Cube].m_startVertex = startVertex;
		m_mesh[Mesh::Cube].m_numVertices = BX_COUNTOF(s_cubeVertices);
		m_mesh[Mesh::Cube].m_startIndex[0] = startIndex;
		m_mesh[Mesh::Cube].m_numIndices[0] = BX_COUNTOF(s_cubeIndices);
		m_mesh[Mesh::Cube].m_startIndex[1] = 0;
		m_mesh[Mesh::Cube].m_numIndices[1] = 0;
		startVertex += m_mesh[Mesh::Cube].m_numVertices;
		startIndex  += m_mesh[Mesh::Cube].m_numIndices[0];

		const bgfx::Memory* vb = bgfx::alloc(startVertex*stride);
		const bgfx::Memory* ib = bgfx::alloc(startIndex*sizeof(uint16_t) );

		for (uint32_t mesh = Mesh::Sphere0; mesh < Mesh::Cube; ++mesh)
		{
			Mesh::Enum id = Mesh::Enum(mesh);
			memcpy(&vb->data[m_mesh[id].m_startVertex * stride]
				 , vertices[id]
				 , m_mesh[id].m_numVertices*stride
				 );

			memcpy(&ib->data[m_mesh[id].m_startIndex[0] * sizeof(uint16_t)]
				 , indices[id]
				 , (m_mesh[id].m_numIndices[0]+m_mesh[id].m_numIndices[1])*sizeof(uint16_t)
				 );

			BX_FREE(m_allocator, vertices[id]);
			BX_FREE(m_allocator, indices[id]);
		}

		memcpy(&vb->data[m_mesh[Mesh::Cube].m_startVertex * stride]
			, s_cubeVertices
			, sizeof(s_cubeVertices)
			);

		memcpy(&ib->data[m_mesh[Mesh::Cube].m_startIndex[0] * sizeof(uint16_t)]
			, s_cubeIndices
			, sizeof(s_cubeIndices)
			);

		m_vbh = bgfx::createVertexBuffer(vb, DebugShapeVertex::ms_decl);
		m_ibh = bgfx::createIndexBuffer(ib);

		m_mtx       = 0;
		m_viewId    = 0;
		m_pos       = 0;
		m_indexPos  = 0;
		m_vertexPos = 0;
		m_posQuad   = 0;
	}

	void shutdown()
	{
		bgfx::destroyIndexBuffer(m_ibh);
		bgfx::destroyVertexBuffer(m_vbh);
		for (uint32_t ii = 0; ii < Program::Count; ++ii)
		{
			bgfx::destroyProgram(m_program[ii]);
		}
		bgfx::destroyUniform(u_params);
		bgfx::destroyUniform(s_texColor);
		bgfx::destroyTexture(m_texture);
	}

	SpriteHandle createSprite(uint16_t _width, uint16_t _height, const void* _data)
	{
		SpriteHandle handle = m_sprite.create(_width, _height);

		if (isValid(handle) )
		{
			const Pack2D& pack = m_sprite.get(handle);
			bgfx::updateTexture2D(
				  m_texture
				, 0
				, 0
				, pack.m_x
				, pack.m_y
				, pack.m_width
				, pack.m_height
				, bgfx::copy(_data, pack.m_width*pack.m_height*4)
				);
		}

		return handle;
	}

	void destroy(SpriteHandle _handle)
	{
		m_sprite.destroy(_handle);
	}

	void begin(uint8_t _viewId)
	{
		BX_CHECK(State::Count == m_state);

		m_viewId  = _viewId;
		m_mtx     = 0;
		m_state   = State::None;
		m_stack   = 0;

		Attrib& attrib = m_attrib[0];
		attrib.m_state = 0
			| BGFX_STATE_RGB_WRITE
			| (m_depthTestLess ? BGFX_STATE_DEPTH_TEST_LESS : BGFX_STATE_DEPTH_TEST_GREATER)
			| BGFX_STATE_CULL_CW
			| BGFX_STATE_DEPTH_WRITE
			;
		attrib.m_scale     = 1.0f;
		attrib.m_spin      = 0.0f;
		attrib.m_offset    = 0.0f;
		attrib.m_abgr      = UINT32_MAX;
		attrib.m_stipple   = false;
		attrib.m_wireframe = false;
		attrib.m_lod       = 0;
	}

	void end()
	{
		BX_CHECK(0 == m_stack, "Invalid stack %d.", m_stack);

		flushQuad();
		flush();

		m_state  = State::Count;
	}

	void push()
	{
		BX_CHECK(State::Count != m_state);
		++m_stack;
		m_attrib[m_stack] = m_attrib[m_stack-1];
	}

	void pop()
	{
		BX_CHECK(State::Count != m_state);
		const Attrib& curr = m_attrib[m_stack];
		const Attrib& prev = m_attrib[m_stack-1];
		if (curr.m_stipple != prev.m_stipple
		||  curr.m_state   != prev.m_state)
		{
			flush();
		}
		--m_stack;
	}

	void setTransform(const void* _mtx)
	{
		BX_CHECK(State::Count != m_state);
		flush();

		if (NULL == _mtx)
		{
			m_mtx = 0;
			return;
		}

		bgfx::Transform transform;
		m_mtx = bgfx::allocTransform(&transform, 1);
		memcpy(transform.data, _mtx, 64);
	}

	void setTranslate(float _x, float _y, float _z)
	{
		float mtx[16];
		bx::mtxTranslate(mtx, _x, _y, _z);
		setTransform(mtx);
	}

	void setTranslate(const float* _pos)
	{
		setTranslate(_pos[0], _pos[1], _pos[2]);
	}

	void setState(bool _depthTest, bool _depthWrite, bool _clockwise)
	{
		const uint64_t depthTest = m_depthTestLess
			? BGFX_STATE_DEPTH_TEST_LESS
			: BGFX_STATE_DEPTH_TEST_GREATER
			;

		uint64_t state = m_attrib[m_stack].m_state & ~(0
			| BGFX_STATE_DEPTH_TEST_MASK
			| BGFX_STATE_DEPTH_WRITE
			| BGFX_STATE_CULL_CW
			| BGFX_STATE_CULL_CCW
			);

		state |= _depthTest
			? depthTest
			: 0
			;

		state |= _depthWrite
			? BGFX_STATE_DEPTH_WRITE
			: 0
			;

		state |= _clockwise
			? BGFX_STATE_CULL_CW
			: BGFX_STATE_CULL_CCW
			;

		if (m_attrib[m_stack].m_state != state)
		{
			flush();
		}

		m_attrib[m_stack].m_state = state;
	}

	void setColor(uint32_t _abgr)
	{
		BX_CHECK(State::Count != m_state);
		m_attrib[m_stack].m_abgr = _abgr;
	}

	void setLod(uint8_t _lod)
	{
		BX_CHECK(State::Count != m_state);
		m_attrib[m_stack].m_lod = _lod;
	}

	void setWireframe(bool _wireframe)
	{
		BX_CHECK(State::Count != m_state);
		m_attrib[m_stack].m_wireframe = _wireframe;
	}

	void setStipple(bool _stipple, float _scale = 1.0f, float _offset = 0.0f)
	{
		BX_CHECK(State::Count != m_state);

		Attrib& attrib = m_attrib[m_stack];

		if (attrib.m_stipple != _stipple)
		{
			flush();
		}

		attrib.m_stipple = _stipple;
		attrib.m_offset  = _offset;
		attrib.m_scale   = _scale;
	}

	void setSpin(float _spin)
	{
		Attrib& attrib = m_attrib[m_stack];
		attrib.m_spin = _spin;
	}

	void moveTo(float _x, float _y, float _z = 0.0f)
	{
		BX_CHECK(State::Count != m_state);

		softFlush();

		m_state = State::MoveTo;

		DebugVertex& vertex = m_cache[m_pos];
		vertex.m_x = _x;
		vertex.m_y = _y;
		vertex.m_z = _z;

		Attrib& attrib = m_attrib[m_stack];
		vertex.m_abgr = attrib.m_abgr;
		vertex.m_len  = attrib.m_offset;

		m_vertexPos = m_pos;
	}

	void moveTo(const void* _pos)
	{
		BX_CHECK(State::Count != m_state);

		const float* pos = (const float*)_pos;
		moveTo(pos[0], pos[1], pos[2]);
	}

	void moveTo(Axis::Enum _axis, float _x, float _y)
	{
		float pos[3];
		getPoint(pos, _axis, _x, _y);
		moveTo(pos);
	}

	void lineTo(float _x, float _y, float _z = 0.0f)
	{
		BX_CHECK(State::Count != m_state);
		if (State::None == m_state)
		{
			moveTo(_x, _y, _z);
			return;
		}

		if (m_pos+2 > uint16_t(BX_COUNTOF(m_cache) ) )
		{
			uint32_t pos = m_pos;
			uint32_t vertexPos = m_vertexPos;

			flush();

			memcpy(&m_cache[0], &m_cache[vertexPos], sizeof(DebugVertex) );
			if (vertexPos == pos)
			{
				m_pos = 1;
			}
			else
			{
				memcpy(&m_cache[1], &m_cache[pos - 1], sizeof(DebugVertex) );
				m_pos = 2;
			}

			m_state = State::LineTo;
		}
		else if (State::MoveTo == m_state)
		{
			++m_pos;
			m_state = State::LineTo;
		}

		uint16_t prev = m_pos-1;
		uint16_t curr = m_pos++;
		DebugVertex& vertex = m_cache[curr];
		vertex.m_x = _x;
		vertex.m_y = _y;
		vertex.m_z = _z;

		Attrib& attrib = m_attrib[m_stack];
		vertex.m_abgr = attrib.m_abgr;
		vertex.m_len  = attrib.m_offset;

		float tmp[3];
		bx::vec3Sub(tmp, &vertex.m_x, &m_cache[prev].m_x);
		float len = bx::vec3Length(tmp) * attrib.m_scale;
		vertex.m_len = m_cache[prev].m_len + len;

		m_indices[m_indexPos++] = prev;
		m_indices[m_indexPos++] = curr;
	}

	void lineTo(const void* _pos)
	{
		BX_CHECK(State::Count != m_state);

		const float* pos = (const float*)_pos;
		lineTo(pos[0], pos[1], pos[2]);
	}

	void lineTo(Axis::Enum _axis, float _x, float _y)
	{
		float pos[3];
		getPoint(pos, _axis, _x, _y);
		lineTo(pos);
	}

	void close()
	{
		BX_CHECK(State::Count != m_state);
		DebugVertex& vertex = m_cache[m_vertexPos];
		lineTo(vertex.m_x, vertex.m_y, vertex.m_z);

		m_state = State::None;
	}

	void draw(const Aabb& _aabb)
	{
		moveTo(_aabb.m_min[0], _aabb.m_min[1], _aabb.m_min[2]);
		lineTo(_aabb.m_max[0], _aabb.m_min[1], _aabb.m_min[2]);
		lineTo(_aabb.m_max[0], _aabb.m_max[1], _aabb.m_min[2]);
		lineTo(_aabb.m_min[0], _aabb.m_max[1], _aabb.m_min[2]);
		close();

		moveTo(_aabb.m_min[0], _aabb.m_min[1], _aabb.m_max[2]);
		lineTo(_aabb.m_max[0], _aabb.m_min[1], _aabb.m_max[2]);
		lineTo(_aabb.m_max[0], _aabb.m_max[1], _aabb.m_max[2]);
		lineTo(_aabb.m_min[0], _aabb.m_max[1], _aabb.m_max[2]);
		close();

		moveTo(_aabb.m_min[0], _aabb.m_min[1], _aabb.m_min[2]);
		lineTo(_aabb.m_min[0], _aabb.m_min[1], _aabb.m_max[2]);

		moveTo(_aabb.m_max[0], _aabb.m_min[1], _aabb.m_min[2]);
		lineTo(_aabb.m_max[0], _aabb.m_min[1], _aabb.m_max[2]);

		moveTo(_aabb.m_min[0], _aabb.m_max[1], _aabb.m_min[2]);
		lineTo(_aabb.m_min[0], _aabb.m_max[1], _aabb.m_max[2]);

		moveTo(_aabb.m_max[0], _aabb.m_max[1], _aabb.m_min[2]);
		lineTo(_aabb.m_max[0], _aabb.m_max[1], _aabb.m_max[2]);
	}

	void draw(const Cylinder& _cylinder, bool _capsule)
	{
		drawCylinder(_cylinder.m_pos, _cylinder.m_end, _cylinder.m_radius, _capsule);
	}

	void draw(const Disk& _disk)
	{
		drawCircle(_disk.m_normal, _disk.m_center, _disk.m_radius, 0.0f);
	}

	void draw(const Obb& _obb)
	{
		const Attrib& attrib = m_attrib[m_stack];
		if (attrib.m_wireframe)
		{
			setTransform(_obb.m_mtx);

			moveTo(-1.0f, -1.0f, -1.0f);
			lineTo( 1.0f, -1.0f, -1.0f);
			lineTo( 1.0f,  1.0f, -1.0f);
			lineTo(-1.0f,  1.0f, -1.0f);
			close();

			moveTo(-1.0f,  1.0f,  1.0f);
			lineTo( 1.0f,  1.0f,  1.0f);
			lineTo( 1.0f, -1.0f,  1.0f);
			lineTo(-1.0f, -1.0f,  1.0f);
			close();

			moveTo( 1.0f, -1.0f, -1.0f);
			lineTo( 1.0f, -1.0f,  1.0f);

			moveTo( 1.0f,  1.0f, -1.0f);
			lineTo( 1.0f,  1.0f,  1.0f);

			moveTo(-1.0f,  1.0f, -1.0f);
			lineTo(-1.0f,  1.0f,  1.0f);

			moveTo(-1.0f, -1.0f, -1.0f);
			lineTo(-1.0f, -1.0f,  1.0f);

			setTransform(NULL);
		}
		else
		{
			draw(Mesh::Cube, _obb.m_mtx, 1, false);
		}
	}

	void draw(const Sphere& _sphere)
	{
		const Attrib& attrib = m_attrib[m_stack];
		float mtx[16];
		bx::mtxSRT(mtx
				, _sphere.m_radius
				, _sphere.m_radius
				, _sphere.m_radius
				, 0.0f
				, 0.0f
				, 0.0f
				, _sphere.m_center[0]
				, _sphere.m_center[1]
				, _sphere.m_center[2]
				);
		uint8_t lod = attrib.m_lod > Mesh::SphereMaxLod
					? uint8_t(Mesh::SphereMaxLod)
					: attrib.m_lod
					;
		draw(Mesh::Enum(Mesh::Sphere0 + lod), mtx, 1, attrib.m_wireframe);
	}

	void drawFrustum(const float* _viewProj)
	{
		Plane planes[6];
		buildFrustumPlanes(planes, _viewProj);

		float points[24];
		intersectPlanes(&points[ 0], planes[0], planes[2], planes[4]);
		intersectPlanes(&points[ 3], planes[0], planes[3], planes[4]);
		intersectPlanes(&points[ 6], planes[0], planes[3], planes[5]);
		intersectPlanes(&points[ 9], planes[0], planes[2], planes[5]);
		intersectPlanes(&points[12], planes[1], planes[2], planes[4]);
		intersectPlanes(&points[15], planes[1], planes[3], planes[4]);
		intersectPlanes(&points[18], planes[1], planes[3], planes[5]);
		intersectPlanes(&points[21], planes[1], planes[2], planes[5]);

		moveTo(&points[ 0]);
		lineTo(&points[ 3]);
		lineTo(&points[ 6]);
		lineTo(&points[ 9]);
		close();

		moveTo(&points[12]);
		lineTo(&points[15]);
		lineTo(&points[18]);
		lineTo(&points[21]);
		close();

		moveTo(&points[ 0]);
		lineTo(&points[12]);

		moveTo(&points[ 3]);
		lineTo(&points[15]);

		moveTo(&points[ 6]);
		lineTo(&points[18]);

		moveTo(&points[ 9]);
		lineTo(&points[21]);
	}

	void drawFrustum(const void* _viewProj)
	{
		drawFrustum( (const float*)_viewProj);
	}

	void drawArc(Axis::Enum _axis, float _x, float _y, float _z, float _radius, float _degrees)
	{
		const Attrib& attrib = m_attrib[m_stack];
		const uint32_t num = getCircleLod(attrib.m_lod);
		const float step = bx::pi * 2.0f / num;

		_degrees = bx::fwrap(_degrees, 360.0f);

		float pos[3];
		getPoint(pos, _axis
			, bx::fsin(step * 0)*_radius
			, bx::fcos(step * 0)*_radius
			);

		moveTo(pos[0] + _x, pos[1] + _y, pos[2] + _z);

		uint32_t n = uint32_t(num*_degrees/360.0f);

		for (uint32_t ii = 1; ii < n+1; ++ii)
		{
			getPoint(pos, _axis
				 , bx::fsin(step * ii)*_radius
				 , bx::fcos(step * ii)*_radius
				 );
			lineTo(pos[0] + _x, pos[1] + _y, pos[2] + _z);
		}

		moveTo(_x, _y, _z);
		getPoint(pos, _axis
			 , bx::fsin(step * 0)*_radius
			 , bx::fcos(step * 0)*_radius
			 );
		lineTo(pos[0] + _x, pos[1] + _y, pos[2] + _z);

		getPoint(pos, _axis
			 , bx::fsin(step * n)*_radius
			 , bx::fcos(step * n)*_radius
			 );
		moveTo(pos[0] + _x, pos[1] + _y, pos[2] + _z);
		lineTo(_x, _y, _z);
	}

	void drawCircle(const float* _normal, const float* _center, float _radius, float _weight)
	{
		const Attrib& attrib = m_attrib[m_stack];
		const uint32_t num = getCircleLod(attrib.m_lod);
		const float step = bx::pi * 2.0f / num;
		_weight = bx::fclamp(_weight, 0.0f, 2.0f);

		float udir[3];
		float vdir[3];
		bx::vec3TangentFrame(_normal, udir, vdir, attrib.m_spin);

		float pos[3];
		float tmp0[3];
		float tmp1[3];

		float xy0[2];
		float xy1[2];
		circle(xy0, 0.0f);
		squircle(xy1, 0.0f);

		bx::vec3Mul(pos,  udir, bx::flerp(xy0[0], xy1[0], _weight)*_radius);
		bx::vec3Mul(tmp0, vdir, bx::flerp(xy0[1], xy1[1], _weight)*_radius);
		bx::vec3Add(tmp1, pos,  tmp0);
		bx::vec3Add(pos,  tmp1, _center);
		moveTo(pos);

		for (uint32_t ii = 1; ii < num; ++ii)
		{
			float angle = step * ii;
			circle(xy0, angle);
			squircle(xy1, angle);

			bx::vec3Mul(pos,  udir, bx::flerp(xy0[0], xy1[0], _weight)*_radius);
			bx::vec3Mul(tmp0, vdir, bx::flerp(xy0[1], xy1[1], _weight)*_radius);
			bx::vec3Add(tmp1, pos,  tmp0);
			bx::vec3Add(pos,  tmp1, _center);
			lineTo(pos);
		}

		close();
	}

	void drawCircle(const void* _normal, const void* _center, float _radius, float _weight)
	{
		drawCircle( (const float*)_normal, (const float*)_center, _radius, _weight);
	}

	void drawCircle(Axis::Enum _axis, float _x, float _y, float _z, float _radius, float _weight)
	{
		const Attrib& attrib = m_attrib[m_stack];
		const uint32_t num = getCircleLod(attrib.m_lod);
		const float step = bx::pi * 2.0f / num;
		_weight = bx::fclamp(_weight, 0.0f, 2.0f);

		float xy0[2];
		float xy1[2];
		circle(xy0, 0.0f);
		squircle(xy1, 0.0f);

		float pos[3];
		getPoint(pos, _axis
			, bx::flerp(xy0[0], xy1[0], _weight)*_radius
			, bx::flerp(xy0[1], xy1[1], _weight)*_radius
			);

		moveTo(pos[0] + _x, pos[1] + _y, pos[2] + _z);
		for (uint32_t ii = 1; ii < num; ++ii)
		{
			float angle = step * ii;
			circle(xy0, angle);
			squircle(xy1, angle);

			getPoint(pos, _axis
				, bx::flerp(xy0[0], xy1[0], _weight)*_radius
				, bx::flerp(xy0[1], xy1[1], _weight)*_radius
				);
			lineTo(pos[0] + _x, pos[1] + _y, pos[2] + _z);
		}
		close();
	}

	void drawQuad(const float* _normal, const float* _center, float _size)
	{
		const Attrib& attrib = m_attrib[m_stack];

		float udir[3];
		float vdir[3];

		bx::vec3TangentFrame(_normal, udir, vdir, attrib.m_spin);

		const float halfExtent = _size*0.5f;

		float umin[3];
		bx::vec3Mul(umin, udir, -halfExtent);

		float umax[3];
		bx::vec3Mul(umax, udir,  halfExtent);

		float vmin[3];
		bx::vec3Mul(vmin, vdir, -halfExtent);

		float vmax[3];
		bx::vec3Mul(vmax, vdir,  halfExtent);

		float pt[3];
		float tmp[3];
		bx::vec3Add(tmp, umin, vmin);
		bx::vec3Add(pt, _center, tmp);
		moveTo(pt);

		bx::vec3Add(tmp, umax, vmin);
		bx::vec3Add(pt, _center, tmp);
		lineTo(pt);

		bx::vec3Add(tmp, umax, vmax);
		bx::vec3Add(pt, _center, tmp);
		lineTo(pt);

		bx::vec3Add(tmp, umin, vmax);
		bx::vec3Add(pt, _center, tmp);
		lineTo(pt);

		close();
	}

	void drawQuad(SpriteHandle _handle, const float* _normal, const float* _center, float _size)
	{
		if (m_posQuad == BX_COUNTOF(m_cacheQuad) )
		{
			flushQuad();
		}

		const Attrib& attrib = m_attrib[m_stack];

		float udir[3];
		float vdir[3];

		bx::vec3TangentFrame(_normal, udir, vdir, attrib.m_spin);

		const Pack2D& pack = m_sprite.get(_handle);
		const float invTextureSize = 1.0f/SPRITE_TEXTURE_SIZE;
		const float us =  pack.m_x                  * invTextureSize;
		const float vs =  pack.m_y                  * invTextureSize;
		const float ue = (pack.m_x + pack.m_width ) * invTextureSize;
		const float ve = (pack.m_y + pack.m_height) * invTextureSize;

		const float aspectRatio = float(pack.m_width)/float(pack.m_height);
		const float halfExtentU =      aspectRatio*_size*0.5f;
		const float halfExtentV = 1.0f/aspectRatio*_size*0.5f;

		float umin[3];
		bx::vec3Mul(umin, udir, -halfExtentU);

		float umax[3];
		bx::vec3Mul(umax, udir,  halfExtentU);

		float vmin[3];
		bx::vec3Mul(vmin, vdir, -halfExtentV);

		float vmax[3];
		bx::vec3Mul(vmax, vdir,  halfExtentV);

		DebugUvVertex* vertex = &m_cacheQuad[m_posQuad];
		m_posQuad += 4;

		float pt[3];
		float tmp[3];
		bx::vec3Add(tmp, umin, vmin);
		bx::vec3Add(pt, _center, tmp);
		vertex->m_x = pt[0];
		vertex->m_y = pt[1];
		vertex->m_z = pt[2];
		vertex->m_u = us;
		vertex->m_v = vs;
		vertex->m_abgr = attrib.m_abgr;
		++vertex;

		bx::vec3Add(tmp, umax, vmin);
		bx::vec3Add(pt, _center, tmp);
		vertex->m_x = pt[0];
		vertex->m_y = pt[1];
		vertex->m_z = pt[2];
		vertex->m_u = ue;
		vertex->m_v = vs;
		vertex->m_abgr = attrib.m_abgr;
		++vertex;

		bx::vec3Add(tmp, umin, vmax);
		bx::vec3Add(pt, _center, tmp);
		vertex->m_x = pt[0];
		vertex->m_y = pt[1];
		vertex->m_z = pt[2];
		vertex->m_u = us;
		vertex->m_v = ve;
		vertex->m_abgr = attrib.m_abgr;
		++vertex;

		bx::vec3Add(tmp, umax, vmax);
		bx::vec3Add(pt, _center, tmp);
		vertex->m_x = pt[0];
		vertex->m_y = pt[1];
		vertex->m_z = pt[2];
		vertex->m_u = ue;
		vertex->m_v = ve;
		vertex->m_abgr = attrib.m_abgr;
		++vertex;
	}

	void drawQuad(bgfx::TextureHandle _handle, const float* _normal, const float* _center, float _size)
	{
		BX_UNUSED(_handle, _normal, _center, _size);
	}

	void drawCone(const float* _from, const float* _to, float _radius)
	{
		const Attrib& attrib = m_attrib[m_stack];

		float tmp0[3];
		bx::vec3Sub(tmp0, _from, _to);

		float normal[3];
		bx::vec3Norm(normal, tmp0);

		float mtx[2][16];
		bx::mtxFromNormal(mtx[0], normal, _radius, _from, attrib.m_spin);

		memcpy(mtx[1], mtx[0], 64);
		mtx[1][12] = _to[0];
		mtx[1][13] = _to[1];
		mtx[1][14] = _to[2];

		uint8_t lod = attrib.m_lod > Mesh::ConeMaxLod
					? uint8_t(Mesh::ConeMaxLod)
					: attrib.m_lod
					;
		draw(Mesh::Enum(Mesh::Cone0 + lod), mtx[0], 2, attrib.m_wireframe);
	}

	void drawCone(const void* _from, const void* _to, float _radius)
	{
		drawCone( (const float*)_from, (const float*)_to, _radius);
	}

	void drawCylinder(const float* _from, const float* _to, float _radius, bool _capsule)
	{
		const Attrib& attrib = m_attrib[m_stack];

		float tmp0[3];
		bx::vec3Sub(tmp0, _from, _to);

		float normal[3];
		bx::vec3Norm(normal, tmp0);

		float mtx[2][16];
		bx::mtxFromNormal(mtx[0], normal, _radius, _from, attrib.m_spin);

		memcpy(mtx[1], mtx[0], 64);
		mtx[1][12] = _to[0];
		mtx[1][13] = _to[1];
		mtx[1][14] = _to[2];

		if (_capsule)
		{
			uint8_t lod = attrib.m_lod > Mesh::CapsuleMaxLod
						? uint8_t(Mesh::CapsuleMaxLod)
						: attrib.m_lod
						;
			draw(Mesh::Enum(Mesh::Capsule0 + lod), mtx[0], 2, attrib.m_wireframe);

			Sphere sphere;
			bx::vec3Move(sphere.m_center, _from);
			sphere.m_radius = _radius;
			draw(sphere);

			bx::vec3Move(sphere.m_center, _to);
			draw(sphere);
		}
		else
		{
			uint8_t lod = attrib.m_lod > Mesh::CylinderMaxLod
						? uint8_t(Mesh::CylinderMaxLod)
						: attrib.m_lod
						;
			draw(Mesh::Enum(Mesh::Cylinder0 + lod), mtx[0], 2, attrib.m_wireframe);
		}
	}

	void drawCylinder(const void* _from, const void* _to, float _radius, bool _capsule)
	{
		drawCylinder( (const float*)_from, (const float*)_to, _radius, _capsule);
	}

	void drawAxis(float _x, float _y, float _z, float _len, Axis::Enum _highlight, float _thickness)
	{
		push();

		if (_thickness > 0.0f)
		{
			float from[3] = { _x, _y, _z };
			float mid[3];
			float to[3];

			setColor(Axis::X == _highlight ? 0xff00ffff : 0xff0000ff);
			mid[0] = _x + _len - _thickness;
			mid[1] = _y;
			mid[2] = _z;
			to[0] = _x + _len;
			to[1] = _y;
			to[2] = _z;
			drawCylinder(from, mid, _thickness, false);
			drawCone(mid, to, _thickness);

			setColor(Axis::Y == _highlight ? 0xff00ffff : 0xff00ff00);
			mid[0] = _x;
			mid[1] = _y + _len - _thickness;
			mid[2] = _z;
			to[0] = _x;
			to[1] = _y + _len;
			to[2] = _z;
			drawCylinder(from, mid, _thickness, false);
			drawCone(mid, to, _thickness);

			setColor(Axis::Z == _highlight ? 0xff00ffff : 0xffff0000);
			mid[0] = _x;
			mid[1] = _y;
			mid[2] = _z + _len - _thickness;
			to[0] = _x;
			to[1] = _y;
			to[2] = _z + _len;
			drawCylinder(from, mid, _thickness, false);
			drawCone(mid, to, _thickness);
		}
		else
		{
			setColor(Axis::X == _highlight ? 0xff00ffff : 0xff0000ff);
			moveTo(_x, _y, _z);
			lineTo(_x + _len, _y, _z);

			setColor(Axis::Y == _highlight ? 0xff00ffff : 0xff00ff00);
			moveTo(_x, _y, _z);
			lineTo(_x, _y + _len, _z);

			setColor(Axis::Z == _highlight ? 0xff00ffff : 0xffff0000);
			moveTo(_x, _y, _z);
			lineTo(_x, _y, _z + _len);
		}

		pop();
	}

	void drawGrid(const float* _normal, const float* _center, uint32_t _size, float _step)
	{
		const Attrib& attrib = m_attrib[m_stack];

		float udir[3];
		float vdir[3];
		bx::vec3TangentFrame(_normal, udir, vdir, attrib.m_spin);

		bx::vec3Mul(udir, udir, _step);
		bx::vec3Mul(vdir, vdir, _step);

		const uint32_t num = (_size/2)*2+1;
		const float halfExtent = float(_size/2);

		float umin[3];
		bx::vec3Mul(umin, udir, -halfExtent);

		float umax[3];
		bx::vec3Mul(umax, udir,  halfExtent);

		float vmin[3];
		bx::vec3Mul(vmin, vdir, -halfExtent);

		float vmax[3];
		bx::vec3Mul(vmax, vdir,  halfExtent);

		float tmp[3];

		float xs[3];
		float xe[3];

		bx::vec3Add(tmp, umin, vmin);
		bx::vec3Add(xs, _center, tmp);

		bx::vec3Add(tmp, umax, vmin);
		bx::vec3Add(xe, _center, tmp);

		float ys[3];
		float ye[3];

		bx::vec3Add(tmp, umin, vmin);
		bx::vec3Add(ys, _center, tmp);

		bx::vec3Add(tmp, umin, vmax);
		bx::vec3Add(ye, _center, tmp);

		for (uint32_t ii = 0; ii < num; ++ii)
		{
			moveTo(xs);
			lineTo(xe);
			bx::vec3Add(xs, xs, vdir);
			bx::vec3Add(xe, xe, vdir);

			moveTo(ys);
			lineTo(ye);
			bx::vec3Add(ys, ys, udir);
			bx::vec3Add(ye, ye, udir);
		}
	}

	void drawGrid(const void* _normal, const void* _center, uint32_t _size, float _step)
	{
		drawGrid( (const float*)_normal, (const float*)_center, _size, _step);
	}

	void drawGrid(Axis::Enum _axis, const float* _center, uint32_t _size, float _step)
	{
		push();
		setTranslate(_center);

		const uint32_t num = (_size/2)*2-1;
		const float halfExtent = float(_size/2) * _step;

		setColor(0xff606060);
		float yy = -halfExtent + _step;
		for (uint32_t ii = 0; ii < num; ++ii)
		{
			moveTo(_axis, -halfExtent, yy);
			lineTo(_axis,  halfExtent, yy);

			moveTo(_axis, yy, -halfExtent);
			lineTo(_axis, yy,  halfExtent);

			yy += _step;
		}

		setColor(0xff101010);
		moveTo(_axis, -halfExtent, -halfExtent);
		lineTo(_axis, -halfExtent,  halfExtent);
		lineTo(_axis,  halfExtent,  halfExtent);
		lineTo(_axis,  halfExtent, -halfExtent);
		close();

		moveTo(_axis, -halfExtent, 0.0f);
		lineTo(_axis,  halfExtent, 0.0f);

		moveTo(_axis, 0.0f, -halfExtent);
		lineTo(_axis, 0.0f,  halfExtent);

		pop();
	}

	void drawGrid(Axis::Enum _axis, const void* _center, uint32_t _size, float _step)
	{
		drawGrid(_axis, (const float*)_center, _size, _step);
	}

	void drawOrb(float _x, float _y, float _z, float _radius, Axis::Enum _hightlight)
	{
		push();

		setColor(Axis::X == _hightlight ? 0xff00ffff : 0xff0000ff);
		drawCircle(Axis::X, _x, _y, _z, _radius, 0.0f);

		setColor(Axis::Y == _hightlight ? 0xff00ffff : 0xff00ff00);
		drawCircle(Axis::Y, _x, _y, _z, _radius, 0.0f);

		setColor(Axis::Z == _hightlight ? 0xff00ffff : 0xffff0000);
		drawCircle(Axis::Z, _x, _y, _z, _radius, 0.0f);

		pop();
	}

private:
	struct Mesh
	{
		enum Enum
		{
			Sphere0,
			Sphere1,
			Sphere2,
			Sphere3,

			Cone0,
			Cone1,
			Cone2,
			Cone3,

			Cylinder0,
			Cylinder1,
			Cylinder2,
			Cylinder3,

			Capsule0,
			Capsule1,
			Capsule2,
			Capsule3,

			Cube,

			Count,

			SphereMaxLod   = Sphere3   - Sphere0,
			ConeMaxLod     = Cone3     - Cone0,
			CylinderMaxLod = Cylinder3 - Cylinder0,
			CapsuleMaxLod  = Capsule3  - Capsule0,
		};

		uint32_t m_startVertex;
		uint32_t m_numVertices;
		uint32_t m_startIndex[2];
		uint32_t m_numIndices[2];
	};

	struct Program
	{
		enum Enum
		{
			Lines,
			LinesStipple,
			Fill,
			FillLit,
			FillTexture,

			Count
		};
	};

	void draw(Mesh::Enum _mesh, const float* _mtx, uint16_t _num, bool _wireframe) const
	{
		const Mesh& mesh = m_mesh[_mesh];

		const Attrib& attrib = m_attrib[m_stack];

		if (0 != mesh.m_numIndices[_wireframe])
		{
			bgfx::setIndexBuffer(m_ibh
				, mesh.m_startIndex[_wireframe]
				, mesh.m_numIndices[_wireframe]
				);
		}

		const float flip = 0 == (attrib.m_state & BGFX_STATE_CULL_CCW) ? 1.0f : -1.0f;
		const uint8_t alpha = attrib.m_abgr>>24;

		float params[4][4] =
		{
			{ // lightDir
				 0.0f * flip,
				-1.0f * flip,
				 0.0f * flip,
				 3.0f, // shininess
			},
			{ // skyColor
				1.0f,
				0.9f,
				0.8f,
				0.0f, // unused
			},
			{ // groundColor.xyz0
				0.2f,
				0.22f,
				0.5f,
				0.0f, // unused
			},
			{ // matColor
				( (attrib.m_abgr    )&0xff)/255.0f,
				( (attrib.m_abgr>> 8)&0xff)/255.0f,
				( (attrib.m_abgr>>16)&0xff)/255.0f,
				(  alpha                  )/255.0f,
			},
		};

		bx::vec3Norm(params[0], params[0]);

		bgfx::setUniform(u_params, params, 4);

		bgfx::setTransform(_mtx, _num);
		bgfx::setVertexBuffer(m_vbh, mesh.m_startVertex, mesh.m_numVertices);
		bgfx::setState(0
				| attrib.m_state
				| (_wireframe ? BGFX_STATE_PT_LINES|BGFX_STATE_LINEAA|BGFX_STATE_BLEND_ALPHA
				: (alpha < 0xff) ? BGFX_STATE_BLEND_ALPHA : 0)
				);
		bgfx::submit(m_viewId, m_program[_wireframe ? Program::Fill : Program::FillLit]);
	}

	void softFlush()
	{
		if (m_pos == uint16_t(BX_COUNTOF(m_cache) ) )
		{
			flush();
		}
	}

	void flush()
	{
		if (0 != m_pos)
		{
			if (checkAvailTransientBuffers(m_pos, DebugVertex::ms_decl, m_indexPos) )
			{
				bgfx::TransientVertexBuffer tvb;
				bgfx::allocTransientVertexBuffer(&tvb, m_pos, DebugVertex::ms_decl);
				memcpy(tvb.data, m_cache, m_pos * DebugVertex::ms_decl.m_stride);

				bgfx::TransientIndexBuffer tib;
				bgfx::allocTransientIndexBuffer(&tib, m_indexPos);
				memcpy(tib.data, m_indices, m_indexPos * sizeof(uint16_t) );

				const Attrib& attrib = m_attrib[m_stack];

				bgfx::setVertexBuffer(&tvb);
				bgfx::setIndexBuffer(&tib);
				bgfx::setState(0
						| BGFX_STATE_RGB_WRITE
						| BGFX_STATE_PT_LINES
						| attrib.m_state
						| BGFX_STATE_LINEAA
						| BGFX_STATE_BLEND_ALPHA
						);
				bgfx::setTransform(m_mtx);
				bgfx::ProgramHandle program = m_program[attrib.m_stipple ? 1 : 0];
				bgfx::submit(m_viewId, program);
			}

			m_state     = State::None;
			m_pos       = 0;
			m_indexPos  = 0;
			m_vertexPos = 0;
		}
	}

	void flushQuad()
	{
		if (0 != m_posQuad)
		{
			const uint32_t numIndices = m_posQuad/4*6;
			if (checkAvailTransientBuffers(m_posQuad, DebugUvVertex::ms_decl, numIndices) )
			{
				bgfx::TransientVertexBuffer tvb;
				bgfx::allocTransientVertexBuffer(&tvb, m_posQuad, DebugUvVertex::ms_decl);
				memcpy(tvb.data, m_cacheQuad, m_posQuad * DebugUvVertex::ms_decl.m_stride);

				bgfx::TransientIndexBuffer tib;
				bgfx::allocTransientIndexBuffer(&tib, numIndices);
				uint16_t* indices = (uint16_t*)tib.data;
				for (uint16_t ii = 0, num = m_posQuad/4; ii < num; ++ii)
				{
					uint16_t startVertex = ii*4;
					indices[0] = startVertex+0;
					indices[1] = startVertex+1;
					indices[2] = startVertex+2;
					indices[3] = startVertex+1;
					indices[4] = startVertex+3;
					indices[5] = startVertex+2;
					indices += 6;
				}

				const Attrib& attrib = m_attrib[m_stack];

				bgfx::setVertexBuffer(&tvb);
				bgfx::setIndexBuffer(&tib);
				bgfx::setState(0
						| (attrib.m_state & ~BGFX_STATE_CULL_MASK)
						);
				bgfx::setTransform(m_mtx);
				bgfx::setTexture(0, s_texColor, m_texture);
				bgfx::submit(m_viewId, m_program[Program::FillTexture]);
			}

			m_posQuad = 0;
		}
	}

	struct State
	{
		enum Enum
		{
			None,
			MoveTo,
			LineTo,

			Count
		};
	};

	static const uint32_t cacheSize = 1024;
	static const uint32_t stackSize = 16;
	BX_STATIC_ASSERT(cacheSize >= 3, "Cache must be at least 3 elements.");
	DebugVertex m_cache[cacheSize+1];
	uint16_t m_indices[cacheSize*2];
	uint16_t m_pos;
	uint16_t m_indexPos;
	uint16_t m_vertexPos;

	static const uint32_t cacheQuadSize = 1024;
	DebugUvVertex m_cacheQuad[cacheQuadSize];
	uint16_t m_posQuad;

	uint32_t m_mtx;
	uint8_t  m_viewId;
	uint8_t  m_stack;
	bool     m_depthTestLess;

	struct Attrib
	{
		uint64_t m_state;
		float    m_offset;
		float    m_scale;
		float    m_spin;
		uint32_t m_abgr;
		bool     m_stipple;
		bool     m_wireframe;
		uint8_t  m_lod;
	};

	Attrib m_attrib[stackSize];

	State::Enum m_state;

	Mesh m_mesh[Mesh::Count];

	typedef SpriteT<256, SPRITE_TEXTURE_SIZE> Sprite;
	Sprite m_sprite;

	bgfx::UniformHandle s_texColor;
	bgfx::TextureHandle m_texture;
	bgfx::ProgramHandle m_program[Program::Count];
	bgfx::UniformHandle u_params;

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle  m_ibh;

	bx::AllocatorI* m_allocator;
};

static DebugDraw s_dd;

void ddInit(bool _depthTestLess, bx::AllocatorI* _allocator)
{
	s_dd.init(_depthTestLess, _allocator);
}

void ddShutdown()
{
	s_dd.shutdown();
}

SpriteHandle ddCreateSprite(uint16_t _width, uint16_t _height, const void* _data)
{
	return s_dd.createSprite(_width, _height, _data);
}

void ddDestroy(SpriteHandle _handle)
{
	s_dd.destroy(_handle);
}

void ddBegin(uint8_t _viewId)
{
	s_dd.begin(_viewId);
}

void ddEnd()
{
	s_dd.end();
}

void ddPush()
{
	s_dd.push();
}

void ddPop()
{
	s_dd.pop();
}

void ddSetState(bool _depthTest, bool _depthWrite, bool _clockwise)
{
	s_dd.setState(_depthTest, _depthWrite, _clockwise);
}

void ddSetColor(uint32_t _abgr)
{
	s_dd.setColor(_abgr);
}

void ddSetLod(uint8_t _lod)
{
	s_dd.setLod(_lod);
}

void ddSetWireframe(bool _wireframe)
{
	s_dd.setWireframe(_wireframe);
}

void ddSetStipple(bool _stipple, float _scale, float _offset)
{
	s_dd.setStipple(_stipple, _scale, _offset);
}

void ddSetSpin(float _spin)
{
	s_dd.setSpin(_spin);
}

void ddSetTransform(const void* _mtx)
{
	s_dd.setTransform(_mtx);
}

void ddSetTranslate(float _x, float _y, float _z)
{
	s_dd.setTranslate(_x, _y, _z);
}

void ddMoveTo(float _x, float _y, float _z)
{
	s_dd.moveTo(_x, _y, _z);
}

void ddMoveTo(const void* _pos)
{
	s_dd.moveTo(_pos);
}

void ddLineTo(float _x, float _y, float _z)
{
	s_dd.lineTo(_x, _y, _z);
}

void ddLineTo(const void* _pos)
{
	s_dd.lineTo(_pos);
}

void ddClose()
{
	s_dd.close();
}

void ddDraw(const Aabb& _aabb)
{
	s_dd.draw(_aabb);
}

void ddDraw(const Cylinder& _cylinder, bool _capsule)
{
	s_dd.draw(_cylinder, _capsule);
}

void ddDraw(const Disk& _disk)
{
	s_dd.draw(_disk);
}

void ddDraw(const Obb& _obb)
{
	s_dd.draw(_obb);
}

void ddDraw(const Sphere& _sphere)
{
	s_dd.draw(_sphere);
}

void ddDrawFrustum(const void* _viewProj)
{
	s_dd.drawFrustum(_viewProj);
}

void ddDrawArc(Axis::Enum _axis, float _x, float _y, float _z, float _radius, float _degrees)
{
	s_dd.drawArc(_axis, _x, _y, _z, _radius, _degrees);
}

void ddDrawCircle(const void* _normal, const void* _center, float _radius, float _weight)
{
	s_dd.drawCircle(_normal, _center, _radius, _weight);
}

void ddDrawCircle(Axis::Enum _axis, float _x, float _y, float _z, float _radius, float _weight)
{
	s_dd.drawCircle(_axis, _x, _y, _z, _radius, _weight);
}

void ddDrawQuad(const float* _normal, const float* _center, float _size)
{
	s_dd.drawQuad(_normal, _center, _size);
}

void ddDrawQuad(SpriteHandle _handle, const float* _normal, const float* _center, float _size)
{
	s_dd.drawQuad(_handle, _normal, _center, _size);
}

void ddDrawQuad(bgfx::TextureHandle _handle, const float* _normal, const float* _center, float _size)
{
	s_dd.drawQuad(_handle, _normal, _center, _size);
}

void ddDrawCone(const void* _from, const void* _to, float _radius)
{
	s_dd.drawCone(_from, _to, _radius);
}

void ddDrawCylinder(const void* _from, const void* _to, float _radius, bool _capsule)
{
	if (_capsule)
	{
		s_dd.push();
		s_dd.setLod(0);
		s_dd.drawCylinder(_from, _to, _radius, true);
		s_dd.pop();
	}
	else
	{
		s_dd.drawCylinder(_from, _to, _radius, false);
	}
}

void ddDrawCapsule(const void* _from, const void* _to, float _radius)
{
	s_dd.drawCylinder(_from, _to, _radius, true);
}

void ddDrawAxis(float _x, float _y, float _z, float _len, Axis::Enum _hightlight, float _thickness)
{
	s_dd.drawAxis(_x, _y, _z, _len, _hightlight, _thickness);
}

void ddDrawGrid(const void* _normal, const void* _center, uint32_t _size, float _step)
{
	s_dd.drawGrid(_normal, _center, _size, _step);
}

void ddDrawGrid(Axis::Enum _axis, const void* _center, uint32_t _size, float _step)
{
	s_dd.drawGrid(_axis, _center, _size, _step);
}

void ddDrawOrb(float _x, float _y, float _z, float _radius, Axis::Enum _hightlight)
{
	s_dd.drawOrb(_x, _y, _z, _radius, _hightlight);
}
