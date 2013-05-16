/*
 * Copyright 2013 Jeremie Roy. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __FONT_MANAGER_H__
#define __FONT_MANAGER_H__

#include <bgfx.h>
#include <bx/handlealloc.h>

class Atlas;
enum FontType
{
	FONT_TYPE_ALPHA = 0x00000100,     // L8
	//FONT_TYPE_LCD      = 0x00000200,  // BGRA8
	//FONT_TYPE_RGBA     = 0x00000300,  // BGRA8
	FONT_TYPE_DISTANCE = 0x00000400,   // L8
	FONT_TYPE_DISTANCE_SUBPIXEL = 0x00000500   // L8
};

struct FontInfo
{
	//the font height in pixel
	uint16_t pixelSize;
	/// Rendering type used for the font
	int16_t fontType;

	/// The pixel extents above the baseline in pixels (typically positive)
	float ascender;
	/// The extents below the baseline in pixels (typically negative)
	float descender;
	/// The spacing in pixels between one row's descent and the next row's ascent
	float lineGap;
	/// The thickness of the under/hover/striketrough line in pixels
	float underline_thickness;
	/// The position of the underline relatively to the baseline
	float underline_position;

	//scale to apply to glyph data
	float scale;
};

// Glyph metrics:
// --------------
//
//                       xmin                     xmax
//                        |                         |
//                        |<-------- width -------->|
//                        |                         |
//              |         +-------------------------+----------------- ymax
//              |         |    ggggggggg   ggggg    |     ^        ^
//              |         |   g:::::::::ggg::::g    |     |        |
//              |         |  g:::::::::::::::::g    |     |        |
//              |         | g::::::ggggg::::::gg    |     |        |
//              |         | g:::::g     g:::::g     |     |        |
//    offset_x -|-------->| g:::::g     g:::::g     |  offset_y    |
//              |         | g:::::g     g:::::g     |     |        |
//              |         | g::::::g    g:::::g     |     |        |
//              |         | g:::::::ggggg:::::g     |     |        |
//              |         |  g::::::::::::::::g     |     |      height
//              |         |   gg::::::::::::::g     |     |        |
//  baseline ---*---------|---- gggggggg::::::g-----*--------      |
//            / |         |             g:::::g     |              |
//     origin   |         | gggggg      g:::::g     |              |
//              |         | g:::::gg   gg:::::g     |              |
//              |         |  g::::::ggg:::::::g     |              |
//              |         |   gg:::::::::::::g      |              |
//              |         |     ggg::::::ggg        |              |
//              |         |         gggggg          |              v
//              |         +-------------------------+----------------- ymin
//              |                                   |
//              |------------- advance_x ---------->|

/// Unicode value of a character
typedef int32_t CodePoint_t;

/// A structure that describe a glyph.
struct GlyphInfo
{
	/// Index for faster retrieval
	int32_t glyphIndex;

	/// Glyph's width in pixels.
	float width;

	/// Glyph's height in pixels.
	float height;

	/// Glyph's left offset in pixels
	float offset_x;

	/// Glyph's top offset in pixels
	/// Remember that this is the distance from the baseline to the top-most
	/// glyph scan line, upwards y coordinates being positive.
	float offset_y;

	/// For horizontal text layouts, this is the unscaled horizontal distance in pixels
	/// used to increment the pen position when the glyph is drawn as part of a string of text.
	float advance_x;

	/// For vertical text layouts, this is the unscaled vertical distance in pixels
	/// used to increment the pen position when the glyph is drawn as part of a string of text.
	float advance_y;

	/// region index in the atlas storing textures
	uint16_t regionIndex;
	///32 bits alignment
	int16_t padding;
};

BGFX_HANDLE(TrueTypeHandle);
BGFX_HANDLE(FontHandle);

class FontManager
{
public:
	/// create the font manager using an external cube atlas (doesn't take ownership of the atlas)
	FontManager(Atlas* _atlas);
	/// create the font manager and create the texture cube as BGRA8 with linear filtering
	FontManager(uint32_t _textureSideWidth = 512);

	~FontManager();

	/// retrieve the atlas used by the font manager (e.g. to add stuff to it)
	Atlas* getAtlas()
	{
		return m_atlas;
	}

	/// load a TrueType font from a file path
	/// @return invalid handle if the loading fail
	TrueTypeHandle loadTrueTypeFromFile(const char* _fontPath);

	/// load a TrueType font from a given buffer.
	/// the buffer is copied and thus can be freed or reused after this call
	/// @return invalid handle if the loading fail
	TrueTypeHandle loadTrueTypeFromMemory(const uint8_t* _buffer, uint32_t _size);

	/// unload a TrueType font (free font memory) but keep loaded glyphs
	void unloadTrueType(TrueTypeHandle _handle);

	/// return a font whose height is a fixed pixel size
	FontHandle createFontByPixelSize(TrueTypeHandle _handle, uint32_t _typefaceIndex, uint32_t _pixelSize, FontType _fontType = FONT_TYPE_ALPHA);

	/// return a scaled child font whose height is a fixed pixel size
	FontHandle createScaledFontToPixelSize(FontHandle _baseFontHandle, uint32_t _pixelSize);

	/// load a baked font (the set of glyph is fixed)
	/// @return INVALID_HANDLE if the loading fail
	FontHandle loadBakedFontFromFile(const char* _imagePath, const char* _descriptorPath);

	/// load a baked font (the set of glyph is fixed)
	/// @return INVALID_HANDLE if the loading fail
	FontHandle loadBakedFontFromMemory(const uint8_t* _imageBuffer, uint32_t _imageSize, const uint8_t* _descriptorBuffer, uint32_t _descriptorSize);

	/// destroy a font (truetype or baked)
	void destroyFont(FontHandle _handle);

	/// Preload a set of glyphs from a TrueType file
	/// @return true if every glyph could be preloaded, false otherwise
	/// if the Font is a baked font, this only do validation on the characters
	bool preloadGlyph(FontHandle _handle, const wchar_t* _string);

	/// Preload a single glyph, return true on success
	bool preloadGlyph(FontHandle _handle, CodePoint_t _character);

	/// bake a font to disk (the set of preloaded glyph)
	/// @return true if the baking succeed, false otherwise
	bool saveBakedFont(FontHandle _handle, const char* _fontDirectory, const char* _fontName);

	/// return the font descriptor of a font
	/// @remark the handle is required to be valid
	const FontInfo& getFontInfo(FontHandle _handle);

	/// Return the rendering informations about the glyph region
	/// Load the glyph from a TrueType font if possible
	/// @return true if the Glyph is available
	bool getGlyphInfo(FontHandle _handle, CodePoint_t _codePoint, GlyphInfo& _outInfo);

	GlyphInfo& getBlackGlyph()
	{
		return m_blackGlyph;
	}

	class TrueTypeFont;         //public to shut off Intellisense warning
private:

	struct CachedFont;
	struct CachedFile
	{
		uint8_t* buffer;
		uint32_t bufferSize;
	};

	void init();
	bool addBitmap(GlyphInfo& _glyphInfo, const uint8_t* _data);

	bool m_ownAtlas;
	Atlas* m_atlas;

	bx::HandleAlloc m_fontHandles;
	CachedFont* m_cachedFonts;

	bx::HandleAlloc m_filesHandles;
	CachedFile* m_cachedFiles;

	GlyphInfo m_blackGlyph;

	//temporary buffer to raster glyph
	uint8_t* m_buffer;
};

#endif // __FONT_MANAGER_H__
