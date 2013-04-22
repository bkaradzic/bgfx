/* Copyright 2013 Jeremie Roy. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
*/
#pragma once
#include "font_manager.h"

namespace bgfx_font
{

BGFX_HANDLE(TextBufferHandle);
	
/// type of vertex and index buffer to use with a TextBuffer
enum BufferType
{
	STATIC,
	DYNAMIC ,
	TRANSIENT
};

/// special style effect (can be combined)
enum TextStyleFlags
{
	STYLE_NORMAL           = 0,
	STYLE_OVERLINE         = 1,
	STYLE_UNDERLINE        = 1<<1,
	STYLE_STRIKE_THROUGH   = 1<<2,
	STYLE_BACKGROUND       = 1<<3,
};

class TextBuffer;
class TextBufferManager
{
public:
	TextBufferManager(FontManager* fontManager = NULL);
	~TextBufferManager();
	
	void init(const char* shaderPath);

	TextBufferHandle createTextBuffer(FontType type, BufferType bufferType);
	void destroyTextBuffer(TextBufferHandle handle);
	void submitTextBuffer(TextBufferHandle handle, uint8_t id, int32_t depth = 0);
	void submitTextBufferMask(TextBufferHandle handle, uint32_t viewMask, int32_t depth = 0);
	
	void setStyle(TextBufferHandle handle, uint32_t flags = STYLE_NORMAL);
	void setTextColor(TextBufferHandle handle, uint32_t rgba = 0x000000FF);
	void setBackgroundColor(TextBufferHandle handle, uint32_t rgba = 0x000000FF);

	void setOverlineColor(TextBufferHandle handle, uint32_t rgba = 0x000000FF);
	void setUnderlineColor(TextBufferHandle handle, uint32_t rgba = 0x000000FF);
	void setStrikeThroughColor(TextBufferHandle handle, uint32_t rgba = 0x000000FF);
	
	void setPenPosition(TextBufferHandle handle, float x, float y);

	/// append an ASCII/utf-8 string to the buffer using current pen position and color
	void appendText(TextBufferHandle _handle, FontHandle fontHandle, const char * _string);

	/// append a wide char unicode string to the buffer using current pen position and color
	void appendText(TextBufferHandle _handle, FontHandle fontHandle, const wchar_t * _string);	

	/// Clear the text buffer and reset its state (pen/color)
	void clearTextBuffer(TextBufferHandle _handle);
		
	/// return the size of the text 
	//Rectangle measureText(FontHandle fontHandle, const char * _string);
	//Rectangle measureText(FontHandle fontHandle, const wchar_t * _string);

private:
	
	struct BufferCache
	{
		uint16_t indexBufferHandle;
		uint16_t vertexBufferHandle;
		TextBuffer* textBuffer;
		BufferType bufferType;
		FontType fontType;		
	};

	BufferCache* m_textBuffers;
	bx::HandleAlloc m_textBufferHandles;
	FontManager* m_fontManager;
	bgfx::VertexDecl m_vertexDecl;
	bgfx::UniformHandle m_u_texColor;
	bgfx::UniformHandle m_u_inverse_gamma;
	//shaders program
	bgfx::ProgramHandle m_basicProgram;
	bgfx::ProgramHandle m_distanceProgram;
	bgfx::ProgramHandle m_distanceSubpixelProgram;
};

}
