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


#define BGFX_FONT_ASSERT(cond, message) assert((cond) && (message));

namespace bgfx_font
{

class FontManager::TrueTypeFont
{
public:	
	TrueTypeFont();
	~TrueTypeFont();

	/// Initialize from  an external buffer
	/// @remark The ownership of the buffer is external, and you must ensure it stays valid up to this object lifetime
	/// @return true if the initialization succeed
    bool init(const uint8_t* buffer, uint32_t bufferSize, int32_t fontIndex, uint32_t pixelHeight );
	
	/// return the font descriptor of the current font
	FontInfo getFontInfo();
	
	/// raster a glyph as 8bit alpha to a memory buffer
	/// update the GlyphInfo according to the raster strategy
	/// @ remark buffer min size: glyphInfo.width * glyphInfo * height * sizeof(char)
    bool bakeGlyphAlpha(CodePoint_t codePoint, GlyphInfo& outGlyphInfo, uint8_t* outBuffer);

	/// raster a glyph as 32bit subpixel rgba to a memory buffer
	/// update the GlyphInfo according to the raster strategy
	/// @ remark buffer min size: glyphInfo.width * glyphInfo * height * sizeof(uint32_t)
    bool bakeGlyphSubpixel(CodePoint_t codePoint, GlyphInfo& outGlyphInfo, uint8_t* outBuffer);

	/// raster a glyph as 8bit signed distance to a memory buffer
	/// update the GlyphInfo according to the raster strategy
	/// @ remark buffer min size: glyphInfo.width * glyphInfo * height * sizeof(char)
	bool bakeGlyphDistance(CodePoint_t codePoint, GlyphInfo& outGlyphInfo, uint8_t* outBuffer);
private:
	void* m_font;
};


struct FTHolder
{
	FT_Library library;
	FT_Face face;
};
FontManager::TrueTypeFont::TrueTypeFont(): m_font(NULL)
{	
}

FontManager::TrueTypeFont::~TrueTypeFont()
{
	if(m_font!=NULL)
	{
		FTHolder* holder = (FTHolder*) m_font;
		FT_Done_Face( holder->face );
        FT_Done_FreeType( holder->library );
		delete m_font;
		m_font = NULL;
	}
}

bool FontManager::TrueTypeFont::init(const uint8_t* buffer, uint32_t bufferSize, int32_t fontIndex, uint32_t pixelHeight)
{
	assert((bufferSize > 256 && bufferSize < 100000000) && "TrueType buffer size is suspicious");
	assert((pixelHeight > 4 && pixelHeight < 128) && "TrueType buffer size is suspicious");
	
	assert(m_font == NULL && "TrueTypeFont already initialized" );
	
	FTHolder* holder = new FTHolder();	

	// Initialize Freetype library
	FT_Error error = FT_Init_FreeType( &holder->library );
	if( error)
	{
		delete holder;
		return false;
	}

	error = FT_New_Memory_Face( holder->library, buffer, bufferSize, fontIndex, &holder->face );
	if ( error == FT_Err_Unknown_File_Format )
	{		
		// the font file could be opened and read, but it appears
		//that its font format is unsupported
		FT_Done_FreeType( holder->library );
		delete holder;
		return false;
	}
	else if ( error )
	{
		// another error code means that the font file could not
		// be opened or read, or simply that it is broken...
		FT_Done_FreeType( holder->library );
		delete holder;
		return false;
	}

    // Select unicode charmap 
    error = FT_Select_Charmap( holder->face, FT_ENCODING_UNICODE );
    if( error )
    {
		FT_Done_Face( holder->face );
		FT_Done_FreeType( holder->library );
        return false;
    }
	//set size in pixels
	error = FT_Set_Pixel_Sizes( holder->face, 0, pixelHeight );  
	if( error )
    {
		FT_Done_Face( holder->face );
		FT_Done_FreeType( holder->library );
        return false;
    }

	m_font = holder;
	return true;
}

FontInfo FontManager::TrueTypeFont::getFontInfo()
{
	assert(m_font != NULL && "TrueTypeFont not initialized" );
	FTHolder* holder = (FTHolder*) m_font;
	
	assert(FT_IS_SCALABLE (holder->face));

	FT_Size_Metrics metrics = holder->face->size->metrics;

	//todo manage unscalable font
	FontInfo outFontInfo;
	outFontInfo.scale = 1.0f;
	outFontInfo.ascender = metrics.ascender /64.0f;
	outFontInfo.descender = metrics.descender /64.0f;
	outFontInfo.lineGap = (metrics.height - metrics.ascender + metrics.descender) /64.0f;
	
	outFontInfo.underline_position = FT_MulFix(holder->face->underline_position, metrics.y_scale) /64.0f;
	outFontInfo.underline_thickness= FT_MulFix(holder->face->underline_thickness,metrics.y_scale) /64.0f;
	return outFontInfo;
}

bool FontManager::TrueTypeFont::bakeGlyphAlpha(CodePoint_t codePoint, GlyphInfo& glyphInfo, uint8_t* outBuffer)
{	
	assert(m_font != NULL && "TrueTypeFont not initialized" );
	FTHolder* holder = (FTHolder*) m_font;
	
	glyphInfo.glyphIndex = FT_Get_Char_Index( holder->face, codePoint );
	
	FT_GlyphSlot slot = holder->face->glyph;
	FT_Error error = FT_Load_Glyph(  holder->face, glyphInfo.glyphIndex, FT_LOAD_DEFAULT );
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

	glyphInfo.offset_x = (float) x;
	glyphInfo.offset_y = (float) y;	
	glyphInfo.width = (float) w;	
	glyphInfo.height = (float) h;	
	glyphInfo.advance_x = (float)slot->advance.x /64.0f;
	glyphInfo.advance_y = (float)slot->advance.y /64.0f;

	int charsize = 1;
	int depth=1;
	int stride = bitmap->bitmap.pitch;
	for( int i=0; i<h; ++i )
    {
        memcpy(outBuffer+(i*w) * charsize * depth, 
			bitmap->bitmap.buffer + (i*stride) * charsize, w * charsize * depth  );
    }
	FT_Done_Glyph(glyph);
	return true;
}

bool FontManager::TrueTypeFont::bakeGlyphSubpixel(CodePoint_t codePoint, GlyphInfo& glyphInfo, uint8_t* outBuffer)
{
	assert(m_font != NULL && "TrueTypeFont not initialized" );
	FTHolder* holder = (FTHolder*) m_font;
	
	glyphInfo.glyphIndex = FT_Get_Char_Index( holder->face, codePoint );
	
	FT_GlyphSlot slot = holder->face->glyph;
	FT_Error error = FT_Load_Glyph(  holder->face, glyphInfo.glyphIndex, FT_LOAD_DEFAULT );
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

	glyphInfo.offset_x = (float) x;
	glyphInfo.offset_y = (float) y;	
	glyphInfo.width = (float) w;	
	glyphInfo.height = (float) h;	
	glyphInfo.advance_x = (float)slot->advance.x /64.0f;
	glyphInfo.advance_y = (float)slot->advance.y /64.0f;
	int charsize = 1;
	int depth=3;
	int stride = bitmap->bitmap.pitch;
	for( int i=0; i<h; ++i )
    {
        memcpy(outBuffer+(i*w) * charsize * depth, 
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


bool FontManager::TrueTypeFont::bakeGlyphDistance(CodePoint_t codePoint, GlyphInfo& glyphInfo, uint8_t* outBuffer)
{	
	assert(m_font != NULL && "TrueTypeFont not initialized" );
	FTHolder* holder = (FTHolder*) m_font;
	
	glyphInfo.glyphIndex = FT_Get_Char_Index( holder->face, codePoint );
	
	FT_Int32 loadMode = FT_LOAD_DEFAULT|FT_LOAD_NO_HINTING;
	FT_Render_Mode renderMode = FT_RENDER_MODE_NORMAL;

	FT_GlyphSlot slot = holder->face->glyph;
	FT_Error error = FT_Load_Glyph(  holder->face, glyphInfo.glyphIndex, loadMode );
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

	glyphInfo.offset_x = (float) x;
	glyphInfo.offset_y = (float) y;	
	glyphInfo.width = (float) w;	
	glyphInfo.height = (float) h;	
	glyphInfo.advance_x = (float)slot->advance.x /64.0f;
	glyphInfo.advance_y = (float)slot->advance.y /64.0f;
	 
	int charsize = 1;
	int depth=1;
	int stride = bitmap->bitmap.pitch;
	
	for( int i=0; i<h; ++i )
    {	

        memcpy(outBuffer+(i*w) * charsize * depth, 
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
			memcpy(alphaImg+i*nw+dw, outBuffer+(i-dh)*w, w);
		}
	
		make_distance_map(alphaImg, outBuffer, nw, nh);
		free(alphaImg);	
		
		glyphInfo.offset_x -= (float) dw;
		glyphInfo.offset_y -= (float) dh;
		glyphInfo.width = (float) nw ;
		glyphInfo.height = (float) nh;
	}
	
	return true;	
}



//*************************************************************

typedef stl::unordered_map<CodePoint_t, GlyphInfo> GlyphHash_t;	
// cache font data
struct FontManager::CachedFont
{
	CachedFont(){ trueTypeFont = NULL; masterFontHandle.idx = -1; }
	FontInfo fontInfo;
	GlyphHash_t cachedGlyphs;
	FontManager::TrueTypeFont* trueTypeFont;
	// an handle to a master font in case of sub distance field font
	FontHandle masterFontHandle; 
	int16_t __padding__;
};




const uint16_t MAX_OPENED_FILES = 64;
const uint16_t MAX_OPENED_FONT = 64;
const uint32_t MAX_FONT_BUFFER_SIZE = 512*512*4;

FontManager::FontManager(bgfx::Atlas* atlas):m_filesHandles(MAX_OPENED_FILES), m_fontHandles(MAX_OPENED_FONT)
{
	m_atlas = atlas;
	m_ownAtlas = false;	
	init();	
}

FontManager::FontManager(uint32_t textureSideWidth):m_filesHandles(MAX_OPENED_FILES), m_fontHandles(MAX_OPENED_FONT)
{
	m_atlas = new bgfx::Atlas(textureSideWidth);
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

	m_blackGlyph.width=3;
	m_blackGlyph.height=3;
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



TrueTypeHandle FontManager::loadTrueTypeFromFile(const char* fontPath)
{
	FILE * pFile;
	pFile = fopen (fontPath, "rb");
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

TrueTypeHandle FontManager::loadTrueTypeFromMemory(const uint8_t* buffer, uint32_t size)
{	
	uint16_t id = m_filesHandles.alloc();
	assert(id != bx::HandleAlloc::invalid);
	m_cachedFiles[id].buffer = new uint8_t[size];
	m_cachedFiles[id].bufferSize = size;
	memcpy(m_cachedFiles[id].buffer, buffer, size);
	
	//TODO validate font	
	TrueTypeHandle ret = {id};
	return ret;
}

void FontManager::unloadTrueType(TrueTypeHandle handle)
{
	assert(bgfx::invalidHandle != handle.idx);
	delete m_cachedFiles[handle.idx].buffer;
	m_cachedFiles[handle.idx].bufferSize = 0;
	m_cachedFiles[handle.idx].buffer = NULL;
	m_filesHandles.free(handle.idx);
}

FontHandle FontManager::createFontByPixelSize(TrueTypeHandle handle, uint32_t typefaceIndex, uint32_t pixelSize, FontType fontType)
{
	assert(bgfx::invalidHandle != handle.idx);

	TrueTypeFont* ttf = new TrueTypeFont();
	if(!ttf->init(  m_cachedFiles[handle.idx].buffer,  m_cachedFiles[handle.idx].bufferSize, typefaceIndex, pixelSize))
	{
		delete ttf;
		FontHandle invalid = BGFX_INVALID_HANDLE;
		return invalid;
	}
	
	uint16_t fontIdx = m_fontHandles.alloc();
	assert(fontIdx != bx::HandleAlloc::invalid);	
	
	m_cachedFonts[fontIdx].trueTypeFont = ttf;
	m_cachedFonts[fontIdx].fontInfo = ttf->getFontInfo();
	m_cachedFonts[fontIdx].fontInfo.fontType = fontType;	
	m_cachedFonts[fontIdx].fontInfo.pixelSize = pixelSize;
	m_cachedFonts[fontIdx].cachedGlyphs.clear();
	m_cachedFonts[fontIdx].masterFontHandle.idx = -1;
	FontHandle ret = {fontIdx};
	return ret;
}

FontHandle FontManager::createScaledFontToPixelSize(FontHandle _baseFontHandle, uint32_t _pixelSize)
{
	assert(bgfx::invalidHandle != _baseFontHandle.idx);
	CachedFont& font = m_cachedFonts[_baseFontHandle.idx];
	FontInfo& fontInfo = font.fontInfo;

	FontInfo newFontInfo = fontInfo;
	newFontInfo.pixelSize = _pixelSize;
	newFontInfo.scale = (float)_pixelSize / (float) fontInfo.pixelSize;
	newFontInfo.ascender = (newFontInfo.ascender * newFontInfo.scale);
	newFontInfo.descender = (newFontInfo.descender * newFontInfo.scale);
	newFontInfo.lineGap = (newFontInfo.lineGap * newFontInfo.scale);
	newFontInfo.underline_thickness = (newFontInfo.underline_thickness * newFontInfo.scale);
	newFontInfo.underline_position = (newFontInfo.underline_position * newFontInfo.scale);


	uint16_t fontIdx = m_fontHandles.alloc();
	assert(fontIdx != bx::HandleAlloc::invalid);
	m_cachedFonts[fontIdx].cachedGlyphs.clear();
	m_cachedFonts[fontIdx].fontInfo = newFontInfo;
	m_cachedFonts[fontIdx].trueTypeFont = NULL;
	m_cachedFonts[fontIdx].masterFontHandle = _baseFontHandle;
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

	if(m_cachedFonts[_handle.idx].trueTypeFont != NULL)
	{
		delete m_cachedFonts[_handle.idx].trueTypeFont;
		m_cachedFonts[_handle.idx].trueTypeFont = NULL;
	}
	m_cachedFonts[_handle.idx].cachedGlyphs.clear();	
	m_fontHandles.free(_handle.idx);
}

bool FontManager::preloadGlyph(FontHandle handle, const wchar_t* _string)
{
	assert(bgfx::invalidHandle != handle.idx);
	CachedFont& font = m_cachedFonts[handle.idx];

	//if truetype present
	if(font.trueTypeFont != NULL)
	{	
		//parse string
		for( size_t i=0, end = wcslen(_string) ; i < end; ++i )
		{
			//if glyph cached, continue
			CodePoint_t codePoint = _string[i];
			if(!preloadGlyph(handle, codePoint))
			{
				return false;
			}
		}
		return true;
	}

	return false;
}

bool FontManager::preloadGlyph(FontHandle handle, CodePoint_t codePoint)
{
	assert(bgfx::invalidHandle != handle.idx);
	CachedFont& font = m_cachedFonts[handle.idx];
	FontInfo& fontInfo = font.fontInfo;
	//check if glyph not already present
	GlyphHash_t::iterator iter = font.cachedGlyphs.find(codePoint);
	if(iter != font.cachedGlyphs.end())
	{
		return true;
	}

	//if truetype present
	if(font.trueTypeFont != NULL)
	{
		GlyphInfo glyphInfo;
		
		//bake glyph as bitmap to buffer
		switch(font.fontInfo.fontType)
		{
		case FONT_TYPE_ALPHA:
			font.trueTypeFont->bakeGlyphAlpha(codePoint, glyphInfo, m_buffer);
			break;
		//case FONT_TYPE_LCD:
			//font.trueTypeFont->bakeGlyphSubpixel(codePoint, glyphInfo, m_buffer);
			//break;
		case FONT_TYPE_DISTANCE:
			font.trueTypeFont->bakeGlyphDistance(codePoint, glyphInfo, m_buffer);
			break;
		case FONT_TYPE_DISTANCE_SUBPIXEL:
			font.trueTypeFont->bakeGlyphDistance(codePoint, glyphInfo, m_buffer);
			break;
		default:
			assert(false && "TextureType not supported yet");
		};

		//copy bitmap to texture
		if(!addBitmap(glyphInfo, m_buffer) )
		{
			return false;
		}

		glyphInfo.advance_x = (glyphInfo.advance_x * fontInfo.scale);
		glyphInfo.advance_y = (glyphInfo.advance_y * fontInfo.scale);
		glyphInfo.offset_x = (glyphInfo.offset_x * fontInfo.scale);
		glyphInfo.offset_y = (glyphInfo.offset_y * fontInfo.scale);
		glyphInfo.height = (glyphInfo.height * fontInfo.scale);
		glyphInfo.width =  (glyphInfo.width * fontInfo.scale);

		// store cached glyph
		font.cachedGlyphs[codePoint] = glyphInfo;
		return true;
	}else
	{
		//retrieve glyph from parent font if any
		if(font.masterFontHandle.idx != bgfx::invalidHandle)
		{
			if(preloadGlyph(font.masterFontHandle, codePoint))
			{
				GlyphInfo glyphInfo;
				getGlyphInfo(font.masterFontHandle, codePoint, glyphInfo);

				glyphInfo.advance_x = (glyphInfo.advance_x * fontInfo.scale);
				glyphInfo.advance_y = (glyphInfo.advance_y * fontInfo.scale);
				glyphInfo.offset_x = (glyphInfo.offset_x * fontInfo.scale);
				glyphInfo.offset_y = (glyphInfo.offset_y * fontInfo.scale);
				glyphInfo.height = (glyphInfo.height * fontInfo.scale);
				glyphInfo.width = (glyphInfo.width * fontInfo.scale);

				// store cached glyph
				font.cachedGlyphs[codePoint] = glyphInfo;
				return true;
			}
		}
	}

	return false;
}

const FontInfo& FontManager::getFontInfo(FontHandle handle)
{ 
	assert(handle.idx != bgfx::invalidHandle);
	return m_cachedFonts[handle.idx].fontInfo;
}

bool FontManager::getGlyphInfo(FontHandle fontHandle, CodePoint_t codePoint, GlyphInfo& outInfo)
{	
	GlyphHash_t::iterator iter = m_cachedFonts[fontHandle.idx].cachedGlyphs.find(codePoint);
	if(iter == m_cachedFonts[fontHandle.idx].cachedGlyphs.end())
	{
		if(preloadGlyph(fontHandle, codePoint))
		{
			iter = m_cachedFonts[fontHandle.idx].cachedGlyphs.find(codePoint);
		}else
		{
			return false;
		}
	}
	outInfo = iter->second;
	return true;
}

// ****************************************************************************


bool FontManager::addBitmap(GlyphInfo& glyphInfo, const uint8_t* data)
{
	glyphInfo.regionIndex = m_atlas->addRegion((uint16_t) ceil(glyphInfo.width),(uint16_t) ceil(glyphInfo.height), data, bgfx::AtlasRegion::TYPE_GRAY);
	return true;
}





}
