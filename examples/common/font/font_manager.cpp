/*
 * Copyright 2013 Jeremie Roy. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bx/bx.h>

#include <stb/stb_truetype.h>

#include "../common.h"

#include <bgfx/bgfx.h>

#define SDF_IMPLEMENTATION
#include <sdf/sdf.h>

#include <wchar.h> // wcslen

#include <tinystl/allocator.h>
#include <tinystl/unordered_map.h>
namespace stl = tinystl;

#include "font_manager.h"
#include "../cube_atlas.h"


class TrueTypeFont
{
public:
	TrueTypeFont();
	~TrueTypeFont();

	/// Initialize from  an external buffer
	/// @remark The ownership of the buffer is external, and you must ensure it stays valid up to this object lifetime
	/// @return true if the initialization succeed
	bool init(const uint8_t* _buffer, uint32_t _bufferSize, int32_t _fontIndex, uint32_t _pixelHeight);

	/// return the font descriptor of the current font
	FontInfo getFontInfo();

	/// raster a glyph as 8bit alpha to a memory buffer
	/// update the GlyphInfo according to the raster strategy
	/// @ remark buffer min size: glyphInfo.m_width * glyphInfo * height * sizeof(char)
	bool bakeGlyphAlpha(CodePoint _codePoint, GlyphInfo& _outGlyphInfo, uint8_t* _outBuffer);

	/// raster a glyph as 8bit signed distance to a memory buffer
	/// update the GlyphInfo according to the raster strategy
	/// @ remark buffer min size: glyphInfo.m_width * glyphInfo * height * sizeof(char)
	bool bakeGlyphDistance(CodePoint _codePoint, GlyphInfo& _outGlyphInfo, uint8_t* _outBuffer);

private:
	stbtt_fontinfo m_font;
	float m_scale;
};

TrueTypeFont::TrueTypeFont() : m_font()
{
}

TrueTypeFont::~TrueTypeFont()
{
}

bool TrueTypeFont::init(const uint8_t* _buffer, uint32_t _bufferSize, int32_t _fontIndex, uint32_t _pixelHeight)
{
	BX_CHECK(m_font == NULL, "TrueTypeFont already initialized");
	BX_CHECK( (_bufferSize > 256 && _bufferSize < 100000000), "TrueType buffer size is suspicious");
	BX_CHECK( (_pixelHeight > 4 && _pixelHeight < 128), "TrueType buffer size is suspicious");
	BX_UNUSED(_bufferSize);

	int offset = stbtt_GetFontOffsetForIndex(_buffer, _fontIndex);

	stbtt_InitFont(&m_font, _buffer, offset);

	m_scale = stbtt_ScaleForMappingEmToPixels(&m_font, (float)_pixelHeight);

	return true;
}

FontInfo TrueTypeFont::getFontInfo()
{
	BX_CHECK(m_font != NULL, "TrueTypeFont not initialized");

	int ascent;
	int descent;
	int lineGap;
	stbtt_GetFontVMetrics(&m_font, &ascent, &descent, &lineGap);

	float scale = m_scale;

	int x0, y0, x1, y1;
	stbtt_GetFontBoundingBox(&m_font, &x0, &y0, &x1, &y1);

	FontInfo outFontInfo;
	outFontInfo.scale = 1.0f;
	outFontInfo.ascender = bx::round(ascent * scale);
	outFontInfo.descender = bx::round(descent * scale);
	outFontInfo.lineGap = bx::round(lineGap * scale);
	outFontInfo.maxAdvanceWidth = bx::round((y1 - y0) * scale);

	outFontInfo.underlinePosition = (x1 - x0) * scale - ascent;
	outFontInfo.underlineThickness = (x1 - x0) * scale / 24.f;
	return outFontInfo;
}

bool TrueTypeFont::bakeGlyphAlpha(CodePoint _codePoint, GlyphInfo& _glyphInfo, uint8_t* _outBuffer)
{
	BX_CHECK(m_font != NULL, "TrueTypeFont not initialized");

	int xx;
	int yy;
	int ww;
	int hh;
	int advance;
	int ascent;
	int descent;
	int lineGap;
	int lsb;

	float scale = m_scale;

	stbtt_GetFontVMetrics(&m_font, &ascent, &descent, &lineGap);
	stbtt_GetCodepointHMetrics(&m_font, _codePoint, &advance, &lsb);
	stbtt_GetCodepointBitmap(&m_font, scale, scale, _codePoint, &ww, &hh, &xx, &yy);

	_glyphInfo.offset_x = (float)xx;
	_glyphInfo.offset_y = (float)yy;
	_glyphInfo.width = (float)ww;
	_glyphInfo.height = (float)hh;
	_glyphInfo.advance_x = bx::round(((float)advance) * scale);
	_glyphInfo.advance_y = bx::round(((float)(ascent + descent + lineGap)) * scale);

	uint32_t bpp = 1;
	uint32_t dstPitch = ww * bpp;

	stbtt_MakeCodepointBitmap(&m_font, _outBuffer, ww, hh, dstPitch, scale, scale, _codePoint);

	return true;
}

bool TrueTypeFont::bakeGlyphDistance(CodePoint _codePoint, GlyphInfo& _glyphInfo, uint8_t* _outBuffer)
{
	BX_CHECK(m_font != NULL, "TrueTypeFont not initialized");

	int32_t xx;
	int32_t yy;
	int32_t ww;
	int32_t hh;
	int advance;
	int ascent;
	int descent;
	int lineGap;
	int lsb;

	float scale = m_scale;

	stbtt_GetFontVMetrics(&m_font, &ascent, &descent, &lineGap);
	stbtt_GetCodepointHMetrics(&m_font, _codePoint, &advance, &lsb);
	stbtt_GetCodepointBitmap(&m_font, scale, scale, _codePoint, &ww, &hh, &xx, &yy);

	_glyphInfo.offset_x = (float)xx;
	_glyphInfo.offset_y = (float)yy;
	_glyphInfo.width = (float)ww;
	_glyphInfo.height = (float)hh;
	_glyphInfo.advance_x = bx::round(((float)advance) * scale);
	_glyphInfo.advance_y = bx::round(((float)(ascent + descent + lineGap)) * scale);

	uint32_t bpp = 1;
	uint32_t dstPitch = ww * bpp;

	stbtt_MakeCodepointBitmap(&m_font, _outBuffer, ww, hh, dstPitch, scale, scale, _codePoint);

	if (ww * hh > 0)
	{
		uint32_t dw = 6;
		uint32_t dh = 6;

		uint32_t nw = ww + dw * 2;
		uint32_t nh = hh + dh * 2;
		BX_CHECK(nw * nh < 128 * 128, "Buffer overflow (size %d)", nw * nh);

		uint32_t buffSize = nw * nh * sizeof(uint8_t);

		uint8_t* alphaImg = (uint8_t*)malloc(buffSize);
		bx::memSet(alphaImg, 0, nw * nh * sizeof(uint8_t) );

		//copy the original buffer to the temp one
		for (uint32_t ii = dh; ii < nh - dh; ++ii)
		{
			bx::memCopy(alphaImg + ii * nw + dw, _outBuffer + (ii - dh) * ww, ww);
		}

		// stb_truetype has some builtin sdf functionality, we can investigate using that too
		sdfBuild(_outBuffer, nw, 8.0f, alphaImg, nw, nh, nw);
		free(alphaImg);

		_glyphInfo.offset_x -= (float)dw;
		_glyphInfo.offset_y -= (float)dh;
		_glyphInfo.width = (float)nw;
		_glyphInfo.height = (float)nh;
	}

	return true;
}

typedef stl::unordered_map<CodePoint, GlyphInfo> GlyphHashMap;

// cache font data
struct FontManager::CachedFont
{
	CachedFont()
		: trueTypeFont(NULL)
	{
		masterFontHandle.idx = bx::kInvalidHandle;
	}

	FontInfo fontInfo;
	GlyphHashMap cachedGlyphs;
	TrueTypeFont* trueTypeFont;
	// an handle to a master font in case of sub distance field font
	FontHandle masterFontHandle;
	int16_t padding;
};

#define MAX_FONT_BUFFER_SIZE (512 * 512 * 4)

FontManager::FontManager(Atlas* _atlas)
	: m_ownAtlas(false)
	, m_atlas(_atlas)
{
	init();
}

FontManager::FontManager(uint16_t _textureSideWidth)
	: m_ownAtlas(true)
	, m_atlas(new Atlas(_textureSideWidth) )
{
	init();
}

void FontManager::init()
{
	m_cachedFiles = new CachedFile[MAX_OPENED_FILES];
	m_cachedFonts = new CachedFont[MAX_OPENED_FONT];
	m_buffer = new uint8_t[MAX_FONT_BUFFER_SIZE];

	const uint32_t W = 3;
	// Create filler rectangle
	uint8_t buffer[W * W * 4];
	bx::memSet(buffer, 255, W * W * 4);

	m_blackGlyph.width = W;
	m_blackGlyph.height = W;

	///make sure the black glyph doesn't bleed by using a one pixel inner outline
	m_blackGlyph.regionIndex = m_atlas->addRegion(W, W, buffer, AtlasRegion::TYPE_GRAY, 1);
}

FontManager::~FontManager()
{
	BX_CHECK(m_fontHandles.getNumHandles() == 0, "All the fonts must be destroyed before destroying the manager");
	delete [] m_cachedFonts;

	BX_CHECK(m_filesHandles.getNumHandles() == 0, "All the font files must be destroyed before destroying the manager");
	delete [] m_cachedFiles;

	delete [] m_buffer;

	if (m_ownAtlas)
	{
		delete m_atlas;
	}
}

TrueTypeHandle FontManager::createTtf(const uint8_t* _buffer, uint32_t _size)
{
	uint16_t id = m_filesHandles.alloc();
	BX_CHECK(id != bx::kInvalidHandle, "Invalid handle used");
	m_cachedFiles[id].buffer = new uint8_t[_size];
	m_cachedFiles[id].bufferSize = _size;
	bx::memCopy(m_cachedFiles[id].buffer, _buffer, _size);

	TrueTypeHandle ret = { id };
	return ret;
}

void FontManager::destroyTtf(TrueTypeHandle _handle)
{
	BX_CHECK(bgfx::isValid(_handle), "Invalid handle used");
	delete m_cachedFiles[_handle.idx].buffer;
	m_cachedFiles[_handle.idx].bufferSize = 0;
	m_cachedFiles[_handle.idx].buffer = NULL;
	m_filesHandles.free(_handle.idx);
}

FontHandle FontManager::createFontByPixelSize(TrueTypeHandle _ttfHandle, uint32_t _typefaceIndex, uint32_t _pixelSize, uint32_t _fontType)
{
	BX_CHECK(bgfx::isValid(_ttfHandle), "Invalid handle used");

	TrueTypeFont* ttf = new TrueTypeFont();
	if (!ttf->init(m_cachedFiles[_ttfHandle.idx].buffer, m_cachedFiles[_ttfHandle.idx].bufferSize, _typefaceIndex, _pixelSize) )
	{
		delete ttf;
		FontHandle invalid = { bx::kInvalidHandle };
		return invalid;
	}

	uint16_t fontIdx = m_fontHandles.alloc();
	BX_CHECK(fontIdx != bx::kInvalidHandle, "Invalid handle used");

	CachedFont& font = m_cachedFonts[fontIdx];
	font.trueTypeFont = ttf;
	font.fontInfo = ttf->getFontInfo();
	font.fontInfo.fontType  = int16_t(_fontType);
	font.fontInfo.pixelSize = uint16_t(_pixelSize);
	font.cachedGlyphs.clear();
	font.masterFontHandle.idx = bx::kInvalidHandle;

	FontHandle handle = { fontIdx };
	return handle;
}

FontHandle FontManager::createScaledFontToPixelSize(FontHandle _baseFontHandle, uint32_t _pixelSize)
{
	BX_CHECK(bgfx::isValid(_baseFontHandle), "Invalid handle used");
	CachedFont& baseFont = m_cachedFonts[_baseFontHandle.idx];
	FontInfo& fontInfo = baseFont.fontInfo;

	FontInfo newFontInfo  = fontInfo;
	newFontInfo.pixelSize = uint16_t(_pixelSize);
	newFontInfo.scale     = (float)_pixelSize / (float) fontInfo.pixelSize;
	newFontInfo.ascender  = (newFontInfo.ascender * newFontInfo.scale);
	newFontInfo.descender = (newFontInfo.descender * newFontInfo.scale);
	newFontInfo.lineGap   = (newFontInfo.lineGap * newFontInfo.scale);
	newFontInfo.maxAdvanceWidth    = (newFontInfo.maxAdvanceWidth * newFontInfo.scale);
	newFontInfo.underlineThickness = (newFontInfo.underlineThickness * newFontInfo.scale);
	newFontInfo.underlinePosition  = (newFontInfo.underlinePosition * newFontInfo.scale);

	uint16_t fontIdx = m_fontHandles.alloc();
	BX_CHECK(fontIdx != bx::kInvalidHandle, "Invalid handle used");

	CachedFont& font = m_cachedFonts[fontIdx];
	font.cachedGlyphs.clear();
	font.fontInfo = newFontInfo;
	font.trueTypeFont = NULL;
	font.masterFontHandle = _baseFontHandle;

	FontHandle handle = { fontIdx };
	return handle;
}

void FontManager::destroyFont(FontHandle _handle)
{
	BX_CHECK(bgfx::isValid(_handle), "Invalid handle used");

	CachedFont& font = m_cachedFonts[_handle.idx];

	if (font.trueTypeFont != NULL)
	{
		delete font.trueTypeFont;
		font.trueTypeFont = NULL;
	}

	font.cachedGlyphs.clear();
	m_fontHandles.free(_handle.idx);
}

bool FontManager::preloadGlyph(FontHandle _handle, const wchar_t* _string)
{
	BX_CHECK(bgfx::isValid(_handle), "Invalid handle used");
	CachedFont& font = m_cachedFonts[_handle.idx];

	if (NULL == font.trueTypeFont)
	{
		return false;
	}

	for (uint32_t ii = 0, end = (uint32_t)wcslen(_string); ii < end; ++ii)
	{
		CodePoint codePoint = _string[ii];
		if (!preloadGlyph(_handle, codePoint) )
		{
			return false;
		}
	}

	return true;
}

bool FontManager::preloadGlyph(FontHandle _handle, CodePoint _codePoint)
{
	BX_CHECK(bgfx::isValid(_handle), "Invalid handle used");
	CachedFont& font = m_cachedFonts[_handle.idx];
	FontInfo& fontInfo = font.fontInfo;

	GlyphHashMap::iterator iter = font.cachedGlyphs.find(_codePoint);
	if (iter != font.cachedGlyphs.end() )
	{
		return true;
	}

	if (NULL != font.trueTypeFont)
	{
		GlyphInfo glyphInfo;

		switch (font.fontInfo.fontType)
		{
		case FONT_TYPE_ALPHA:
			font.trueTypeFont->bakeGlyphAlpha(_codePoint, glyphInfo, m_buffer);
			break;

		case FONT_TYPE_DISTANCE:
			font.trueTypeFont->bakeGlyphDistance(_codePoint, glyphInfo, m_buffer);
			break;

		case FONT_TYPE_DISTANCE_SUBPIXEL:
			font.trueTypeFont->bakeGlyphDistance(_codePoint, glyphInfo, m_buffer);
			break;

		default:
			BX_CHECK(false, "TextureType not supported yet");
		}

		if (!addBitmap(glyphInfo, m_buffer) )
		{
			return false;
		}

		glyphInfo.advance_x = (glyphInfo.advance_x * fontInfo.scale);
		glyphInfo.advance_y = (glyphInfo.advance_y * fontInfo.scale);
		glyphInfo.offset_x = (glyphInfo.offset_x * fontInfo.scale);
		glyphInfo.offset_y = (glyphInfo.offset_y * fontInfo.scale);
		glyphInfo.height = (glyphInfo.height * fontInfo.scale);
		glyphInfo.width = (glyphInfo.width * fontInfo.scale);

		font.cachedGlyphs[_codePoint] = glyphInfo;
		return true;
	}

	if (isValid(font.masterFontHandle)
	&&  preloadGlyph(font.masterFontHandle, _codePoint) )
	{
		const GlyphInfo* glyph = getGlyphInfo(font.masterFontHandle, _codePoint);

		GlyphInfo glyphInfo = *glyph;
		glyphInfo.advance_x = (glyphInfo.advance_x * fontInfo.scale);
		glyphInfo.advance_y = (glyphInfo.advance_y * fontInfo.scale);
		glyphInfo.offset_x = (glyphInfo.offset_x * fontInfo.scale);
		glyphInfo.offset_y = (glyphInfo.offset_y * fontInfo.scale);
		glyphInfo.height = (glyphInfo.height * fontInfo.scale);
		glyphInfo.width = (glyphInfo.width * fontInfo.scale);

		font.cachedGlyphs[_codePoint] = glyphInfo;
		return true;
	}

	return false;
}

const FontInfo& FontManager::getFontInfo(FontHandle _handle) const
{
	BX_CHECK(bgfx::isValid(_handle), "Invalid handle used");
	return m_cachedFonts[_handle.idx].fontInfo;
}

const GlyphInfo* FontManager::getGlyphInfo(FontHandle _handle, CodePoint _codePoint)
{
	const GlyphHashMap& cachedGlyphs = m_cachedFonts[_handle.idx].cachedGlyphs;
	GlyphHashMap::const_iterator it = cachedGlyphs.find(_codePoint);

	if (it == cachedGlyphs.end() )
	{
		if (!preloadGlyph(_handle, _codePoint) )
		{
			return NULL;
		}

		it = cachedGlyphs.find(_codePoint);
	}

	BX_CHECK(it != cachedGlyphs.end(), "Failed to preload glyph.");
	return &it->second;
}

bool FontManager::addBitmap(GlyphInfo& _glyphInfo, const uint8_t* _data)
{
	_glyphInfo.regionIndex = m_atlas->addRegion(
		  (uint16_t)bx::ceil(_glyphInfo.width)
		, (uint16_t)bx::ceil(_glyphInfo.height)
		, _data
		, AtlasRegion::TYPE_GRAY
		);
	return true;
}
