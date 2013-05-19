/*
 * Copyright 2013 Jeremie Roy. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "../common.h"

#include <bgfx.h>
#include <freetype/freetype.h>
#include <edtaa3/edtaa3func.cpp>
#include <wchar.h> // wcslen

#include "font_manager.h"
#include "../cube_atlas.h"

#if BGFX_CONFIG_USE_TINYSTL
namespace tinystl
{
	//struct bgfx_allocator
	//{
	//static void* static_allocate(size_t _bytes);
	//static void static_deallocate(void* _ptr, size_t /*_bytes*/);
	//};
} // namespace tinystl
//#	define TINYSTL_ALLOCATOR tinystl::bgfx_allocator
#   include <TINYSTL/unordered_map.h>
//#	include <TINYSTL/unordered_set.h>
namespace stl = tinystl;
#else
#   include <unordered_map>
namespace std
{ namespace tr1
{}
}
namespace stl
{
	using namespace std;
	using namespace std::tr1;
}
#endif // BGFX_CONFIG_USE_TINYSTL

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
	if (m_font != NULL)
	{
		FTHolder* holder = (FTHolder*) m_font;
		FT_Done_Face(holder->face);
		FT_Done_FreeType(holder->library);
		delete m_font;
		m_font = NULL;
	}
}

bool TrueTypeFont::init(const uint8_t* _buffer, uint32_t _bufferSize, int32_t _fontIndex, uint32_t _pixelHeight)
{
	BX_CHECK( (_bufferSize > 256 && _bufferSize < 100000000), "TrueType buffer size is suspicious");
	BX_CHECK( (_pixelHeight > 4 && _pixelHeight < 128), "TrueType buffer size is suspicious");

	BX_CHECK(m_font == NULL, "TrueTypeFont already initialized");

	FTHolder* holder = new FTHolder();

	// Initialize Freetype library
	FT_Error error = FT_Init_FreeType(&holder->library);
	if (error)
	{
		delete holder;
		return false;
	}

	error = FT_New_Memory_Face(holder->library, _buffer, _bufferSize, _fontIndex, &holder->face);
	if (error == FT_Err_Unknown_File_Format)
	{
		// the font file could be opened and read, but it appears
		//that its font format is unsupported
		FT_Done_FreeType(holder->library);
		delete holder;
		return false;
	}
	else if (error)
	{
		// another error code means that the font file could not
		// be opened or read, or simply that it is broken...
		FT_Done_FreeType(holder->library);
		delete holder;
		return false;
	}

	// Select unicode charmap
	error = FT_Select_Charmap(holder->face, FT_ENCODING_UNICODE);
	if (error)
	{
		FT_Done_Face(holder->face);
		FT_Done_FreeType(holder->library);
		return false;
	}

	//set size in pixels
	error = FT_Set_Pixel_Sizes(holder->face, 0, _pixelHeight);
	if (error)
	{
		FT_Done_Face(holder->face);
		FT_Done_FreeType(holder->library);
		return false;
	}

	m_font = holder;
	return true;
}

FontInfo TrueTypeFont::getFontInfo()
{
	BX_CHECK(m_font != NULL, "TrueTypeFont not initialized");
	FTHolder* holder = (FTHolder*) m_font;

	BX_CHECK(FT_IS_SCALABLE(holder->face), "Font is unscalable");

	FT_Size_Metrics metrics = holder->face->size->metrics;

	FontInfo outFontInfo;
	outFontInfo.scale = 1.0f;
	outFontInfo.ascender = metrics.ascender / 64.0f;
	outFontInfo.descender = metrics.descender / 64.0f;
	outFontInfo.lineGap = (metrics.height - metrics.ascender + metrics.descender) / 64.0f;

	outFontInfo.underlinePosition = FT_MulFix(holder->face->underline_position, metrics.y_scale) / 64.0f;
	outFontInfo.underlineThickness = FT_MulFix(holder->face->underline_thickness, metrics.y_scale) / 64.0f;
	return outFontInfo;
}

bool TrueTypeFont::bakeGlyphAlpha(CodePoint _codePoint, GlyphInfo& _glyphInfo, uint8_t* _outBuffer)
{
	BX_CHECK(m_font != NULL, "TrueTypeFont not initialized");
	FTHolder* holder = (FTHolder*) m_font;

	_glyphInfo.glyphIndex = FT_Get_Char_Index(holder->face, _codePoint);

	FT_GlyphSlot slot = holder->face->glyph;
	FT_Error error = FT_Load_Glyph(holder->face, _glyphInfo.glyphIndex, FT_LOAD_DEFAULT);
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

	int32_t x = bitmap->left;
	int32_t y = -bitmap->top;
	int32_t w = bitmap->bitmap.width;
	int32_t h = bitmap->bitmap.rows;

	_glyphInfo.offset_x = (float) x;
	_glyphInfo.offset_y = (float) y;
	_glyphInfo.width = (float) w;
	_glyphInfo.height = (float) h;
	_glyphInfo.advance_x = (float)slot->advance.x / 64.0f;
	_glyphInfo.advance_y = (float)slot->advance.y / 64.0f;

	int32_t charsize = 1;
	int32_t depth = 1;
	int32_t stride = bitmap->bitmap.pitch;
	for (int32_t ii = 0; ii < h; ++ii)
	{
		memcpy(_outBuffer + (ii * w) * charsize * depth,
			bitmap->bitmap.buffer + (ii * stride) * charsize, w * charsize * depth);
	}

	FT_Done_Glyph(glyph);
	return true;
}

bool TrueTypeFont::bakeGlyphSubpixel(CodePoint _codePoint, GlyphInfo& _glyphInfo, uint8_t* _outBuffer)
{
	BX_CHECK(m_font != NULL, "TrueTypeFont not initialized");
	FTHolder* holder = (FTHolder*) m_font;

	_glyphInfo.glyphIndex = FT_Get_Char_Index(holder->face, _codePoint);

	FT_GlyphSlot slot = holder->face->glyph;
	FT_Error error = FT_Load_Glyph(holder->face, _glyphInfo.glyphIndex, FT_LOAD_DEFAULT);
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
	int32_t x = bitmap->left;
	int32_t y = -bitmap->top;
	int32_t w = bitmap->bitmap.width;
	int32_t h = bitmap->bitmap.rows;

	_glyphInfo.offset_x = (float) x;
	_glyphInfo.offset_y = (float) y;
	_glyphInfo.width = (float) w;
	_glyphInfo.height = (float) h;
	_glyphInfo.advance_x = (float)slot->advance.x / 64.0f;
	_glyphInfo.advance_y = (float)slot->advance.y / 64.0f;
	int32_t charsize = 1;
	int32_t depth = 3;
	int32_t stride = bitmap->bitmap.pitch;
	for (int32_t ii = 0; ii < h; ++ii)
	{
		memcpy(_outBuffer + (ii * w) * charsize * depth,
			bitmap->bitmap.buffer + (ii * stride) * charsize, w * charsize * depth);
	}

	FT_Done_Glyph(glyph);
	return true;
}

void make_distance_map(uint8_t* _img, uint8_t* _outImg, uint32_t _width, uint32_t _height)
{
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
}

bool TrueTypeFont::bakeGlyphDistance(CodePoint _codePoint, GlyphInfo& _glyphInfo, uint8_t* _outBuffer)
{
	BX_CHECK(m_font != NULL, "TrueTypeFont not initialized");
	FTHolder* holder = (FTHolder*) m_font;

	_glyphInfo.glyphIndex = FT_Get_Char_Index(holder->face, _codePoint);

	FT_Int32 loadMode = FT_LOAD_DEFAULT | FT_LOAD_NO_HINTING;
	FT_Render_Mode renderMode = FT_RENDER_MODE_NORMAL;

	FT_GlyphSlot slot = holder->face->glyph;
	FT_Error error = FT_Load_Glyph(holder->face, _glyphInfo.glyphIndex, loadMode);
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

	int32_t x = bitmap->left;
	int32_t y = -bitmap->top;
	int32_t w = bitmap->bitmap.width;
	int32_t h = bitmap->bitmap.rows;

	_glyphInfo.offset_x = (float) x;
	_glyphInfo.offset_y = (float) y;
	_glyphInfo.width = (float) w;
	_glyphInfo.height = (float) h;
	_glyphInfo.advance_x = (float)slot->advance.x / 64.0f;
	_glyphInfo.advance_y = (float)slot->advance.y / 64.0f;

	int32_t charsize = 1;
	int32_t depth = 1;
	int32_t stride = bitmap->bitmap.pitch;

	for (int32_t ii = 0; ii < h; ++ii)
	{
		memcpy(_outBuffer + (ii * w) * charsize * depth,
			bitmap->bitmap.buffer + (ii * stride) * charsize, w * charsize * depth);
	}

	FT_Done_Glyph(glyph);

	if (w * h > 0)
	{
		uint32_t dw = 6;
		uint32_t dh = 6;
		if (dw < 2)
		{
			dw = 2;
		}

		if (dh < 2)
		{
			dh = 2;
		}

		uint32_t nw = w + dw * 2;
		uint32_t nh = h + dh * 2;
		BX_CHECK(nw * nh < 128 * 128, "buffer overflow");
		uint32_t buffSize = nw * nh * sizeof(uint8_t);

		uint8_t* alphaImg = (uint8_t*)  malloc(buffSize);
		memset(alphaImg, 0, nw * nh * sizeof(uint8_t) );

		//copy the original buffer to the temp one
		for (uint32_t ii = dh; ii < nh - dh; ++ii)
		{
			memcpy(alphaImg + ii * nw + dw, _outBuffer + (ii - dh) * w, w);
		}

		make_distance_map(alphaImg, _outBuffer, nw, nh);
		free(alphaImg);

		_glyphInfo.offset_x -= (float) dw;
		_glyphInfo.offset_y -= (float) dh;
		_glyphInfo.width = (float) nw;
		_glyphInfo.height = (float) nh;
	}

	return true;
}

typedef stl::unordered_map<CodePoint, GlyphInfo> GlyphHashMap;

// cache font data
struct FontManager::CachedFont
{
	CachedFont()
	{
		trueTypeFont = NULL; masterFontHandle.idx = -1;
	}
	FontInfo fontInfo;
	GlyphHashMap cachedGlyphs;
	TrueTypeFont* trueTypeFont;
	// an handle to a master font in case of sub distance field font
	FontHandle masterFontHandle;
	int16_t padding;
};

const uint16_t MAX_OPENED_FILES = 64;
const uint16_t MAX_OPENED_FONT = 64;
const uint32_t MAX_FONT_BUFFER_SIZE = 512 * 512 * 4;

FontManager::FontManager(Atlas* _atlas)
	: m_ownAtlas(false)
	, m_atlas(_atlas)
	, m_fontHandles(MAX_OPENED_FONT)
	, m_filesHandles(MAX_OPENED_FILES)
{
	init();
}

FontManager::FontManager(uint32_t _textureSideWidth) 
	: m_ownAtlas(true)
	, m_atlas(new Atlas(_textureSideWidth) )
	, m_fontHandles(MAX_OPENED_FONT)
	, m_filesHandles(MAX_OPENED_FILES)
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
	delete[] m_cachedFonts;

	BX_CHECK(m_filesHandles.getNumHandles() == 0, "All the font files must be destroyed before destroying the manager");
	delete[] m_cachedFiles;

	delete[] m_buffer;

	if (m_ownAtlas)
	{
		delete m_atlas;
	}
}

TrueTypeHandle FontManager::loadTrueTypeFromFile(const char* _fontPath)
{
	FILE* pFile;
	pFile = fopen(_fontPath, "rb");
	if (pFile == NULL)
	{
		TrueTypeHandle invalid = BGFX_INVALID_HANDLE;
		return invalid;
	}

	// Go to the end of the file.
	if (fseek(pFile, 0L, SEEK_END) == 0)
	{
		// Get the size of the file.
		long bufsize = ftell(pFile);
		if (bufsize == -1)
		{
			fclose(pFile);
			TrueTypeHandle invalid = BGFX_INVALID_HANDLE;
			return invalid;
		}

		uint8_t* buffer = new uint8_t[bufsize];

		// Go back to the start of the file.
		fseek(pFile, 0L, SEEK_SET);

		// Read the entire file into memory.
		uint32_t newLen = fread( (void*)buffer, sizeof(char), bufsize, pFile);
		if (newLen == 0)
		{
			fclose(pFile);
			delete[] buffer;
			TrueTypeHandle invalid = BGFX_INVALID_HANDLE;
			return invalid;
		}

		fclose(pFile);

		uint16_t id = m_filesHandles.alloc();
		BX_CHECK(id != bx::HandleAlloc::invalid, "No more room for files");
		m_cachedFiles[id].buffer = buffer;
		m_cachedFiles[id].bufferSize = bufsize;
		TrueTypeHandle ret = {id};
		return ret;
	}

	TrueTypeHandle invalid = BGFX_INVALID_HANDLE;
	return invalid;
}

TrueTypeHandle FontManager::loadTrueTypeFromMemory(const uint8_t* _buffer, uint32_t _size)
{
	uint16_t id = m_filesHandles.alloc();
	BX_CHECK(id != bx::HandleAlloc::invalid, "Invalid handle used");
	m_cachedFiles[id].buffer = new uint8_t[_size];
	m_cachedFiles[id].bufferSize = _size;
	memcpy(m_cachedFiles[id].buffer, _buffer, _size);

	TrueTypeHandle ret = {id};
	return ret;
}

void FontManager::unloadTrueType(TrueTypeHandle _handle)
{
	BX_CHECK(bgfx::invalidHandle != _handle.idx, "Invalid handle used");
	delete m_cachedFiles[_handle.idx].buffer;
	m_cachedFiles[_handle.idx].bufferSize = 0;
	m_cachedFiles[_handle.idx].buffer = NULL;
	m_filesHandles.free(_handle.idx);
}

FontHandle FontManager::createFontByPixelSize(TrueTypeHandle _tt_handle, uint32_t _typefaceIndex, uint32_t _pixelSize, uint32_t _fontType)
{
	BX_CHECK(bgfx::invalidHandle != _tt_handle.idx, "Invalid handle used");

	TrueTypeFont* ttf = new TrueTypeFont();
	if (!ttf->init(m_cachedFiles[_tt_handle.idx].buffer, m_cachedFiles[_tt_handle.idx].bufferSize, _typefaceIndex, _pixelSize) )
	{
		delete ttf;
		FontHandle invalid = BGFX_INVALID_HANDLE;
		return invalid;
	}

	uint16_t fontIdx = m_fontHandles.alloc();
	BX_CHECK(fontIdx != bx::HandleAlloc::invalid, "Invalid handle used");

	m_cachedFonts[fontIdx].trueTypeFont = ttf;
	m_cachedFonts[fontIdx].fontInfo = ttf->getFontInfo();
	m_cachedFonts[fontIdx].fontInfo.fontType = _fontType;
	m_cachedFonts[fontIdx].fontInfo.pixelSize = _pixelSize;
	m_cachedFonts[fontIdx].cachedGlyphs.clear();
	m_cachedFonts[fontIdx].masterFontHandle.idx = -1;
	FontHandle ret = {fontIdx};
	return ret;
}

FontHandle FontManager::createScaledFontToPixelSize(FontHandle _baseFontHandle, uint32_t _pixelSize)
{
	BX_CHECK(bgfx::invalidHandle != _baseFontHandle.idx, "Invalid handle used");
	CachedFont& font = m_cachedFonts[_baseFontHandle.idx];
	FontInfo& fontInfo = font.fontInfo;

	FontInfo newFontInfo = fontInfo;
	newFontInfo.pixelSize = _pixelSize;
	newFontInfo.scale = (float)_pixelSize / (float) fontInfo.pixelSize;
	newFontInfo.ascender = (newFontInfo.ascender * newFontInfo.scale);
	newFontInfo.descender = (newFontInfo.descender * newFontInfo.scale);
	newFontInfo.lineGap = (newFontInfo.lineGap * newFontInfo.scale);
	newFontInfo.underlineThickness = (newFontInfo.underlineThickness * newFontInfo.scale);
	newFontInfo.underlinePosition = (newFontInfo.underlinePosition * newFontInfo.scale);

	uint16_t fontIdx = m_fontHandles.alloc();
	BX_CHECK(fontIdx != bx::HandleAlloc::invalid, "Invalid handle used");
	m_cachedFonts[fontIdx].cachedGlyphs.clear();
	m_cachedFonts[fontIdx].fontInfo = newFontInfo;
	m_cachedFonts[fontIdx].trueTypeFont = NULL;
	m_cachedFonts[fontIdx].masterFontHandle = _baseFontHandle;
	FontHandle ret = {fontIdx};
	return ret;
}

void FontManager::destroyFont(FontHandle _handle)
{
	BX_CHECK(bgfx::invalidHandle != _handle.idx, "Invalid handle used");

	if (m_cachedFonts[_handle.idx].trueTypeFont != NULL)
	{
		delete m_cachedFonts[_handle.idx].trueTypeFont;
		m_cachedFonts[_handle.idx].trueTypeFont = NULL;
	}

	m_cachedFonts[_handle.idx].cachedGlyphs.clear();
	m_fontHandles.free(_handle.idx);
}

bool FontManager::preloadGlyph(FontHandle _handle, const wchar_t* _string)
{
	BX_CHECK(bgfx::invalidHandle != _handle.idx, "Invalid handle used");
	CachedFont& font = m_cachedFonts[_handle.idx];

	//if truetype present
	if (font.trueTypeFont != NULL)
	{
		//parse string
		for (uint32_t ii = 0, end = wcslen(_string); ii < end; ++ii)
		{
			//if glyph cached, continue
			CodePoint codePoint = _string[ii];
			if (!preloadGlyph(_handle, codePoint) )
			{
				return false;
			}
		}

		return true;
	}

	return false;
}

bool FontManager::preloadGlyph(FontHandle _handle, CodePoint _codePoint)
{
	BX_CHECK(bgfx::invalidHandle != _handle.idx, "Invalid handle used");
	CachedFont& font = m_cachedFonts[_handle.idx];
	FontInfo& fontInfo = font.fontInfo;
	//check if glyph not already present
	GlyphHashMap::iterator iter = font.cachedGlyphs.find(_codePoint);
	if (iter != font.cachedGlyphs.end() )
	{
		return true;
	}

	//if truetype present
	if (font.trueTypeFont != NULL)
	{
		GlyphInfo glyphInfo;

		//bake glyph as bitmap to buffer
		switch (font.fontInfo.fontType)
		{
		case FONT_TYPE_ALPHA:
			font.trueTypeFont->bakeGlyphAlpha(_codePoint, glyphInfo, m_buffer);
			break;

			//case FONT_TYPE_LCD:
			//font.m_trueTypeFont->bakeGlyphSubpixel(codePoint, glyphInfo, m_buffer);
			//break;
		case FONT_TYPE_DISTANCE:
			font.trueTypeFont->bakeGlyphDistance(_codePoint, glyphInfo, m_buffer);
			break;

		case FONT_TYPE_DISTANCE_SUBPIXEL:
			font.trueTypeFont->bakeGlyphDistance(_codePoint, glyphInfo, m_buffer);
			break;

		default:
			BX_CHECK(false, "TextureType not supported yet");
		}

		//copy bitmap to texture
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

		// store cached glyph
		font.cachedGlyphs[_codePoint] = glyphInfo;
		return true;
	}
	else
	{
		//retrieve glyph from parent font if any
		if (font.masterFontHandle.idx != bgfx::invalidHandle)
		{
			if (preloadGlyph(font.masterFontHandle, _codePoint) )
			{
				GlyphInfo glyphInfo;
				getGlyphInfo(font.masterFontHandle, _codePoint, glyphInfo);

				glyphInfo.advance_x = (glyphInfo.advance_x * fontInfo.scale);
				glyphInfo.advance_y = (glyphInfo.advance_y * fontInfo.scale);
				glyphInfo.offset_x = (glyphInfo.offset_x * fontInfo.scale);
				glyphInfo.offset_y = (glyphInfo.offset_y * fontInfo.scale);
				glyphInfo.height = (glyphInfo.height * fontInfo.scale);
				glyphInfo.width = (glyphInfo.width * fontInfo.scale);

				// store cached glyph
				font.cachedGlyphs[_codePoint] = glyphInfo;
				return true;
			}
		}
	}

	return false;
}

const FontInfo& FontManager::getFontInfo(FontHandle _handle)
{
	BX_CHECK(bgfx::invalidHandle != _handle.idx, "Invalid handle used");
	return m_cachedFonts[_handle.idx].fontInfo;
}

bool FontManager::getGlyphInfo(FontHandle _handle, CodePoint _codePoint, GlyphInfo& _outInfo)
{
	GlyphHashMap::iterator iter = m_cachedFonts[_handle.idx].cachedGlyphs.find(_codePoint);
	if (iter == m_cachedFonts[_handle.idx].cachedGlyphs.end() )
	{
		if (preloadGlyph(_handle, _codePoint) )
		{
			iter = m_cachedFonts[_handle.idx].cachedGlyphs.find(_codePoint);
		}
		else
		{
			return false;
		}
	}

	_outInfo = iter->second;
	return true;
}

bool FontManager::addBitmap(GlyphInfo& _glyphInfo, const uint8_t* _data)
{
	_glyphInfo.regionIndex = m_atlas->addRegion( (uint16_t) ceil(_glyphInfo.width), (uint16_t) ceil(_glyphInfo.height), _data, AtlasRegion::TYPE_GRAY);
	return true;
}
