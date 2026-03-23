/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

// GPU font rendering using the Slug algorithm.
// 
// Slug reference shaders by Eric Lengyel (MIT License).
// https://github.com/EricLengyel/Slug?tab=readme-ov-file#slug
//
// For more information see:
// https://sluglibrary.com/

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"
#include "font/utf8.h"

#include <bx/math.h>
#include <bx/easing.h>
#include <bx/sort.h>
#include <bx/string.h>

#include <tinystl/unordered_map.h>
#include <tinystl/vector.h>
namespace stl = tinystl;

#include <stb/stb_truetype.h>

namespace
{

static constexpr uint16_t kTexWidth = 4096;
static constexpr uint8_t  kMaxBands = 8;

struct Curve
{
	float p1x, p1y;
	float p2x, p2y;
	float p3x, p3y;
};

struct Rect
{
	float minX;
	float minY;
	float maxX;
	float maxY;
};

struct SlugGlyph
{
	int32_t  glyphIndex;
	int32_t  advance;
	int32_t  bearingX;
	int32_t  bearingY;
	int32_t  width;
	int32_t  height;

	Rect     rect;

	int32_t  curveStart;
	int32_t  curveCount;

	uint16_t glyphLocX;
	uint16_t glyphLocY;
	uint8_t  bandMaxX;
	uint8_t  bandMaxY;

	float    bandScaleX;
	float    bandScaleY;
	float    bandOffsetX;
	float    bandOffsetY;
};

struct FontVertex
{
	float m_x;           // pos.xy = object-space vertex coordinates.
	float m_y;           //
	float m_nx;          // pos.zw = object-space normal vector.
	float m_ny;          //

	float m_u;           // tex.xy = em-space sample coordinates.
	float m_v;           //
	float m_glyphLoc;    // tex.z = location of glyph data in band texture / Bit-packed: (glyphLocY << 16) | glyphLocX, reinterpreted as float.
	float m_bandMax;     // tex.w = max band indexes and flags             / Bit-packed: (bandMaxY  << 16) | bandMaxX,  reinterpreted as float.

	float m_bandScaleX;  // banding
	float m_bandScaleY;
	float m_bandOffsetX;
	float m_bandOffsetY;

	static void init()
	{
		ms_layout.begin()
			.add(bgfx::Attrib::Position,  4, bgfx::AttribType::Float) // pos.xy = object-space vertex coordinates.
			                                                          // pos.zw = object-space normal vector.
			.add(bgfx::Attrib::TexCoord0, 4, bgfx::AttribType::Float) // tex.xy = em-space sample coordinates.
			                                                          // tex.z = location of glyph data in band texture (interpreted as integer):
			                                                          // tex.w = max band indexes and flags (interpreted as integer): 
			.add(bgfx::Attrib::TexCoord1, 4, bgfx::AttribType::Float) // banding
			.end();
	}

	static bgfx::VertexLayout ms_layout;
};

bgfx::VertexLayout FontVertex::ms_layout;

class SlugFont
{
public:
	float worldSize;

	SlugFont(const uint8_t* _fontData, float _worldSize)
		: worldSize(_worldSize)
		, m_curveTex(BGFX_INVALID_HANDLE)
		, m_bandTex(BGFX_INVALID_HANDLE)
		, m_vbh(BGFX_INVALID_HANDLE)
		, m_ibh(BGFX_INVALID_HANDLE)
	{
		if (!stbtt_InitFont(&m_fontInfo, _fontData, stbtt_GetFontOffsetForIndex(_fontData, 0) ) )
		{
			return;
		}

		float scale1px = stbtt_ScaleForMappingEmToPixels(&m_fontInfo, 1.0f);
		m_emSize = 1.0f / scale1px;
	
		buildGlyph(0, 0); // Undefined glyph at index 0.

		for (uint32_t codePoint = 32; codePoint < 128; ++codePoint)
		{
			const int32_t glyphIdx = stbtt_FindGlyphIndex(&m_fontInfo, codePoint);

			if (0 != glyphIdx)
			{
				buildGlyph(codePoint, glyphIdx);
			}

		}

		uploadTextures();
	}

	~SlugFont()
	{
		if (bgfx::isValid(m_curveTex) )
		{
			bgfx::destroy(m_curveTex);
			m_curveTex = BGFX_INVALID_HANDLE;
		}

		if (bgfx::isValid(m_bandTex) )
		{
			bgfx::destroy(m_bandTex);
			m_bandTex = BGFX_INVALID_HANDLE;
		}

		destroyMesh();
	}

	void destroyMesh()
	{
		if (bgfx::isValid(m_vbh) )
		{
			bgfx::destroy(m_vbh);
			m_vbh = BGFX_INVALID_HANDLE;
		}

		if (bgfx::isValid(m_ibh) )
		{
			bgfx::destroy(m_ibh);
			m_ibh = BGFX_INVALID_HANDLE;
		}
	}

	void prepareGlyphsForText(const bx::StringView& _text)
	{
		bool changed = false;

		uint32_t state = 0;

		for (const char* textIt = _text.getPtr(); textIt != _text.getTerm(); ++textIt)
		{
			uint32_t codePoint;
			if (0 != utf8_decode(&state, &codePoint, *textIt) )
			{
				continue;
			}

			if ('\r' == codePoint
			||  '\n' == codePoint)
			{
				continue;
			}

			if (m_glyphs.find(codePoint) != m_glyphs.end() )
			{
				continue;
			}

			const int32_t glyphIdx = stbtt_FindGlyphIndex(&m_fontInfo, codePoint);
			if (0 != glyphIdx)
			{
				buildGlyph(codePoint, glyphIdx);
				changed = true;
			}
		}

		BX_ASSERT(state == UTF8_ACCEPT, "The string is not well-formed");

		if (changed)
		{
			uploadTextures();
		}
	}

	void buildMesh(float _x, float _y, const bx::StringView& _text)
	{
		destroyMesh();

		float originalX = _x;

		stl::vector<FontVertex> vertices;
		stl::vector<uint32_t>   indices;

		uint32_t state = 0;

		int32_t previous = 0;
		for (const char* textIt = _text.getPtr(); textIt != _text.getTerm(); ++textIt)
		{
			uint32_t codePoint;
			if (0 != utf8_decode(&state, &codePoint, *textIt) )
			{
				continue;
			}

			if ('\r' == codePoint)
			{
				continue;
			}

			if ('\n' == codePoint)
			{
				_x = originalX;
				int32_t ascent, descent, lineGap;
				stbtt_GetFontVMetrics(&m_fontInfo, &ascent, &descent, &lineGap);
				float lineHeight = (float)(ascent - descent + lineGap) / m_emSize * worldSize;
				_y -= lineHeight;
				continue;
			}

			auto glyphIt = m_glyphs.find(codePoint);
			SlugGlyph& glyph = (glyphIt == m_glyphs.end() ) ? m_glyphs[0] : glyphIt->second;

			if (previous != 0 && glyph.glyphIndex != 0)
			{
				int32_t kern = stbtt_GetGlyphKernAdvance(&m_fontInfo, previous, glyph.glyphIndex);
				_x += (float)kern / m_emSize * worldSize;
			}

			if (glyph.curveCount > 0)
			{
				const float u0 = glyph.rect.minX;
				const float v0 = glyph.rect.minY;
				const float u1 = glyph.rect.maxX;
				const float v1 = glyph.rect.maxY;

				const float x0 = _x + u0 * worldSize;
				const float y0 = _y + v0 * worldSize;
				const float x1 = _x + u1 * worldSize;
				const float y1 = _y + v1 * worldSize;

				static constexpr float kN = 1.0f;

				uint32_t base = (uint32_t)vertices.size();

				FontVertex vert;
				vert.m_bandScaleX  = glyph.bandScaleX;
				vert.m_bandScaleY  = glyph.bandScaleY;
				vert.m_bandOffsetX = glyph.bandOffsetX;
				vert.m_bandOffsetY = glyph.bandOffsetY;
				{
					uint32_t loc = (uint32_t(glyph.glyphLocY) << 16) | uint32_t(glyph.glyphLocX);
					uint32_t bm  = (uint32_t(glyph.bandMaxY)  << 16) | uint32_t(glyph.bandMaxX);
					bx::memCopy(&vert.m_glyphLoc, &loc, sizeof(float));
					bx::memCopy(&vert.m_bandMax,  &bm,  sizeof(float));
				}

				vert.m_x  =  x0;
				vert.m_y  =  y0;
				vert.m_u  =  u0;
				vert.m_v  =  v0;
				vert.m_nx = -kN;
				vert.m_ny = -kN;
				vertices.push_back(vert);

				vert.m_x  =  x1;
				vert.m_y  =  y0;
				vert.m_u  =  u1;
				vert.m_v  =  v0;
				vert.m_nx = +kN;
				vert.m_ny = -kN;
				vertices.push_back(vert);

				vert.m_x  =  x1;
				vert.m_y  =  y1;
				vert.m_u  =  u1;
				vert.m_v  =  v1;
				vert.m_nx = +kN;
				vert.m_ny = +kN;
				vertices.push_back(vert);

				vert.m_x  =  x0;
				vert.m_y  =  y1;
				vert.m_u  =  u0;
				vert.m_v  =  v1;
				vert.m_nx = -kN;
				vert.m_ny = +kN;
				vertices.push_back(vert);

				indices.push_back(base + 0);
				indices.push_back(base + 1);
				indices.push_back(base + 2);
				indices.push_back(base + 2);
				indices.push_back(base + 3);
				indices.push_back(base + 0);
			}

			_x += float(glyph.advance) / m_emSize * worldSize;
			previous = glyph.glyphIndex;
		}

		BX_ASSERT(state == UTF8_ACCEPT, "The string is not well-formed");

		if (!indices.empty() )
		{
			const bgfx::Memory* vmem = bgfx::alloc( (uint32_t)(vertices.size() * sizeof(FontVertex)) );
			bx::memCopy(vmem->data, vertices.data(), vmem->size);

			const bgfx::Memory* imem = bgfx::alloc( (uint32_t)(indices.size() * sizeof(uint32_t)) );
			bx::memCopy(imem->data, indices.data(), imem->size);

			m_vbh = bgfx::createVertexBuffer(vmem, FontVertex::ms_layout);
			m_ibh = bgfx::createIndexBuffer(imem, BGFX_BUFFER_INDEX32);
		}
	}

	void submit(
		  bgfx::ViewId _view
		, bgfx::ProgramHandle _program
		, bgfx::UniformHandle _curveSampler
		, bgfx::UniformHandle _bandSampler
		, bgfx::UniformHandle _paramsUniform
		)
	{
		const float params[] =
		{
			bx::bitCast<float>(0xffffffff),
			bx::bitCast<float>(0x303030ff),
			worldSize,
			1.0f / worldSize,
		};

		bgfx::setVertexBuffer(0, m_vbh);
		bgfx::setIndexBuffer(m_ibh);

		bgfx::setTexture(0, _curveSampler, m_curveTex);
		bgfx::setTexture(1, _bandSampler,  m_bandTex);

		bgfx::setUniform(_paramsUniform, params);

		bgfx::setState(0
			| BGFX_STATE_WRITE_RGB
			| BGFX_STATE_WRITE_A
			| BGFX_STATE_DEPTH_TEST_ALWAYS
			| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA)
			);

		bgfx::submit(_view, _program);
	}

	Rect measure(float _x, float _y, const bx::StringView& _text)
	{
		Rect bb;
		bb.minX = bx::max<float>();
		bb.minY = bx::max<float>();
		bb.maxX = bx::min<float>();
		bb.maxY = bx::min<float>();

		float originalX = _x;

		uint32_t state = 0;
		int32_t previous = 0;
		for (const char* textIt = _text.getPtr(); textIt != _text.getTerm(); ++textIt)
		{
			uint32_t codePoint;
			if (0 != utf8_decode(&state, &codePoint, *textIt) )
			{
				continue;
			}

			if (codePoint == '\r')
			{
				continue;
			}

			if (codePoint == '\n')
			{
				_x = originalX;
				int32_t ascent, descent, lineGap;
				stbtt_GetFontVMetrics(&m_fontInfo, &ascent, &descent, &lineGap);
				const float lineHeight = float(ascent - descent + lineGap) / m_emSize * worldSize;
				_y -= lineHeight;
				continue;
			}

			auto glyphIt = m_glyphs.find(codePoint);
			SlugGlyph& glyph = (glyphIt == m_glyphs.end() ) ? m_glyphs[0] : glyphIt->second;

			if (0 != previous
			&&  0 != glyph.glyphIndex)
			{
				const int32_t kern = stbtt_GetGlyphKernAdvance(&m_fontInfo, previous, glyph.glyphIndex);
				_x += float(kern) / m_emSize * worldSize;
			}

			const float x0 = _x + glyph.rect.minX * worldSize;
			const float y0 = _y + glyph.rect.minY * worldSize;
			const float x1 = _x + glyph.rect.maxX * worldSize;
			const float y1 = _y + glyph.rect.maxY * worldSize;

			bb.minX = bx::min(bb.minX, x0);
			bb.minY = bx::min(bb.minY, y0);
			bb.maxX = bx::max(bb.maxX, x1);
			bb.maxY = bx::max(bb.maxY, y1);

			_x += (float)glyph.advance / m_emSize * worldSize;
			previous = glyph.glyphIndex;
		}

		return bb;
	}

private:
	void buildGlyph(uint32_t _charcode, int32_t _glyphIndex)
	{
		SlugGlyph glyph;
		glyph.glyphIndex = _glyphIndex;
		glyph.curveStart = (int32_t)m_curves.size();

		stbtt_vertex* stbVerts = NULL;
		int32_t numVerts = stbtt_GetGlyphShape(&m_fontInfo, _glyphIndex, &stbVerts);

		if (0 < numVerts)
		{
			convertOutline(stbVerts, numVerts);
			stbtt_FreeShape(&m_fontInfo, stbVerts);
		}

		glyph.curveCount = int32_t(m_curves.size() ) - glyph.curveStart;

		int32_t advanceWidth, leftSideBearing;
		stbtt_GetGlyphHMetrics(&m_fontInfo, _glyphIndex, &advanceWidth, &leftSideBearing);
		glyph.advance = advanceWidth;

		int32_t x0, y0, x1, y1;
		if (!stbtt_GetGlyphBox(&m_fontInfo, _glyphIndex, &x0, &y0, &x1, &y1) )
		{
			x0 = y0 = x1 = y1 = 0;
		}

		glyph.bearingX = x0;
		glyph.bearingY = y1;
		glyph.width    = x1 - x0;
		glyph.height   = y1 - y0;

		glyph.rect.minX = float(x0 / m_emSize);
		glyph.rect.minY = float(y0 / m_emSize);
		glyph.rect.maxX = float(x1 / m_emSize);
		glyph.rect.maxY = float(y1 / m_emSize);

		glyph.glyphLocX   = 0;
		glyph.glyphLocY   = 0;
		glyph.bandMaxX    = 0;
		glyph.bandMaxY    = 0;
		glyph.bandScaleX  = 0.0f;
		glyph.bandScaleY  = 0.0f;
		glyph.bandOffsetX = 0.0f;
		glyph.bandOffsetY = 0.0f;

		m_glyphs[_charcode] = glyph;
	}

	void convertOutline(const stbtt_vertex* _vertices, int32_t _numVertices)
	{
		const float emSize = m_emSize;

		float cx = 0.0f, cy = 0.0f;

		for (int32_t ii = 0; ii < _numVertices; ++ii)
		{
			const stbtt_vertex& v = _vertices[ii];

			switch (v.type)
			{
			case STBTT_vmove:
				cx = float(v.x)/emSize;
				cy = float(v.y)/emSize;
				break;

			case STBTT_vline:
				{
					Curve c;
					c.p1x = cx;
					c.p1y = cy;
					c.p3x = float(v.x)/emSize;
					c.p3y = float(v.y)/emSize;
					c.p2x = 0.5f * (c.p1x + c.p3x);
					c.p2y = 0.5f * (c.p1y + c.p3y);
					m_curves.push_back(c);

					cx = c.p3x;
					cy = c.p3y;
				}
				break;

			case STBTT_vcurve:
				{
					Curve c;
					c.p1x = cx;
					c.p1y = cy;
					c.p2x = float(v.cx)/emSize;
					c.p2y = float(v.cy)/emSize;
					c.p3x = float(v.x )/emSize;
					c.p3y = float(v.y )/emSize;
					m_curves.push_back(c);

					cx = c.p3x;
					cy = c.p3y;
				}
				break;

			case STBTT_vcubic:
				{
					const float b1x = float(v.cx )/emSize;
					const float b1y = float(v.cy )/emSize;
					const float b2x = float(v.cx1)/emSize;
					const float b2y = float(v.cy1)/emSize;
					const float b3x = float(v.x  )/emSize;
					const float b3y = float(v.y  )/emSize;

					const float c0x = cx  + (b1x - cx ) * 0.75f;
					const float c0y = cy  + (b1y - cy ) * 0.75f;
					const float c1x = b3x + (b2x - b3x) * 0.75f;
					const float c1y = b3y + (b2y - b3y) * 0.75f;
					const float dx  = 0.5f * (c0x + c1x);
					const float dy  = 0.5f * (c0y + c1y);

					Curve q1;
					q1.p1x = cx;  q1.p1y = cy;
					q1.p2x = c0x; q1.p2y = c0y;
					q1.p3x = dx;  q1.p3y = dy;
					m_curves.push_back(q1);

					Curve q2;
					q2.p1x = dx;  q2.p1y = dy;
					q2.p2x = c1x; q2.p2y = c1y;
					q2.p3x = b3x; q2.p3y = b3y;
					m_curves.push_back(q2);

					cx = b3x;
					cy = b3y;
				}
				break;
			}
		}
	}

	struct CurveRef
	{
		int32_t index;
		float   sortKey;
	};

	static int32_t compareCurveRefDescending(const void* _lhs, const void* _rhs)
	{
		const float lk = static_cast<const CurveRef*>(_lhs)->sortKey;
		const float rk = static_cast<const CurveRef*>(_rhs)->sortKey;
		return (lk > rk) ? -1 : (lk < rk) ? 1 : 0;
	}

	static void collectHBand(
		  const stl::vector<Curve>& _curves
		, int32_t _start
		, int32_t _count
		, float _bandMinY
		, float _bandMaxY
		, stl::vector<int32_t>& _outResult
		)
	{
		stl::vector<CurveRef> refs;

		for (int32_t ii = 0; ii < _count; ++ii)
		{
			const Curve& curve = _curves[_start + ii];
			const float  cMinY = bx::min(curve.p1y, curve.p2y, curve.p3y);
			const float  cMaxY = bx::max(curve.p1y, curve.p2y, curve.p3y);

			if (cMaxY >= _bandMinY
			&&  cMinY <= _bandMaxY)
			{
				CurveRef ref = { _start + ii, bx::max(curve.p1x, curve.p2x, curve.p3x) };
				refs.push_back(ref);
			}
		}

		if (!refs.empty() )
		{
			bx::quickSort(refs.data(), (uint32_t)refs.size(), compareCurveRefDescending);
		}

		for (const CurveRef& ref : refs)
		{
			_outResult.push_back(ref.index);
		}
	}

	static void collectVBand(
		  const stl::vector<Curve>& _curves
		, int32_t _start
		, int32_t _count
		, float _bandMinX
		, float _bandMaxX
		, stl::vector<int32_t>& _outResult
		)
	{
		stl::vector<CurveRef> refs;

		for (int32_t ii = 0; ii < _count; ++ii)
		{
			const Curve& curve = _curves[_start + ii];
			const float  cMinX = bx::min(curve.p1x, curve.p2x, curve.p3x);
			const float  cMaxX = bx::max(curve.p1x, curve.p2x, curve.p3x);

			if (cMaxX >= _bandMinX
			&&  cMinX <= _bandMaxX)
			{
				CurveRef ref = { _start + ii, bx::max(curve.p1y, curve.p2y, curve.p3y) };
				refs.push_back(ref);
			}
		}

		if (!refs.empty() )
		{
			bx::quickSort(refs.data(), (uint32_t)refs.size(), compareCurveRefDescending);
		}

		for (const CurveRef& ref : refs)
		{
			_outResult.push_back(ref.index);
		}
	}

	void uploadTextures()
	{
		uint32_t numCurves = (uint32_t)m_curves.size();

		stl::vector<uint32_t> curveTexelIndex(numCurves);
		uint32_t curveTexels = 0;

		for (uint32_t ii = 0; ii < numCurves; ++ii)
		{
			const uint32_t row0 = curveTexels / kTexWidth;
			const uint32_t row1 = (curveTexels + 1) / kTexWidth;

			if (row0 != row1)
			{
				curveTexels = row1 * kTexWidth;
			}

			curveTexelIndex[ii] = curveTexels;
			curveTexels += 2;
		}

		uint16_t curveTexH = (uint16_t)( (curveTexels + kTexWidth - 1) / kTexWidth);
		curveTexH = bx::max<uint16_t>(1, curveTexH);

		struct BandEntry
		{
			uint32_t count;
			uint32_t offset;
		};

		struct GlyphBandData
		{
			BandEntry hbands[kMaxBands];
			BandEntry vbands[kMaxBands];
			uint8_t   numHBands;
			uint8_t   numVBands;
			stl::vector<uint32_t>  curveLocList;
		};

		stl::vector<GlyphBandData> allGlyphBands;
		allGlyphBands.reserve(m_glyphs.size() );

		uint32_t bandTexRow = 0;

		for (auto& kv : m_glyphs)
		{
			SlugGlyph& glyph = kv.second;

			GlyphBandData gbd;

			if (glyph.curveCount == 0)
			{
				glyph.glyphLocX   = 0;
				glyph.glyphLocY   = uint16_t(bandTexRow);
				glyph.bandMaxX    = 0;
				glyph.bandMaxY    = 0;
				glyph.bandScaleX  = 0.0f;
				glyph.bandScaleY  = 0.0f;
				glyph.bandOffsetX = 0.0f;
				glyph.bandOffsetY = 0.0f;

				gbd.hbands[0] = {0, 0};
				gbd.vbands[0] = {0, 0};
				gbd.numHBands = 1;
				gbd.numVBands = 1;
				allGlyphBands.push_back(gbd);

				bandTexRow++;
				continue;
			}

			float bbW = glyph.rect.maxX - glyph.rect.minX;
			float bbH = glyph.rect.maxY - glyph.rect.minY;

			const uint8_t numHBands = bx::clamp(uint8_t(glyph.curveCount / 2), 1, kMaxBands);
			const uint8_t numVBands = bx::clamp(uint8_t(glyph.curveCount / 2), 1, kMaxBands);

			glyph.bandMaxX = numVBands - 1;
			glyph.bandMaxY = numHBands - 1;

			if (bbH > 0.0f)
			{
				glyph.bandScaleY  = float(numHBands) / bbH;
				glyph.bandOffsetY = -glyph.rect.minY * glyph.bandScaleY;
			}
			else
			{
				glyph.bandScaleY  = 0.0f;
				glyph.bandOffsetY = 0.0f;
			}

			if (bbW > 0.0f)
			{
				glyph.bandScaleX  = float(numVBands) / bbW;
				glyph.bandOffsetX = -glyph.rect.minX * glyph.bandScaleX;
			}
			else
			{
				glyph.bandScaleX  = 0.0f;
				glyph.bandOffsetX = 0.0f;
			}

			glyph.glyphLocX = 0;
			glyph.glyphLocY = uint16_t(bandTexRow);

			gbd.numHBands = numHBands;

			const float bandH = bbH / (float)numHBands;

			for (int32_t bb = 0; bb < numHBands; ++bb)
			{
				const float bMinY = glyph.rect.minY + float(bb    ) * bandH;
				const float bMaxY = glyph.rect.minY + float(bb + 1) * bandH;

				stl::vector<int32_t> curvesInBand;
				collectHBand(m_curves, glyph.curveStart, glyph.curveCount, bMinY, bMaxY, curvesInBand);

				gbd.hbands[bb].count  = (uint32_t)curvesInBand.size();
				gbd.hbands[bb].offset = (uint32_t)gbd.curveLocList.size();

				for (int32_t ci : curvesInBand)
				{
					uint32_t texIdx = curveTexelIndex[ci];
					gbd.curveLocList.push_back(texIdx % kTexWidth);
					gbd.curveLocList.push_back(texIdx / kTexWidth);
				}
			}

			gbd.numVBands = numVBands;

			const float bandW = bbW / (float)numVBands;

			for (int32_t bb = 0; bb < numVBands; ++bb)
			{
				const float bMinX = glyph.rect.minX + float(bb    ) * bandW;
				const float bMaxX = glyph.rect.minX + float(bb + 1) * bandW;

				stl::vector<int32_t> curvesInBand;
				collectVBand(m_curves, glyph.curveStart, glyph.curveCount, bMinX, bMaxX, curvesInBand);

				gbd.vbands[bb].count  = (uint32_t)curvesInBand.size();
				gbd.vbands[bb].offset = (uint32_t)gbd.curveLocList.size();

				for (int32_t ci : curvesInBand)
				{
					uint32_t texIdx = curveTexelIndex[ci];
					gbd.curveLocList.push_back(texIdx % kTexWidth);
					gbd.curveLocList.push_back(texIdx / kTexWidth);
				}
			}

			allGlyphBands.push_back(gbd);
			bandTexRow++;
		}

		{
			uint32_t glyphIdx = 0;
			for (auto& kv : m_glyphs)
			{
				BX_UNUSED(kv);
				GlyphBandData& gbd = allGlyphBands[glyphIdx];

				const int32_t  numHBands  = gbd.numHBands;
				const int32_t  numVBands  = gbd.numVBands;
				const uint32_t headerSize = uint32_t(numHBands + numVBands);

				for (int32_t bb = 0; bb < numHBands; ++bb)
				{
					gbd.hbands[bb].offset = headerSize + gbd.hbands[bb].offset / 2;
				}

				for (int32_t bb = 0; bb < numVBands; ++bb)
				{
					gbd.vbands[bb].offset = headerSize + gbd.vbands[bb].offset / 2;
				}

				glyphIdx++;
			}
		}

		{
			if (bgfx::isValid(m_curveTex) )
			{
				bgfx::destroy(m_curveTex);
			}

			const bgfx::Memory* mem = bgfx::alloc(kTexWidth * curveTexH * 4 * sizeof(float) );
			bx::memSet(mem->data, 0, mem->size);
			float* dst = (float*)mem->data;

			for (uint32_t ii = 0; ii < numCurves; ++ii)
			{
				const Curve& curve = m_curves[ii];
				const uint32_t texIdx = curveTexelIndex[ii];

				uint32_t off0 = texIdx * 4;
				dst[off0 + 0] = curve.p1x;
				dst[off0 + 1] = curve.p1y;
				dst[off0 + 2] = curve.p2x;
				dst[off0 + 3] = curve.p2y;

				uint32_t off1 = (texIdx + 1) * 4;
				dst[off1 + 0] = curve.p3x;
				dst[off1 + 1] = curve.p3y;
				dst[off1 + 2] = 0.0f;
				dst[off1 + 3] = 0.0f;
			}

			m_curveTex = bgfx::createTexture2D(
				  kTexWidth
				, curveTexH
				, false
				, 1
				, bgfx::TextureFormat::RGBA32F
				, BGFX_SAMPLER_POINT | BGFX_SAMPLER_UVW_CLAMP
				, mem
				);
		}

		{
			if (bgfx::isValid(m_bandTex) )
			{
				bgfx::destroy(m_bandTex);
			}

			uint16_t bandTexH = uint16_t(bandTexRow);

			const bgfx::Memory* mem = bgfx::alloc(kTexWidth * bandTexH * 4 * sizeof(float) );
			bx::memSet(mem->data, 0, mem->size);
			float* dst = (float*)mem->data;

			uint32_t glyphIdx = 0;
			for (auto& kv : m_glyphs)
			{
				SlugGlyph&   glyph = kv.second;
				GlyphBandData& gbd = allGlyphBands[glyphIdx];

				uint32_t rowBase = (uint32_t)glyph.glyphLocY * kTexWidth;

				const int32_t numHBands = gbd.numHBands;
				const int32_t numVBands = gbd.numVBands;

				for (int32_t bb = 0; bb < numHBands; ++bb)
				{
					uint32_t col = (uint32_t)(glyph.glyphLocX + bb);
					uint32_t off = (rowBase + col) * 4;
					dst[off + 0] = (float)gbd.hbands[bb].count;
					dst[off + 1] = (float)gbd.hbands[bb].offset;
					dst[off + 2] = 0.0f;
					dst[off + 3] = 0.0f;
				}

				for (int32_t bb = 0; bb < numVBands; ++bb)
				{
					uint32_t col = (uint32_t)(glyph.glyphLocX + numHBands + bb);
					uint32_t off = (rowBase + col) * 4;
					dst[off + 0] = (float)gbd.vbands[bb].count;
					dst[off + 1] = (float)gbd.vbands[bb].offset;
					dst[off + 2] = 0.0f;
					dst[off + 3] = 0.0f;
				}

				const uint32_t headerSize = (uint32_t)(numHBands + numVBands);
				const uint32_t numLocPairs = (uint32_t)(gbd.curveLocList.size() / 2);

				for (uint32_t ll = 0; ll < numLocPairs; ++ll)
				{
					uint32_t col = glyph.glyphLocX + headerSize + ll;
					uint32_t off = (rowBase + col) * 4;
					dst[off + 0] = (float)gbd.curveLocList[ll * 2 + 0];
					dst[off + 1] = (float)gbd.curveLocList[ll * 2 + 1];
					dst[off + 2] = 0.0f;
					dst[off + 3] = 0.0f;
				}

				glyphIdx++;
			}

			m_bandTex = bgfx::createTexture2D(
				  kTexWidth
				, bandTexH
				, false
				, 1
				, bgfx::TextureFormat::RGBA32F
				, BGFX_SAMPLER_POINT | BGFX_SAMPLER_UVW_CLAMP
				, mem
				);
		}
	}

	stbtt_fontinfo m_fontInfo;
	float m_emSize;

	stl::vector<Curve> m_curves;
	stl::unordered_map<uint32_t, SlugGlyph> m_glyphs;

	bgfx::TextureHandle m_curveTex;
	bgfx::TextureHandle m_bandTex;

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle  m_ibh;
};

class ExampleGpuFont : public entry::AppI
{
public:
	ExampleGpuFont(const char* _name, const char* _description, const char* _url)
		: entry::AppI(_name, _description, _url)
		, m_fontData(NULL)
		, m_mainFont(NULL)
		, m_fontProgram(BGFX_INVALID_HANDLE)
		, m_curveSampler(BGFX_INVALID_HANDLE)
		, m_bandSampler(BGFX_INVALID_HANDLE)
		, m_paramsUniform(BGFX_INVALID_HANDLE)
		, m_animate(true)
		, m_scrollSpeed(0.25f)
		, m_scrollOffset(0.0f)
		, m_scrollDirection(1.0f)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		Args args(_argc, _argv);

		m_width  = _width;
		m_height = _height;
		m_debug  = BGFX_DEBUG_NONE;
		m_reset  = BGFX_RESET_VSYNC;

		bgfx::Init init;
		init.type     = args.m_type;
		init.vendorId = args.m_pciId;
		init.platformData.nwh  = entry::getNativeWindowHandle(entry::kDefaultWindowHandle);
		init.platformData.ndt  = entry::getNativeDisplayHandle();
		init.platformData.type = entry::getNativeWindowHandleType();
		init.resolution.width  = m_width;
		init.resolution.height = m_height;
		init.resolution.reset  = m_reset;
		bgfx::init(init);

		bgfx::setDebug(m_debug);

		bgfx::setViewClear(0
			, BGFX_CLEAR_COLOR
			, 0x303030ff
			, 1.0f
			, 0
			);

		FontVertex::init();

		m_curveSampler  = bgfx::createUniform("s_curveData", bgfx::UniformType::Sampler);
		m_bandSampler   = bgfx::createUniform("s_bandData",  bgfx::UniformType::Sampler);
		m_paramsUniform = bgfx::createUniform("u_params",    bgfx::UniformType::Vec4);

		m_fontProgram = loadProgram("vs_slug", "fs_slug");

		imguiCreate();

		{
			uint32_t txtSize = 0;
			void* txtData = load("text/sherlock_holmes_a_scandal_in_bohemia_arthur_conan_doyle.txt", &txtSize);
			BX_ASSERT(NULL != txtData, "Text file not found!");

			const bx::StringView text = bx::StringView( (const char*)txtData, txtSize);

			uint32_t fontDataSize = 0;
			m_fontData = (uint8_t*)load("font/roboto-regular.ttf", &fontDataSize);
			m_mainFont = new SlugFont(m_fontData, 0.05f);
			m_mainFont->prepareGlyphsForText(text);
			m_bb = m_mainFont->measure(0.0f, 0.0f, text);

			const float cx = 0.5f * (m_bb.minX + m_bb.maxX);
			const float cy = m_bb.maxY;
			m_mainFont->buildMesh(-cx, -cy, text);

			unload(txtData);
			txtData = NULL;
		}

		{
			const float textW  = m_bb.maxX - m_bb.minX;
			const float aspect = float(m_width) / float(m_height);
			const float halfFovRad = 30.0f * bx::kPi / 180.0f; // half of 60° vertical FOV
			m_distance = (textW * 0.5f) / (bx::tan(halfFovRad) * aspect) * 1.1f;
		}

		m_posX = 0.0f;
		m_posY = 0.0f;
		m_rotX = 0.0f;
		m_rotY = 0.0f;
		m_rotZ = 0.0f;
		m_lastMouseX = 0;
		m_lastMouseY = 0;
		m_lastMz = 0;
		m_dragging = false;

		m_frameTime.reset();
		m_animTimeOffset = bx::toSeconds<float>(m_frameTime.getDurationTime() );
		m_animReset = true;
	}

	virtual int32_t shutdown() override
	{
		delete m_mainFont;
		m_mainFont = NULL;

		if (m_fontData != NULL)
		{
			unload(m_fontData);
			m_fontData = NULL;
		}

		imguiDestroy();

		bgfx::destroy(m_curveSampler);
		bgfx::destroy(m_bandSampler);
		bgfx::destroy(m_paramsUniform);
		bgfx::destroy(m_fontProgram);

		bgfx::shutdown();

		return 0;
	}

	bool update() override
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			m_frameTime.frame();

			const float time = bx::toSeconds<float>(m_frameTime.getDurationTime() );

			imguiBeginFrame(m_mouseState.m_mx
				,  m_mouseState.m_my
				, (m_mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT   : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT  : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
				,  m_mouseState.m_mz
				, uint16_t(m_width)
				, uint16_t(m_height)
				);

			showExampleDialog(this);

			ImGui::SetNextWindowPos(
				  ImVec2(m_width - m_width / 5.0f - 10.0f, 10.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::SetNextWindowSize(
				  ImVec2(m_width / 5.0f, m_height / 3.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::Begin("Settings", NULL, 0);

			ImGui::Checkbox("Animate", &m_animate);
			ImGui::SliderFloat("Scroll Speed", &m_scrollSpeed, 0.0f, 2.0f);

			if (ImGui::Button("Reset View") )
			{
				const float textW  = m_bb.maxX - m_bb.minX;
				const float aspect = float(m_width) / float(m_height);
				const float halfFovRad = 30.0f * bx::kPi / 180.0f;
				m_distance = (textW * 0.5f) / (bx::tan(halfFovRad) * aspect) * 1.1f;
				m_posX = 0.0f;
				m_posY = 0.0f;
				m_rotX = 0.0f;
				m_rotY = 0.0f;
				m_scrollOffset = 0.0f;
				m_scrollDirection = 1.0f;
			}

			ImGui::End();

			if (!ImGui::GetIO().WantCaptureMouse)
			{
				if (m_mouseState.m_buttons[entry::MouseButton::Right])
				{
					if (!m_dragging)
					{
						m_dragging = true;
						m_lastMouseX = m_mouseState.m_mx;
						m_lastMouseY = m_mouseState.m_my;
					}

					const float deltaX = (float)(m_mouseState.m_mx - m_lastMouseX);
					const float deltaY = (float)(m_mouseState.m_my - m_lastMouseY);
					m_lastMouseX = m_mouseState.m_mx;
					m_lastMouseY = m_mouseState.m_my;

					m_posX += deltaX * m_distance * 0.001f;
					m_posY -= deltaY * m_distance * 0.001f;
				}
				else if (m_mouseState.m_buttons[entry::MouseButton::Left])
				{
					if (!m_dragging)
					{
						m_dragging = true;
						m_lastMouseX = m_mouseState.m_mx;
						m_lastMouseY = m_mouseState.m_my;
					}

					const float deltaX = (float)(m_mouseState.m_mx - m_lastMouseX);
					const float deltaY = (float)(m_mouseState.m_my - m_lastMouseY);
					m_lastMouseX = m_mouseState.m_mx;
					m_lastMouseY = m_mouseState.m_my;

					const float size = bx::min((float)m_width, (float)m_height);
					m_rotY -= deltaX / size * bx::kPi;
					m_rotX -= deltaY / size * bx::kPi;
				}
				else if (m_mouseState.m_buttons[entry::MouseButton::Middle])
				{
					if (!m_dragging)
					{
						m_dragging = true;
						m_lastMouseX = m_mouseState.m_mx;
						m_lastMouseY = m_mouseState.m_my;
					}

					const float deltaX = (float)(m_mouseState.m_mx - m_lastMouseX);
					const float deltaY = (float)(m_mouseState.m_my - m_lastMouseY);
					m_lastMouseX = m_mouseState.m_mx;
					m_lastMouseY = m_mouseState.m_my;

					const float size = bx::min((float)m_width, (float)m_height);
					m_rotZ -= (deltaX + deltaY) / size * bx::kPi;
				}
				else
				{
					m_dragging = false;
				}

				bool resetAnimation = m_dragging;

				{
					const int32_t deltaZ = m_mouseState.m_mz - m_lastMz;
					m_lastMz = m_mouseState.m_mz;
					if (deltaZ != 0)
					{
						float factor = bx::clamp(1.0f - (float)deltaZ / 40.0f, 0.1f, 1.9f);
						m_distance = bx::clamp(m_distance * factor, 0.01f, 10.0f);
						resetAnimation = true;
					}
				}

				if (resetAnimation)
				{
					m_animTimeOffset = time + 3.0f;
				}
			}

			if (m_animate)
			{
				const float dt = bx::toMilliseconds<float>(m_frameTime.getDeltaTime() );
				m_scrollOffset += m_scrollDirection * m_scrollSpeed/1000.0f * dt;

				const float textHeight = m_bb.maxY - m_bb.minY;

				if (m_scrollOffset > textHeight)
				{
					m_scrollOffset    = textHeight;
					m_scrollDirection = -1.0f;
				}
				else if (m_scrollOffset < 0.0f)
				{
					m_scrollOffset    = 0.0f;
					m_scrollDirection = 1.0f;
				}
			}

			if (time > m_animTimeOffset)
			{
				struct Frame
				{
					float px, py, pz;
					float rx, ry, rz;
				};

				struct AnimFrame
				{
					Frame frame;
					float animTime;
					float duration;
				};

				static const AnimFrame animFrame[] =
				{
					{ {  0.0f,   0.0f,  2.00f,   0.0f,   0.0f, bx::kPiHalf }, 1.0f, 2.0f },
					{ {  0.0f,   0.0f,  3.00f,   0.0f,   0.0f, bx::kPiHalf }, 3.0f, 4.0f },
					{ {  0.0f,   0.0f, 10.00f,   0.0f,   0.0f, bx::kPiHalf }, 1.0f, 5.0f },
					{ {  0.0f,   0.0f,   0.5f,   0.0f,   0.0f,        0.0f }, 6.0f, 8.0f },
					{ {  0.0f,   0.0f,   0.5f,   0.0f,   0.0f,        1.0f }, 1.0f, 3.0f },
					{ { 0.42f,  0.05f,  0.69f,  0.79f, -0.55f,        0.0f }, 1.0f, 5.0f },
					{ { 0.07f, -0.31f,  0.59f, -0.50f, -0.00f,       -0.3f }, 1.0f, 5.0f },
					{ { 0.07f, -0.31f,  0.59f, -0.50f, -0.00f,        0.3f }, 1.0f, 5.0f },
					{ { 0.00f,  0.00f,  0.85f,  1.35f, -0.01f,        0.0f }, 1.0f, 5.0f },
				};

				static uint32_t currIdx = 0;
				static float timeOffset = time;
				static Frame prev;

				if (m_animReset)
				{
					currIdx = 0;
					timeOffset = time;

					prev =
					{
						.px = m_posX,
						.py = m_posY,
						.pz = m_distance,
						.rx = m_rotX,
						.ry = m_rotY,
						.rz = m_rotZ,
					};

					m_animReset = false;
				}

				float animFrameTime = time - timeOffset;
				if (animFrameTime >= animFrame[currIdx].duration)
				{
					timeOffset = time;
					animFrameTime -= animFrame[currIdx].duration;
					prev = animFrame[currIdx].frame;
					currIdx = (currIdx + 1) % BX_COUNTOF(animFrame);
				}

				const float animTime = bx::min(animFrameTime, animFrame[currIdx].animTime) / animFrame[currIdx].animTime;
				const Frame& curr = animFrame[currIdx].frame;
				const float tt = bx::easeInOutQuad(animTime);

				Frame frame =
				{
					.px = bx::lerp(prev.px, curr.px, tt),
					.py = bx::lerp(prev.py, curr.py, tt),
					.pz = bx::lerp(prev.pz, curr.pz, tt),
					.rx = bx::lerp(prev.rx, curr.rx, tt),
					.ry = bx::lerp(prev.ry, curr.ry, tt),
					.rz = bx::lerp(prev.rz, curr.rz, tt),
				};

				m_posX = frame.px;
				m_posY = frame.py;
				m_distance = frame.pz;
				m_rotX     = frame.rx;
				m_rotY     = frame.ry;
				m_rotZ     = frame.rz;
			}
			else
			{
				m_animReset = true;
			}

			imguiEndFrame();

			bgfx::touch(0);
			bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );

			const float aspect = float(m_width) / float(m_height);

			float view[16];
			{
				float eye[16];
				bx::mtxLookAt(eye
					, { 0.0f, 0.0f, m_distance }
					, { 0.0f, 0.0f, 0.0f }
					, { 0.0f, 1.0f, 0.0f }
					, bx::Handedness::Right
					);

				float rotation[16];
				bx::mtxRotateXYZ(rotation, m_rotX, m_rotY, m_rotZ);

				float translation[16];
				bx::mtxTranslate(translation, m_posX, m_posY, 0.0f);

				float tmp[16];
				bx::mtxMul(tmp, rotation, translation);
				bx::mtxMul(view, tmp, eye);
			}

			float proj[16];
			bx::mtxProj(proj
				, 60.0f
				, aspect
				, 0.002f
				, 12.0f
				, bgfx::getCaps()->homogeneousDepth
				, bx::Handedness::Right
				);

			bgfx::setViewTransform(0, view, proj);

			float mtxScroll[16];
			bx::mtxTranslate(mtxScroll, 0.0f, m_scrollOffset, 0.0f);
			bgfx::setTransform(mtxScroll);

			m_mainFont->submit(0
				, m_fontProgram
				, m_curveSampler
				, m_bandSampler
				, m_paramsUniform
				);

			bgfx::frame();

			return true;
		}

		return false;
	}

	entry::MouseState m_mouseState;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

	float m_animTimeOffset;
	bool  m_animReset = true;

	FrameTime m_frameTime;

	uint8_t*  m_fontData;
	SlugFont* m_mainFont;
	Rect m_bb;

	bgfx::ProgramHandle m_fontProgram;
	bgfx::UniformHandle m_curveSampler;
	bgfx::UniformHandle m_bandSampler;
	bgfx::UniformHandle m_paramsUniform;

	bool     m_animate;
	float    m_scrollSpeed;
	float    m_scrollOffset;
	float    m_scrollDirection;

	float    m_distance;
	float    m_posX;
	float    m_posY;
	float    m_rotX;
	float    m_rotY;
	float    m_rotZ;
	int32_t  m_lastMouseX;
	int32_t  m_lastMouseY;
	int32_t  m_lastMz;
	bool     m_dragging;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleGpuFont
	, "51-gpu-font"
	, "GPU Font Rendering (Slug Algorithm)"
	, "https://bkaradzic.github.io/bgfx/examples.html#gpu-font"
	);
