/*
 * Copyright 2013 Jeremie Roy. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "../common.h"

#include <bgfx.h>
#include <stddef.h> // offsetof
#include <memory.h> // memcpy
#include <wchar.h>  // wcslen

#include "text_buffer_manager.h"
#include "utf8.h"
#include "../cube_atlas.h"

#include "vs_font_basic.bin.h"
#include "fs_font_basic.bin.h"
#include "vs_font_distance_field.bin.h"
#include "fs_font_distance_field.bin.h"
#include "vs_font_distance_field_subpixel.bin.h"
#include "fs_font_distance_field_subpixel.bin.h"

#define MAX_BUFFERED_CHARACTERS (8192 - 5)

class TextBuffer
{
public:

	/// TextBuffer is bound to a fontManager for glyph retrieval
	/// @remark the ownership of the manager is not taken
	TextBuffer(FontManager* _fontManager);
	~TextBuffer();

	void setStyle(uint32_t _flags = STYLE_NORMAL)
	{
		m_styleFlags = _flags;
	}

	void setTextColor(uint32_t _rgba = 0x000000FF)
	{
		m_textColor = toABGR(_rgba);
	}

	void setBackgroundColor(uint32_t _rgba = 0x000000FF)
	{
		m_backgroundColor = toABGR(_rgba);
	}

	void setOverlineColor(uint32_t _rgba = 0x000000FF)
	{
		m_overlineColor = toABGR(_rgba);
	}

	void setUnderlineColor(uint32_t _rgba = 0x000000FF)
	{
		m_underlineColor = toABGR(_rgba);
	}

	void setStrikeThroughColor(uint32_t _rgba = 0x000000FF)
	{
		m_strikeThroughColor = toABGR(_rgba);
	}

	void setPenPosition(float _x, float _y)
	{
		m_penX = _x; m_penY = _y;
	}

	/// Append an ASCII/utf-8 string to the buffer using current pen
	/// position and color.
	void appendText(FontHandle _fontHandle, const char* _string, const char* _end = NULL);

	/// Append a wide char unicode string to the buffer using current pen
	/// position and color.
	void appendText(FontHandle _fontHandle, const wchar_t* _string, const wchar_t* _end = NULL);

	/// Append a whole face of the atlas cube, mostly used for debugging
	/// and visualizing atlas.
	void appendAtlasFace(uint16_t _faceIndex);

	/// Clear the text buffer and reset its state (pen/color)
	void clearTextBuffer();

	/// Get pointer to the vertex buffer to submit it to the graphic card.
	const uint8_t* getVertexBuffer()
	{
		return (uint8_t*) m_vertexBuffer;
	}

	/// Number of vertex in the vertex buffer.
	uint32_t getVertexCount() const
	{
		return m_vertexCount;
	}

	/// Size in bytes of a vertex.
	uint32_t getVertexSize() const
	{
		return sizeof(TextVertex);
	}

	/// get a pointer to the index buffer to submit it to the graphic
	const uint16_t* getIndexBuffer() const
	{
		return m_indexBuffer;
	}

	/// number of index in the index buffer
	uint32_t getIndexCount() const
	{
		return m_indexCount;
	}

	/// Size in bytes of an index.
	uint32_t getIndexSize() const
	{
		return sizeof(uint16_t);
	}

	uint32_t getTextColor() const
	{
		return toABGR(m_textColor);
	}

	TextRectangle getRectangle() const
	{
		return m_rectangle;
	}

private:
	void appendGlyph(FontHandle _handle, CodePoint _codePoint);
	void verticalCenterLastLine(float _txtDecalY, float _top, float _bottom);

	static uint32_t toABGR(uint32_t _rgba)
	{
		return ( ( (_rgba >>  0) & 0xff) << 24)
			 | ( ( (_rgba >>  8) & 0xff) << 16)
			 | ( ( (_rgba >> 16) & 0xff) <<  8)
			 | ( ( (_rgba >> 24) & 0xff) <<  0)
			 ;
	}

	uint32_t m_styleFlags;

	// color states
	uint32_t m_textColor;

	uint32_t m_backgroundColor;
	uint32_t m_overlineColor;
	uint32_t m_underlineColor;
	uint32_t m_strikeThroughColor;

	//position states
	float m_penX;
	float m_penY;

	float m_originX;
	float m_originY;

	float m_lineAscender;
	float m_lineDescender;
	float m_lineGap;

	TextRectangle m_rectangle;
	FontManager* m_fontManager;

	void setVertex(uint32_t _i, float _x, float _y, uint32_t _rgba, uint8_t _style = STYLE_NORMAL)
	{
		m_vertexBuffer[_i].x = _x;
		m_vertexBuffer[_i].y = _y;
		m_vertexBuffer[_i].rgba = _rgba;
		m_styleBuffer[_i] = _style;
	}

	struct TextVertex
	{
		float x, y;
		int16_t u, v, w, t;
		uint32_t rgba;
	};

	TextVertex* m_vertexBuffer;
	uint16_t* m_indexBuffer;
	uint8_t* m_styleBuffer;

	uint32_t m_indexCount;
	uint32_t m_lineStartIndex;
	uint16_t m_vertexCount;
};

TextBuffer::TextBuffer(FontManager* _fontManager)
	: m_styleFlags(STYLE_NORMAL)
	, m_textColor(0xffffffff)
	, m_backgroundColor(0xffffffff)
	, m_overlineColor(0xffffffff)
	, m_underlineColor(0xffffffff)
	, m_strikeThroughColor(0xffffffff)
	, m_penX(0)
	, m_penY(0)
	, m_originX(0)
	, m_originY(0)
	, m_lineAscender(0)
	, m_lineDescender(0)
	, m_lineGap(0)
	, m_fontManager(_fontManager)
	, m_vertexBuffer(new TextVertex[MAX_BUFFERED_CHARACTERS * 4])
	, m_indexBuffer(new uint16_t[MAX_BUFFERED_CHARACTERS * 6])
	, m_styleBuffer(new uint8_t[MAX_BUFFERED_CHARACTERS * 4])
	, m_indexCount(0)
	, m_lineStartIndex(0)
	, m_vertexCount(0)
{
	m_rectangle.width = 0;
	m_rectangle.height = 0;
}

TextBuffer::~TextBuffer()
{
	delete [] m_vertexBuffer;
	delete [] m_indexBuffer;
	delete [] m_styleBuffer;
}

void TextBuffer::appendText(FontHandle _fontHandle, const char* _string, const char* _end)
{
	if (m_vertexCount == 0)
	{
		m_originX = m_penX;
		m_originY = m_penY;
		m_lineDescender = 0;
		m_lineAscender = 0;
		m_lineGap = 0;
	}

	CodePoint codepoint = 0;
	uint32_t state = 0;

	if (_end == NULL)
	{
		_end = _string + strlen(_string);
	}
	BX_CHECK(_end >= _string);

	for (; *_string && _string < _end ; ++_string)
	{
		if (utf8_decode(&state, (uint32_t*)&codepoint, *_string) == UTF8_ACCEPT )
		{
			appendGlyph(_fontHandle, codepoint);
		}
	}

	BX_CHECK(state == UTF8_ACCEPT, "The string is not well-formed");
}

void TextBuffer::appendText(FontHandle _fontHandle, const wchar_t* _string, const wchar_t* _end)
{
	if (m_vertexCount == 0)
	{
		m_originX = m_penX;
		m_originY = m_penY;
		m_lineDescender = 0;
		m_lineAscender = 0;
		m_lineGap = 0;
	}

	if (_end == NULL)
	{
		_end = _string + wcslen(_string);
	}
	BX_CHECK(_end >= _string);

	for (const wchar_t* _current = _string; _current < _end; ++_current)
	{
		uint32_t _codePoint = *_current;
		appendGlyph(_fontHandle, _codePoint);
	}
}

void TextBuffer::appendAtlasFace(uint16_t _faceIndex)
{
	if( m_vertexCount/4 >= MAX_BUFFERED_CHARACTERS)
	{
		return;
	}

	float x0 = m_penX;
	float y0 = m_penY;
	float x1 = x0 + (float)m_fontManager->getAtlas()->getTextureSize();
	float y1 = y0 + (float)m_fontManager->getAtlas()->getTextureSize();

	m_fontManager->getAtlas()->packFaceLayerUV(_faceIndex
		, (uint8_t*)m_vertexBuffer
		, sizeof(TextVertex) * m_vertexCount + offsetof(TextVertex, u)
		, sizeof(TextVertex)
		);

	setVertex(m_vertexCount + 0, x0, y0, m_backgroundColor);
	setVertex(m_vertexCount + 1, x0, y1, m_backgroundColor);
	setVertex(m_vertexCount + 2, x1, y1, m_backgroundColor);
	setVertex(m_vertexCount + 3, x1, y0, m_backgroundColor);

	m_indexBuffer[m_indexCount + 0] = m_vertexCount + 0;
	m_indexBuffer[m_indexCount + 1] = m_vertexCount + 1;
	m_indexBuffer[m_indexCount + 2] = m_vertexCount + 2;
	m_indexBuffer[m_indexCount + 3] = m_vertexCount + 0;
	m_indexBuffer[m_indexCount + 4] = m_vertexCount + 2;
	m_indexBuffer[m_indexCount + 5] = m_vertexCount + 3;
	m_vertexCount += 4;
	m_indexCount += 6;
}

void TextBuffer::clearTextBuffer()
{
	m_penX = 0;
	m_penY = 0;
	m_originX = 0;
	m_originY = 0;

	m_vertexCount = 0;
	m_indexCount = 0;
	m_lineStartIndex = 0;
	m_lineAscender = 0;
	m_lineDescender = 0;
	m_lineGap = 0;
	m_rectangle.width = 0;
	m_rectangle.height = 0;
}

void TextBuffer::appendGlyph(FontHandle _handle, CodePoint _codePoint)
{
	const GlyphInfo* glyph = m_fontManager->getGlyphInfo(_handle, _codePoint);
	BX_WARN(NULL != glyph, "Glyph not found (font handle %d, code point %d)", _handle.idx, _codePoint);
	if (NULL == glyph)
	{
		return;
	}

	const FontInfo& font = m_fontManager->getFontInfo(_handle);

	if( m_vertexCount/4 >= MAX_BUFFERED_CHARACTERS)
	{
		return;
	}

	if (_codePoint == L'\n')
	{
		m_penX = m_originX;
		m_penY += m_lineGap + m_lineAscender -m_lineDescender;
		m_lineGap = font.lineGap;
		m_lineDescender = font.descender;
		m_lineAscender = font.ascender;
		m_lineStartIndex = m_vertexCount;
		return;
	}

	//is there a change of font size that require the text on the left to be centered again ?
	if (font.ascender > m_lineAscender
		|| (font.descender < m_lineDescender) )
	{
		if (font.descender < m_lineDescender)
		{
			m_lineDescender = font.descender;
			m_lineGap = font.lineGap;
		}

		float txtDecals = (font.ascender - m_lineAscender);
		m_lineAscender = font.ascender;
		m_lineGap = font.lineGap;
		verticalCenterLastLine( (txtDecals), (m_penY - m_lineAscender), (m_penY + m_lineAscender - m_lineDescender + m_lineGap) );
	}

	float kerning = 0 * font.scale;
	m_penX += kerning;

	const GlyphInfo& blackGlyph = m_fontManager->getBlackGlyph();
	const Atlas* atlas = m_fontManager->getAtlas();

	if (m_styleFlags & STYLE_BACKGROUND
	&&  m_backgroundColor & 0xFF000000)
	{
		float x0 = (m_penX - kerning);
		float y0 = (m_penY);
		float x1 = ( (float)x0 + (glyph->advance_x) );
		float y1 = (m_penY + m_lineAscender - m_lineDescender + m_lineGap);

		atlas->packUV(blackGlyph.regionIndex
			, (uint8_t*)m_vertexBuffer
			, sizeof(TextVertex) * m_vertexCount + offsetof(TextVertex, u)
			, sizeof(TextVertex)
			);

		const uint16_t vertexCount = m_vertexCount;
		setVertex(vertexCount + 0, x0, y0, m_backgroundColor, STYLE_BACKGROUND);
		setVertex(vertexCount + 1, x0, y1, m_backgroundColor, STYLE_BACKGROUND);
		setVertex(vertexCount + 2, x1, y1, m_backgroundColor, STYLE_BACKGROUND);
		setVertex(vertexCount + 3, x1, y0, m_backgroundColor, STYLE_BACKGROUND);

		m_indexBuffer[m_indexCount + 0] = vertexCount + 0;
		m_indexBuffer[m_indexCount + 1] = vertexCount + 1;
		m_indexBuffer[m_indexCount + 2] = vertexCount + 2;
		m_indexBuffer[m_indexCount + 3] = vertexCount + 0;
		m_indexBuffer[m_indexCount + 4] = vertexCount + 2;
		m_indexBuffer[m_indexCount + 5] = vertexCount + 3;
		m_vertexCount += 4;
		m_indexCount += 6;
	}

	if (m_styleFlags & STYLE_UNDERLINE
	&&  m_underlineColor & 0xFF000000)
	{
		float x0 = (m_penX - kerning);
		float y0 = (m_penY + m_lineAscender - m_lineDescender * 0.5f);
		float x1 = ( (float)x0 + (glyph->advance_x) );
		float y1 = y0 + font.underlineThickness;

		atlas->packUV(blackGlyph.regionIndex
			, (uint8_t*)m_vertexBuffer
			, sizeof(TextVertex) * m_vertexCount + offsetof(TextVertex, u)
			, sizeof(TextVertex)
			);

		setVertex(m_vertexCount + 0, x0, y0, m_underlineColor, STYLE_UNDERLINE);
		setVertex(m_vertexCount + 1, x0, y1, m_underlineColor, STYLE_UNDERLINE);
		setVertex(m_vertexCount + 2, x1, y1, m_underlineColor, STYLE_UNDERLINE);
		setVertex(m_vertexCount + 3, x1, y0, m_underlineColor, STYLE_UNDERLINE);

		m_indexBuffer[m_indexCount + 0] = m_vertexCount + 0;
		m_indexBuffer[m_indexCount + 1] = m_vertexCount + 1;
		m_indexBuffer[m_indexCount + 2] = m_vertexCount + 2;
		m_indexBuffer[m_indexCount + 3] = m_vertexCount + 0;
		m_indexBuffer[m_indexCount + 4] = m_vertexCount + 2;
		m_indexBuffer[m_indexCount + 5] = m_vertexCount + 3;
		m_vertexCount += 4;
		m_indexCount += 6;
	}

	if (m_styleFlags & STYLE_OVERLINE
	&&  m_overlineColor & 0xFF000000)
	{
		float x0 = (m_penX - kerning);
		float y0 = (m_penY);
		float x1 = ( (float)x0 + (glyph->advance_x) );
		float y1 = y0 + font.underlineThickness;

		m_fontManager->getAtlas()->packUV(blackGlyph.regionIndex
			, (uint8_t*)m_vertexBuffer
			, sizeof(TextVertex) * m_vertexCount + offsetof(TextVertex, u)
			, sizeof(TextVertex)
			);

		setVertex(m_vertexCount + 0, x0, y0, m_overlineColor, STYLE_OVERLINE);
		setVertex(m_vertexCount + 1, x0, y1, m_overlineColor, STYLE_OVERLINE);
		setVertex(m_vertexCount + 2, x1, y1, m_overlineColor, STYLE_OVERLINE);
		setVertex(m_vertexCount + 3, x1, y0, m_overlineColor, STYLE_OVERLINE);

		m_indexBuffer[m_indexCount + 0] = m_vertexCount + 0;
		m_indexBuffer[m_indexCount + 1] = m_vertexCount + 1;
		m_indexBuffer[m_indexCount + 2] = m_vertexCount + 2;
		m_indexBuffer[m_indexCount + 3] = m_vertexCount + 0;
		m_indexBuffer[m_indexCount + 4] = m_vertexCount + 2;
		m_indexBuffer[m_indexCount + 5] = m_vertexCount + 3;
		m_vertexCount += 4;
		m_indexCount += 6;
	}

	if (m_styleFlags & STYLE_STRIKE_THROUGH
	&&  m_strikeThroughColor & 0xFF000000)
	{
		float x0 = (m_penX - kerning);
		float y0 = (m_penY + 0.666667f * font.ascender);
		float x1 = ( (float)x0 + (glyph->advance_x) );
		float y1 = y0 + font.underlineThickness;

		atlas->packUV(blackGlyph.regionIndex
			, (uint8_t*)m_vertexBuffer
			, sizeof(TextVertex) * m_vertexCount + offsetof(TextVertex, u)
			, sizeof(TextVertex)
			);

		setVertex(m_vertexCount + 0, x0, y0, m_strikeThroughColor, STYLE_STRIKE_THROUGH);
		setVertex(m_vertexCount + 1, x0, y1, m_strikeThroughColor, STYLE_STRIKE_THROUGH);
		setVertex(m_vertexCount + 2, x1, y1, m_strikeThroughColor, STYLE_STRIKE_THROUGH);
		setVertex(m_vertexCount + 3, x1, y0, m_strikeThroughColor, STYLE_STRIKE_THROUGH);

		m_indexBuffer[m_indexCount + 0] = m_vertexCount + 0;
		m_indexBuffer[m_indexCount + 1] = m_vertexCount + 1;
		m_indexBuffer[m_indexCount + 2] = m_vertexCount + 2;
		m_indexBuffer[m_indexCount + 3] = m_vertexCount + 0;
		m_indexBuffer[m_indexCount + 4] = m_vertexCount + 2;
		m_indexBuffer[m_indexCount + 5] = m_vertexCount + 3;
		m_vertexCount += 4;
		m_indexCount += 6;
	}

	float x0 = m_penX + (glyph->offset_x);
	float y0 = (m_penY + m_lineAscender + (glyph->offset_y) );
	float x1 = (x0 + glyph->width);
	float y1 = (y0 + glyph->height);

	atlas->packUV(glyph->regionIndex
		, (uint8_t*)m_vertexBuffer
		, sizeof(TextVertex) * m_vertexCount + offsetof(TextVertex, u)
		, sizeof(TextVertex)
		);

	setVertex(m_vertexCount + 0, x0, y0, m_textColor);
	setVertex(m_vertexCount + 1, x0, y1, m_textColor);
	setVertex(m_vertexCount + 2, x1, y1, m_textColor);
	setVertex(m_vertexCount + 3, x1, y0, m_textColor);

	m_indexBuffer[m_indexCount + 0] = m_vertexCount + 0;
	m_indexBuffer[m_indexCount + 1] = m_vertexCount + 1;
	m_indexBuffer[m_indexCount + 2] = m_vertexCount + 2;
	m_indexBuffer[m_indexCount + 3] = m_vertexCount + 0;
	m_indexBuffer[m_indexCount + 4] = m_vertexCount + 2;
	m_indexBuffer[m_indexCount + 5] = m_vertexCount + 3;
	m_vertexCount += 4;
	m_indexCount += 6;

	m_penX += glyph->advance_x;
	if (m_penX > m_rectangle.width)
	{
		m_rectangle.width = m_penX;
	}

	if ( (m_penY +m_lineAscender - m_lineDescender+m_lineGap) > m_rectangle.height)
	{
		m_rectangle.height = (m_penY +m_lineAscender - m_lineDescender+m_lineGap);
	}
}

void TextBuffer::verticalCenterLastLine(float _dy, float _top, float _bottom)
{
	for (uint32_t ii = m_lineStartIndex; ii < m_vertexCount; ii += 4)
	{
		if (m_styleBuffer[ii] == STYLE_BACKGROUND)
		{
			m_vertexBuffer[ii + 0].y = _top;
			m_vertexBuffer[ii + 1].y = _bottom;
			m_vertexBuffer[ii + 2].y = _bottom;
			m_vertexBuffer[ii + 3].y = _top;
		}
		else
		{
			m_vertexBuffer[ii + 0].y += _dy;
			m_vertexBuffer[ii + 1].y += _dy;
			m_vertexBuffer[ii + 2].y += _dy;
			m_vertexBuffer[ii + 3].y += _dy;
		}
	}
}

TextBufferManager::TextBufferManager(FontManager* _fontManager)
	: m_fontManager(_fontManager)
{
	m_textBuffers = new BufferCache[MAX_TEXT_BUFFER_COUNT];

	const bgfx::Memory* vs_font_basic;
	const bgfx::Memory* fs_font_basic;
	const bgfx::Memory* vs_font_distance_field;
	const bgfx::Memory* fs_font_distance_field;
	const bgfx::Memory* vs_font_distance_field_subpixel;
	const bgfx::Memory* fs_font_distance_field_subpixel;

	switch (bgfx::getRendererType() )
	{
	case bgfx::RendererType::Direct3D9:
		vs_font_basic = bgfx::makeRef(vs_font_basic_dx9, sizeof(vs_font_basic_dx9) );
		fs_font_basic = bgfx::makeRef(fs_font_basic_dx9, sizeof(fs_font_basic_dx9) );
		vs_font_distance_field = bgfx::makeRef(vs_font_distance_field_dx9, sizeof(vs_font_distance_field_dx9) );
		fs_font_distance_field = bgfx::makeRef(fs_font_distance_field_dx9, sizeof(fs_font_distance_field_dx9) );
		vs_font_distance_field_subpixel = bgfx::makeRef(vs_font_distance_field_subpixel_dx9, sizeof(vs_font_distance_field_subpixel_dx9) );
		fs_font_distance_field_subpixel = bgfx::makeRef(fs_font_distance_field_subpixel_dx9, sizeof(fs_font_distance_field_subpixel_dx9) );
		break;

	case bgfx::RendererType::Direct3D11:
	case bgfx::RendererType::Direct3D12:
		vs_font_basic = bgfx::makeRef(vs_font_basic_dx11, sizeof(vs_font_basic_dx11) );
		fs_font_basic = bgfx::makeRef(fs_font_basic_dx11, sizeof(fs_font_basic_dx11) );
		vs_font_distance_field = bgfx::makeRef(vs_font_distance_field_dx11, sizeof(vs_font_distance_field_dx11) );
		fs_font_distance_field = bgfx::makeRef(fs_font_distance_field_dx11, sizeof(fs_font_distance_field_dx11) );
		vs_font_distance_field_subpixel = bgfx::makeRef(vs_font_distance_field_subpixel_dx11, sizeof(vs_font_distance_field_subpixel_dx11) );
		fs_font_distance_field_subpixel = bgfx::makeRef(fs_font_distance_field_subpixel_dx11, sizeof(fs_font_distance_field_subpixel_dx11) );
		break;

	case bgfx::RendererType::Metal:
		vs_font_basic = bgfx::makeRef(vs_font_basic_mtl, sizeof(vs_font_basic_mtl) );
		fs_font_basic = bgfx::makeRef(fs_font_basic_mtl, sizeof(fs_font_basic_mtl) );
		vs_font_distance_field = bgfx::makeRef(vs_font_distance_field_mtl, sizeof(vs_font_distance_field_mtl) );
		fs_font_distance_field = bgfx::makeRef(fs_font_distance_field_mtl, sizeof(fs_font_distance_field_mtl) );
		vs_font_distance_field_subpixel = bgfx::makeRef(vs_font_distance_field_subpixel_mtl, sizeof(vs_font_distance_field_subpixel_mtl) );
		fs_font_distance_field_subpixel = bgfx::makeRef(fs_font_distance_field_subpixel_mtl, sizeof(fs_font_distance_field_subpixel_mtl) );
		break;
			
	default:
		vs_font_basic = bgfx::makeRef(vs_font_basic_glsl, sizeof(vs_font_basic_glsl) );
		fs_font_basic = bgfx::makeRef(fs_font_basic_glsl, sizeof(fs_font_basic_glsl) );
		vs_font_distance_field = bgfx::makeRef(vs_font_distance_field_glsl, sizeof(vs_font_distance_field_glsl) );
		fs_font_distance_field = bgfx::makeRef(fs_font_distance_field_glsl, sizeof(fs_font_distance_field_glsl) );
		vs_font_distance_field_subpixel = bgfx::makeRef(vs_font_distance_field_subpixel_glsl, sizeof(vs_font_distance_field_subpixel_glsl) );
		fs_font_distance_field_subpixel = bgfx::makeRef(fs_font_distance_field_subpixel_glsl, sizeof(fs_font_distance_field_subpixel_glsl) );
		break;
	}

	m_basicProgram = bgfx::createProgram(
									  bgfx::createShader(vs_font_basic)
									, bgfx::createShader(fs_font_basic)
									, true
									);

	m_distanceProgram = bgfx::createProgram(
									  bgfx::createShader(vs_font_distance_field)
									, bgfx::createShader(fs_font_distance_field)
									, true
									);

	m_distanceSubpixelProgram = bgfx::createProgram(
									  bgfx::createShader(vs_font_distance_field_subpixel)
									, bgfx::createShader(fs_font_distance_field_subpixel)
									, true
									);

	m_vertexDecl
		.begin()
		.add(bgfx::Attrib::Position,  2, bgfx::AttribType::Float)
		.add(bgfx::Attrib::TexCoord0, 4, bgfx::AttribType::Int16, true)
		.add(bgfx::Attrib::Color0,    4, bgfx::AttribType::Uint8, true)
		.end();

	s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Int1);
}

TextBufferManager::~TextBufferManager()
{
	BX_CHECK(m_textBufferHandles.getNumHandles() == 0, "All the text buffers must be destroyed before destroying the manager");
	delete [] m_textBuffers;

	bgfx::destroyUniform(s_texColor);

	bgfx::destroyProgram(m_basicProgram);
	bgfx::destroyProgram(m_distanceProgram);
	bgfx::destroyProgram(m_distanceSubpixelProgram);
}

TextBufferHandle TextBufferManager::createTextBuffer(uint32_t _type, BufferType::Enum _bufferType)
{
	uint16_t textIdx = m_textBufferHandles.alloc();
	BufferCache& bc = m_textBuffers[textIdx];

	bc.textBuffer = new TextBuffer(m_fontManager);
	bc.fontType = _type;
	bc.bufferType = _bufferType;
	bc.indexBufferHandleIdx = bgfx::invalidHandle;
	bc.vertexBufferHandleIdx = bgfx::invalidHandle;

	TextBufferHandle ret = {textIdx};
	return ret;
}

void TextBufferManager::destroyTextBuffer(TextBufferHandle _handle)
{
	BX_CHECK(bgfx::isValid(_handle), "Invalid handle used");

	BufferCache& bc = m_textBuffers[_handle.idx];
	m_textBufferHandles.free(_handle.idx);
	delete bc.textBuffer;
	bc.textBuffer = NULL;

	if (bc.vertexBufferHandleIdx == bgfx::invalidHandle)
	{
		return;
	}

	switch (bc.bufferType)
	{
	case BufferType::Static:
		{
			bgfx::IndexBufferHandle ibh;
			bgfx::VertexBufferHandle vbh;
			ibh.idx = bc.indexBufferHandleIdx;
			vbh.idx = bc.vertexBufferHandleIdx;
			bgfx::destroyIndexBuffer(ibh);
			bgfx::destroyVertexBuffer(vbh);
		}

		break;

	case BufferType::Dynamic:
		bgfx::DynamicIndexBufferHandle ibh;
		bgfx::DynamicVertexBufferHandle vbh;
		ibh.idx = bc.indexBufferHandleIdx;
		vbh.idx = bc.vertexBufferHandleIdx;
		bgfx::destroyDynamicIndexBuffer(ibh);
		bgfx::destroyDynamicVertexBuffer(vbh);

		break;

	case BufferType::Transient: // destroyed every frame
		break;
	}
}

void TextBufferManager::submitTextBuffer(TextBufferHandle _handle, uint8_t _id, int32_t _depth)
{
	BX_CHECK(bgfx::isValid(_handle), "Invalid handle used");

	BufferCache& bc = m_textBuffers[_handle.idx];

	uint32_t indexSize  = bc.textBuffer->getIndexCount()  * bc.textBuffer->getIndexSize();
	uint32_t vertexSize = bc.textBuffer->getVertexCount() * bc.textBuffer->getVertexSize();

	if (0 == indexSize || 0 == vertexSize)
	{
		return;
	}

	bgfx::setTexture(0, s_texColor, m_fontManager->getAtlas()->getTextureHandle() );

	bgfx::ProgramHandle program = BGFX_INVALID_HANDLE;
	switch (bc.fontType)
	{
	case FONT_TYPE_ALPHA:
		program = m_basicProgram;
		bgfx::setState(0
			| BGFX_STATE_RGB_WRITE
			| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA)
			);
		break;

	case FONT_TYPE_DISTANCE:
		program = m_distanceProgram;
		bgfx::setState(0
			| BGFX_STATE_RGB_WRITE
			| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA)
			);
		break;

	case FONT_TYPE_DISTANCE_SUBPIXEL:
		program = m_distanceSubpixelProgram;
		bgfx::setState(0
			| BGFX_STATE_RGB_WRITE
			| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_FACTOR, BGFX_STATE_BLEND_INV_SRC_COLOR)
			, bc.textBuffer->getTextColor()
			);
		break;
	}

	switch (bc.bufferType)
	{
	case BufferType::Static:
		{
			bgfx::IndexBufferHandle ibh;
			bgfx::VertexBufferHandle vbh;

			if (bgfx::invalidHandle == bc.vertexBufferHandleIdx)
			{
				ibh = bgfx::createIndexBuffer(
								bgfx::copy(bc.textBuffer->getIndexBuffer(), indexSize)
								);

				vbh = bgfx::createVertexBuffer(
								  bgfx::copy(bc.textBuffer->getVertexBuffer(), vertexSize)
								, m_vertexDecl
								);

				bc.vertexBufferHandleIdx = vbh.idx;
				bc.indexBufferHandleIdx = ibh.idx;
			}
			else
			{
				vbh.idx = bc.vertexBufferHandleIdx;
				ibh.idx = bc.indexBufferHandleIdx;
			}

			bgfx::setVertexBuffer(vbh, 0, bc.textBuffer->getVertexCount() );
			bgfx::setIndexBuffer(ibh, 0, bc.textBuffer->getIndexCount() );
		}
		break;

	case BufferType::Dynamic:
		{
			bgfx::DynamicIndexBufferHandle ibh;
			bgfx::DynamicVertexBufferHandle vbh;

			if (bgfx::invalidHandle == bc.vertexBufferHandleIdx )
			{
				ibh = bgfx::createDynamicIndexBuffer(
								bgfx::copy(bc.textBuffer->getIndexBuffer(), indexSize)
								);

				vbh = bgfx::createDynamicVertexBuffer(
								  bgfx::copy(bc.textBuffer->getVertexBuffer(), vertexSize)
								, m_vertexDecl
								);

				bc.indexBufferHandleIdx = ibh.idx;
				bc.vertexBufferHandleIdx = vbh.idx;
			}
			else
			{
				ibh.idx = bc.indexBufferHandleIdx;
				vbh.idx = bc.vertexBufferHandleIdx;

				bgfx::updateDynamicIndexBuffer(ibh
						, 0
						, bgfx::copy(bc.textBuffer->getIndexBuffer(), indexSize)
						);

				bgfx::updateDynamicVertexBuffer(vbh
						, 0
						, bgfx::copy(bc.textBuffer->getVertexBuffer(), vertexSize)
						);
			}

			bgfx::setVertexBuffer(vbh, bc.textBuffer->getVertexCount() );
			bgfx::setIndexBuffer(ibh, bc.textBuffer->getIndexCount() );
		}
		break;

	case BufferType::Transient:
		{
			bgfx::TransientIndexBuffer tib;
			bgfx::TransientVertexBuffer tvb;
			bgfx::allocTransientIndexBuffer(&tib, bc.textBuffer->getIndexCount() );
			bgfx::allocTransientVertexBuffer(&tvb, bc.textBuffer->getVertexCount(), m_vertexDecl);
			memcpy(tib.data, bc.textBuffer->getIndexBuffer(), indexSize);
			memcpy(tvb.data, bc.textBuffer->getVertexBuffer(), vertexSize);
			bgfx::setVertexBuffer(&tvb, 0, bc.textBuffer->getVertexCount() );
			bgfx::setIndexBuffer(&tib, 0, bc.textBuffer->getIndexCount() );
		}
		break;
	}

	bgfx::submit(_id, program, _depth);
}

void TextBufferManager::setStyle(TextBufferHandle _handle, uint32_t _flags)
{
	BX_CHECK(bgfx::isValid(_handle), "Invalid handle used");
	BufferCache& bc = m_textBuffers[_handle.idx];
	bc.textBuffer->setStyle(_flags);
}

void TextBufferManager::setTextColor(TextBufferHandle _handle, uint32_t _rgba)
{
	BX_CHECK(bgfx::isValid(_handle), "Invalid handle used");
	BufferCache& bc = m_textBuffers[_handle.idx];
	bc.textBuffer->setTextColor(_rgba);
}

void TextBufferManager::setBackgroundColor(TextBufferHandle _handle, uint32_t _rgba)
{
	BX_CHECK(bgfx::isValid(_handle), "Invalid handle used");
	BufferCache& bc = m_textBuffers[_handle.idx];
	bc.textBuffer->setBackgroundColor(_rgba);
}

void TextBufferManager::setOverlineColor(TextBufferHandle _handle, uint32_t _rgba)
{
	BX_CHECK(bgfx::isValid(_handle), "Invalid handle used");
	BufferCache& bc = m_textBuffers[_handle.idx];
	bc.textBuffer->setOverlineColor(_rgba);
}

void TextBufferManager::setUnderlineColor(TextBufferHandle _handle, uint32_t _rgba)
{
	BX_CHECK(bgfx::isValid(_handle), "Invalid handle used");
	BufferCache& bc = m_textBuffers[_handle.idx];
	bc.textBuffer->setUnderlineColor(_rgba);
}

void TextBufferManager::setStrikeThroughColor(TextBufferHandle _handle, uint32_t _rgba)
{
	BX_CHECK(bgfx::isValid(_handle), "Invalid handle used");
	BufferCache& bc = m_textBuffers[_handle.idx];
	bc.textBuffer->setStrikeThroughColor(_rgba);
}

void TextBufferManager::setPenPosition(TextBufferHandle _handle, float _x, float _y)
{
	BX_CHECK(bgfx::isValid(_handle), "Invalid handle used");
	BufferCache& bc = m_textBuffers[_handle.idx];
	bc.textBuffer->setPenPosition(_x, _y);
}

void TextBufferManager::appendText(TextBufferHandle _handle, FontHandle _fontHandle, const char* _string, const char* _end)
{
	BX_CHECK(bgfx::isValid(_handle), "Invalid handle used");
	BufferCache& bc = m_textBuffers[_handle.idx];
	bc.textBuffer->appendText(_fontHandle, _string, _end);
}

void TextBufferManager::appendText(TextBufferHandle _handle, FontHandle _fontHandle, const wchar_t* _string, const wchar_t* _end)
{
	BX_CHECK(bgfx::isValid(_handle), "Invalid handle used");
	BufferCache& bc = m_textBuffers[_handle.idx];
	bc.textBuffer->appendText(_fontHandle, _string, _end);
}

void TextBufferManager::appendAtlasFace(TextBufferHandle _handle, uint16_t _faceIndex)
{
	BX_CHECK(bgfx::isValid(_handle), "Invalid handle used");
	BufferCache& bc = m_textBuffers[_handle.idx];
	bc.textBuffer->appendAtlasFace(_faceIndex);
}

void TextBufferManager::clearTextBuffer(TextBufferHandle _handle)
{
	BX_CHECK(bgfx::isValid(_handle), "Invalid handle used");
	BufferCache& bc = m_textBuffers[_handle.idx];
	bc.textBuffer->clearTextBuffer();
}

TextRectangle TextBufferManager::getRectangle(TextBufferHandle _handle) const
{
	BX_CHECK(bgfx::isValid(_handle), "Invalid handle used");
	BufferCache& bc = m_textBuffers[_handle.idx];
	return bc.textBuffer->getRectangle();
}
