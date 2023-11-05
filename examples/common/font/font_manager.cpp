/*
 * Copyright 2013 Jeremie Roy. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include <bx/bx.h>
#include <stb/stb_truetype.h>
#include "../common.h"
#include <bgfx/bgfx.h>

BX_PRAGMA_DIAGNOSTIC_PUSH()
BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4244) //  warning C4244: '=': conversion from 'double' to 'float', possible loss of data
BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4701) //  warning C4701: potentially uninitialized local variable 'pt' used
#define SDF_IMPLEMENTATION
#include <sdf/sdf.h>
BX_PRAGMA_DIAGNOSTIC_POP()

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
	bool init(const uint8_t* _buffer, uint32_t _bufferSize, int32_t _fontIndex, uint32_t _pixelHeight, int16_t _widthPadding, int16_t _heightPadding);

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
	friend class FontManager;

	stbtt_fontinfo m_font;
	float m_scale;

	int16_t m_widthPadding;
	int16_t m_heightPadding;
};

TrueTypeFont::TrueTypeFont() : m_font()
	, m_widthPadding(6)
	, m_heightPadding(6)
{
}

TrueTypeFont::~TrueTypeFont()
{
}

bool TrueTypeFont::init(const uint8_t* _buffer, uint32_t _bufferSize, int32_t _fontIndex, uint32_t _pixelHeight, int16_t _widthPadding, int16_t _heightPadding)
{
	BX_WARN( (_bufferSize > 256 && _bufferSize < 100000000), "(FontIndex %d) TrueType buffer size is suspicious (%d)", _fontIndex, _bufferSize);
	BX_WARN( (_pixelHeight > 4 && _pixelHeight < 128), "(FontIndex %d) TrueType pixel height is suspicious (%d)", _fontIndex, _pixelHeight);
	BX_UNUSED(_bufferSize);

	int offset = stbtt_GetFontOffsetForIndex(_buffer, _fontIndex);

	stbtt_InitFont(&m_font, _buffer, offset);

	m_scale = stbtt_ScaleForMappingEmToPixels(&m_font, (float)_pixelHeight);

	m_widthPadding = _widthPadding;
	m_heightPadding = _heightPadding;
	return true;
}

FontInfo TrueTypeFont::getFontInfo()
{
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
	int32_t ascent, descent, lineGap;
	stbtt_GetFontVMetrics(&m_font, &ascent, &descent, &lineGap);

	int32_t advance, lsb;
	stbtt_GetCodepointHMetrics(&m_font, _codePoint, &advance, &lsb);

	const float scale = m_scale;
	int32_t x0, y0, x1, y1;
	stbtt_GetCodepointBitmapBox(&m_font, _codePoint, scale, scale, &x0, &y0, &x1, &y1);

	const int32_t ww = x1-x0;
	const int32_t hh = y1-y0;

	_glyphInfo.offset_x  = (float)x0;
	_glyphInfo.offset_y  = (float)y0;
	_glyphInfo.width     = (float)ww;
	_glyphInfo.height    = (float)hh;
	_glyphInfo.advance_x = bx::round(((float)advance) * scale);
	_glyphInfo.advance_y = bx::round(((float)(ascent + descent + lineGap)) * scale);

	uint32_t bpp = 1;
	uint32_t dstPitch = ww * bpp;

	stbtt_MakeCodepointBitmap(&m_font, _outBuffer, ww, hh, dstPitch, scale, scale, _codePoint);

	return true;
}

bool TrueTypeFont::bakeGlyphDistance(CodePoint _codePoint, GlyphInfo& _glyphInfo, uint8_t* _outBuffer)
{
	int32_t ascent, descent, lineGap;
	stbtt_GetFontVMetrics(&m_font, &ascent, &descent, &lineGap);

	int32_t advance, lsb;
	stbtt_GetCodepointHMetrics(&m_font, _codePoint, &advance, &lsb);

	const float scale = m_scale;
	int32_t x0, y0, x1, y1;
	stbtt_GetCodepointBitmapBox(&m_font, _codePoint, scale, scale, &x0, &y0, &x1, &y1);

	const int32_t ww = x1-x0;
	const int32_t hh = y1-y0;

	_glyphInfo.offset_x  = (float)x0;
	_glyphInfo.offset_y  = (float)y0;
	_glyphInfo.width     = (float)ww;
	_glyphInfo.height    = (float)hh;
	_glyphInfo.advance_x = bx::round(((float)advance) * scale);
	_glyphInfo.advance_y = bx::round(((float)(ascent + descent + lineGap)) * scale);

	uint32_t bpp = 1;
	uint32_t dstPitch = ww * bpp;

	stbtt_MakeCodepointBitmap(&m_font, _outBuffer, ww, hh, dstPitch, scale, scale, _codePoint);

	if (ww * hh > 0)
	{
		uint32_t dw = m_widthPadding;
		uint32_t dh = m_heightPadding;

		uint32_t nw = ww + dw * 2;
		uint32_t nh = hh + dh * 2;
		BX_ASSERT(nw * nh < 128 * 128, "Buffer overflow (size %d)", nw * nh);

		uint32_t buffSize = nw * nh * sizeof(uint8_t);

		uint8_t* alphaImg = (uint8_t*)malloc(buffSize);
		bx::memSet(alphaImg, 0, nw * nh * sizeof(uint8_t) );

		//copy the original buffer to the temp one
		for (uint32_t ii = dh; ii < nh - dh; ++ii)
		{
			bx::memCopy(alphaImg + ii * nw + dw, _outBuffer + (ii - dh) * ww, ww);
		}

		// stb_truetype has some builtin sdf functionality, we can investigate using that too
		sdfBuildDistanceField(_outBuffer, nw, 8.0f, alphaImg, nw, nh, nw);
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
	BX_ASSERT(m_fontHandles.getNumHandles() == 0, "All the fonts must be destroyed before destroying the manager");
	delete [] m_cachedFonts;

	BX_ASSERT(m_filesHandles.getNumHandles() == 0, "All the font files must be destroyed before destroying the manager");
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
	BX_ASSERT(id != bx::kInvalidHandle, "Invalid handle used");
	m_cachedFiles[id].buffer = new uint8_t[_size];
	m_cachedFiles[id].bufferSize = _size;
	bx::memCopy(m_cachedFiles[id].buffer, _buffer, _size);

	TrueTypeHandle ret = { id };
	return ret;
}

void FontManager::destroyTtf(TrueTypeHandle _handle)
{
	BX_ASSERT(isValid(_handle), "Invalid handle used");
	delete[] m_cachedFiles[_handle.idx].buffer;
	m_cachedFiles[_handle.idx].bufferSize = 0;
	m_cachedFiles[_handle.idx].buffer = NULL;
	m_filesHandles.free(_handle.idx);
}

FontHandle FontManager::createFontByPixelSize(TrueTypeHandle _ttfHandle, uint32_t _typefaceIndex, uint32_t _pixelSize, uint32_t _fontType,
		uint16_t _glyphWidthPadding, uint16_t _glyphHeightPadding)
{
	BX_ASSERT(isValid(_ttfHandle), "Invalid handle used");

	TrueTypeFont* ttf = new TrueTypeFont();
	if (!ttf->init(m_cachedFiles[_ttfHandle.idx].buffer, m_cachedFiles[_ttfHandle.idx].bufferSize, _typefaceIndex, _pixelSize, _glyphWidthPadding, _glyphHeightPadding) )
	{
		delete ttf;
		FontHandle invalid = { bx::kInvalidHandle };
		return invalid;
	}

	uint16_t fontIdx = m_fontHandles.alloc();
	BX_ASSERT(fontIdx != bx::kInvalidHandle, "Invalid handle used");

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
	BX_ASSERT(isValid(_baseFontHandle), "Invalid handle used");
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
	BX_ASSERT(fontIdx != bx::kInvalidHandle, "Invalid handle used");

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
	BX_ASSERT(isValid(_handle), "Invalid handle used");

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
	BX_ASSERT(isValid(_handle), "Invalid handle used");
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
	BX_ASSERT(isValid(_handle), "Invalid handle used");
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

		case FONT_TYPE_DISTANCE_OUTLINE:
		case FONT_TYPE_DISTANCE_OUTLINE_IMAGE:
		case FONT_TYPE_DISTANCE_DROP_SHADOW:
		case FONT_TYPE_DISTANCE_DROP_SHADOW_IMAGE:
		case FONT_TYPE_DISTANCE_OUTLINE_DROP_SHADOW_IMAGE:
			font.trueTypeFont->bakeGlyphDistance(_codePoint, glyphInfo, m_buffer);
			break;

		default:
			BX_ASSERT(false, "TextureType not supported yet");
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

bool FontManager::addGlyphBitmap(FontHandle _handle, CodePoint _codePoint, uint16_t _width, uint16_t _height, uint16_t _pitch, float extraScale, const uint8_t* _bitmapBuffer, float glyphOffsetX, float glyphOffsetY)
{
	BX_ASSERT(isValid(_handle), "Invalid handle used");
	CachedFont& font = m_cachedFonts[_handle.idx];

	GlyphHashMap::iterator iter = font.cachedGlyphs.find(_codePoint);
	if (iter != font.cachedGlyphs.end() )
	{
		return true;
	}

	GlyphInfo glyphInfo;

	float glyphScale = extraScale;
	glyphInfo.offset_x = glyphOffsetX * glyphScale;
	glyphInfo.offset_y = glyphOffsetY * glyphScale;
	glyphInfo.width = (float)_width;
	glyphInfo.height = (float)_height;
	glyphInfo.advance_x = (float)_width * glyphScale;
	glyphInfo.advance_y = (float)_height * glyphScale;
	glyphInfo.bitmapScale = glyphScale;

	uint32_t dstPitch = _width * 4;

	uint8_t* dst = m_buffer;
	const uint8_t* src = _bitmapBuffer;
	uint32_t srcPitch = _pitch;

	for (int32_t ii = 0; ii < _height; ++ii)
	{
		bx::memCopy(dst, src, dstPitch);

		dst += dstPitch;
		src += srcPitch;
	}

	glyphInfo.regionIndex = m_atlas->addRegion(
		  (uint16_t)bx::ceil(glyphInfo.width)
		, (uint16_t)bx::ceil(glyphInfo.height)
		, m_buffer
		, AtlasRegion::TYPE_BGRA8
		);

	font.cachedGlyphs[_codePoint] = glyphInfo;
	return true;
}

const FontInfo& FontManager::getFontInfo(FontHandle _handle) const
{
	BX_ASSERT(isValid(_handle), "Invalid handle used");
	return m_cachedFonts[_handle.idx].fontInfo;
}

float FontManager::getKerning(FontHandle _handle, CodePoint _prevCodePoint, CodePoint _codePoint)
{
	const CachedFont& cachedFont = m_cachedFonts[_handle.idx];
	if (isValid(cachedFont.masterFontHandle))
	{
		CachedFont& baseFont = m_cachedFonts[cachedFont.masterFontHandle.idx];
		return baseFont.trueTypeFont->m_scale 
			* stbtt_GetCodepointKernAdvance(&baseFont.trueTypeFont->m_font, _prevCodePoint, _codePoint)
			* cachedFont.fontInfo.scale;
	}
	else
	{
		return cachedFont.trueTypeFont->m_scale * stbtt_GetCodepointKernAdvance(&cachedFont.trueTypeFont->m_font, _prevCodePoint, _codePoint);
	}
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

	BX_ASSERT(it != cachedGlyphs.end(), "Failed to preload glyph.");
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
