/* Copyright 2013 Jeremie Roy. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
*/
#include "font_manager.h"
#include "../cube_atlas.h"

#pragma warning( push )
#pragma warning( disable: 4146 )
#pragma warning( disable: 4700 )
#pragma warning( disable: 4100 )
#pragma warning( disable: 4701 )
#include "../../../3rdparty/freetype/freetype.h"
#pragma warning( pop )

#include "../../../3rdparty/edtaa3/edtaa3func.h"
#include "../../../3rdparty/edtaa3/edtaa3func.cpp"
#include <math.h>
#include <assert.h>


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
#	include <TINYSTL/unordered_map.h>
//#	include <TINYSTL/unordered_set.h>
namespace stl = tinystl;
#else
#	include <unordered_map>
namespace std { namespace tr1 {} }
namespace stl {
	using namespace std;
	using namespace std::tr1;
}
#endif // BGFX_CONFIG_USE_TINYSTL

class FontManager::TrueTypeFont
{
public:	
	TrueTypeFont();
	~TrueTypeFont();

	/// Initialize from  an external buffer
	/// @remark The ownership of the buffer is external, and you must ensure it stays valid up to this object lifetime
	/// @return true if the initialization succeed
    bool init(const uint8_t* _buffer, uint32_t _bufferSize, int32_t _fontIndex, uint32_t _pixelHeight );
	
	/// return the font descriptor of the current font
	FontInfo getFontInfo();
	
	/// raster a glyph as 8bit alpha to a memory buffer
	/// update the GlyphInfo according to the raster strategy
	/// @ remark buffer min size: glyphInfo.m_width * glyphInfo * height * sizeof(char)
    bool bakeGlyphAlpha(CodePoint_t _codePoint, GlyphInfo& _outGlyphInfo, uint8_t* _outBuffer);

	/// raster a glyph as 32bit subpixel rgba to a memory buffer
	/// update the GlyphInfo according to the raster strategy
	/// @ remark buffer min size: glyphInfo.m_width * glyphInfo * height * sizeof(uint32_t)
    bool bakeGlyphSubpixel(CodePoint_t _codePoint, GlyphInfo& _outGlyphInfo, uint8_t* _outBuffer);

	/// raster a glyph as 8bit signed distance to a memory buffer
	/// update the GlyphInfo according to the raster strategy
	/// @ remark buffer min size: glyphInfo.m_width * glyphInfo * height * sizeof(char)
	bool bakeGlyphDistance(CodePoint_t _codePoint, GlyphInfo& _outGlyphInfo, uint8_t* _outBuffer);
private:
	void* m_font;
};


struct FTHolder
{
	FT_Library m_library;
	FT_Face m_face;
};
FontManager::TrueTypeFont::TrueTypeFont(): m_font(NULL)
{	
}

FontManager::TrueTypeFont::~TrueTypeFont()
{
	if(m_font!=NULL)
	{
		FTHolder* holder = (FTHolder*) m_font;
		FT_Done_Face( holder->m_face );
        FT_Done_FreeType( holder->m_library );
		delete m_font;
		m_font = NULL;
	}
}

bool FontManager::TrueTypeFont::init(const uint8_t* _buffer, uint32_t _bufferSize, int32_t _fontIndex, uint32_t _pixelHeight)
{
	assert((_bufferSize > 256 && _bufferSize < 100000000) && "TrueType buffer size is suspicious");
	assert((_pixelHeight > 4 && _pixelHeight < 128) && "TrueType buffer size is suspicious");
	
	assert(m_font == NULL && "TrueTypeFont already initialized" );
	
	FTHolder* holder = new FTHolder();	

	// Initialize Freetype library
	FT_Error error = FT_Init_FreeType( &holder->m_library );
	if( error)
	{
		delete holder;
		return false;
	}

	error = FT_New_Memory_Face( holder->m_library, _buffer, _bufferSize, _fontIndex, &holder->m_face );
	if ( error == FT_Err_Unknown_File_Format )
	{		
		// the font file could be opened and read, but it appears
		//that its font format is unsupported
		FT_Done_FreeType( holder->m_library );
		delete holder;
		return false;
	}
	else if ( error )
	{
		// another error code means that the font file could not
		// be opened or read, or simply that it is broken...
		FT_Done_FreeType( holder->m_library );
		delete holder;
		return false;
	}

    // Select unicode charmap 
    error = FT_Select_Charmap( holder->m_face, FT_ENCODING_UNICODE );
    if( error )
    {
		FT_Done_Face( holder->m_face );
		FT_Done_FreeType( holder->m_library );
        return false;
    }
	//set size in pixels
	error = FT_Set_Pixel_Sizes( holder->m_face, 0, _pixelHeight );  
	if( error )
    {
		FT_Done_Face( holder->m_face );
		FT_Done_FreeType( holder->m_library );
        return false;
    }

	m_font = holder;
	return true;
}

FontInfo FontManager::TrueTypeFont::getFontInfo()
{
	assert(m_font != NULL && "TrueTypeFont not initialized" );
	FTHolder* holder = (FTHolder*) m_font;
	
	assert(FT_IS_SCALABLE (holder->m_face));

	FT_Size_Metrics metrics = holder->m_face->size->metrics;

	//todo manage unscalable font
	FontInfo outFontInfo;
	outFontInfo.m_scale = 1.0f;
	outFontInfo.m_ascender = metrics.ascender /64.0f;
	outFontInfo.m_descender = metrics.descender /64.0f;
	outFontInfo.m_lineGap = (metrics.height - metrics.ascender + metrics.descender) /64.0f;
	
	outFontInfo.m_underline_position = FT_MulFix(holder->m_face->underline_position, metrics.y_scale) /64.0f;
	outFontInfo.m_underline_thickness= FT_MulFix(holder->m_face->underline_thickness,metrics.y_scale) /64.0f;
	return outFontInfo;
}

bool FontManager::TrueTypeFont::bakeGlyphAlpha(CodePoint_t _codePoint, GlyphInfo& _glyphInfo, uint8_t* _outBuffer)
{	
	assert(m_font != NULL && "TrueTypeFont not initialized" );
	FTHolder* holder = (FTHolder*) m_font;
	
	_glyphInfo.m_glyphIndex = FT_Get_Char_Index( holder->m_face, _codePoint );
	
	FT_GlyphSlot slot = holder->m_face->glyph;
	FT_Error error = FT_Load_Glyph(  holder->m_face, _glyphInfo.m_glyphIndex, FT_LOAD_DEFAULT );
	if(error) { return false; }
	
	FT_Glyph glyph;
	error = FT_Get_Glyph( slot, &glyph );
	if ( error ) { return false; }
		
	error = FT_Glyph_To_Bitmap( &glyph, FT_RENDER_MODE_NORMAL, 0, 1 );
	if(error){ return false; }
	
	FT_BitmapGlyph bitmap = (FT_BitmapGlyph)glyph;
		
	int x = bitmap->left;
	int y = -bitmap->top;
	int w = bitmap->bitmap.width;
	int h = bitmap->bitmap.rows;

	_glyphInfo.m_offset_x = (float) x;
	_glyphInfo.m_offset_y = (float) y;	
	_glyphInfo.m_width = (float) w;	
	_glyphInfo.m_height = (float) h;	
	_glyphInfo.m_advance_x = (float)slot->advance.x /64.0f;
	_glyphInfo.m_advance_y = (float)slot->advance.y /64.0f;

	int charsize = 1;
	int depth=1;
	int stride = bitmap->bitmap.pitch;
	for( int i=0; i<h; ++i )
    {
        memcpy(_outBuffer+(i*w) * charsize * depth, 
			bitmap->bitmap.buffer + (i*stride) * charsize, w * charsize * depth  );
    }
	FT_Done_Glyph(glyph);
	return true;
}

bool FontManager::TrueTypeFont::bakeGlyphSubpixel(CodePoint_t _codePoint, GlyphInfo& _glyphInfo, uint8_t* _outBuffer)
{
	assert(m_font != NULL && "TrueTypeFont not initialized" );
	FTHolder* holder = (FTHolder*) m_font;
	
	_glyphInfo.m_glyphIndex = FT_Get_Char_Index( holder->m_face, _codePoint );
	
	FT_GlyphSlot slot = holder->m_face->glyph;
	FT_Error error = FT_Load_Glyph(  holder->m_face, _glyphInfo.m_glyphIndex, FT_LOAD_DEFAULT );
	if(error) { return false; }
	
	FT_Glyph glyph;
	error = FT_Get_Glyph( slot, &glyph );
	if ( error ) { return false; }
		
	error = FT_Glyph_To_Bitmap( &glyph, FT_RENDER_MODE_LCD, 0, 1 );
	if(error){ return false; }
	
	FT_BitmapGlyph bitmap = (FT_BitmapGlyph)glyph;
	int x = bitmap->left;
	int y = -bitmap->top;
	int w = bitmap->bitmap.width;
	int h = bitmap->bitmap.rows;

	_glyphInfo.m_offset_x = (float) x;
	_glyphInfo.m_offset_y = (float) y;	
	_glyphInfo.m_width = (float) w;	
	_glyphInfo.m_height = (float) h;	
	_glyphInfo.m_advance_x = (float)slot->advance.x /64.0f;
	_glyphInfo.m_advance_y = (float)slot->advance.y /64.0f;
	int charsize = 1;
	int depth=3;
	int stride = bitmap->bitmap.pitch;
	for( int i=0; i<h; ++i )
    {
        memcpy(_outBuffer+(i*w) * charsize * depth, 
			bitmap->bitmap.buffer + (i*stride) * charsize, w * charsize * depth  );
    }
	FT_Done_Glyph(glyph);
	return true;
}

//TODO optimize: remove dynamic allocation and convert double to float
void make_distance_map( unsigned char *img, unsigned char *outImg, unsigned int width, unsigned int height )
{
    short * xdist = (short *)  malloc( width * height * sizeof(short) );
    short * ydist = (short *)  malloc( width * height * sizeof(short) );
    double * gx   = (double *) calloc( width * height, sizeof(double) );
    double * gy      = (double *) calloc( width * height, sizeof(double) );
    double * data    = (double *) calloc( width * height, sizeof(double) );
    double * outside = (double *) calloc( width * height, sizeof(double) );
    double * inside  = (double *) calloc( width * height, sizeof(double) );
    uint32_t i;

    // Convert img into double (data)
    double img_min = 255, img_max = -255;
    for( i=0; i<width*height; ++i)
    {
        double v = img[i];
        data[i] = v;
        if (v > img_max) img_max = v;
        if (v < img_min) img_min = v;
    }
    // Rescale image levels between 0 and 1
    for( i=0; i<width*height; ++i)
    {
        data[i] = (img[i]-img_min)/(img_max-img_min);
    }

    // Compute outside = edtaa3(bitmap); % Transform background (0's)
    computegradient( data, width, height, gx, gy);
    edtaa3(data, gx, gy, width, height, xdist, ydist, outside);
    for( i=0; i<width*height; ++i)
        if( outside[i] < 0 )
            outside[i] = 0.0;

    // Compute inside = edtaa3(1-bitmap); % Transform foreground (1's)
    memset(gx, 0, sizeof(double)*width*height );
    memset(gy, 0, sizeof(double)*width*height );
    for( i=0; i<width*height; ++i)
        data[i] = 1.0 - data[i];
    computegradient( data, width, height, gx, gy);
    edtaa3(data, gx, gy, width, height, xdist, ydist, inside);
    for( i=0; i<width*height; ++i)
        if( inside[i] < 0 )
            inside[i] = 0.0;

    // distmap = outside - inside; % Bipolar distance field
    unsigned char *out = outImg;//(unsigned char *) malloc( width * height * sizeof(unsigned char) );
    for( i=0; i<width*height; ++i)
    {
		//out[i] = 127 - outside[i]*8;
		//if(out[i]<0) out[i] = 0;
		//out[i] += inside[i]*16;
		//if(out[i]>255) out[i] = 255;

		outside[i] -= inside[i];
        outside[i] = 128 + outside[i]*16;

		//if(outside[i] > 8) outside[i] = 8;
		//if(inside[i] > 8) outside[i] = 8;

		//outside[i] = 128 - inside[i]*8 + outside[i]*8;
		
        if( outside[i] < 0 ) outside[i] = 0;
        if( outside[i] > 255 ) outside[i] = 255;
        out[i] = 255 - (unsigned char) outside[i];
        //out[i] = (unsigned char) outside[i];
    }

    free( xdist );
    free( ydist );
    free( gx );
    free( gy );
    free( data );
    free( outside );
    free( inside );
}


bool FontManager::TrueTypeFont::bakeGlyphDistance(CodePoint_t _codePoint, GlyphInfo& _glyphInfo, uint8_t* _outBuffer)
{	
	assert(m_font != NULL && "TrueTypeFont not initialized" );
	FTHolder* holder = (FTHolder*) m_font;
	
	_glyphInfo.m_glyphIndex = FT_Get_Char_Index( holder->m_face, _codePoint );
	
	FT_Int32 loadMode = FT_LOAD_DEFAULT|FT_LOAD_NO_HINTING;
	FT_Render_Mode renderMode = FT_RENDER_MODE_NORMAL;

	FT_GlyphSlot slot = holder->m_face->glyph;
	FT_Error error = FT_Load_Glyph(  holder->m_face, _glyphInfo.m_glyphIndex, loadMode );
	if(error) { return false; }
	
	FT_Glyph glyph;
	error = FT_Get_Glyph( slot, &glyph );
	if ( error ) { return false; }
	
	error = FT_Glyph_To_Bitmap( &glyph, renderMode, 0, 1 );
	if(error){ return false; }
	
	FT_BitmapGlyph bitmap = (FT_BitmapGlyph)glyph;
	
	int x = bitmap->left;
	int y = -bitmap->top;
	int w = bitmap->bitmap.width;
	int h = bitmap->bitmap.rows;

	_glyphInfo.m_offset_x = (float) x;
	_glyphInfo.m_offset_y = (float) y;	
	_glyphInfo.m_width = (float) w;	
	_glyphInfo.m_height = (float) h;	
	_glyphInfo.m_advance_x = (float)slot->advance.x /64.0f;
	_glyphInfo.m_advance_y = (float)slot->advance.y /64.0f;
	 
	int charsize = 1;
	int depth=1;
	int stride = bitmap->bitmap.pitch;
	
	for( int i=0; i<h; ++i )
    {	

        memcpy(_outBuffer+(i*w) * charsize * depth, 
			bitmap->bitmap.buffer + (i*stride) * charsize, w * charsize * depth  );
    }
	FT_Done_Glyph(glyph);
		
	if(w*h >0)
	{
		uint32_t dw = 6;
		uint32_t dh = 6;	
		if(dw<2) dw = 2;
		if(dh<2) dh = 2;
	
		uint32_t nw = w + dw*2;
		uint32_t nh = h + dh*2;
		assert(nw*nh < 128*128);
		uint32_t buffSize = nw*nh*sizeof(uint8_t);
	
		uint8_t * alphaImg = (uint8_t *)  malloc( buffSize );
		memset(alphaImg, 0, nw*nh*sizeof(uint8_t));

		//copy the original buffer to the temp one
		for(uint32_t  i= dh; i< nh-dh; ++i)
		{
			memcpy(alphaImg+i*nw+dw, _outBuffer+(i-dh)*w, w);
		}
	
		make_distance_map(alphaImg, _outBuffer, nw, nh);
		free(alphaImg);	
		
		_glyphInfo.m_offset_x -= (float) dw;
		_glyphInfo.m_offset_y -= (float) dh;
		_glyphInfo.m_width = (float) nw ;
		_glyphInfo.m_height = (float) nh;
	}
	
	return true;	
}



//*************************************************************

typedef stl::unordered_map<CodePoint_t, GlyphInfo> GlyphHash_t;	
// cache font data
struct FontManager::CachedFont
{
	CachedFont(){ m_trueTypeFont = NULL; m_masterFontHandle.idx = -1; }
	FontInfo m_fontInfo;
	GlyphHash_t m_cachedGlyphs;
	FontManager::TrueTypeFont* m_trueTypeFont;
	// an handle to a master font in case of sub distance field font
	FontHandle m_masterFontHandle; 
	int16_t m_padding;
};




const uint16_t MAX_OPENED_FILES = 64;
const uint16_t MAX_OPENED_FONT = 64;
const uint32_t MAX_FONT_BUFFER_SIZE = 512*512*4;

FontManager::FontManager(Atlas* _atlas):m_filesHandles(MAX_OPENED_FILES), m_fontHandles(MAX_OPENED_FONT)
{
	m_atlas = _atlas;
	m_ownAtlas = false;	
	init();	
}

FontManager::FontManager(uint32_t _textureSideWidth):m_filesHandles(MAX_OPENED_FILES), m_fontHandles(MAX_OPENED_FONT)
{
	m_atlas = new Atlas(_textureSideWidth);
	m_ownAtlas = true;	
	init();
}

void FontManager::init()
{
	m_cachedFiles = new CachedFile[MAX_OPENED_FILES];
	m_cachedFonts = new CachedFont[MAX_OPENED_FONT];
	m_buffer = new uint8_t[MAX_FONT_BUFFER_SIZE];
	
	// Create filler rectangle
	uint8_t buffer[4*4*4];
	memset( buffer, 255, 4 * 4 * 4);

	m_blackGlyph.m_width=3;
	m_blackGlyph.m_height=3;
	assert( addBitmap(m_blackGlyph, buffer) );
	//make sure the black glyph doesn't bleed
	
	/*int16_t texUnit = 65535 / m_textureWidth;
	m_blackGlyph.texture_x0 += texUnit;
	m_blackGlyph.texture_y0 += texUnit;
	m_blackGlyph.texture_x1 -= texUnit;
	m_blackGlyph.texture_y1 -= texUnit;*/
	
}

FontManager::~FontManager()
{
	assert(m_fontHandles.getNumHandles() == 0 && "All the fonts must be destroyed before destroying the manager");
	delete [] m_cachedFonts;

	assert(m_filesHandles.getNumHandles() == 0 && "All the font files must be destroyed before destroying the manager");
	delete [] m_cachedFiles;
	
	delete [] m_buffer;
	
	if(m_ownAtlas)
	{		
		delete m_atlas;
	}
}



TrueTypeHandle FontManager::loadTrueTypeFromFile(const char* _fontPath)
{
	FILE * pFile;
	pFile = fopen (_fontPath, "rb");
	if (pFile==NULL)
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
		size_t newLen = fread((void*)buffer, sizeof(char), bufsize, pFile);						
		if (newLen == 0) 
		{
			fclose(pFile);
			delete [] buffer;
			TrueTypeHandle invalid = BGFX_INVALID_HANDLE;
			return invalid;
		}
		fclose(pFile);

		uint16_t id = m_filesHandles.alloc();
		assert(id != bx::HandleAlloc::invalid);
		m_cachedFiles[id].buffer = buffer;
		m_cachedFiles[id].bufferSize = bufsize;
		TrueTypeHandle ret = {id};
		return ret;
	}
	//TODO validate font
	TrueTypeHandle invalid = BGFX_INVALID_HANDLE;
	return invalid;
}

TrueTypeHandle FontManager::loadTrueTypeFromMemory(const uint8_t* _buffer, uint32_t _size)
{	
	uint16_t id = m_filesHandles.alloc();
	assert(id != bx::HandleAlloc::invalid);
	m_cachedFiles[id].buffer = new uint8_t[_size];
	m_cachedFiles[id].bufferSize = _size;
	memcpy(m_cachedFiles[id].buffer, _buffer, _size);
	
	//TODO validate font	
	TrueTypeHandle ret = {id};
	return ret;
}

void FontManager::unloadTrueType(TrueTypeHandle _handle)
{
	assert(bgfx::invalidHandle != _handle.idx);
	delete m_cachedFiles[_handle.idx].buffer;
	m_cachedFiles[_handle.idx].bufferSize = 0;
	m_cachedFiles[_handle.idx].buffer = NULL;
	m_filesHandles.free(_handle.idx);
}

FontHandle FontManager::createFontByPixelSize(TrueTypeHandle _tt_handle, uint32_t _typefaceIndex, uint32_t _pixelSize, FontType _fontType)
{
	assert(bgfx::invalidHandle != _tt_handle.idx);

	TrueTypeFont* ttf = new TrueTypeFont();
	if(!ttf->init(  m_cachedFiles[_tt_handle.idx].buffer,  m_cachedFiles[_tt_handle.idx].bufferSize, _typefaceIndex, _pixelSize))
	{
		delete ttf;
		FontHandle invalid = BGFX_INVALID_HANDLE;
		return invalid;
	}
	
	uint16_t fontIdx = m_fontHandles.alloc();
	assert(fontIdx != bx::HandleAlloc::invalid);	
	
	m_cachedFonts[fontIdx].m_trueTypeFont = ttf;
	m_cachedFonts[fontIdx].m_fontInfo = ttf->getFontInfo();
	m_cachedFonts[fontIdx].m_fontInfo.m_fontType = _fontType;	
	m_cachedFonts[fontIdx].m_fontInfo.m_pixelSize = _pixelSize;
	m_cachedFonts[fontIdx].m_cachedGlyphs.clear();
	m_cachedFonts[fontIdx].m_masterFontHandle.idx = -1;
	FontHandle ret = {fontIdx};
	return ret;
}

FontHandle FontManager::createScaledFontToPixelSize(FontHandle _baseFontHandle, uint32_t _pixelSize)
{
	assert(bgfx::invalidHandle != _baseFontHandle.idx);
	CachedFont& font = m_cachedFonts[_baseFontHandle.idx];
	FontInfo& fontInfo = font.m_fontInfo;

	FontInfo newFontInfo = fontInfo;
	newFontInfo.m_pixelSize = _pixelSize;
	newFontInfo.m_scale = (float)_pixelSize / (float) fontInfo.m_pixelSize;
	newFontInfo.m_ascender = (newFontInfo.m_ascender * newFontInfo.m_scale);
	newFontInfo.m_descender = (newFontInfo.m_descender * newFontInfo.m_scale);
	newFontInfo.m_lineGap = (newFontInfo.m_lineGap * newFontInfo.m_scale);
	newFontInfo.m_underline_thickness = (newFontInfo.m_underline_thickness * newFontInfo.m_scale);
	newFontInfo.m_underline_position = (newFontInfo.m_underline_position * newFontInfo.m_scale);


	uint16_t fontIdx = m_fontHandles.alloc();
	assert(fontIdx != bx::HandleAlloc::invalid);
	m_cachedFonts[fontIdx].m_cachedGlyphs.clear();
	m_cachedFonts[fontIdx].m_fontInfo = newFontInfo;
	m_cachedFonts[fontIdx].m_trueTypeFont = NULL;
	m_cachedFonts[fontIdx].m_masterFontHandle = _baseFontHandle;
	FontHandle ret = {fontIdx};
	return ret;
}

FontHandle FontManager::loadBakedFontFromFile(const char* /*fontPath*/,  const char* /*descriptorPath*/)
{
	assert(false); //TODO implement
	FontHandle invalid = BGFX_INVALID_HANDLE;
	return invalid;
}

FontHandle FontManager::loadBakedFontFromMemory(const uint8_t* /*imageBuffer*/, uint32_t /*imageSize*/, const uint8_t* /*descriptorBuffer*/, uint32_t /*descriptorSize*/)
{
	assert(false); //TODO implement
	FontHandle invalid = BGFX_INVALID_HANDLE;
	return invalid;
}

void FontManager::destroyFont(FontHandle _handle)
{
	assert(bgfx::invalidHandle != _handle.idx);

	if(m_cachedFonts[_handle.idx].m_trueTypeFont != NULL)
	{
		delete m_cachedFonts[_handle.idx].m_trueTypeFont;
		m_cachedFonts[_handle.idx].m_trueTypeFont = NULL;
	}
	m_cachedFonts[_handle.idx].m_cachedGlyphs.clear();	
	m_fontHandles.free(_handle.idx);
}

bool FontManager::preloadGlyph(FontHandle _handle, const wchar_t* _string)
{
	assert(bgfx::invalidHandle != _handle.idx);
	CachedFont& font = m_cachedFonts[_handle.idx];

	//if truetype present
	if(font.m_trueTypeFont != NULL)
	{	
		//parse string
		for( size_t i=0, end = wcslen(_string) ; i < end; ++i )
		{
			//if glyph cached, continue
			CodePoint_t codePoint = _string[i];
			if(!preloadGlyph(_handle, codePoint))
			{
				return false;
			}
		}
		return true;
	}

	return false;
}

bool FontManager::preloadGlyph(FontHandle _handle, CodePoint_t _codePoint)
{
	assert(bgfx::invalidHandle != _handle.idx);
	CachedFont& font = m_cachedFonts[_handle.idx];
	FontInfo& fontInfo = font.m_fontInfo;
	//check if glyph not already present
	GlyphHash_t::iterator iter = font.m_cachedGlyphs.find(_codePoint);
	if(iter != font.m_cachedGlyphs.end())
	{
		return true;
	}

	//if truetype present
	if(font.m_trueTypeFont != NULL)
	{
		GlyphInfo glyphInfo;
		
		//bake glyph as bitmap to buffer
		switch(font.m_fontInfo.m_fontType)
		{
		case FONT_TYPE_ALPHA:
			font.m_trueTypeFont->bakeGlyphAlpha(_codePoint, glyphInfo, m_buffer);
			break;
		//case FONT_TYPE_LCD:
			//font.m_trueTypeFont->bakeGlyphSubpixel(codePoint, glyphInfo, m_buffer);
			//break;
		case FONT_TYPE_DISTANCE:
			font.m_trueTypeFont->bakeGlyphDistance(_codePoint, glyphInfo, m_buffer);
			break;
		case FONT_TYPE_DISTANCE_SUBPIXEL:
			font.m_trueTypeFont->bakeGlyphDistance(_codePoint, glyphInfo, m_buffer);
			break;
		default:
			assert(false && "TextureType not supported yet");
		};

		//copy bitmap to texture
		if(!addBitmap(glyphInfo, m_buffer) )
		{
			return false;
		}

		glyphInfo.m_advance_x = (glyphInfo.m_advance_x * fontInfo.m_scale);
		glyphInfo.m_advance_y = (glyphInfo.m_advance_y * fontInfo.m_scale);
		glyphInfo.m_offset_x = (glyphInfo.m_offset_x * fontInfo.m_scale);
		glyphInfo.m_offset_y = (glyphInfo.m_offset_y * fontInfo.m_scale);
		glyphInfo.m_height = (glyphInfo.m_height * fontInfo.m_scale);
		glyphInfo.m_width =  (glyphInfo.m_width * fontInfo.m_scale);

		// store cached glyph
		font.m_cachedGlyphs[_codePoint] = glyphInfo;
		return true;
	}else
	{
		//retrieve glyph from parent font if any
		if(font.m_masterFontHandle.idx != bgfx::invalidHandle)
		{
			if(preloadGlyph(font.m_masterFontHandle, _codePoint))
			{
				GlyphInfo glyphInfo;
				getGlyphInfo(font.m_masterFontHandle, _codePoint, glyphInfo);

				glyphInfo.m_advance_x = (glyphInfo.m_advance_x * fontInfo.m_scale);
				glyphInfo.m_advance_y = (glyphInfo.m_advance_y * fontInfo.m_scale);
				glyphInfo.m_offset_x = (glyphInfo.m_offset_x * fontInfo.m_scale);
				glyphInfo.m_offset_y = (glyphInfo.m_offset_y * fontInfo.m_scale);
				glyphInfo.m_height = (glyphInfo.m_height * fontInfo.m_scale);
				glyphInfo.m_width = (glyphInfo.m_width * fontInfo.m_scale);

				// store cached glyph
				font.m_cachedGlyphs[_codePoint] = glyphInfo;
				return true;
			}
		}
	}

	return false;
}

const FontInfo& FontManager::getFontInfo(FontHandle _handle)
{ 
	assert(_handle.idx != bgfx::invalidHandle);
	return m_cachedFonts[_handle.idx].m_fontInfo;
}

bool FontManager::getGlyphInfo(FontHandle _handle, CodePoint_t _codePoint, GlyphInfo& _outInfo)
{	
	GlyphHash_t::iterator iter = m_cachedFonts[_handle.idx].m_cachedGlyphs.find(_codePoint);
	if(iter == m_cachedFonts[_handle.idx].m_cachedGlyphs.end())
	{
		if(preloadGlyph(_handle, _codePoint))
		{
			iter = m_cachedFonts[_handle.idx].m_cachedGlyphs.find(_codePoint);
		}else
		{
			return false;
		}
	}
	_outInfo = iter->second;
	return true;
}

// ****************************************************************************


bool FontManager::addBitmap(GlyphInfo& _glyphInfo, const uint8_t* _data)
{
	_glyphInfo.m_regionIndex = m_atlas->addRegion((uint16_t) ceil(_glyphInfo.m_width),(uint16_t) ceil(_glyphInfo.m_height), _data, AtlasRegion::TYPE_GRAY);
	return true;
}
