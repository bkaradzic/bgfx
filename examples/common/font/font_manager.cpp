/*
 * Copyright 2013 Jeremie Roy. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#define USE_EDTAA3 0

#include <bx/macros.h>

#if BX_COMPILER_MSVC
#	define generic GenericFromFreeType // WinRT language extensions see "generic" as a keyword... this is stupid
#endif // BX_COMPILER_MSVC

BX_PRAGMA_DIAGNOSTIC_PUSH();
BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4245) // error C4245: '=' : conversion from 'int' to 'FT_UInt', signed/unsigned mismatch
#if BX_COMPILER_MSVC || BX_COMPILER_GCC >= 40300
#pragma push_macro("interface")
#endif
#undef interface
#include <freetype/freetype.h>
#if BX_COMPILER_MSVC || BX_COMPILER_GCC >= 40300
#pragma pop_macro("interface")
#endif
BX_PRAGMA_DIAGNOSTIC_POP();

#include "../common.h"

#include <bgfx/bgfx.h>
#include <math.h>

#if USE_EDTAA3
#	include <edtaa3/edtaa3func.cpp>
#else
#	define SDF_IMPLEMENTATION
#	include <sdf/sdf.h>
#endif // USE_EDTAA3

#include <wchar.h> // wcslen

#include <tinystl/allocator.h>
#include <tinystl/unordered_map.h>
namespace stl = tinystl;

#include "font_manager.h"
#include "../cube_atlas.h"

struct FTHolder
{
	FT_Library library;
	FT_Face face;
};

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

	/// raster a glyph as 32bit subpixel rgba to a memory buffer
	/// update the GlyphInfo according to the raster strategy
	/// @ remark buffer min size: glyphInfo.m_width * glyphInfo * height * sizeof(uint32_t)
	bool bakeGlyphSubpixel(CodePoint _codePoint, GlyphInfo& _outGlyphInfo, uint8_t* _outBuffer);

	/// raster a glyph as 8bit signed distance to a memory buffer
	/// update the GlyphInfo according to the raster strategy
	/// @ remark buffer min size: glyphInfo.m_width * glyphInfo * height * sizeof(char)
	bool bakeGlyphDistance(CodePoint _codePoint, GlyphInfo& _outGlyphInfo, uint8_t* _outBuffer);

private:
	FTHolder* m_font;
};

TrueTypeFont::TrueTypeFont() : m_font(NULL)
{
}

TrueTypeFont::~TrueTypeFont()
{
	if (NULL != m_font)
	{
		FT_Done_Face(m_font->face);
		FT_Done_FreeType(m_font->library);
		delete m_font;
		m_font = NULL;
	}
}

bool TrueTypeFont::init(const uint8_t* _buffer, uint32_t _bufferSize, int32_t _fontIndex, uint32_t _pixelHeight)
{
	BX_CHECK(m_font == NULL, "TrueTypeFont already initialized");
	BX_CHECK( (_bufferSize > 256 && _bufferSize < 100000000), "TrueType buffer size is suspicious");
	BX_CHECK( (_pixelHeight > 4 && _pixelHeight < 128), "TrueType buffer size is suspicious");

	FTHolder* holder = new FTHolder;

	FT_Error error = FT_Init_FreeType(&holder->library);
	BX_WARN(!error, "FT_Init_FreeType failed.");

	if (error)
	{
		goto err0;
	}

	error = FT_New_Memory_Face(holder->library, _buffer, _bufferSize, _fontIndex, &holder->face);
	BX_WARN(!error, "FT_Init_FreeType failed.");

	if (error)
	{
		if (FT_Err_Unknown_File_Format == error)
		{
			goto err0;
		}

		goto err1;
	}

	error = FT_Select_Charmap(holder->face, FT_ENCODING_UNICODE);
	BX_WARN(!error, "FT_Init_FreeType failed.");

	if (error)
	{
		goto err2;
	}

	error = FT_Set_Pixel_Sizes(holder->face, 0, _pixelHeight);
	BX_WARN(!error, "FT_Init_FreeType failed.");

	if (error)
	{
		goto err2;
	}

	m_font = holder;
	return true;

err2:
	FT_Done_Face(holder->face);

err1:
	FT_Done_FreeType(holder->library);

err0:
	delete holder;
	return false;
}

FontInfo TrueTypeFont::getFontInfo()
{
	BX_CHECK(m_font != NULL, "TrueTypeFont not initialized");
	BX_CHECK(FT_IS_SCALABLE(m_font->face), "Font is unscalable");

	FT_Size_Metrics metrics = m_font->face->size->metrics;

	FontInfo outFontInfo;
	outFontInfo.scale = 1.0f;
	outFontInfo.ascender = metrics.ascender / 64.0f;
	outFontInfo.descender = metrics.descender / 64.0f;
	outFontInfo.lineGap = (metrics.height - metrics.ascender + metrics.descender) / 64.0f;
	outFontInfo.maxAdvanceWidth = metrics.max_advance/ 64.0f;

	outFontInfo.underlinePosition = FT_MulFix(m_font->face->underline_position, metrics.y_scale) / 64.0f;
	outFontInfo.underlineThickness = FT_MulFix(m_font->face->underline_thickness, metrics.y_scale) / 64.0f;
	return outFontInfo;
}

static void glyphInfoInit(GlyphInfo& _glyphInfo, FT_BitmapGlyph _bitmap, FT_GlyphSlot _slot, uint8_t* _dst, uint32_t _bpp)
{
	int32_t xx = _bitmap->left;
	int32_t yy = -_bitmap->top;
	int32_t ww = _bitmap->bitmap.width;
	int32_t hh = _bitmap->bitmap.rows;

	_glyphInfo.offset_x = (float)xx;
	_glyphInfo.offset_y = (float)yy;
	_glyphInfo.width = (float)ww;
	_glyphInfo.height = (float)hh;
	_glyphInfo.advance_x = (float)_slot->advance.x / 64.0f;
	_glyphInfo.advance_y = (float)_slot->advance.y / 64.0f;

	uint32_t dstPitch = ww * _bpp;

	uint8_t* src = _bitmap->bitmap.buffer;
	uint32_t srcPitch = _bitmap->bitmap.pitch;

	for (int32_t ii = 0; ii < hh; ++ii)
	{
		memcpy(_dst, src, dstPitch);

		_dst += dstPitch;
		src += srcPitch;
	}
}

bool TrueTypeFont::bakeGlyphAlpha(CodePoint _codePoint, GlyphInfo& _glyphInfo, uint8_t* _outBuffer)
{
	BX_CHECK(m_font != NULL, "TrueTypeFont not initialized");

	_glyphInfo.glyphIndex = FT_Get_Char_Index(m_font->face, _codePoint);

	FT_GlyphSlot slot = m_font->face->glyph;
	FT_Error error = FT_Load_Glyph(m_font->face, _glyphInfo.glyphIndex, FT_LOAD_DEFAULT);
	if (error)
	{
		return false;
	}

	FT_Glyph glyph;
	error = FT_Get_Glyph(slot, &glyph);
	if (error)
	{
		return false;
	}

	error = FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, 0, 1);
	if (error)
	{
		return false;
	}

	FT_BitmapGlyph bitmap = (FT_BitmapGlyph)glyph;

	glyphInfoInit(_glyphInfo, bitmap, slot, _outBuffer, 1);

	FT_Done_Glyph(glyph);
	return true;
}

bool TrueTypeFont::bakeGlyphSubpixel(CodePoint _codePoint, GlyphInfo& _glyphInfo, uint8_t* _outBuffer)
{
	BX_CHECK(m_font != NULL, "TrueTypeFont not initialized");

	_glyphInfo.glyphIndex = FT_Get_Char_Index(m_font->face, _codePoint);

	FT_GlyphSlot slot = m_font->face->glyph;
	FT_Error error = FT_Load_Glyph(m_font->face, _glyphInfo.glyphIndex, FT_LOAD_DEFAULT);
	if (error)
	{
		return false;
	}

	FT_Glyph glyph;
	error = FT_Get_Glyph(slot, &glyph);
	if (error)
	{
		return false;
	}

	error = FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_LCD, 0, 1);
	if (error)
	{
		return false;
	}

	FT_BitmapGlyph bitmap = (FT_BitmapGlyph)glyph;

	glyphInfoInit(_glyphInfo, bitmap, slot, _outBuffer, 3);
	FT_Done_Glyph(glyph);

	return true;
}

static void makeDistanceMap(const uint8_t* _img, uint8_t* _outImg, uint32_t _width, uint32_t _height)
{
#if USE_EDTAA3
	int16_t* xdist = (int16_t*)malloc(_width * _height * sizeof(int16_t) );
	int16_t* ydist = (int16_t*)malloc(_width * _height * sizeof(int16_t) );
	double* gx = (double*)calloc(_width * _height, sizeof(double) );
	double* gy = (double*)calloc(_width * _height, sizeof(double) );
	double* data = (double*)calloc(_width * _height, sizeof(double) );
	double* outside = (double*)calloc(_width * _height, sizeof(double) );
	double* inside = (double*)calloc(_width * _height, sizeof(double) );
	uint32_t ii;

	// Convert img into double (data)
	double img_min = 255, img_max = -255;
	for (ii = 0; ii < _width * _height; ++ii)
	{
		double v = _img[ii];
		data[ii] = v;
		if (v > img_max)
		{
			img_max = v;
		}

		if (v < img_min)
		{
			img_min = v;
		}
	}

	// Rescale image levels between 0 and 1
	for (ii = 0; ii < _width * _height; ++ii)
	{
		data[ii] = (_img[ii] - img_min) / (img_max - img_min);
	}

	// Compute outside = edtaa3(bitmap); % Transform background (0's)
	computegradient(data, _width, _height, gx, gy);
	edtaa3(data, gx, gy, _width, _height, xdist, ydist, outside);
	for (ii = 0; ii < _width * _height; ++ii)
	{
		if (outside[ii] < 0)
		{
			outside[ii] = 0.0;
		}
	}

	// Compute inside = edtaa3(1-bitmap); % Transform foreground (1's)
	memset(gx, 0, sizeof(double) * _width * _height);
	memset(gy, 0, sizeof(double) * _width * _height);
	for (ii = 0; ii < _width * _height; ++ii)
	{
		data[ii] = 1.0 - data[ii];
	}

	computegradient(data, _width, _height, gx, gy);
	edtaa3(data, gx, gy, _width, _height, xdist, ydist, inside);
	for (ii = 0; ii < _width * _height; ++ii)
	{
		if (inside[ii] < 0)
		{
			inside[ii] = 0.0;
		}
	}

	// distmap = outside - inside; % Bipolar distance field
	uint8_t* out = _outImg;
	for (ii = 0; ii < _width * _height; ++ii)
	{
		outside[ii] -= inside[ii];
		outside[ii] = 128 + outside[ii] * 16;

		if (outside[ii] < 0)
		{
			outside[ii] = 0;
		}

		if (outside[ii] > 255)
		{
			outside[ii] = 255;
		}

		out[ii] = 255 - (uint8_t) outside[ii];
	}

	free(xdist);
	free(ydist);
	free(gx);
	free(gy);
	free(data);
	free(outside);
	free(inside);
#else
	sdfBuild(_outImg, _width, 8.0f, _img, _width, _height, _width);
#endif // USE_EDTAA3
}

bool TrueTypeFont::bakeGlyphDistance(CodePoint _codePoint, GlyphInfo& _glyphInfo, uint8_t* _outBuffer)
{
	BX_CHECK(m_font != NULL, "TrueTypeFont not initialized");

	_glyphInfo.glyphIndex = FT_Get_Char_Index(m_font->face, _codePoint);

	FT_Int32 loadMode = FT_LOAD_DEFAULT | FT_LOAD_NO_HINTING;
	FT_Render_Mode renderMode = FT_RENDER_MODE_NORMAL;

	FT_GlyphSlot slot = m_font->face->glyph;
	FT_Error error = FT_Load_Glyph(m_font->face, _glyphInfo.glyphIndex, loadMode);
	if (error)
	{
		return false;
	}

	FT_Glyph glyph;
	error = FT_Get_Glyph(slot, &glyph);
	if (error)
	{
		return false;
	}

	error = FT_Glyph_To_Bitmap(&glyph, renderMode, 0, 1);
	if (error)
	{
		return false;
	}

	FT_BitmapGlyph bitmap = (FT_BitmapGlyph)glyph;

	int32_t ww = bitmap->bitmap.width;
	int32_t hh = bitmap->bitmap.rows;

	glyphInfoInit(_glyphInfo, bitmap, slot, _outBuffer, 1);

	FT_Done_Glyph(glyph);

	if (ww * hh > 0)
	{
		uint32_t dw = 6;
		uint32_t dh = 6;

		uint32_t nw = ww + dw * 2;
		uint32_t nh = hh + dh * 2;
		BX_CHECK(nw * nh < 128 * 128, "Buffer overflow (size %d)", nw * nh);

		uint32_t buffSize = nw * nh * sizeof(uint8_t);

		uint8_t* alphaImg = (uint8_t*)malloc(buffSize);
		memset(alphaImg, 0, nw * nh * sizeof(uint8_t) );

		//copy the original buffer to the temp one
		for (uint32_t ii = dh; ii < nh - dh; ++ii)
		{
			memcpy(alphaImg + ii * nw + dw, _outBuffer + (ii - dh) * ww, ww);
		}

		makeDistanceMap(alphaImg, _outBuffer, nw, nh);
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
		masterFontHandle.idx = bx::HandleAlloc::invalid;
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

FontManager::FontManager(uint32_t _textureSideWidth) 
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
	memset(buffer, 255, W * W * 4);

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
	BX_CHECK(id != bx::HandleAlloc::invalid, "Invalid handle used");
	m_cachedFiles[id].buffer = new uint8_t[_size];
	m_cachedFiles[id].bufferSize = _size;
	memcpy(m_cachedFiles[id].buffer, _buffer, _size);

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
		FontHandle invalid = { bx::HandleAlloc::invalid };
		return invalid;
	}

	uint16_t fontIdx = m_fontHandles.alloc();
	BX_CHECK(fontIdx != bx::HandleAlloc::invalid, "Invalid handle used");

	CachedFont& font = m_cachedFonts[fontIdx];
	font.trueTypeFont = ttf;
	font.fontInfo = ttf->getFontInfo();
	font.fontInfo.fontType = _fontType;
	font.fontInfo.pixelSize = _pixelSize;
	font.cachedGlyphs.clear();
	font.masterFontHandle.idx = bx::HandleAlloc::invalid;

	FontHandle handle = { fontIdx };
	return handle;
}

FontHandle FontManager::createScaledFontToPixelSize(FontHandle _baseFontHandle, uint32_t _pixelSize)
{
	BX_CHECK(bgfx::isValid(_baseFontHandle), "Invalid handle used");
	CachedFont& baseFont = m_cachedFonts[_baseFontHandle.idx];
	FontInfo& fontInfo = baseFont.fontInfo;

	FontInfo newFontInfo = fontInfo;
	newFontInfo.pixelSize = _pixelSize;
	newFontInfo.scale = (float)_pixelSize / (float) fontInfo.pixelSize;
	newFontInfo.ascender = (newFontInfo.ascender * newFontInfo.scale);
	newFontInfo.descender = (newFontInfo.descender * newFontInfo.scale);
	newFontInfo.lineGap = (newFontInfo.lineGap * newFontInfo.scale);
	newFontInfo.maxAdvanceWidth = (newFontInfo.maxAdvanceWidth * newFontInfo.scale);
	newFontInfo.underlineThickness = (newFontInfo.underlineThickness * newFontInfo.scale);
	newFontInfo.underlinePosition = (newFontInfo.underlinePosition * newFontInfo.scale);

	uint16_t fontIdx = m_fontHandles.alloc();
	BX_CHECK(fontIdx != bx::HandleAlloc::invalid, "Invalid handle used");

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
	_glyphInfo.regionIndex = m_atlas->addRegion( (uint16_t) ceil(_glyphInfo.width), (uint16_t) ceil(_glyphInfo.height), _data, AtlasRegion::TYPE_GRAY);
	return true;
}
