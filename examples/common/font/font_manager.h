/*
 * Copyright 2013 Jeremie Roy. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __FONT_MANAGER_H__
#define __FONT_MANAGER_H__

#include <bx/handlealloc.h>
#include <bgfx.h>

class Atlas;

#define FONT_TYPE_ALPHA             UINT32_C(0x00000100) // L8
// #define FONT_TYPE_LCD               UINT32_C(0x00000200) // BGRA8
// #define FONT_TYPE_RGBA              UINT32_C(0x00000300) // BGRA8
#define FONT_TYPE_DISTANCE          UINT32_C(0x00000400) // L8
#define FONT_TYPE_DISTANCE_SUBPIXEL UINT32_C(0x00000500) // L8

struct FontInfo
{
	/// The font height in pixel.
	uint16_t pixelSize;
	/// Rendering type used for the font.
	int16_t fontType;

	/// The pixel extents above the baseline in pixels (typically positive).
	float ascender;
	/// The extents below the baseline in pixels (typically negative).
	float descender;
	/// The spacing in pixels between one row's descent and the next row's ascent.
	float lineGap;
	/// This field gives the maximum horizontal cursor advance for all glyphs in the font. 
	float maxAdvanceWidth;
	/// The thickness of the under/hover/strike-trough line in pixels.
	float underlineThickness;
	/// The position of the underline relatively to the baseline.
	float underlinePosition;

	/// Scale to apply to glyph data.
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
typedef int32_t CodePoint;

/// A structure that describe a glyph.
struct GlyphInfo
{
	/// Index for faster retrieval.
	int32_t glyphIndex;

	/// Glyph's width in pixels.
	float width;

	/// Glyph's height in pixels.
	float height;

	/// Glyph's left offset in pixels
	float offset_x;

	/// Glyph's top offset in pixels.
	///
	/// @remark This is the distance from the baseline to the top-most glyph
	///   scan line, upwards y coordinates being positive.
	float offset_y;

	/// For horizontal text layouts, this is the unscaled horizontal
	/// distance in pixels used to increment the pen position when the 
	/// glyph is drawn as part of a string of text.
	float advance_x;

	/// For vertical text layouts, this is the unscaled vertical distance
	/// in pixels used to increment the pen position when the glyph is 
	/// drawn as part of a string of text.
	float advance_y;

	/// Region index in the atlas storing textures.
	uint16_t regionIndex;
};

BGFX_HANDLE(TrueTypeHandle);
BGFX_HANDLE(FontHandle);

class FontManager
{
public:
	/// Create the font manager using an external cube atlas (doesn't take
	/// ownership of the atlas).
	FontManager(Atlas* _atlas);

	/// Create the font manager and create the texture cube as BGRA8 with
	/// linear filtering.
	FontManager(uint32_t _textureSideWidth = 512);

	~FontManager();

	/// Retrieve the atlas used by the font manager (e.g. to add stuff to it)
	Atlas* getAtlas()
	{
		return m_atlas;
	}

	/// Load a TrueType font from a file path.
	///
	/// @return INVALID_HANDLE if the loading fail.
	TrueTypeHandle loadTrueTypeFromFile(const char* _fontPath);

	/// Load a TrueType font from a given buffer. The buffer is copied and 
	/// thus can be freed or reused after this call.
	///
	/// @return invalid handle if the loading fail
	TrueTypeHandle loadTrueTypeFromMemory(const uint8_t* _buffer, uint32_t _size);

	/// Unload a TrueType font (free font memory) but keep loaded glyphs.
	void unloadTrueType(TrueTypeHandle _handle);

	/// Return a font whose height is a fixed pixel size.
	FontHandle createFontByPixelSize(TrueTypeHandle _handle, uint32_t _typefaceIndex, uint32_t _pixelSize, uint32_t _fontType = FONT_TYPE_ALPHA);

	/// Return a scaled child font whose height is a fixed pixel size.
	FontHandle createScaledFontToPixelSize(FontHandle _baseFontHandle, uint32_t _pixelSize);

	/// destroy a font (truetype or baked)
	void destroyFont(FontHandle _handle);

	/// Preload a set of glyphs from a TrueType file.
	///
	/// @return True if every glyph could be preloaded, false otherwise if 
	///   the Font is a baked font, this only do validation on the characters.
	bool preloadGlyph(FontHandle _handle, const wchar_t* _string);

	/// Preload a single glyph, return true on success.
	bool preloadGlyph(FontHandle _handle, CodePoint _character);

	/// Bake a font to disk (the set of preloaded glyph).
	///
	/// @return true if the baking succeed, false otherwise
	bool saveBakedFont(FontHandle _handle, const char* _fontDirectory, const char* _fontName);

	/// Return the font descriptor of a font.
	///
	/// @remark the handle is required to be valid
	const FontInfo& getFontInfo(FontHandle _handle) const;

	/// Return the rendering informations about the glyph region. Load the 
	/// glyph from a TrueType font if possible
	///
	/// @return True if the Glyph is available.
	bool getGlyphInfo(FontHandle _handle, CodePoint _codePoint, GlyphInfo& _outInfo);

	GlyphInfo& getBlackGlyph()
	{
		return m_blackGlyph;
	}

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
